#include "io.h"
#include "../core/types.h"
#include "../error/error.h"

#include <stdio.h>
#include <errno.h>
#include <stdlib.h>

// Open file for reading, error handling
// OBS: Not visible to users
static int fopen_read(char * file, FILE ** fp);

// Get all contents of file
char * file_get_all(char * file) {
	FILE * fp;
	char * buff;
	int nread;
	int file_size;

	if(! fopen_read(file, &fp))
		return NULL;

	if((file_size = file_get_size(file)) < 0)
		return NULL;

	buff = malloc(file_size + 1);
	nread = fread(buff, sizeof(char), file_size, fp);

	buff[file_size] = '\0';

	fclose(fp);
	return buff;
}

// Get size of file
int file_get_size(char * file) {
	FILE * fp;
	int size;

	if(! fopen_read(file, &fp))
		return -1;

	fseek(fp, 0L, SEEK_END);
	size = ftell(fp);
	fseek(fp, 0L, SEEK_SET);

	fclose(fp);
	return size;
}

static int fopen_read(char * file, FILE ** fp) {
	if((*fp = fopen(file, "rb")) == NULL) {
		switch(errno) {
			case ENOENT:
				SET_ERROR("File: '%s' not found.", file);
				break;
		}

		return 0;
	}

	return 1;
}
