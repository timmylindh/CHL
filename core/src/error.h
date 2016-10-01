#ifndef ERROR_H_
#define ERROR_H_

#include <stdio.h>
#include <stdlib.h>

// Whether to compile as FastCGI
#ifdef _F_CHL_
#include "fcgi_stdio.h"
#endif


#define CHL_E_FILENF 0 // Error: file not found
#define CHL_E_FILEINT 1 // Error: opening of file interrupted by signal
#define CHL_E_FILESIZE 2 // Error: file too large
#define CHL_E_NOTERMIN 3 // Error: no inline code terminator
#define CHL_E_NOTERMFUNC 4 // Error: no function code terminator
#define CHL_E_UNEXV 5 // Error: no clear end of variable name
#define CHL_E_UNKFUNC 6 // Error: unknown function

void error_append(char, char *);
void chl_print_errors();
void _error_init();

// Dynamically allocated variable for error string
extern char * _alloce_;

// Macro to dynamically allocate an error string and pass it to error_append
#define chl_error_append(id, ...) snprintf((_alloce_ = malloc(100)), 100, __VA_ARGS__), error_append(id, _alloce_);

#endif /* ERROR_H_ */
