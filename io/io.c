#include "io.h"
#include "../types.h"
#include "../error/error.h"

#include <stdio.h>
#include <errno.h>

// Open file for reading, error handling
// OBS: Not visible to users
static int fopen_read(char * file, FILE ** fp);

int file_get_all(char * file, char * buff, int buff_size) {
	FILE * fp;
	int nread;

	if(! fopen_read(file, &fp))
		return 0;

	nread = fread(buff, sizeof(char), buff_size, fp);
	buff[nread] = '\0';

	fclose(fp);
	return 1;
}

static int fopen_read(char * file, FILE ** fp) {
	if((*fp = fopen(file, "r")) == NULL) {
		switch(errno) {
			case ENOENT:
				set_errno(ERRNO_FILE_NOT_FOUND, file);
				break;
		}

		return 0;
	}

	return 1;
}
