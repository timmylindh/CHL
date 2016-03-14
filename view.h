#ifndef VIEW_H_
#define VIEW_H_

#include <stdio.h>

#define VIEW_SIZE_LIM 100000 // Maximum size of a view file

void chl_view(char *);
char file_read_open();
char file_read_data();
void parse_view();

#endif /* VIEW_H_ */
