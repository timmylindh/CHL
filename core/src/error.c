/*
 * This source file's purpose is to provide an interface for error handling
 * header imported by other source files
 */

#include <stdio.h>
#include <stdlib.h>

// Struct for holding error data
typedef struct {
	unsigned char id;
	char * value;
} ERROR;

// Struct array to hold errors of type [ERROR], dynamically allocated
static ERROR * ERRORS;

// Size of [ERRORS]
static unsigned char errors_size = 0;

// Dynamically allocated variable for error string
char * _alloce_;

// Append error [ERROR] to [ERRORS] array, see macro chl_error_append
void error_append(char id, char * value) {
	// Prevent char overflow, a greater number than 512
	if(errors_size >= 510)
		return;

	// Allocate memory for new error variable
	ERRORS = realloc(ERRORS, ++errors_size * sizeof(ERROR));

	// Set variable properties
	ERRORS[errors_size - 1].id = id;
	ERRORS[errors_size - 1].value = value;
}

// Output errors in [ERRORS] struct array
void chl_print_errors() {
	int i;

	// Loop through [ERRORS] array and output errors
	for(i = 0; i < errors_size; i++)
		printf("<span style='display: block; position: absolute; top: 0; padding: 10px; background: #FFF; color: #333;'>Error %d: %s.</span>", ERRORS[i].id, ERRORS[i].value);

	fflush(stdout);
}

// Initialize and free objects, called by chl_fcgi_init
void _error_init() {
	errors_size = 0;

	free(ERRORS);
	free(_alloce_);
}
