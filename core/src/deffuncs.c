/*
 * This source file's purpose is to define the default inline functions for CHL
 */

#include "deffuncs.h"
#include "inline.h"
#include "view.h"

// Default inline function for importing files
void _def_import(char * args) {
	char * file;

	// Import file if argument file name is defined
	if((file = chl_next_arg(args)))
		chl_import(args);
}

// Append default functions to [FUNCS] array in "inline.c"
void append_default_funcs() {
	// Add default inline import function
	chl_func_append(DEF_FUNC_IMPORT, _def_import);

}
