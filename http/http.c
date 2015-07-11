#include "http.h"

#include <stdlib.h>
#include <ctype.h>

// Decode URL
void url_decode(char * str) {
	char * decoded;
	decoded = str;

	if(*str == '\0')
		return;

	while(*str != '\0') {
		if((*str == '%') && (isxdigit(str[1]) && isxdigit(str[2]))) {
			{
				if(str[1] >= 'a')
					str[1] -= ('a' - 'A');
				else if(str[1] >= 'A')
					str[1] -= ('A' - 10);
				else
					str[1] -= '0';
			}

			{
				if(str[2] >= 'a')
					str[2] -= ('a' - 'A');
				else if(str[2] >= 'A')
					str[2] -= ('A' - 10);
				else
					str[2] -= '0';
			}

			*decoded++ = (16 * str[1]) + str[2];
			str += 3;
		}

		else
			*decoded++ = *str++;
	}

	*decoded++ = '\0';
}

// Convert string to hex form
int strtohex(char * str) {
	char * pt;
	return (int) strtol(str, &pt, 16);
}


