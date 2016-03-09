#include "vas.h"
#include "../core/types.h"
#include "../error/error.h"

#include <stdio.h>
#include <stdint.h>
#include <string.h>

static t_INDEX vfs_index = 0;
static t_INDEX vvs_index = 0;

VASItem vfs[VIEW_FUNCTION_SPACE_LIM];
VASItem vvs[VIEW_VARIABLE_SPACE_LIM];

// Push item to vfs
void fpush(const char * name,  CHL_FUNC address) {
	if(vfs_index > VIEW_FUNCTION_SPACE_LIM) {
		SET_ERROR("View function space overflow.");
		return;
	}

	volatile uintptr_t pt = (uintptr_t) address;

	vfs[vfs_index].address = (t_ADDRESS) pt;
	strncpy(vfs[vfs_index].name, name, VASITEM_NAME_LIM);

	vfs_index++;
}

// Push item to vvs
void vpush(const char * name, void * address) {
	if(vvs_index > VIEW_VARIABLE_SPACE_LIM) {
		SET_ERROR("View variable space overflow");
		return;
	}

	volatile uintptr_t pt = (uintptr_t) address;

	vvs[vvs_index].address = (t_ADDRESS) pt;
	strncpy(vvs[vvs_index].name, name, VASITEM_NAME_LIM);

	vvs_index++;
}

// Get function from vfs
t_ADDRESS fpop(const char * name) {
	int i;

	for(i = 0; (i < vfs_index) && strncmp(vfs[i].name, name, VASITEM_NAME_LIM); i++);

	if(i == vfs_index)
		return 0;

	return vfs[i].address;
}
