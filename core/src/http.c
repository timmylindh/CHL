/*
 * This source file's purpose is to provide functions for reading and manipulating
 * HTTP headers and data, cookies
 */

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "http.h"
#include "std.h"

// Implemented from cgi.c
extern char * get_env(char *);

#define HEADER_X_POW_BY "CHL" // Default x-powered-by header
#define HEADER_CON_TYPE "text/html" // Default content-type header
#define COOKIES_DATA_ENV "HTTP_COOKIE" // Cookies environment variable

// A struct to hold HTTP variables (headers, cookies)
typedef struct {
	char * name;
	char * value;
} HTTP_VAR;

static HTTP_VAR * HEADERS = NULL; // Struct array for HTTP header variables, dynamically allocated
static HTTP_VAR * COOKIES = NULL; // Struct array for HTTP cookies, dynamically allocated

static unsigned char headers_size = 0; // The amount of headers in [HEADERS]
static unsigned char cookies_size = 0; // The amount of cookies in [COOKIES]

static char headers_used = 0; // Whether headers have been printed
static char cookies_used = 0; // Whether cookies have been parsed or not

static char * raw_data_cookies = NULL; // Buffer for cookies data, dynamically allocated

// Add header element to [HEADERS] array
void chl_set_header(char * name, char * value) {
	char * value_pt; // Points to last value if header already set

	// Has header already been set
	if((value_pt = chl_get_header(name)) != NULL) {
		value_pt = value;
		return;
	}

	// Allocate memory for new header
	HEADERS = std_realloc(HEADERS, ++headers_size * sizeof(HTTP_VAR));

	// Set header properties
	HEADERS[headers_size - 1].name = name;
	HEADERS[headers_size - 1].value = value;
}

// Returns [name]'s value in [HEADERS] array
char * chl_get_header(char * name) {
	// Check if [HEADERS] array is initialized to prevent error
	if(! headers_size)
		return 0;

	int i, x;

	// Loop through every index in [HEADERS] array until [name] is found
	for(i = 0; (i < headers_size) && (x = strcmp(HEADERS[i].name, name)); i++);

	// Found a matching value for [name]
	if(!x)
		return HEADERS[i].value;

	// Did not find a match
	return 0;
}

// Output headers in [HEADERS]
void chl_print_headers() {
	// Prevent multiple outputs of headers
	if(headers_used)
		return;

	int i;

	// Loop through [HEADERS] array and output name and value
	for(i = 0; i < headers_size; i++)
		printf("%s: %s\n", HEADERS[i].name, HEADERS[i].value);

	// Terminate headers, \n\n
	puts("");

	headers_used = 1;
}

// Set default HTTP headers
void chl_set_default_headers() {
	// Allocate memory for new headers
	HEADERS = std_realloc(HEADERS, (++headers_size + 1) * sizeof(HTTP_VAR));

	// Set default content-type header properties
	HEADERS[headers_size - 1].name = "Content-Type";
	HEADERS[headers_size - 1].value = HEADER_CON_TYPE;

	// Set default x-powered-by header properties
	HEADERS[headers_size].name = "X-Powered-By";
	HEADERS[headers_size++].value = HEADER_X_POW_BY;
}

// Initialize [COOKIES] array and cookies data
void http_cookies_init() {
	// Prevent function from being called multiple times
	if(cookies_used)
		return;

	// Assign [raw_data_cookies] its value
	raw_data_cookies = get_env(COOKIES_DATA_ENV);

	// Append temporary blank variable to [COOKIES] array to prevent NULL error, overwritten
	cookies_append_var(" ", " ");

	// Split data into variables
	format_cookies_data();

	cookies_used = 1;
}

// Format cookies data and split into variables in [COOKIES] array
void format_cookies_data() {
	char * data = raw_data_cookies; // Cookies data pointer
	char * var_name, * var_value; // Pointer to variable in [data]
	char * last_var; // Last occurrence of ';', or start of string [data]

	last_var = data;
	var_name = data;

	// Loop through data and split into variables
	while(*data != '\0') {
		// If new variable
		if((*data == ':') || (*data == '=')) {
			// Set end of variable name
			*data++ = '\0';

			// Skip first spaces
			while(*data == ' ')
				data++;

			var_name = last_var;
			var_value = data;

			// Loop to next variable, next occurrence of ';'
			while((*data != ';') && (*data != '\0'))
				data++;

			// Set end of variable value
			if(*data != '\0') {
				*data = '\0';
				last_var = (data++ + 2);
			}

			// Append variable to [COOKIES] array
			cookies_append_var(var_name, var_value);
		}

		// Continue if just letter
		else
			data++;
	}
}

// Append cookie variable to [COOKIES] array
void cookies_append_var(char * name, char * value) {
	// Prevent char overflow, a greater number than 512
	if(cookies_size >= 510)
		return;

	// Allocate memory for new variable
	COOKIES = std_realloc(COOKIES, ++cookies_size * sizeof(HTTP_VAR));

	// Set variable properties
	COOKIES[cookies_size - 1].name = name;
	COOKIES[cookies_size - 1].value = value;
}

// Returns variable [name]'s value in [COOKIES] data array
char * chl_cookies(char * name) {
	// Check if [COOKIES] array has been initialized
	if(! cookies_used)
		http_cookies_init();

	int i, x;

	// Loop through every index in [HEADERS] array until [name] is found
	for(i = 0; (i < cookies_size) && (x = strcmp(COOKIES[i].name, name)); i++);

	// Found a matching value for [name]
	if(!x)
		return COOKIES[i].value;

	// Did not find a match
	return 0;
}

// Set and output cookie
void chl_set_cookie(char * name, char * value, char * expires) {
	// If headers have not been printed
	if(! headers_used) {
		// Session cookie
		if(expires == NULL)
			printf("Set-Cookie: %s=%s;\n", name, value);
		else
			printf("Set-Cookie: %s=%s; expires=%s\n", name, value, expires);
	}
}

// Delete cookie
void chl_delete_cookie(char * name) {
	// If headers have not been printed
	if(! headers_used)
		printf("Set-Cookie: %s=; expires=Thu, 01 Jan 1970 00:00:00 GMT\n", name);

}

// Initialize and free objects, called by chl_fcgi_init
void _http_init() {
	headers_size = 0;
	headers_used = 0;
	cookies_used = 0;

	for(int i = 0; i < cookies_size; i++) {
		free(HEADERS[i].name);
		free(HEADERS[i].value);
	}

	cookies_size = 0;

	free(HEADERS);
	free(COOKIES);

	HEADERS = NULL;
	COOKIES = NULL;
	raw_data_cookies = NULL;

}
