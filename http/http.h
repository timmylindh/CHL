#ifndef HTTP_H_
#define HTTP_H_

#include "cookies.h"

#define HEADER_HEADER_LIM 30
#define HEADER_VALUE_LIM 100
#define HEADERS_LIM 10

// Output headers
void headers();

// Initialize standard headers
void headers_init();

// Set header value
void set_header(char * header, char * value);

// Set header, create a new one if already exists
void set_header_new(char * header, char * value);

// Get header value
char * get_header(char * header);

// Decode URL format
void url_decode(char * str);

// Convert string to hex
int strtohex(char * str);

// Get data from POST array
char * post(char * name);

// Get data from GET array
char * get(char * name);

// Get number of elements in GET array
int get_size();

// Get number of elements in POST array
int post_size();

#endif /* HTTP_H_ */
