#ifndef HTTP_H_
#define HTTP_H_

void chl_set_header(char *, char *);
char * chl_get_header(char *);
void chl_print_headers();
void chl_set_default_headers();
void http_cookies_init();
void format_cookies_data();
void cookies_append_var(char *, char *);
char * chl_cookies(char *);
void chl_set_cookie(char *, char *, char *);
void chl_delete_cookie(char *);

#endif

