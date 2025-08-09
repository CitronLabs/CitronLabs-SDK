#pragma once
#define __EBEE_SRC_DEF__
#include "../../include/ebee-data.h"

Type(EBSource_Data,
	inst(TimeShort) time_lastmodified;
);

errvt getSourcesFromDir(List(EBEE_SOURCE) result, inst(String) srcdir_path, Stack(fsPath) nested_dirs, inst(String) file_extention){

	inst(Dir) srcdir = NULL;


	if((srcdir = push(Dir, srcdir_path->txt, 0)) == NULL){
		ERR(BUILDERR_SOURCE, "could not find source dir");
	}

	DirForEach(srcdir, 10){
		if(ent.is_dir){
			fsPath source_dir_path;
			catNameandDirPath(source_dir_path, srcdir_path->txt, ent.name);
			Stack.Push(nested_dirs, &source_dir_path, 1);
		}else {
		if(file_extention->txt != NULL &&
		   EB.utils.checkExtension(
			ent.name,
			file_extention)
	  	){
			fsPath source_file_path = {0};
			catNameandDirPath(source_file_path, srcdir_path->txt, ent.name);
			
			EB.source.add(new(EB_Source, source_file_path));
		}
		}
	}

	pop(srcdir);

return OK;
}

errvt eb_source_addDir(List(EBEE_SOURCE) result, inst(String) path, inst(String) file_extention, bool recursive){
	nonull(result,    return nullerr);
	nonull(path->txt, return nullerr);

	Stack(fsPath) nested_dirs = pushStack(dirpath);
	
	getSourcesFromDir(result, path, nested_dirs, file_extention);
	
	if(recursive){
		while(Stack.Count(nested_dirs) != 0){
			fsPath path;
			Stack.Pop(nested_dirs, path, 1);
			getSourcesFromDir(result, pathtostr(path), nested_dirs, file_extention);
		}
	}
	pop(nested_dirs);

return OK;
}

errvt eb_source_add(inst(EB_Source) src){

	nonull(src, return nullerr);

	fsEntry ent = {0};

	inst(Struct) src_data;
	if((src_data = EB.store.cacheSearch(COMPILE_CACHE, src->path)) != NULL){
		
		fsEntry source_ent;
			
		if(getFileSystemEntry(src->path->txt, &source_ent))
			EB.store.cacheRemove(COMPILE_CACHE, src->path);

		inst(DSN_data) mod_nsec = Struct.SearchField(src_data, s("mod_nsec"));
		inst(DSN_data) mod_sec  = Struct.SearchField(src_data, s("mod_sec"));

		if(mod_nsec->type != DSN_NUMBER || mod_sec->type != DSN_NUMBER)
		 	ERR(BUILDERR_TARGETS, "invalid cache format");
		else{
			inst(Time) time_lastmodified = push(Time, 
				       .seconds = mod_sec->asNumber->as_u64,
				       .nanosec = mod_nsec->asNumber->as_u64
			);

	 		if(Time.Compare(time_lastmodified, ent.time_modified, NULL)){
				List.Append(result, 
				  &(EBEE_SOURCE){
					.requires_build = false,
				  	.output_name = data.output_path,
				  	.src_path = path
				  });
				return NOERROR;
			}else{
				eb_cache_remove(COMPILE_CACHE, path);
			}
		}
	}
	
	if(ent.name[0] == '\0')
		checkreturnerr(getFileSystemEntry(path.txt, &ent), 
		 	BUILDERR_SOURCE, "could not find source");
	       

	checkreturnerr(ent.is_dir, 
		BUILDERR_SOURCE, "source files cannot be directories",
	)
	
	EBEE_SOURCE source_file = {0};

	listAppend(result, &(EBEE_SOURCE){
			.requires_build = true,
			.src_path = path
		});

	_del(output_name);	

return NOERROR;
}

errvt eb_source_build(List(EBEE_SOURCE) sources, errvt fn(build_routine, inst(EB_Source),void*), void* args){

	dirSetCurrent("/build_files/out_files");
	
	listForEach(sources, EBEE_SOURCE, src){
		
		if(!src.requires_build) continue;

		fsEntry source_file = {0};	
	
		if(getFileSystemEntry(src.output_name.txt, &source_file))
			println(RED  "[Compilation Failed] :: "NC, $(src.src_path));
		else{
			println(GREEN"[Compilation Done] ::"NC, $(src.src_path));
		

			eb_cache_load(COMPILE_CACHE, src.src_path, 
	 			dataStructCreate(true, NULL, 
					$(src.output_name),
	      				$(source_file.time_modified)
				)
	 		);
		}
	}


	dirSetCurrent((char*)__eb_settings.BUILD_DIR);

return NOERROR;
}

construct(EB_Source){
	if(!args.path || !args.build_routine) return NULL;
	self->path = newString(args.path, 255);
	self->build_routine = args.build_routine;
	self->requires_build = true;
	self->args = NULL;
return self;
};
