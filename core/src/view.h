#ifndef VIEW_H_
#define VIEW_H_

#include <stdio.h>

#define VIEW_SIZE_LIM 100000 // Maximum size of a view file

// Whether to compile as FastCGI
#ifdef _F_CHL_
#include "fcgi_stdio.h"
#endif

void chl_view(char *);
char file_read_open(char *, FILE **);
char * file_read_data(char **, char *, FILE *);
void parse_view(char **, char *);
void chl_import(char *);

#endif /* VIEW_H_ */
