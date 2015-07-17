#include "http.h"
#include "../core/cgi.h"

#include <stdio.h>
#include <string.h>

#define COOKIE_HEADER_LIM (COOKIE_VALUE_LIM * (3/2))

// Set cookie
void set_cookie(char * name, char * value, char * expires) {
	char val[COOKIE_HEADER_LIM];

	if(expires == NULL)
		snprintf(val, COOKIE_HEADER_LIM, "%s=%s", name, value);
	else
		snprintf(val, COOKIE_HEADER_LIM, "%s=%s; expires=%s", name, value, expires);

	set_header_new("Set-Cookie", val);
}

// Remove cookie
void remove_cookie(char * name) {
	char val[COOKIE_HEADER_LIM];

	snprintf(val, COOKIE_HEADER_LIM, "%s=; expires=Thu, 01 Jan 1970 00:00:00 GMT", name);
	set_header_new("Set-Cookie", val);
}

// Get cookie value
char * cookies(char * name) {
	if(! cookies_state)
		init_cookies();

	int i;

	for(i = 0; (i < cookies_index) && strncmp(name, COOKIES[i].name, QUERY_NAME_LIM); i++);

	if(i == cookies_index)
		return NULL;

	return COOKIES[i].value;
}
