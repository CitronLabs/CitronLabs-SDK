#pragma once
#include "elements.h"
#include "componants.h"

#define pct(percentage) ((float)percentage/100.0)
typedef float PercentValue;
static const mesh(SQUARE,
__attribs(
	attr_vec(float, 2)
),
	      1.0f, 0.0f,
	      0.0f, 1.0f,
	      0.0f, 0.0f,
	      1.0f, 1.0f
)

elmnt(BOX,
__data(
	.mesh = (GumlMesh*)&SQUARE_MESH
),
	Color bgcolor;
      	PercentValue round; 
)

#define box(...) COMPONANT_MACRO_LAYOUT(BOX, __VA_ARGS__)
