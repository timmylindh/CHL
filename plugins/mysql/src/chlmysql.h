#ifndef CHLMYSQL_H_
#define CHLMYSQL_H_

// Whether to compile as FastCGI
#ifdef _F_CHL_
#include "../../../core/src/fcgi_stdio.h"
#endif

typedef char ** MYSQL_ROW;

// Errors state definitions
#define ERRORS_STATE_TRUE 1
#define ERRORS_STATE_FALSE 0

char chl_mysql_connect(char *, char *, char *, char *);
MYSQL_ROW chl_mysql_next_row();
void chl_mysql_free_result();
char chl_mysql_query(char *);
void chl_mysql_close();
int chl_mysql_num_rows();
void chl_mysql_db(char *);
void chl_mysql_toggle_errors(char);
const char * chl_mysql_error();
void _print_errors();

#endif /* CHLMYSQL_H_ */
