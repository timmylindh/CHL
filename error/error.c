#include "error.h"

#include <stdio.h>

char CHL_ERROR[ERROR_LIM] = {'\0'};

void print_error() {
	if(*CHL_ERROR == '\0')
		printf("<span>No error</span>");
	else
		printf("<span>%s</span>", CHL_ERROR);
}

