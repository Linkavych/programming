// Reading in arbitrary amounts of data and allocating space
#include <stdio.h>
#include <stdlib.h>

// Read a line of arbitrary size from a file
//
// Returns a pointer to the line
// Returns NULL on EOF or error
//
// Caller MUST free() the pointer when done
//
// This example strips the newline; switch to a do-while if needed

char *readline(FILE *fp){

	int offset = 0; //index next char goes in the buffer
	int bufsize = 4; // preferably power of 2 initial size
	char *buf;	// buffer
	int c;		// the character being read in

	buf = malloc(bufsize); // allocate the inital buffer

	if (buf == NULL)
		return NULL;	// Error checking on memory allocation

	// Main loop, reads until newline or EOF
	while (c = fgetc(fp), c != '\n' && c != EOF){
		// Check space available in buffer

		if (offset == bufsize - 1) { //-1 for the NUL terminator
			bufsize *= 2; // increase space x2

			char *new_buf = realloc(buf, bufsize);

			if (new_buf == NULL) {
				free(buf); // on error, free and bail
				return NULL;
			}
			buf = new_buf;
		}

		buf[offset++] = c;	// Add byte to the buffer
	}

	// hit the newline of EOF
	// if at EOF and read no bytes, free buffer and return NULL
	if (c == EOF && offset == 0){
		free(buf);
		return NULL;
	}

	// Shrink buf to fit
	if (offset < bufsize - 1){ // if we're short of the end
		char *new_buf = realloc(buf, offset + 1); // +1 for NUL terminator

		// if success, point to new-buf
		if (new_buf != NULL)
			buf = new_buf;
	}

	// Add the NUL terminator
	buf[offset] = '\0';

	return buf;
}

int main(void){

	FILE *fp = fopen("foo.txt", "r");

	char *line;

	while ((line = readline(fp)) != NULL) {
		printf("%s\n", line);
		free(line);
	}

	fclose(fp);
}
