#ifndef CGI_H_
#define CGI_H_

#define CGI_POST_LIM 100000 // CGI POST data limit
#define CGI_GET_LIM 1000 // Not used, see environment variable limit

char * get_env(char *);
void method_post_init();
void method_get_init();
void format_data(char *, const char);
void http_form_decode(char *);
void method_append_var(char *, char *, const char);
char * chl_post(char *);
int chl_posti(char *);
float chl_postf(char *);
char * chl_get(char *);
int chl_geti(char *);
float chl_getf(char *);
void method_post_read_input();

#endif /* CGI_H_ */
