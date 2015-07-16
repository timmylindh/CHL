#include "funcs.h"
#include "../core/types.h"
#include "../core/vas.h"
#include "../error/error.h"

#include <stdint.h>
#include <ctype.h>
#include <string.h>
#include <stdarg.h>
#include <stdlib.h>

#define ARGS_LIM 10
#define TYPE_STRING 1
#define TYPE_INT 2
#define TYPE_FLOAT 3

static t_STATE get_args(char * args, ARGS fargs);
static t_STATE args_remove_spaces(char * args);
static t_STATE get_type(char * str);
static t_STATE is_string(char * str);
static t_STATE is_int(char * str);
static t_STATE is_float(char * str);
static void get_string(char * str);

// Execute function
t_STATE function(char * name, char * args) {
	t_ADDRESS address;
	CHL_FUNC func;
	char * arguments[ARGS_LIM] = {0};

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

// Fetch arguments
void fargs(ARGS args, ...) {
	va_list arguments;
	int i;
	int * x;
	float * y;
	char ** str;

	va_start(arguments, args);

	for(i = 0; args[i] != 0; i++) {
		switch(get_type(args[i])) {
			case TYPE_STRING: // If string
				str = va_arg(arguments, char**);
				get_string(args[i]);

				*str = args[i];
				break;

			case TYPE_INT: // If int
				x = va_arg(arguments, int*);
				*x = (int) strtol(args[i], (char **) NULL, 10);

				break;

			case TYPE_FLOAT: // If float
				y = va_arg(arguments, float*);
				*y = (float) strtof(args[i], (char **) NULL);

				break;
		}
	}

	va_end(arguments);
}

// Return type of contents of str
static t_STATE get_type(char * str) {
	if(is_string(str))
		return TYPE_STRING;

	if(is_int(str))
		return TYPE_INT;

	if(is_float(str))
		return TYPE_FLOAT;

	return 0;
}

// Check if int
static t_STATE is_int(char * str) {
	while(*str != '\0') {
		if(isdigit(*str)) {
			str++;
			continue;
		}

		return 0;
	}

	return 1;
}

// Check if float
static t_STATE is_float(char * str) {
	while(*str != '\0') {
		if(isdigit(*str) || *str == '.') {
			str++;
			continue;
		}

		return 0;
	}

	return 1;
}

// Check if string
static t_STATE is_string(char * str) {
	if((*str == '"') || (*str == '\''))
		return 1;

	return 0;
}

// Remove delimiters from string
static void get_string(char * str) {
	char * new;
	char delim;

	new = str;
	delim = *str;

	while(*str != '\0') {
		if(*str == delim) {
			str++;
			continue;
		}

		*new++ = *str++;
	}

	*new = '\0';
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
