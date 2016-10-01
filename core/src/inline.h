#ifndef INLINE_H_
#define INLINE_H_

// Whether to compile as FastCGI
#ifdef _F_CHL_
#include "fcgi_stdio.h"
#endif

char parse_inline(char **, char *, int *);
void chl_func_append(char *, void (*)(char *));
char chl_func(char *, char *);
char * chl_next_arg(char *);
int chl_next_argi(char *);
float chl_next_argf(char *);
char chl_get_args(char *(**), char *);
void _inline_init();

#endif /* INLINE_H_ */
