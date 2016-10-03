/*
 * This source file's purpose is to provide an interface for the standard MySQL API
 */

#include <stdio.h>
#include "../../../core/src/error.h"
#include "chlmysql.h"
#include "mysql.h"

static MYSQL * con; // MySQL connection struct
static MYSQL_RES * sql_result = NULL; // MySQL result
static MYSQL_ROW sql_row = NULL;
static char errors_state = ERRORS_STATE_TRUE; // Whether to output errors or not

// Connect to mysql server
char chl_mysql_connect(char * host, char * username, char * password, char * database) {
	// Create MySQL struct
	if((con = mysql_init(NULL)) == NULL) {
		if(errors_state)
			_print_errors();

		return 0;
	}

	// Connect to MySQL server
	if(mysql_real_connect(con, host, username, password, database, 0, NULL, 0) == NULL) {
		if(errors_state)
			_print_errors();

		return 0;
	}

	return 1;
}

// Issue a MySQL query
char chl_mysql_query(char * query) {
	if(mysql_query(con, query)) {
		if(errors_state)
			_print_errors();

		return 0;
	}

	return 1;
}

// Check if there is a mysql row available, run in a loop by caller
MYSQL_ROW chl_mysql_next_row() {
	// If no result has been acquired
	if(sql_result == NULL) {
		// Fetch result
		if((sql_result = mysql_store_result(con)) == NULL) {
			if(errors_state)
				_print_errors();

			chl_mysql_free_result();
			return 0;
		}
	}

	// Check if no rows left, fetch row if there are rows left
	if(! (sql_row = mysql_fetch_row(sql_result))) {
		chl_mysql_free_result(); // End reached, free result
		return 0;
	}

	return sql_row;
}

// Free and reset result
void chl_mysql_free_result() {
	mysql_free_result(sql_result);
	sql_result = NULL;
	sql_row = NULL;
}

// Return number of rows in result
int chl_mysql_num_rows() {
	// Fetch result if not already fetched
	if(sql_result == NULL)
	if((sql_result = mysql_store_result(con)) == NULL) {
		if(errors_state)
			_print_errors();

		chl_mysql_free_result();
		return 0;
	}

	return mysql_num_rows(sql_result);
}

// Select MySQL database
void chl_mysql_db(char * database) {
	mysql_select_db(con, database);
}

// Disconnect from mysql server
void chl_mysql_close() {
	mysql_close(con);
}

// Turn on or off automatic output of errors
void chl_mysql_toggle_errors(char state) {
	errors_state = state;
}

// Return mysql error message
const char * chl_mysql_error() {
	return mysql_error(con);
}

// Print errors wrapper function
void _print_errors() {
	chl_error_append(CHL_E_MYSQL, "%s", mysql_error(con));
	chl_print_errors();
}
