#ifndef VAS_H_
#define VAS_H_

#include "../core/types.h"

#define VASITEM_NAME_LIM 20
#define VIEW_FUNCTION_SPACE_LIM 500
#define VIEW_VARIABLE_SPACE_LIM 500

// View address space item
typedef struct {
	t_ADDRESS address;
	char name[VASITEM_NAME_LIM];
} VASItem;

extern VASItem vfs[VIEW_FUNCTION_SPACE_LIM];
extern VASItem vvs[VIEW_VARIABLE_SPACE_LIM];

// Push function to vfs
void fpush(const char * name, t_ADDRESS address);

// Push variable to vvs
void vpush(const char * name, t_ADDRESS address);

#endif /* VAS_H_ */
