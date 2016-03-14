/*
 * This source file's purpose is to handle everything that has to do with inline code
 */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "inline.h"
#include "error.h"

// Struct for CHL inline functions
typedef struct {
	char * name;
	void (* function)(char *);
} FUNC;

// Struct array for CHL inline functions, dynamically allocated
static FUNC * FUNCS;

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
		else if(isspace(**buff)) {
			goto next_byte;
		}

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
	// Skip if [FUNCS] is empty
	if(! funcs_size)
		return 0;

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
