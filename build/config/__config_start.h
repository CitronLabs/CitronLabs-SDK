#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

#define global static 
#define define(name) 	typedef struct name##_Config name##_Config; struct name##_Config
#define setting 	const bool
#define value 		const long long
#define deci 		const double
#define text		const char*
#define config(name)	const name##_Config
#define enums		typedef enum
