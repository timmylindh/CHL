#ifndef CGI_H_
#define CGI_H_

#include "../core/types.h"

#define QUERY_NAME_LIM 100
#define QUERY_VALUE_LIM 500
#define POST_LIM 50
#define GET_LIM 50
#define COOKIES_LIM 50

// Initialization states
extern t_STATE post_state;
extern t_STATE get_state;
extern t_STATE cookies_state;

typedef struct {
	char name[QUERY_NAME_LIM];
	char value[QUERY_VALUE_LIM];
} QUERY_ITEM;

// POST and GET arrays
extern QUERY_ITEM POST[POST_LIM];
extern QUERY_ITEM GET[GET_LIM];
extern QUERY_ITEM COOKIES[COOKIES_LIM];

// Current index of POST and GET arrays
extern t_INDEX post_index;
extern t_INDEX get_index;
extern t_INDEX cookies_index;

// Initialize GET data
void init_get();

// Initialize POST data
void init_post();

// Initialize cookies data
void init_cookies();

// Get environment variable
char * get_env(char * var);

#endif /* CGI_H_ */
