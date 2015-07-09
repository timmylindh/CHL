#include "error.h"
#include "../types.h"
#include <string.h>
#include <stdio.h>

#define SPEC_LIM 20
#define ERROR_LIM 100

static t_ERROR errorn = 0;
static char spec[SPEC_LIM] = {0};

// Return errorn
t_ERROR get_errno() {
	return errorn;
}

// Set errorn
void set_errno(t_ERROR errno, char * other) {
	errorn = errno;

	if(other != NULL)
		strncpy(spec, other, SPEC_LIM);
}

// Get textual representation of current errno
void get_error(char * str, int str_size) {
	eget_error(errorn, str, str_size);
}

// Get textual representation of t_ERROR errno
void eget_error(t_ERROR errno, char * str, int str_size) {
	char error[ERROR_LIM];

	switch(errno) {
		case ERRNO_VFS_OVERFLOW:
			strncpy(error, "View function space overflow", ERROR_LIM);
			break;

		case ERRNO_VVS_OVERFLOW:
			strncpy(error, "View variable space overflow", ERROR_LIM);
			break;

		case ERRNO_FILE_NOT_FOUND:
			snprintf(error, ERROR_LIM, "File '%s' not found", spec);
			break;

		default:
			strncpy(error, "No error", ERROR_LIM);
			break;
	}

	strncpy(str, error, str_size);
}
