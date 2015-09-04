#include "funcs.h"
#include "../core/types.h"
#include "../core/vas.h"
#include "../error/error.h"
#include "../core/view.h"

#include <stdint.h>
#include <ctype.h>
#include <string.h>
#include <stdio.h>

#define ARGS_LIM 10
#define IS_STRING_START (((delim = *args) == '\'') || ((delim = *args) == '"'))

static Argument arguments[ARGS_LIM];
static t_STATE args_formatted; // Has the args already been formatted?
static t_INDEX args_index; // Arguments index
static char * func_name; // Function name
static ARGS args_gb; // Arguments global

static t_STATE format_arguments();
static t_STATE put_arg(ARGS address);

// Execute function
t_STATE function(char * name, ARGS args) {
	t_ADDRESS address;
	CHL_FUNC func;

	args_formatted = 0;
	args_index = 0;
	func_name = name;
	args_gb = args;

	// Function not in vfs
	if(! (address = fpop(name)))
		return 0;

	// Convert address to CHL_FUNC pointer
	volatile uintptr_t pt = (uintptr_t) address;
	func = (CHL_FUNC) pt;

	// Execute function
	(*func)(args);

	return 1;
}

// Format args and split them up and put them into arguments array
static t_STATE format_arguments() {
	ARGS new, args;
	char delim;

	args = args_gb;
	new = args;

	if(! put_arg(new))
		return 0;

	while(*args != '\0') {
		if(isspace(*args))
			args++;

		// Check for end of arg
		else if(*args == ',') {
			*new++ = '\0';
			args++;

			while(isspace(*args))
				args++;

			if( !put_arg(new))
				return 0;
		}

		// Is it a string?
		else if(IS_STRING_START) {
			args++;

			while((*args != delim) && (*args != '\0'))
				*new++ = *args++;

			// No ending delim
			if(*args == '\0') {
				SET_ERROR("Syntax error in view '%s' on line %d, missing char '%c' in function %s", file_name, linenr, delim, func_name);
				return 0;
			}

			args++;
		}

		else
			*new++ = *args++;
	}

	*new = '\0';
	args_formatted = 1;

	return 1;
}

// Put argument into array, check for overflow
static t_STATE put_arg(ARGS address, t_STATE type) {
	if(args_index == ARGS_LIM) {
		SET_ERROR("Arguments buffer overflow in view '%s', on line %d function %s", file_name, linenr, func_name);
		return 0;
	}

	arguments[args_index].argument = address;
	arguments[args_index++].type = type;

	return 1;
}

// Get integer argument from arguments array
t_STATE getint(int * x) {

}
