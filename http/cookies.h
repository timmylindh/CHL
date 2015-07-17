#ifndef COOKIES_H_
#define COOKIES_H

#define COOKIE_VALUE_LIM (HEADER_VALUE_LIM - 1)

// Set cookie, leave [expires] to NULL for session lifetime
void set_cookie(char * name, char * value, char * expires);

// Get cookie
char * cookies(char * name);

// Remove cookie
void remove_cookie(char * name);

#endif /* COOKIES_H_ */
