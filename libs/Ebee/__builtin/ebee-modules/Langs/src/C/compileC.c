#pragma once
#define __LANGS_SRC_DEF__
#include "./CBuild.h"


errvt methodimpl(CBuild, addSrcDirs,,bool recursive, List(String) srcdirs){
	nonull(self);
	nonull(srcdirs);

	List(EB_Source) result = 
		EB.utils.addSourceDirs(srcdirs, s(".c"), recursive);
	
	if(result == NULL){
		pop(srcdirs);
		return ERR(COMPILEERR_SOURCES, "could not get sources from source dirs")
	}

	List.Merge(self->srcfiles, result, UINT64_MAX);

	del(result);
	pop(srcdirs);
return OK;
}

errvt imethodimpl(CBuild, Free){
	self(CBuild)

	del(self->srcfiles);
	del(self->includes);
	del(self->libs);
	del(self->cc);
return OK;
}

typedef struct{
	inst(String) cc;
	inst(String) args;
}C_Source_Args;


errvt C_Source_Build(EB_Source src, void* build_args){

	inst(String) cc = ((C_Source_Args*)build_args)->cc;
	inst(String) args = ((C_Source_Args*)build_args)->args;
	inst(StringBuilder) compile_command = push(StringBuilder); 
	inst(String) command = &(String_Instance){0};
	inst(String) output_name = EB.utils.makeUniqueName(src.path);

	StringBuilder.Set(compile_command,
		$(cc)," ",
		$(args)," -c ",
		$(src.path)," -o ",
		$(output_name),
		endstr);
	
	*command = StringBuilder.GetStr(compile_command);

	if(EB.getFlag(EBFL_VERBOSE)){
		println(LIGHTPURPLE "--Compiling Source :: " WHITE, $(src.path), "\n",
			"Command :: {\n\t", 
				$(command), 
			"\n} "NC " ==> ", LIGHTGREEN , $(output_name), WHITE " ... " NC
		);
	}else{
		print(
			NC "CC==> ", LIGHTGREEN , $(output_name), WHITE " ... " NC
		);
	}
	
	EB.utils.runShell(command);
		
	pop(compile_command);

return OK;
}

errvt methodimpl(CBuild, Compile,, inst(String) name, u16 flags){
	
	nonull(self, return nullerr;);

	compileC_FLAGS struct_flags = {.flags = flags};
	inst(StringBuilder) compile_args = push(StringBuilder, NULL, UINT64_MAX);

	if(self->includes != NULL){
		
		foreach(self->includes, inst(String), include){

			StringBuilder.Append(compile_args, NULL, 
		       		"-I ",$(include)," ", endstr
			);
		}
	}
		
	eb_source_build(blueprint->srcfiles, compileC_Source, blueprint);
	if(struct_flags.do_flag == CCFL_DO_EVERYTHING){
		blueprint->result = CBuild.Linker.link(
		);	
	}
		
	pop(compile_args);

return OK;
}


construct(CBuild,
	.addSourceDirs = CBuild_addSrcDirs
){
	*self = (CBuild_Instance){
		.cc = args.cc ? args.cc : NULL,
		.srcfiles = newList(inst(String)),
		.includes = newList(inst(String)),
		.libs = newList(inst(String))
	};

	if(args.libs != NULL){
	    foreach(args.libs, cstr, lib){
		inst(String) lib_str = new(String, lib, 255);
		List.Append(self->srcfiles, &lib_str, 1);
	    }
	}
	if(args.includes != NULL){
	    foreach(args.includes, cstr, include){
		inst(String) include_str = new(String, include, 255);
		List.Append(self->srcfiles, &include_str, 1);
	    }
	}
	if(args.srcfiles != NULL){
	    foreach(args.srcfiles, cstr, srcfile){
		inst(String) srcfile_str = new(String, srcfile, 255);
		List.Append(self->srcfiles, &srcfile_str, 1);
	    }
	}

return self;
}
