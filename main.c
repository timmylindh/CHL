/*
 * main.c
 *
 *  Created on: 8 mar 2016
 *      Author: timmy
 */

#include "cgi.h"
#include <stdio.h>

int main() {
	puts(chl_post("username"));
	puts(chl_post("password"));

	return 0;
}
