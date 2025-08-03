#pragma once

/*---------------------------\
   		 ,-.	      \
    		 \_/           \
	      _	{|||)<		\
     | |	 / \		 \
  ___| |_    __ `-'__             \     
 / _ \ '_ \ / _ \/ _ \		   \
|  __/ |_) |  __/  __/		    \
 \___|_.__/ \___|\___|		     \
	"Easy" Build System           \         
--------------------------------------*/                      

#define EBEE_ERRORCODES \
BUILDERR_BUILDENV, 	\
BUILDERR_CACHE, 	\
BUILDERR_SOURCE, 	\
BUILDERR_UTILS, 	\
BUILDERR_TARGETS
#ifndef __USER_ERRORCODES__
	#define __USER_ERRORCODES__ EBEE_ERRORCODES
#endif
#include "../XC/core.h"
#include "../XC/os.h"
#include "./cli.h"
#include "./utils.h"

const static data(Version) __eb_version = {
	.schema = V_ALPHABETA,
	.version = (u32[]){
		0, ABV_RELEASE,	// MAJOR_VERSION
		1, ABV_ALPHA,	// MINOR_VERSION
		0 		// PATCH_VERSION
	}
};

Enum(EB_Flag,  EBFL_VERBOSE);

/*-----------------------|
 *     Ebee Cache	 |
------------------------*/
Enum(EB_Cache, COMPILE_CACHE);

Interface(EBctl_Store,
	errvt 		vmethod(cacheLoad,   EB_Cache cache_type, inst(String) key, inst(Struct) data);
	inst(Struct) 	vmethod(cacheSearch, EB_Cache cache_type, inst(String) key);
	errvt 		vmethod(cacheRemove, EB_Cache cache_type, inst(String) key);
	errvt 		vmethod(cacheSave,   EB_Cache cache_type);
)

/*-----------------------|
 *     Ebee Sources	 |
------------------------*/
Data(EB_Source,
__INIT(cstr path;),
	inst(String) path;
	errvt fn(build_routine, EB_Source, void*);
	void* args;
	u8 requires_build : 1;
);

Interface(EBctl_Source,
	errvt 	   	vmethod(add,    EB_Source* source);
	EB_Source* 	vmethod(search, inst(String) source_name);

	errvt      	vmethod(depRequire, List(cstr) dependencies);
	errvt      	vmethod(depDefine,  inst(String) dependency_name, EB_Source(*build_routine)());
)

/*-----------------------|
 *    Ebee Projects	 |
------------------------*/

Data(EB_Project,
__INIT(cstr name; cstr build_dir; cstr project_dir; 
    List(
	entry(String, errvt(*)(inst(EB_Project) project))
    ) tasks
),
	#define task(name, fn) (data_entry){name, fn}

	u64 id;
	data(String)
     		* name,
     		* build_dir,
     		* project_dir;
      	Map(String, errvt(*)()) tasks; 
){return self;}

/*-----------------------|
 *    Ebee Namespace	 |
------------------------*/

Static(EB,
	interfaceAs(EBctl_Cli) 		cli;
	interfaceAs(EBctl_Store) 	store;
       	interfaceAs(EB_Utils)		utils;
       	interfaceAs(EBctl_Source)	source;
	void  vmethod(rebuild);
	void  vmethod(rerun);
	bool  vmethod(getFlag, EB_Flag flag);
	cstr* vmethod(getArgv);
);

errvt build();


