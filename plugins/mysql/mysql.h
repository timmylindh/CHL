/*
 * This is the standard header file for CHL MySQL library
 * Contains all of the available functions and properties part of the CHL MySQL API
 * Built on top of standard MySQL C connector library
 */
#ifndef MYSQL_H_
#define MYSQL_H_

// Used for fetching MySQL data
typedef char ** MYSQL_ROW;

// Errors state definitions
#define ERRORS_STATE_TRUE 1
#define ERRORS_STATE_FALSE 0

// chlmysql.c

/*
 * Function for connection to MySQL server.
 * [host]: server host
 * [username]: mysql username
 * [password]: myqsl password
 * [database]: mysql database, leave NULL if none
 *
 * Return: 1 if successful, 0 on error
 */
char chl_mysql_connect(char * host, char * username, char * password, char * database);

/*
 * Function for issuing a MySQL query.
 * [query]: the query
 *
 * Return: 1 if successful, 0 on error
 */
char chl_mysql_query(char * query);

/*
 * Function for fetching the next row after issuing a fetch query
 *
 * Return: the row if successful, 0 if no rows left or on error
 */
MYSQL_ROW chl_mysql_next_row();

/*
 * Function for freeing MySQL result data, should be called in the end every time you fetch
 * something from the database
 */
void chl_mysql_free_result();

/*
 * Function for fetching the amount of rows in a MySQL result after a fetch query.
 *
 * Return: number of rows
 */
int chl_mysql_num_rows();

/*
 * Function for selecting MySQL database
 * [database]: database name
 */
void chl_mysql_db(char * database);

/*
 * Function for closing the MySQL connection. Should be called when you are done
 * with the MySQL server.
 */
void chl_mysql_close();

/*
 * Function to toggle whether to turn on or off automatic MySQL error printing
 * [state]: ERRORS_STATE_TRUE | ERRORS_STATE_FALSE
 */
void chl_mysql_toggle_errors(char state);

/*
 * Function to acquire MySQL error message
 *
 * Return: a string of the error message
 */
const char * chl_mysql_error();

#endif /* MYSQL_H_ */
