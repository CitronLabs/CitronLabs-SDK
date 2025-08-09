#pragma once
#include "../../../../APIs/ebee/core.h" //temp

Interface(Linker,
	inst(EB_Source) imethod(link,, List(EB_Source) files_to_link, inst(String) output_name);
)

Class(LibArchiver,,,
	interface(Linker);
)

Class(CBuild,
__INIT(
	cstr cc;
	List(cstr) srcfiles;
	List(cstr) includes;
	List(cstr) libs
),
__FIELD(
	inst(String) cc;
	List(String) srcfiles;
	List(String) includes;
	List(String) libs
),

	#define CCFL_DO_EVERYTHING 0b00
	#define CCFL_DO_COMPILE_ONLY 0b01
	#define CCFL_DO_ASSEMBLE_ONLY 0b10
	#define CCFL_DO_PREPROCESS_ONLY 0b10

      	interface(Linker);

	errvt method(CBuild, addSourceDirs,, bool recursive, List(const cstr) srcdirs);
	errvt method(CBuild, compile,, inst(String) name, u16 flags);
	List(EB_Source) method(CBuild, getResults);
)
