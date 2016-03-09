/*
 * This source file's purpose is to work as an interface between the server and CHL.
 * Contains all the code for interpreting and manipulating CGI environment variables.
 */

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include "cgi.h"

#define GET_DATA_ENV "QUERY_STRING" // GET data environment variable
#define METHOD_POST 1
#define METHOD_GET 0

// A struct to hold CGI [method] data
typedef struct {
	char * name;
	char * value;
} CGI_METHOD_DATA;


CGI_METHOD_DATA * POST; // Struct for CGI POST data, dynamically allocated
CGI_METHOD_DATA * GET; // Struct for CGI GET data, dynamically allocated
char post_size = 0, get_size = 0; // Size of [method] structs

// Buffer for [method] data, dynamically allocated
char * raw_data_post, * raw_data_get;

// Whether [method] has been successfully manipulated or not
char post_used = 0, get_used = 0;

// Function for reading environment variables from server
char * get_env(char * var_name) {
	 char * val;

	 if((val = getenv(var_name)) != NULL)
		 return val;

	 val = "\0";
	 return val;
}

// Function to interpret data sent with the POST method
void method_post_init() {
	if(post_used) // Check if the POST data has already been interpreted
		return;

	// Allocate memory for POST data
	raw_data_post = malloc(CGI_POST_LIM * sizeof(char)); // POST data

	// Assign raw_data_post its value
	fgets(raw_data_post, CGI_POST_LIM, stdin);
	raw_data_post[CGI_POST_LIM] = '\0';

	// Split data into variables, url-decode
	format_data(raw_data_post, METHOD_POST);

	post_used = 1; // Set that POST data is done
}

// Function to interpret data sent with the GET method
void method_get_init() {
	if(get_used) // Check if the GET data has already been interpreted
		return;

	// Allocate memory for GET data
	raw_data_get = malloc(CGI_GET_LIM * sizeof(char)); // GET data

	// Assign raw_data_post its value
	strncpy(raw_data_get, get_env(GET_DATA_ENV), CGI_GET_LIM);
	raw_data_post[CGI_GET_LIM] = '\0';

	// Split data into variables, url-decode
	format_data(raw_data_get, METHOD_GET);

	get_used = 1; // Set that GET data is done
}

// Function for interpreting and splitting [method] data
void format_data(char * data, const char method) {
	char * last_var; // Pointer to last occurrence of '&', or start of string [data]
	char * var_name, * var_value; // Pointer to variable in [data]

	last_var = data;

	// Initialize allocation of memory to [method] struct
	(method == METHOD_POST) ?
			(POST = malloc(sizeof(CGI_METHOD_DATA)))
			: (GET = malloc(sizeof(CGI_METHOD_DATA)));

	// Loop through [data] and interpret the data
	while(*data != '\0') {
		// If variable with '=' character
		if(*data == '=') {
			// Set end of variable name
			*data++ = '\0';

			var_name = last_var;
			var_value = data;

			// Loop to next variable, next occurrence of '&'
			while((*data != '&') && (*data != '\0'))
				data++;

			// Set end of variable value
			(*data == '\0') ? 0 : (*data++ = '\0');

			last_var = data;

			// Decode HTTP URL GET data
			if(method == METHOD_GET) {
				http_url_decode(var_name);
				http_url_decode(var_value);
			}

			// Append variable to method struct
			method_append_var(var_name, var_value, method);
		}

		// If variable without value (without '=' character)
		else if(*data == '&') {
			*data = '\0';

			// Set name, and set value to null
			var_value = data++;
			var_name = last_var;

			last_var = data;

			// Append variable to [method] struct
			method_append_var(var_name, var_value, method);
		}

		// Go on if just a letter
		else
			data++;
	}
}

// Decode HTTP URL GET data
void http_url_decode(char * str) {
	char * decoded; // The final decoded string
	decoded = str;

	// If string is empty
	if(*str == '\0')
		return;

	// Loop through string and interpret characters
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

// Append a variable to [method] array
void method_append_var(char * name, char * value, const char method) {
	switch(method) {
		case METHOD_POST:
			// Allocate memory for new variable
			POST = realloc(POST, ++post_size * sizeof(CGI_METHOD_DATA));

			// Set variable properties
			POST[post_size - 1].name = name;
			POST[post_size - 1].value = value;

			break;

		case METHOD_GET:
			// Allocate memory for new variable
			GET = realloc(GET, ++get_size * sizeof(CGI_METHOD_DATA));

			// Set variable properties
			GET[get_size - 1].name = name;
			GET[get_size - 1].value = value;

			break;
	}
}

// Returns variable [name]'s value in POST data array
char * chl_post(char * name) {
	// Check if POST data array has been initialized
	if(! post_used)
		method_post_init();

	int i, x;

	// Loop through every index in POST data array until [name] is found
	for(i = 0; (i < post_size) && (x = strcmp(POST[i].name, name)); i++);

	// Found a matching value for [name]
	if(!x)
		return POST[i].value;

	// Did not find a match
	return NULL;
}

// Returns variable [name]'s value in GET data array
char * chl_get(char * name) {
	// Check if GET data array has been initialized
	if(! get_used)
		method_get_init();

	int i, x;

	// Loop through every index in GET data array until [name] is found
	for(i = 0; (i < get_size) && (x = strcmp(GET[i].name, name)); i++);

	// Found a matching value for [name]
	if(!x)
		return GET[i].value;

	// Did not find a match
	return NULL;
}

