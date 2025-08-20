#pragma once
#include "../extern.h"
#include "./user.h"

#define FS_DIR true
#define FS_FILE false

typedef void* fsHandle;
typedef char fsPath[256];
Type(fsEntry,
	bool is_dir;
	char name[256];
	size_t size;
	inst(Time) time_created;
	inst(Time) time_modified;
)

Interface(filesys,
	int CREATE_FLAG, APPEND_FLAG, WRITE_FLAG, READ_FLAG, ASYNC_FLAG;
	fsHandle vmethod(open,    bool DIR, fsPath path, int flags);
	i64 	 vmethod(write,   fsHandle handle, pntr data, size_t size);
	i64 	 vmethod(read,    fsHandle handle, pntr data, size_t size);
	errvt 	 vmethod(search,  fsPath path, fsEntry* ent);
	errvt  	 vmethod(close,   fsHandle handle);
	errvt  	 vmethod(delete,  fsPath path);
	errvt  	 vmethod(chdir,   fsPath path);
	errvt  	 vmethod(handleEvents, fsHandle handle, Queue(OSEvent) evntQueue);
	u64  	 vmethod(pollEvents);
	struct {
		errvt vmethod(readLink,     fsPath path, fsPath result)
		errvt vmethod(makeLink,     fsPath path, fsPath result)
		errvt vmethod(changePerms,  fsPath path, userPermissions perms);
	} ext;	
)
