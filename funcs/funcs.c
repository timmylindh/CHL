#include "funcs.h"
#include "../core/types.h"
#include "../core/vas.h"
#include "../error/error.h"

#include <stdint.h>
#include <ctype.h>
#include <string.h>
#include <stdio.h>
#define ARGS_LIM 10

static t_STATE get_args(char * args, ARGS fargs);
static t_STATE args_remove_spaces(char * args);

// Execute function
t_STATE function(char * name, char * args) {
	t_ADDRESS address;
	CHL_FUNC func;

	char * arguments[ARGS_LIM];

	// Function not in vfs
	if(! (address = fpop(name))) {
		set_errno(ERRNO_UNKNOWN_FUNCTION, name);
		return 0;
	}

	// Convert address to CHL_FUNC pointer
	volatile uintptr_t pt = (uintptr_t) address;
	func = (CHL_FUNC) pt;

	// Get arguments
	if(! get_args(args, arguments)) {
		set_errno(ERRNO_INVALID_ARGS, name);
		return 0;
	}

	// Execute function
	(*func)(arguments);

	return 1;
}

// Format and get function arguments
static t_STATE get_args(char * args, ARGS fargs) {
	char * arg;
	int i = 0;

	if(! args_remove_spaces(args))
		return 0;

	if((arg = strtok(args, ",")) == NULL) {
		fargs[0] = args;
		return 1;
	}

	while(arg != NULL) {
		fargs[i++] = arg;
		arg = strtok(NULL, ",");
	}

	return 1;
}

// Remove and handle spaces in arguments
static t_STATE args_remove_spaces(char * args) {
	char * new;
	char delim;

	new = args;

	while(*args != '\0') {
		if((*args == '"') || (*args == '\'')) {
			delim = *args;
			*new++ = *args++;

			{ // Check for ending delimiter
				while((*args != delim) && (*args != '\0'))
					*new++ = *args++;

				if(*args == '\0')
					return 0;

				*new++ = *args++;
			}

			continue;
		}

		if(isspace(*args)) {
			args++;
			continue;
		}

		*new++ = *args++;
	}

	*new = '\0';
	return 1;
}
