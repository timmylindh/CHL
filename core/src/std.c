/*
 * This source file's purpose is to provide important shared functions for
 * other source files.
 */

#include <stdlib.h>
#include <unistd.h>

#define SLEEP_INTERVAL_TIME 1000
#define SLEEP_INTERVAL_MULTI_LIM 10

// malloc with proper error handling
void * std_malloc(size_t size) {
	void * mem;
	char inter_multi = 1;

	while((mem = malloc(size)) == NULL) {
		if(inter_multi > SLEEP_INTERVAL_MULTI_LIM)
			exit(-1);

		sleep(SLEEP_INTERVAL_TIME * inter_multi++);
	}

	return mem;
}

// realloc with proper error handling
void * std_realloc(void * ptr, size_t newsize) {
	void * mem;
	char inter_multi = 1;

	while((mem = realloc(ptr, newsize)) == NULL) {
		if(inter_multi > SLEEP_INTERVAL_MULTI_LIM)
			exit(-1);

		sleep(SLEEP_INTERVAL_TIME * inter_multi++);
	}

	return mem;
}


