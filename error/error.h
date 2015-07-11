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

// Get current error number
t_ERROR get_errno();

// Get textual error based on get_errno
void get_error(char * str, int str_size);

// Get textual error based on specified errno
void eget_error(t_ERROR errno, char * str, int str_size);

// Set error number
void set_errno(t_ERROR errno, char * other);

#endif /* ERROR_H_ */
