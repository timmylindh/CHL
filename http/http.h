#ifndef HTTP_H_
#define HTTP_H_

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
