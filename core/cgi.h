#ifndef CGI_H_
#define CGI_H_

#define QUERY_NAME_LIM 100
#define QUERY_VALUE_LIM 500
#define POST_LIM 50
#define GET_LIM 50

// Host struct
typedef struct {
	char * SERVER;
	char * PORT;
	char * NAME;
	char * EMAIL;
	char * SCRIPT_PATH;
	char * SCRIPT_REL_PATH;
	char * SYS_PATH;
	char * ROOT;
} Host;

// Request struct
typedef struct {
	char * HOST;
	char * REFERER;
	char * USER_AGENT;
	char * HTTPS;
	char * IP;
	char * PORT;
	char * USERNAME;
	char * METHOD;
	char * URI;
} Request;

extern Host _host;
extern Request _request;

// Initialize CGI and format data passed from server
void cgi_init();

#endif /* CGI_H_ */
