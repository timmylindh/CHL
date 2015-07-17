#ifndef ERROR_H_
#define ERROR_H_

#include "../core/types.h"

// Error codes
#define ERRNO_VFS_OVERFLOW 1
#define ERRNO_VVS_OVERFLOW 2
#define ERRNO_FILE_NOT_FOUND 3
#define ERRNO_GET_OVERFLOW 4
#define ERRNO_POST_OVERFLOW 5
#define ERRNO_HEADERS_OVERFLOW 6
#define ERRNO_INVALID_SYNTAX 7
#define ERRNO_UNKNOWN_FUNCTION 8
#define ERRNO_INVALID_ARGS 9

// Get current error number
t_ERROR get_errno();

// Get textual error based on get_errno
char * get_error();

// Get textual error based on specified errno
char * eget_error(t_ERROR errno);

// Set error number
void set_errno(t_ERROR errno, char * other);

#endif /* ERROR_H_ */
