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
#define METHOD_POST_NREAD 2000 // POST data bytes per interation limit

// A struct to hold CGI [method] data
typedef struct {
	char * name;
	char * value;
} CGI_METHOD_DATA;


static CGI_METHOD_DATA * POST; // Struct array for CGI POST data, dynamically allocated
static CGI_METHOD_DATA * GET; // Struct array for CGI GET data, dynamically allocated
static unsigned char post_size = 0, get_size = 0; // Size of [method] structs

// Buffer for [method] data, dynamically allocated
static char * raw_data_post, * raw_data_get;

// Whether [method] has been successfully manipulated or not
static char post_used = 0, get_used = 0;

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
	raw_data_post = malloc(METHOD_POST_NREAD * sizeof(char)); // POST data

	//Append temporary blank variable to POST array to prevent NULL error, overwritten
	method_append_var(" ", " ", METHOD_POST);

	// Assign raw_data_post its value
	method_post_read_input();

	// Split data into variables, url-decode
	format_data(raw_data_post, METHOD_POST);

	post_used = 1; // Set that POST data is done
}

// Function to interpret data sent with the GET method
void method_get_init() {
	if(get_used) // Check if the GET data has already been interpreted
		return;

	// Append temporary blank variable to GET array to prevent NULL error, overwritten
	method_append_var(" ", " ", METHOD_GET);

	// Assign [raw_data_get] its value
	raw_data_get = get_env(GET_DATA_ENV);

	// Split data into variables, url-decode
	format_data(raw_data_get, METHOD_GET);

	get_used = 1; // Set that GET data is done
}

// Function for interpreting and splitting [method] data
void format_data(char * data, const char method) {
	char * last_var; // Pointer to last occurrence of '&', or start of string [data]
	char * var_name, * var_value; // Pointer to variable in [data]

	last_var = data;
	var_name = data;

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

			// Decode HTTP data
			http_form_decode(var_name);
			http_form_decode(var_value);

			// Append variable to method struct
			method_append_var(var_name, var_value, method);
		}

		// If variable without value (without '=' character)
		else if(*data == '&') {
			*data = '\0';

			// Set name, and set value to null
			var_value = data;
			var_name = last_var;

			last_var = ++data;

			// Append variable to [method] struct
			method_append_var(var_name, var_value, method);
		}

		// Go on if just a letter
		else
			data++;
	}

	// A variable only defined with a variable name, and without '='
	if(var_name == last_var) {
		var_value = data;
		method_append_var(var_name, var_value, method);
	}
}

// Decode HTTP FORM data
void http_form_decode(char * str) {
	char * decoded; // The final decoded string
	decoded = str;

	// If string is empty
	if(*str == '\0')
		return;

	// Loop through string and interpret characters
	while(*str != '\0') {
		if(*str == '+') {
			*decoded++ = ' ';
			str++;
		}

		else if((*str == '%') && (isxdigit(str[1]) && isxdigit(str[2]))) {
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
	// Prevent char overflow, a greater number than 512
	if((post_size >= 510) || (get_size >= 510))
		return;

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
	return 0;
}

// Returns variable [name]'s value in POST data array as integer
int chl_posti(char * name) {
	char * val;
	int ret;

	// Check if POST index exists
	if(! (val = chl_post(name)))
		return 0;

	// Convert to int, return -1 if conversion could not be done
	if(! (ret = (int) strtol(val, NULL, 10)))
		return -1;

	// Did not find a match
	return ret;
}

// Returns variable [name]'s value in POST data array as float
float chl_postf(char * name) {
	char * val;
	float ret;

	// Check if POST index exists
	if(! (val = chl_post(name)))
		return 0;

	// Convert to float, return -1 if conversion could not be done
	if(! (ret =  strtof(val, NULL)))
		return -1;

	// Did not find a match
	return ret;
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
	return 0;
}

// Returns variable [name]'s value in GET data array as integer
int chl_geti(char * name) {
	char * val;
	int ret;

	// Check if GET index exists
	if(! (val = chl_post(name)))
		return 0;

	// Convert to int, return -1 if conversion could not be done
	if(! (ret = (int) strtol(val, NULL, 10)))
		return -1;

	// Did not find a match
	return ret;
}

// Returns variable [name]'s value in GET data array as float
float chl_getf(char * name) {
	char * val;
	float ret;

	// Check if POST index exists
	if(! (val = chl_post(name)))
		return 0;

	// Convert to float, return -1 if conversion could not be done
	if(! (ret =  strtof(val, NULL)))
		return -1;

	// Did not find a match
	return ret;
}

// Read POST data from stdin
void method_post_read_input() {
	int ntotal = 0; // Total bytes read
	int nread; // Bytes read in one iteration
	int iteration = 1; // Number of iterations

	// Read data from stdin [METHOD_POST_NREAD] bytes at time, allocate more memory if needed
	while((nread = fread(raw_data_post + ntotal, sizeof(char), METHOD_POST_NREAD, stdin)) == METHOD_POST_NREAD) {
		// Limit to CGI_POST_LIM bytes
		if((++iteration * METHOD_POST_NREAD) >= CGI_POST_LIM)
			return;

		// Allocate more memory for POST data
		raw_data_post = realloc(raw_data_post, iteration * METHOD_POST_NREAD);
		ntotal += nread;
	}

	// Null terminate data
	raw_data_post[ntotal + nread] = '\0';
}

