/*
 * This source file's purpose is to call functions to initialize and free data
 * inside other source files, and to provide support for FastCGI
 *
 * Put source init functions inside chl_fcgi_init
 */

#include "cgi.h"
#include "error.h"
#include "http.h"
#include "inline.h"
#include "fastcgi.h"
#include "fcgi_stdio.h"

// Call the init function of source files
void chl_fcgi_init() {
	_cgi_init();
	_error_init();
	_http_init();
	_inline_init();
}

// Accept next client using FastCGI, caller should run in a loop
int chl_fcgi_next() {
	chl_fcgi_init();

	if(FCGI_Accept() >= 0)
		return 1;

	return 0;
}


