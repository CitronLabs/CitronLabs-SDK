#pragma once
#include "./types.h"
#include "./error.h"
#include "./timing.h"

#define pathtostr(path) str_cast(path, sizeof(fsPath))

#define FFL_ASYNC 	0x01
#define FFL_READ 	0x02
#define FFL_WRITE 	0x04
#define FFL_APPEND 	0x08

#define ENT_DIR 	true
#define ENT_FILE 	false

#define DFL_READ 	0x01
#define DFL_WRITE 	0x02

#define $(expr)    NULL, __Base_Type__(expr), NULL, expr
#define $O(object) NULL, BASETYPE_OBJECT, &object->__methods->Formatter, object

#define endprint NULL, BASETYPE_NULL
#define endscan  NULL, BASETYPE_NULL

#define print(...) 	 File.PrintTo(File.out, __VA_ARGS__, endprint)
#define fprint(file,...) File.PrintTo(file, 	__VA_ARGS__, endprint)
#define println(...) 	 File.PrintTo(File.out, __VA_ARGS__, "\n" , endprint)

#define scan(delim, ...) 	   File.ScanFrom(File.in, delim,__VA_ARGS__, endscan)
#define fscan(file, delim,...) 	   File.ScanFrom(file,    delim,__VA_ARGS__, endscan)
#define scanln(...) 		   File.ScanFrom(File.in, "\n", __VA_ARGS__, endscan)

typedef char fsPath[256];
Type(fsEntry,
	u8 is_dir : 1;
	char name[256];
	size_t size;
	inst(Time) time_created;
	inst(Time) time_modified;
)

Interface(VirtFS,
	i64 	imethod(write,,   pntr handle, pntr data, size_t size);
	i64 	imethod(read,,    pntr handle, pntr data, size_t size);
	errvt 	imethod(search,,  fsPath path, fsEntry* ent);
	pntr  	imethod(open,,    fsPath path);
	errvt  	imethod(close,,   pntr handle);
)

Class(FileSys,
__INIT(intf(VirtFS) interface; inst(Object) fs),
__FIELD(),
	errvt method(FileSys, search,, fsPath path, fsEntry* result);
	errvt method(FileSys, setCurrent);
)

extern inst(FileSys) sys_fs;

Class(File,
__INIT(cstr path; u8 flags; u16 char_size),
__FIELD(),

	interface(Loggable);

	inst(File) in;
	inst(File) out;
	inst(File) err;
	errvt 		method(File, PrintTo,, ...);
	errvt 		method(File, ScanFrom,, cstr delimiter, ...);
	FILE* 		method(File, ToC);
	i64 		method(File, Read,,     pntr output, u64 len);
	i64 		method(File, Write,,    pntr input,  u64 len);
	errvt 		method(File, Move,,     fsPath path);
	errvt 		method(File, Copy,,     inst(File)* new_file, fsPath path);
	errvt 		method(File, Remove);
	errvt 		method(File, SetFlags,, u8 flags);

	inst(File)  	vmethod(Create, cstr path,  u8 flags, u16 char_size);
	inst(File)  	vmethod(FromC,  FILE* file, u8 flags, u16 char_size);
)

Class(Dir,
__INIT(cstr path; u8 flags;),
__FIELD(),
	
	i64 	  method(Dir, Read,,  fsEntry* output , u64 len);
	i64 	  method(Dir, Write,, fsEntry* input , u64 len);
	errvt 	  method(Dir, Move,,  fsPath path);
	errvt 	  method(Dir, Copy,,  inst(Dir)* new_dir, fsPath path);
	inst(Dir) vmethod(Create,     fsPath path, u8 flags);
	errvt 	  vmethod(SetCurrent, fsPath path);
	
	#define DirForEach(dir, entbuf_size)								\
		fsEntry 	dir##_entries[entbuf_size];						\
		u32 		dir##_entries_read = 0;							\
		while((dir##_entries_read = Dir.Read(dir, dir##_entries, entbuf_size)) > 0)		\
		    for(fsEntry ent = dir##_entries[--dir##_entries_read]; 				\
			dir##_entries_read < 0; 							\
			ent = dir##_entries[--dir##_entries_read])			
)
