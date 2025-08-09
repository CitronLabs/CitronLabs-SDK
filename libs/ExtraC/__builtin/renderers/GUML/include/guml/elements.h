#pragma once
#include "core.h"
#include "types.h"


Enum(GumlShaderType,
	GUMLSHADER_GLSL
);

Type(GumlMesh,
	arry(u32)   attribs_sizes;
	arry(float) data;
)
Type(GumlShader,
	GumlShaderType type;	
	inst(String)   shader;
)
Type(GumlElement,
	inst(GumlMesh)   mesh;
	inst(GumlShader) shader;
)
//------------------------------------------------------|
//			ELEMENT MACROS			|
//------------------------------------------------------|
	
/*\------------------|
        MESHES       |
/------------------*/
	#define mesh(name, attribs, ...) 			\
		GumlMesh name##_MESH = { 			\
			.attribs_sizes = (u32[]){attribs},	\
			.data = (float[]){__VA_ARGS__}}; 	
	#define shader(name, _type, codestring)			\
		GumlShader name##_SHADER = {			\
			.type = SHADERTYPE_##_type,		\
			.shader = codestring};

	#define __attribs(...) __VA_ARGS__
	#define attr_(type) sizeof(type)
	#define attr_vec(type, len) sizeof(type) * len

/*\------------------|
        ELEMENTS     |
/------------------*/
	/*FIRST*/                               #define elmnt(NAME,_data, ...) 		\
	/* Creates a traits struct def for*/    	typedef struct NAME##_TRAITS{	\
	/* new element*/                        		__VA_ARGS__		\
	                                        	}NAME##_TRAITS; 		\
	/*THEN*/                                					\
	/* Creates the actual element struct*/  	typedef struct NAME##_ELEMENT{  \
	/* which stores all of the data for the*/		GumlElement data; 	\
	/* element instance*/                   		u64 traits_len; 	\
	                                        		NAME##_TRAITS traits; 	\
							}NAME##_ELEMENT; 		\
		                                					\
	/*FINALLY*/                             	static const 			\
	/* Creates a base struct which holds */ 	NAME##_ELEMENT NAME##_BASE = {	\
	/* constant data such as the mesh and*/ 		_data, 			\
	/* other element meta data*/				sizeof(NAME##_TRAITS), 	\
							(NAME##_TRAITS){0}};
	


	#define __data(...) (GumlElement){__VA_ARGS__}
	
	#define NEW_ELEMENT(name, ...) 			\
		(name##_ELEMENT){ 			\
		.data = name##_BASE.data, 		\
		.traits_len = name##_BASE.traits_len, 	\
		.traits = {__VA_ARGS__}			\
	}






	






