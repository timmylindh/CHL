#ifndef DEFFUNCS_H_
#define DEFFUNCS_H_

#define DEF_FUNC_IMPORT "import" // Name of default function for inline import of files
#define DEF_FUNC_PRINT "print" // Name of default function for inline print

// Whether to compile as FastCGI
#ifdef _F_CHL_
#include "fcgi_stdio.h"
#endif

extern char def_funcs;
void _def_import(char *);
void _def_print(char *);
void append_default_funcs();

#endif /* DEFFUNCS_H_ */
