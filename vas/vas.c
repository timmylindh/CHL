#include "vas.h"
#include "../core/types.h"
#include "../error/error.h"
#include <string.h>

static t_INDEX vfs_index = 0;
static t_INDEX vvs_index = 0;

VASItem vfs[VIEW_FUNCTION_SPACE_LIM];
VASItem vvs[VIEW_VARIABLE_SPACE_LIM];

// Push item to vfs
void fpush(const char * name, t_ADDRESS address) {
	if(vfs_index > VIEW_FUNCTION_SPACE_LIM) {
		set_errno(ERRNO_VFS_OVERFLOW, NULL);
		return;
	}

	vfs[vfs_index].address = address;
	strncpy(vfs[vfs_index].name, name, VASITEM_NAME_LIM);

	vfs_index++;
}

// Push item to vvs
void vpush(const char * name, t_ADDRESS address) {
	if(vvs_index > VIEW_VARIABLE_SPACE_LIM) {
		set_errno(ERRNO_VVS_OVERFLOW, NULL);
		return;
	}

	vvs[vvs_index].address = address;
	strncpy(vvs[vvs_index].name, name, VASITEM_NAME_LIM);

	vvs_index++;
}
