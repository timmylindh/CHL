#include <stdio.h>
#include <stdlib.h>
#include <chl/fcgi_stdio.h>
#include <chl/chl.h>
#include "fastcgi.h"

int main() {
	while(chl_fcgi_next()) {
		chl_set_default_headers();
		chl_print_headers();

		printf("HELLOsfsdfsdf");
	}

	return 0;
}
