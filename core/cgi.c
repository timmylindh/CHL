#include "cgi.h"
#include "../error/error.h"
#include "../core/types.h"
#include "../http/http.h"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>

#define GET_DATA_LIM (QUERY_NAME_LIM + QUERY_VALUE_LIM) * GET_LIM
#define POST_DATA_LIM (QUERY_NAME_LIM + QUERY_VALUE_LIM) * POST_LIM
#define COOKIES_DATA_LIM (QUERY_NAME_LIM + QUERY_VALUE_LIM) * COOKIES_LIM
#define METHOD_POST 1
#define METHOD_GET 2
#define METHOD_COOKIES 3

QUERY_ITEM POST[POST_LIM];
QUERY_ITEM GET[GET_LIM];
QUERY_ITEM COOKIES[COOKIES_LIM];

t_INDEX post_index = 0;
t_INDEX get_index = 0;
t_INDEX cookies_index = 0;
t_STATE post_state = 0;
t_STATE get_state = 0;
t_STATE cookies_state = 0;

static void set_query_item(char * str, short method);

void init_get() {
	char get_data[GET_DATA_LIM] = {0};
	char * get;
	char * token;

	// Needed for strtok_r to suppress error
	get = get_data;

	strncpy(get_data, get_env("QUERY_STRING"), GET_DATA_LIM);
	((token = strtok_r(get, "&", &get)) == NULL) ? (token = get) : 0;

	do {
		set_query_item(token, METHOD_GET);
		token = strtok_r(NULL, "&", &get);
	}
	while(token != NULL);

	get_state++;
}

// Initialize post array
void init_post() {
	char post_data[POST_DATA_LIM] = {0};
	char * post;
	char * token;

	// Needed for strtok_r to suppress error
	post = post_data;

	fgets(post_data, POST_DATA_LIM, stdin);
	((token = strtok_r(post, "&", &post)) == NULL) ? (token = post) : 0;

	do {
		set_query_item(token, METHOD_POST);
		token = strtok_r(NULL, "&", &post);
	}
	while(token != NULL);

	post_state++;
}

// Initialize cookies array
void init_cookies() {
	char cookies_data[COOKIES_DATA_LIM];
	char * cookies;
	char * token;

	cookies = cookies_data;

	strncpy(cookies_data, get_env("HTTP_COOKIE"), COOKIES_DATA_LIM);
	((token = strtok_r(cookies, ";", &cookies)) == NULL) ? (token = cookies) : 0;

	do {
		set_query_item(token, METHOD_COOKIES);
		token = strtok_r(NULL, ";", &cookies);
	}
	while(token != NULL);

	cookies_state++;
}

// Add element to array of method
static void set_query_item(char * str, short method) {
	char * name;
	char * value;
	char * name_pt;
	char * value_pt;

	name = strtok(str, "=");
	if((value = strtok(NULL, "=")) == NULL)
		value = "\0";

	if(strlen(str) == 0)
		return;

	if(get_index > GET_LIM) {
		set_errno(ERRNO_GET_OVERFLOW, NULL);
		return;
	}

	if(post_index > POST_LIM) {
		set_errno(ERRNO_POST_OVERFLOW, NULL);
		return;
	}

	url_decode(name);
	url_decode(value);

	switch(method) {
		case METHOD_GET:
			name_pt = GET[get_index].name;
			value_pt = GET[get_index++].value;

			break;

		case METHOD_POST:
			name_pt = POST[post_index].name;
			value_pt = POST[post_index++].value;

			break;

		case METHOD_COOKIES:
			// Remove spaces
			while(*name == ' ')
				name++;

			name_pt = COOKIES[cookies_index].name;
			value_pt = COOKIES[cookies_index++].value;

			break;
	}

	strncpy(name_pt, name, QUERY_NAME_LIM);
	strncpy(value_pt, value, QUERY_VALUE_LIM);
}

// Get environment variable
char * get_env(char * var) {
	char * val;

	if((val = getenv(var)) != NULL)
		return val;

	val = "\0";
	return val;
}

