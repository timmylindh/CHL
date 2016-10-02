/*
 * This source file's purpose is to handle everything that has to do with inline code
 */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#include "inline.h"
#include "error.h"
#include "deffuncs.h"

// Struct for CHL inline functions
typedef struct {
	char * name;
	void (* function)(char *);
} FUNC;

// Struct array for CHL inline functions, dynamically allocated
static FUNC * FUNCS = NULL;

// Size of [FUNCS] struct array
static unsigned char funcs_size = 0;

// Parse inline code and handle inline functions and such
char parse_inline(char ** buff, char * path, int * line_nr) {
	char * var_name; // Variable name
	char * var_args; // Variable arguments

	// Loop through every byte until end of inline code is found '}>', or null terminator
	while(**buff != '\0') {
		// New line, increment [line_nr]
		if(**buff == '\n') {
			(*line_nr)++;
			goto next_byte;
		}

		// If space, skip
		else if(isspace(**buff))
			goto next_byte;

		// First letter of inline terminator
		else if(**buff == '}') {
			// Found whole terminator
			if(*(*buff + 1) == '>') {
				*buff += 2; // Move outside inline code
				return 1;
			}

			// Did not find whole terminator
			else
				break;
		}

		// Is start of function
		else {
			// Set start of variable name
			var_name = *buff;

			// Loop until end of variable name and start of arguments
			while((**buff != '(') && (**buff != '\0'))
				(*buff)++;

			// If proper function name
			if(**buff == '(') {
				**buff = '\0'; // Set end of variable name
				var_args = ++(*buff); // Set start of variable arguments

				// Loop until end of variable arguments
				while((**buff != ')') && (**buff != '\0'))
					(*buff)++;

				// Found function terminator ');'
				if((**buff == ')') && (*(*buff + 1) == ';')) {
					*((*buff)++) = '\0'; // Set end of variable arguments

					// Execute function [var_name], check if not existing
					if(! chl_func(var_name, var_args)) {
						// Unknown function error
						chl_error_append(CHL_E_UNKFUNC, "in file '%s' on line %d, unknown function '%s'", path, *line_nr, var_name);
						return 0;
					}
				}

				// Found null terminator, no ending ');' for function
				else {
					// Set error no ending terminator, only comes here if no terminator
					chl_error_append(CHL_E_NOTERMFUNC, "in file '%s' on line %d, missing terminator ');' for function '%s'", path, *line_nr, var_name);
					return 0;
				}
			}

			// Found null terminator, no clear end of variable name
			else {
				chl_error_append(CHL_E_UNEXV, "in file '%s' on line %d, unexpected end of function", path, *line_nr);
				return 0;
			}
		}

		// Next byte
		next_byte:
		(*buff)++;
	}

	// Set error no ending terminator, only comes here if no terminator
	chl_error_append(CHL_E_NOTERMIN, "in file '%s' on line %d, missing terminator '}>'", path, *line_nr);

	return 0;
}

// Append function to [FUNCS] struct array
void chl_func_append(char * name, void (* function)(char *)) {
	// Prevent char overflow, a greater number than 512
	if(funcs_size >= 510)
		return;

	// Allocate memory for new function
	FUNCS = realloc(FUNCS, ++funcs_size * sizeof(FUNC));

	// Set variable properties
	FUNCS[funcs_size - 1].name = name;
	FUNCS[funcs_size - 1].function = function;
}

// Execute function [name], return 0 if not found
char chl_func(char * name, char * args) {
	// Check whether default functions have been initialized
	if(! def_funcs)
		append_default_funcs();

	int i, x;

	// Loop through every index in [HEADERS] array until [name] is found
	for(i = 0; (i < funcs_size) && (x = strcmp(FUNCS[i].name, name)); i++);

	// Found a matching value for [name]
	if(!x) {
		// Execute function
		(*(FUNCS[i].function))(args);
		return 1;
	}

	// Did not find a match
	return 0;
}

// Returns next argument in [args], 0 if no arguments left
char * chl_next_arg(char * args) {
	static char * pt; // Pointer to current byte in [args]
	char * arg; // Pointer to next arg in [args]
	char delim; // String delimiter

	// If args attain a new value
	if(args != NULL)
		pt = args;

	// Loop until start of argument delimiter is found (" | ')
	while(((*pt != '"') && (*pt != '\'')) && (*pt != '\0'))
		pt++;

	// Set delimiter
	delim = *pt;

	// Found end of arguments
	if(*pt == '\0')
		return 0;

	// Set start of argument
	arg = ++pt;

	// Loop until end of argument delimiter is found
	while((*pt != delim) && (*pt != '\0'))
		pt++;

	// No ending delimiter
	if(*pt == '\0')
		return 0;

	// Set end of argument
	*(pt++) = '\0';

	return arg;
}

// Fetches next argument in [args] and converts it to integer, returns -1 on error or if end argument
int chl_next_argi(char * args) {
	char * arg, * err;
	long int ret;

	// Check if last argument
	if(! (arg = chl_next_arg(args)))
		return -1;

	// Convert to int
	ret = strtol(arg, &err, 10);

	// Return -1 if conversion could not be done, or an error occurred
	if((arg == err) || (ret == LONG_MIN) || (ret == LONG_MAX))
		return -1;

	// Return integer
	return (int) ret;
}

// Fetches next argument in [args] and converts it to float, returns -1 on error or 0 if end argument
float chl_next_argf(char * args) {
	char * arg, * err;
	float ret;

	// Check if last argument
	if(! (arg = chl_next_arg(args)))
		return -1;

	// Convert to float
	ret = strtof(arg, &err);

	// Return -1 if conversion could not be done, or an error occurred
	if((arg == err) || (ret == HUGE_VALF))
		return -1;

	// Return float
	return ret;
}

// Allocates memory for [dst] and sets arguments, return number of arguments
char chl_get_args(char *(** dst), char * args) {
	char argsn = 0; // Number of arguments
	char * arg; // Pointer to argument

	// If no arguments
	if(! (arg = chl_next_arg(args)))
		return 0;

	// Allocate memory for argument pointer
	*dst = malloc(++argsn * sizeof(char *));
	**dst = arg;

	// While there are still arguments left
	while((arg = chl_next_arg(NULL))) {
		// Allocate memory for argument pointer
		*dst = realloc(*dst, ++argsn * sizeof(char *));
		*(*dst + (argsn - 1)) = arg;
	}

	// Return number of arguments
	return argsn;
}

// Initialize and free objects, called by chl_fcgi_init
void _inline_init() {
	funcs_size = 0;

	free(FUNCS);
	FUNCS = NULL;
}
