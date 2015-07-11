#include "http.h"
#include "../core/cgi.h"
#include "../core/types.h"
#include "../error/error.h"

#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stdio.h>

#define HEADER_HEADER_LIM 30
#define HEADER_VALUE_LIM 50
#define HEADERS_LIM 10

typedef struct {
	char header[HEADER_HEADER_LIM];
	char value[HEADER_VALUE_LIM];
} Header;

static Header HEADERS[HEADERS_LIM];
static t_INDEX headers_index = 0;

// Output headers
void headers() {
	int i;

	for(i = 0; i < headers_index; i++) {
		if(i == (headers_index - 1)) {
			printf("%s: %s\n\n", HEADERS[headers_index].header, HEADERS[headers_index].value);
			break;
		}

		printf("%s: %s\n", HEADERS[headers_index].header, HEADERS[headers_index].value);
	}

}

// Initialize standard headers
void headers_init() {
	strncpy(HEADERS[headers_index].header, "Content-type", HEADER_HEADER_LIM);
	strncpy(HEADERS[headers_index++].value, "text/html", HEADER_VALUE_LIM);
}

// Get header value
char * get_header(char * header) {
	int i;
	for(i = 0; (i < headers_index) && strncmp(header, HEADERS[headers_index].header, HEADER_HEADER_LIM); i++);

	if(i == headers_index)
		return NULL;

	return HEADERS[headers_index].value;

}

// Set header value
void set_header(char * header, char * value) {
	int i;

	if(headers_index > HEADERS_LIM) {
		set_errno(ERRNO_HEADERS_OVERFLOW, NULL);
		return;
	}

	for(i = 0; i < headers_index; i++) {
		if(! strncmp(header, HEADERS[headers_index].header, HEADER_HEADER_LIM)) {
			strncpy(HEADERS[headers_index].value, value, HEADER_VALUE_LIM);
			break;
		}
	}

	if(i == headers_index) {
		strncpy(HEADERS[headers_index].header, header, HEADER_HEADER_LIM);
		strncpy(HEADERS[headers_index].value, value, HEADER_VALUE_LIM);
	}
}

// Get POST data
char * post(char * name) {
	int i;

	for(i = 0; (i < post_index) && strncmp(name, POST[i].name, QUERY_NAME_LIM); i++);

	if(i == post_index)
		return NULL;

	return POST[i].value;
}

// Get GET data
char * get(char * name) {
	int i;

	for(i = 0; (i < get_index) && strncmp(name, GET[i].name, QUERY_NAME_LIM); i++);

	if(i == get_index)
		return NULL;

	return GET[i].value;
}

// Get size of GET array
int get_size() {
	return get_index;
}

// Get size of POST array
int post_size() {
	return post_index;
}

// Decode URL
void url_decode(char * str) {
	char * decoded;
	decoded = str;

	if(*str == '\0')
		return;

	while(*str != '\0') {
		if((*str == '%') && (isxdigit(str[1]) && isxdigit(str[2]))) {
			{
				if(str[1] >= 'a')
					str[1] -= ('a' - 'A');
				else if(str[1] >= 'A')
					str[1] -= ('A' - 10);
				else
					str[1] -= '0';
			}

			{
				if(str[2] >= 'a')
					str[2] -= ('a' - 'A');
				else if(str[2] >= 'A')
					str[2] -= ('A' - 10);
				else
					str[2] -= '0';
			}

			*decoded++ = (16 * str[1]) + str[2];
			str += 3;
		}

		else
			*decoded++ = *str++;
	}

	*decoded++ = '\0';
}

// Convert string to hex form
int strtohex(char * str) {
	char * pt;
	return (int) strtol(str, &pt, 16);
}


