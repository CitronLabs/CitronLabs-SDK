#include "../systems/__systems.h"
#include <libudev.h>


Type(UdevData,
	struct udev *handle;
	struct udev_monitor *monitor;
	int fd, poll_fd;
)

//shortening the function names for readability
Static(Udev,
       	struct{
		int vmethod(addFilterSubsystem,
		  struct udev_monitor * udev_monitor, 
		  const char * subsystem,
		  const char * devtype
		);
		int vmethod(enable, 	struct udev_monitor* udev_monitor);
		int vmethod(getFD,  	struct udev_monitor* udev_monitor);
		struct udev_device * vmethod(getDevice,  	struct udev_monitor* udev_monitor);
		struct udev_monitor* vmethod(destroy, 		struct udev_monitor* udev_monitor);
		struct udev_monitor* vmethod(newfromNetLink,	struct udev *udev, const char *name);
       	}monitor;
	struct udev* vmethod(destroy,  struct udev* udev_monitor);
	struct udev* vmethod(makeNew);
)
Impl(Udev){
    .monitor = {
	.addFilterSubsystem 	= udev_monitor_filter_add_match_subsystem_devtype,
	.enable 		= udev_monitor_enable_receiving,
	.destroy 			= udev_monitor_unref,
	.getFD 			= udev_monitor_get_fd
    },
	.destroy 			= udev_unref,
};
