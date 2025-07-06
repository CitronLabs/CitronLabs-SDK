

#define RESOURCE_METHODS(Class) \
inst(Class)(*__COLLECT)(inst(Collection) collection, Class##_ConstructArgs args);

#define RESOURCE_ERRORCODES	\
RESOURCERR_INVALID, 		\
RESOURCERR_FAIL, 		\
RESOURCERR_NOTLOADED, 		\
RESOURCERR_TOKENINDEX, 		\
RESOURCERR_TOKENCREATE, 	\
RESOURCERR_TOKENMODIFY, 	\
RESOURCERR_TOKENACCESS

typedef struct Collection_Instance Collection_Instance;
