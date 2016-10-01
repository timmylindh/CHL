/*
 * This source file's purpose is to provide functions for opening views and
 * handling inline C functions
 */

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include "error.h"
#include "http.h"
#include "view.h"
#include "inline.h"

#define BUFF_BLOCK_SIZE 2000 // Size per allocation for [buffer]

// Open and interpret view [view_path]
void chl_view(char * view_path) {
	FILE * fd; // File stream to [view_path]
	char * buff; // Buffer to contain file data, dynamically allocated

	// Output headers
	chl_set_default_headers();
	chl_print_headers();

	// Open file [view_path] for reading
	if(! file_read_open(view_path, &fd))
		goto print_error;

	// Read data from file
	if(! file_read_data(&buff, view_path, fd))
		goto print_error;

	// Parse and interpret view
	parse_view(&buff, view_path);

	// Print errors if any
	print_error:
		chl_print_errors();

	free(buff);
	fclose(fd);
}


// Open file [path] for reading
char file_read_open(char * path, FILE ** fd) {
	// Open file for reading
	if((*fd = fopen(path, "r")) != NULL)
		return 1; // Return success

	// Failed to open file, set appropriate error
	switch(errno) {
		// Could not find file
		case EACCES:
		case ENOENT:
		case ENOSPC:
		case ENOTDIR:
			// Append error
			chl_error_append(CHL_E_FILENF, "could not find file '%s'", path);

			break;

		// Opening of file interrupted by signal
		case EINTR:
			chl_error_append(CHL_E_FILEINT, "a signal was caught when trying to open file: '%s'", path);

			break;
	}

	return 0; // Return failure
}

// Read data from file [fd], allocate more memory for [buff] if needed
char file_read_data(char ** buff, char * path, FILE * fd) {
	int iteration = 1; // Number of iterations
	int ntotal = 0; // Total bytes read
	int nread; // Bytes read in one iteration

	 // Allocate memory for [buff]
	*buff = malloc(BUFF_BLOCK_SIZE * sizeof(char));

	// Read data from stdin [BUFF_BLOCK_SIZE] bytes at time, allocate more memory if needed
	while((nread = fread(*buff + ntotal, sizeof(char), BUFF_BLOCK_SIZE, fd)) == BUFF_BLOCK_SIZE) {
		// Limit to [BUFF_BLOCK_SIZE] bytes
		if((++iteration * BUFF_BLOCK_SIZE) >= VIEW_SIZE_LIM) {
			// Error too big file
			chl_error_append(CHL_E_FILESIZE, "file '%s' size exceeded limit %d", path, VIEW_SIZE_LIM);
			return 0;
		}

		// Allocate more memory for buff
		*buff = realloc(*buff, iteration * VIEW_SIZE_LIM);
		ntotal += nread;
	}

	// Null terminate data
	(*buff)[ntotal + nread] = '\0';

	return 1;
}

// Parse and interpret view file [buff]
void parse_view(char ** buff, char * path) {
	int line_nr = 1; // Current line number
	char * output; // Pointer to end of last output index

	output = *buff;

	// Loop through [buff] and interpret data
	while(**buff != '\0') {
		// If new line
		if(**buff == '\n')
			line_nr++;

		// If start of inline code
		else if((**buff == '<') && (*(*buff + 1) == '{')) {
			**buff = '\0'; // End of string before output
			*buff += 2; // Jump to inline code start

			// Output everything before inline code
			fputs(output, stdout);


			// Parse inline code
			if(! parse_inline(buff, path, &line_nr))
				return;

			output = *buff;
		}

		(*buff)++;
	}

	// Output last bytes
	fputs(output, stdout);
}

// Import file [file_path] contents
void chl_import(char * file_path) {
	FILE * fd; // File stream to [view_path]
	char * buff; // Buffer to contain file data, dynamically allocated

	// Open file [view_path] for reading
	if(! file_read_open(file_path, &fd))
		goto print_error;

	// Read data from file
	if(! file_read_data(&buff, file_path, fd))
		goto print_error;

	// Parse and interpret view
	parse_view(&buff, file_path);

	// Print errors if any
	print_error:
		chl_print_errors();

	free(buff);
	fclose(fd);
}

