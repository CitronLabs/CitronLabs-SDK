#pragma once
#include "std-libc.h"
#include "std-utils.h"
#include "std-error.h"
#include "stdext-time.h"
#include "std-types.h"


typedef char dirpath[256];
Type(dir_entry,
	u8 is_dir : 1;
	char name[256];
	size_t size;
	inst(TimeShort) time_created;
	inst(TimeShort) time_modified;
)


#define catNameandDirPath(out, dirpath, name) \
	strncat(strncat(strncpy(out, dirpath, 255), "/", 255), name, 255);

#define pathtostr(path) str_cast(path, 255)

#define FFL_ASYNC 0x01
#define FFL_READ 0x02
#define FFL_WRITE 0x04
#define FFL_APPEND 0x08

#define ENT_DIR true
#define ENT_FILE false

#define DFL_READ 0x01
#define DFL_WRITE 0x02

errvt getFileSystemEntry(dirpath path, dir_entry* ent);

#define $(expr) NULL, __Base_Type__(expr), NULL, expr
#define $O(object) NULL, BASETYPE_OBJECT, &object->__methods->Formatter, object

#define endprint NULL, BASETYPE_NULL
#define endscan NULL, BASETYPE_NULL

#define print(...) File.PrintTo(File.out, __VA_ARGS__, endprint)
#define fprint(file,...) File.PrintTo(file, __VA_ARGS__, endprint)
#define println(...) File.PrintTo(File.out, __VA_ARGS__, "\n" , endprint)

#define scan(...) File.ScanFrom(File.in, NULL ,__VA_ARGS__, endscan)
#define fscan(file,...) File.ScanFrom(file, NULL ,__VA_ARGS__, endscan)
#define scanln(...) File.ScanFrom(File.in, "\n", __VA_ARGS__, endscan)


Class(File,
__INIT(cstr path; u8 flags; u16 char_size),
__FIELD(),

	interface(Loggable);

	inst(File) in;
	inst(File) out;
	inst(File) err;
	errvt method(File, PrintTo,, ...);
	errvt method(File, ScanFrom,, cstr delimiter, ...);
	inst(File)  (*FromC)(FILE* file, u8 flags, u16 char_size);
	FILE* 	    method(File, ToC);
	i64 	    method(File, Read,, void* output , u64 len);
	i64 	    method(File, Write,, void* input , u64 len);
	errvt 	    method(File, Move,, dirpath path);
	errvt 	    method(File, Copy,, inst(File)* new_file, dirpath path);
	errvt 	    method(File, Remove);
	errvt 	    method(File, SetFlags,, u8 flags);
	inst(File)  (*Create)(cstr path, u8 flags, u16 char_size);
)

Class(Dir,
__INIT(cstr path; u8 flags;),
__FIELD(),
	
	i64 	method(Dir, Read,, dir_entry* output , u64 len);
	i64 	method(Dir, Write,, dir_entry* input , u64 len);
	errvt 	method(Dir, Move,, dirpath path);
	errvt 	method(Dir, Copy,, inst(Dir)* new_dir, dirpath path);
	inst(Dir) (*Create)(dirpath path, u8 flags);
	errvt 	(*SetCurrent)(dirpath path);
)
