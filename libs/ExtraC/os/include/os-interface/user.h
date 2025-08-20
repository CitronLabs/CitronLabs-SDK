#include "../extern.h"

// encompasses both groups and individual users
typedef void* userHandle;

Enum(userPermissions,
    PERMISSION_READ 		= 1,
    PERMISSION_WRITE 		= 2,
    PERMISSION_EXECUTE 		= 4,
    PERMISSION_DELETE 		= 8,
    PERMISSION_LIST_CONTENTS 	= 16,
    PERMISSION_OWNERSHIP 	= 32,
    PERMISSION_CREATE_CHILD 	= 64,
    PERMISSION_DELETE_CHILD 	= 128
);


Type(userInfo,
	inst(String) userName;
	inst(String) fullName;
    	Buffer(data(String)) groups;
    	Buffer(data(String)) subUsers;
    	userPermissions perms;
)


Interface(user, 
	userInfo* 	vmethod(enumUsers,   	u32* count);
	userHandle 	vmethod(fetchUser,   	userInfo* info);
	errvt 		vmethod(closeUser,	userHandle handle);
	errvt 		vmethod(removeUser,	userHandle handle);
	errvt 		vmethod(setPermssions,	userHandle handle, userPermissions perms);
	errvt 		vmethod(setPassword, 	userHandle handle, cstr password);
	errvt 		vmethod(logoutUser,	userHandle handle);
	userHandle 	vmethod(loginUser,    	cstr username, cstr password);
	bool 		vmethod(isSubUser,   	userHandle user, userHandle parent);
	bool 		vmethod(isAdmin,     	userHandle user);
	errvt 		vmethod(getInfo,     	userHandle user, userInfo* info);
	errvt 		vmethod(getCurrent,    	userInfo* info);
)
