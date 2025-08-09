#pragma once 
#include "../../include/Lang-C.h"

private(CBuild,
	List(EB_Source) srcfiles;
	List(EB_Source) out_files;
)

typedef union {
    struct {
	u16 do_flag : 2;
	u16 padd : 14;
    };
	u16 flags;
}compileC_FLAGS;
