#include "cgi.h"
#include "http.h"
#include "view.h"
#include "inline.h"
#include <stdio.h>
#include <string.h>

char * login_status = "You are currently not logged in.";

void get_var(char * args) {
	if(! strcmp(args, "title"))
		(chl_cookies("logged_in")) ? fputs("CHL 2.0 | Administrator page", stdout) : fputs("CHL 2.0 | Login page", stdout);

	else if(! strcmp(args, "status"))
		fputs(login_status, stdout);

	else if(! strcmp(args, "button"))
		(chl_cookies("logged_in")) ? fputs("Logout", stdout) : fputs("Login", stdout);

}

int main() {
	chl_func_append("get_var", get_var);

	if(chl_cookies("logged_in"))
		login_status = "You are now logged in.";

	if(chl_post("Login")) {
		if(!strcmp(chl_post("username"), "admin") && !strcmp(chl_post("password"), "123")) {
			login_status = "You are now logged in.";
			chl_set_cookie("logged_in", "10", NULL);
		}

		else {
			login_status = "Incorrect username or password.";
		}
	}

	else if(chl_post("Logout"))
		chl_delete_cookie("logged_in");

	chl_view("view.vw");

	return 0;
}
