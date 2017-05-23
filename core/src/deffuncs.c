/*
 * This source file's purpose is to define the default inline functions for CHL
 */

#include "inline.h"
#include "view.h"
#include "deffuncs.h"

// Whether default functions have been initialized or not
char def_funcs = 0;

// Default inline function for importing files
void _def_import(char * args) {
	char * file;

	// Import file if argument file name is defined
	if((file = chl_next_arg(args)))
		chl_import(file);
}

// Default inline print function
void _def_print(char * args) {
	char * arg;

	// Attain first argument
	if(! (arg = chl_next_arg(args)))
		return;

	// Output first argument
	fputs(arg, stdout);

	// Loop through rest of arguments and output data
	while((arg = chl_next_arg(NULL)))
		fputs(arg, stdout);
}

// Append default functions to [FUNCS] array in "inline.c"
void append_default_funcs() {
	// Add default inline import function
	chl_func_append(DEF_FUNC_IMPORT, _def_import);
	// Add default inline print function
	chl_func_append(DEF_FUNC_PRINT, _def_print);

	def_funcs = 1;
}

//Arbitrary function for creating the best input manager in Java.
void scanner(int imaginaryInputStream){
	fputs("Do you want to fuck?");
	int horny = 1;
	if(horny)
		fputs("I do.");
	else
		fputs("Not right now.");
		
}
