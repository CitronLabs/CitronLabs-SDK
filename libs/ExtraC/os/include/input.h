#pragma once
#include "./extern.h"



typedef struct {
	inhert(VecData);
     	float x,y,z;
}Pos3D;
asClassExt(Pos3D, __INIT(float x,y,z;));


typedef struct{inhertAs(Pos3D) pos; float max, min;}* posData;
Interface(PosDevice,
	posData imethod(get);	
	errvt imethod(update,, posData pos);
	inputHandle imethod(getHandle);
)

typedef struct{u32 code; bool cont;} keyCode;
Interface(KeyDevice,
	keyCode imethod(get);
	inputHandle imethod(getHandle);
)
