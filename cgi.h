#ifndef CGI_H_
#define CGI_H_

#define CGI_POST_LIM 100000 // CGI POST data limit
#define CGI_GET_LIM 1000 // CGI GET data limit

char * get_env(char *);
void method_post_init();
void method_get_init();
void format_data(char *, const char);
void http_url_decode(char *);
void method_append_var(char *, char *, const char);
char * chl_post(char *);
char * chl_get(char *);

#endif /* CGI_H_ */
