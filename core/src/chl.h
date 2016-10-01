/*
 * This is the standard header file for CHL.
 * Contains all of the available functions and properties part of the CHL API
 */
#ifndef CHL_H_
#define CHL_H_

// <error.c>

#include <stdio.h>
#include <stdlib.h>

// Only used for macro chl_error_append
void error_append(char, char *);

/*
 * Function for outputting CHL errors
 */
void chl_print_errors();

// Dynamically allocated variable for error string
extern char * _alloce_;

// Macro to dynamically allocate an error string and pass it to error_append
#define chl_error_append(id, ...) snprintf((_alloce_ = malloc(100)), 100, __VA_ARGS__), error_append(id, _alloce_);

// <cgi.c>

/*
 * Function for acquiring HTTP POST data.
 * [name]: a string containing the name of the POST variable
 *
 * Return: 0 if not defined, or POST variable value
 */
char * chl_post(char * name);

/*
 * Function for acquiring HTTP POST data as integer value.
 * [name]: a string containing the name of the POST variable
 *
 * Return: 0 if not defined, -1 if conversion to int failed, or POST variable value
 */
int chl_posti(char * name);

/*
 * Function for acquiring HTTP POST data as float value.
 * [name]: a string containing the name of the POST variable
 *
 * Return: 0 if not defined, -1 if conversion to float failed, or POST variable value
 */
float chl_postf(char * name);

/*
 * Function for acquiring GET data.
 * [name]: a string containing the name of the GET variable
 *
 * Return: 0 if not defined, or GET variable value
 */
char * chl_get(char * name);

/*
 * Function for acquiring GET data as integer value.
 * [name]: a string containing the name of the GET variable
 *
 * Return: 0 if not defined, -1 if conversion to int failed, or GET variable value
 */
int chl_geti(char * name);

/*
 * Function for acquiring GET data as float value.
 * [name]: a string containing the name of the GET variable
 *
 * Return: 0 if not defined, -1 if conversion to float failed, or GET variable value
 */
float chl_getf(char * name);

// <http.c>

/*
 * Function for defining HTTP headers
 * [name]: a string containing the name of the HTTP header, [value]: which value to assign
 */
void chl_set_header(char * name, char * value);

/*
 * Function for acquiring a self-set header
 * [name]: a string containing the name of the HTTP header
 *
 * Return: 0 if not defined, or header value
 */
char * chl_get_header(char * name);

/*
 * Function for outputting headers
 */
void chl_print_headers();

/*
 * Function for setting default headers
 */
void chl_set_default_headers();

/*
 * Function for acquiring HTTP cookies data
 * [name]: a string containing the name of the HTTP cookie
 *
 * Return: 0 if not defined, or cookie value
 */
char * chl_cookies(char * name);

/*
 * Function for creating  HTTP cookies
 * [name]: a string containing the name of the HTTP cookie, [value]: which value to assign, [expires]: lifetime of cookie in format: Wdy, DD-Mon-YYYY HH:MM:SS GMT
 */
void chl_set_cookie(char * name, char * value, char * expires);

/*
 * Function for deleting  HTTP cookies
 * [name]: a string containing the name of the HTTP cookie
 */
void chl_delete_cookie(char * name);



// <view.c>

/*
 * Function for opening a CHL view file
 * Also outputs headers
 * [path]: path to file
 */
void chl_view(char * path);

/*
 * Function for acquiring contents of files
 * [name]: path to file
 */
void chl_import(char * path);




// <inline.c>


/*
 * Function for appending CHL function so it can be executed through inline CHL code
 * [name]: which function name to set, [function]: pointer to a function returning void and taking a char pointer as argument
 */
void chl_func_append(char * name, void (* function)(char *));

/*
 * Function for executing CHL functions
 * [name]: name of function, [args]: arguments passed to function
 *
 * Return: 0 if function not found, or >0 if found
 */
char chl_func(char * name, char * args);

/*
 * Function for acquiring next argument of function
 * [args]: the char pointer argument to CHL function
 *
 * Return: 0 if no arguments left, or argument data
 */
char * chl_next_arg(char * args);

/*
 * Function for acquiring next argument of function as integer value
 * [args]: the char pointer argument to CHL function
 *
 * Return: 0 if no arguments left, -1 if conversion to int failed, or argument data
 */
int chl_next_argi(char * args);

/*
 * Function for acquiring next argument of function as float value
 * [args]: the char pointer argument to CHL function
 *
 * Return: 0 if no arguments left, -1 if conversion to float failed, or argument data
 */
float chl_next_argf(char * args);

/*
 * Function for acquiring all arguments of a function
 * [arguments]: the address of a char ** variable. Will contain all arguments. [args]: the char pointer argument to CHL function
 */
char chl_get_args(char *(** arguments), char * args);

// <fastcgi.c>

/*
 * Function for calling init methods of other source files to work with FastCGI
 */
void chl_fcgi_init();

/*
 * Function for accepting next client using FastCGI
 * Should be called in a loop by caller
 *
 * Return: 1 if pending client, 0 if an error accoured
 */
int chl_fcgi_next();

#endif /* CHL_H_ */
