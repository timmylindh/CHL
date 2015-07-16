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

#define OUTPUT_LIM 400
#define ST_FUNC_NAME 1
#define ST_FUNC_ARGS 2
#define ST_FUNC_DONE 3

// Static char to access file name from other functions
static char * file_name;

static void interpret(char * buff);
static t_STATE proc_inline(char ** start, char ** out);
static void output(char * buff, char ** out, t_INDEX * size);
static inline t_STATE get_function_name(char ** name, t_STATE * first);
static inline t_STATE get_function_args(char ** args, t_STATE * first);

// Open a view
void view(char * file) {
	char * buff;

	file_name = file;
	headers();

	if((buff = file_get_all(file)) == NULL) {
		free(buff);
		return;
	}

	interpret(buff);
	free(buff);
}

// Interpret view buffer
static void interpret(char * buff) {
	char * out;
	t_INDEX output_size;

	output_size = 0;
	out = buff;

	while(*buff != '\0') {
		if(output_size == OUTPUT_LIM) // Time to output
			output(buff, &out, &output_size);

		// Handle inline code
		if((*buff == '<') && (*(buff + 1) == '{')) {
			output(buff, &out, &output_size);
			buff += 2;

			proc_inline(&buff, &out);
			continue;
		}

		output_size++;
		buff++;
	}

	if(output_size != 0) {
		*buff = '\0';
		fputs(out, stdout);
	}
}

// Output buffer to stdout, works with OUTPUT_LIM
static void output(char * buff, char ** out, t_INDEX * size) {
	char last;

	last = *buff;
	*buff = '\0';

	fputs(*out, stdout);
	*buff = last;

	*out += *size;
	*size = 0;
}

// Process inline C code, advanced sh*t
static t_STATE proc_inline(char ** code, char ** out) {
	char * func_name;
	char * func_args;
	t_STATE state = 0;
	t_STATE first = 0;

	// Check if end of code, or null char
	while(((**code != '}') && (*(*code + 1) != '>')) && (**code != '\0')) {
		switch(state) {
			case ST_FUNC_NAME: // Get function name state
				(first) ? (func_name = *code) : 0;
				state = get_function_name(code, &first);

				continue;

			case ST_FUNC_ARGS: // Get function args state
				(first) ? (func_args = *code) : 0;
				state = get_function_args(code, &first);

				continue;

			case ST_FUNC_DONE: // Handle function, done
				if(! function(func_name, func_args))
					return 0;

				state = 0;

				break;
		}

		if(isspace(**code)) {
			(*code)++;
			continue;
		}

		// If first char in function name is not alpha, return
		if(! isalpha(**code)) {
			set_errno(ERRNO_INVALID_SYNTAX, file_name);
			return 0;
		}

		// Set state to get function name
		state = ST_FUNC_NAME;
		first = 1;
	}

	// An error occoured
	if(**code == '\0') {
		set_errno(ERRNO_INVALID_SYNTAX, file_name);
		return 0;
	}

	*code += 2;
	*out = *code;

	return 1;
}

// Called every loop until name is acquired
static inline t_STATE get_function_name(char ** name, t_STATE * first) {
	// Done
	if(**name == '(') {
		*first = 1;
		*((*name)++) = '\0';

		return ST_FUNC_ARGS;
	}

	if(*((*name) + 1) == '}')
		set_errno(ERRNO_INVALID_SYNTAX, file_name);

	// Continue
	*first = 0;
	(*name)++;

	return ST_FUNC_NAME;
}

// Called every loop until args are acquired
static inline t_STATE get_function_args(char ** args, t_STATE * first) {
	// Done
	if((**args == ')') && (*((*args) + 1) == ';')) {
		*first = 1;
		**args = '\0';

		*args += 2;
		return ST_FUNC_DONE;
	}

	if(*((*args) + 1) == '}')
		set_errno(ERRNO_INVALID_SYNTAX, file_name);

	// Continue
	*first = 0;
	(*args)++;

	return ST_FUNC_ARGS;
}
