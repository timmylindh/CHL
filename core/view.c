#include "view.h"
#include "../io/io.h"
#include "types.h"
#include "../http/http.h"
#include "../error/error.h"
#include "../funcs/funcs.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Operation states
#define STATE_FUNC_NAME 1
#define STATE_FUNC_ARGS 2
#define STATE_FUNC_DONE 3

#define NEW_LINE (*buff == '\n')
#define INLINE_START ((*buff == '<') && (*(buff + 1) == '{'))
#define INLINE_END ((*buff == '}') && (*(buff + 1) == '>'))
#define OUTPUT(str) fputs(str, stdout)


static char * file_name; // File name
static t_INDEX linenr; // Current line
static char * buff; // File buffer
static t_STATE state; // Next operation
static char * func_name; // Current function name
static char * func_args; // Current function arguments

void view(char * file);
static void interpret();
static t_STATE parse_inline(char ** out);
static inline t_STATE get_function_name(t_STATE * first);
static inline t_STATE get_function_args(t_STATE * first);

// Open a view
void view(char * file) {
	char * start;

	file_name = file;
	linenr = 1;
	state = 0;

	headers();

	if((start = file_get_all(file)) == NULL) {
		free(start);
		return;
	}

	buff = start;

	interpret();
	free(start);
}

// Interpret the file buffer, go through every character
static void interpret() {
	char * out;

	out = buff;

	while(*buff != '\0') {
		if(NEW_LINE)
			linenr++;

		// Inline code
		else if(INLINE_START) {
			*buff = '\0';
			buff += 2;

			OUTPUT(out);

			if(! parse_inline(&out)) {
				print_error();
				return;
			}

			continue;
		}

		buff++;
	}

	OUTPUT(out); // Output last characters in buffer
}

// Handle and execute inline code, advanced sh*t
static t_STATE parse_inline(char ** out) {
	t_STATE first;

	while(*buff != '\0') {
		switch(state) {
			case STATE_FUNC_NAME: // Get function name
				if(! (state = get_function_name(&first)))
					return 0;

				continue;

			case STATE_FUNC_ARGS: // Get function arguments
				if(! (state = get_function_args(&first)))
					return 0;

				continue;

			case STATE_FUNC_DONE: // Done, execute function
				if(! function(func_name, func_args)) {
					SET_ERROR("Unknown function %s in view '%s' on line %d", func_name, file_name, linenr);
					return 0;
				}

				state = 0;
				break;
		}

		if(INLINE_END)
			break;

		if(NEW_LINE) {
			linenr++;
			buff++;

			continue;
		}

		if(isspace(*buff)) {
			buff++;
			continue;
		}

		// Unvalid function name
		if(isdigit(*buff)) {
			SET_ERROR("Unexpected character '%c', in view '%s' on line %d", *buff, file_name, linenr);
			return 0;
		}

		state = STATE_FUNC_NAME;
		first = 1;
	}

	// No ending }> found
	if(*buff == '\0') {
		SET_ERROR("Unexpected end of view '%s' on line %d, expected '}>'", file_name, linenr);
		return 0;
	}

	buff += 2;
	*out = buff;

	return 1;
}

// Get function name
static inline t_STATE get_function_name(t_STATE * first) {
	if(*first) { // Is it a new function?
		func_name = buff;
		*first = 0;
	}

	if(*buff == '(') { // Is the function name done?
		*buff++ = '\0';
		*first = 1;

		return STATE_FUNC_ARGS;
	}

	if(INLINE_END) { // Is the end of code reached?
		SET_ERROR("Syntax error: missing '(' in view '%s' on line %d", file_name, linenr);
		return 0;
	}

	buff++;
	return STATE_FUNC_NAME; // Continue with name
}

// Get function arguments
static inline t_STATE get_function_args(t_STATE * first) {
	if(*first) {
		func_args = buff;
		*first = 0;
	}

	// Is the end of arguments reached?
	if((*buff == ')') && (*(buff + 1) == ';')) {
		*buff = '\0';
		buff += 2;

		*first = 1;

		return STATE_FUNC_DONE; // Execute function
	}

	if(INLINE_END) {
		SET_ERROR("Unexpected end of function '%s', in view '%s on line %d, expected ');'", func_name, file_name, linenr);
		return 0;
	}

	buff++;
	return STATE_FUNC_ARGS; // Continue with args
}
