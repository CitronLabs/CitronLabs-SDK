#pragma once
#ifdef __unix__
#include "../io.h"
#include <sys/stat.h>
#include "dirent.h"
#include "fcntl.h"
#include "unistd.h"
#include <wctype.h>

private(File, 
	int fd;
	u16 char_size;
	dirpath path;
	u8 flags;
	void* async_store;
);
private(Dir,
	DIR* dir;
	dirpath path;
);

errvt File_PrintTo(inst(File) file, ...);

#ifndef __EXT_IO_SOURCE_DEF__
#include "./file.c"
#include "./dir.c"
#endif

#endif
