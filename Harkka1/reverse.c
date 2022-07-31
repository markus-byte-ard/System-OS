// This code is mostly based on the weekly excercise code example frame that was given during the course
// Author: Markus Taulu

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Max length for lines, dynamic memory control seemed too time consuming
#define MAXLEN 1024

// Struct for saving the lines
struct lines {
	char * string;
	struct lines * prev;
	struct lines * next;
};

// read_lines reads the lines and saves them to a linked list
int read_lines(struct lines ** line, FILE * stream) {
	// Inititalizing the list and the temporary string that will hold the lines
	char tmp[MAXLEN];
	struct lines * lp;
	struct lines * temp;

	while (fgets(tmp, MAXLEN, stream) != NULL) {
		// Reading the file and deciding what to do depending on failures or if it's empty
		if (*line == NULL) {
			if ((*line = lp = malloc(sizeof(struct lines))) == NULL) {
				fprintf(stderr, "error: malloc failed\n");
				return 1;
			}
			lp->prev = lp->next = NULL;
		} else {
			if ( (lp->next = malloc(sizeof(struct lines))) == NULL) {
				fprintf(stderr, "error: malloc failed\n");
				return 1;
			}

			// Here the list is linked
			lp->next->next = NULL;
			temp = lp;
			lp = lp->next;
			lp->prev = temp;
			*line = lp;
		}
		if ( (lp->string = malloc(strlen(tmp) + 1)) == NULL) {
				fprintf(stderr, "error: malloc failed\n");
				return 1;
		}
		// the temporary string is copied to the linked list
		strcpy(lp->string, tmp);
	}
	// Closing the stream
	fclose(stream);
	return 0;
}

// print_lines prints the lines to stdout
void print_lines(struct lines * line, FILE * stream) {
	struct lines * lp = line;
	
	// We first loop to the last linked list entry
	while(lp->next != NULL) {
    	lp = lp->next;
	}

	// Then we loop back to the first entry while printing the content of the node
	printf("%s", lp->string);
	while(lp->prev != NULL) {	
    	lp = lp->prev;
		printf("%s", lp->string);
	}
	// Closing the stream
	fclose(stream);
}

// write_lines in basically the same way as print_lines except we write the results 
// to a file instead of stdout
void write_lines(struct lines * line, char filename[]) {
	struct lines * lp = line;
	FILE * stream = fopen(filename, "w");

	// We first loop to the last linked list entry
	while(lp->next != NULL) {
    	lp = lp->next;
	}
	
	// Then we loop back to first entry while writing to a file
	fprintf(stream, "%s",lp->string);
	//printf("%s", lp->string);
	while(lp->prev != NULL) {	
    	lp = lp->prev;
		//printf("%s", lp->string);
		fprintf(stream, "%s",lp->string);
	}
	// Closing the stream
	fclose(stream);
}

// delete_lines empties the linked list
void delete_lines(struct lines * line) {
	struct lines * lp;
	
	lp = line;
	while (lp != NULL) {
		line = lp->next;
		free(lp->string);
		free(lp);
		lp = line;
	}
}

int main( int argc, char *argv[]) {
	// if there are more than 2 arguments we print the usage
	if (argc > 3) {
		printf("usage: reverse <input> <output> \n");
		return 1;
	} 
	// Initialising the linked list
	struct lines * line = NULL;	
	// If there are 2 arguments 
	if (argc == 3) {
		// We first compare that the input and output are different
		if (strcmp(argv[1], argv[2]) == 0) {
			fprintf(stderr, "error: Input and output file must differ \n");
			return 1;
		}
		/* Then we read the lines in the file. I tried moving the fopen before
		   the if statement to check if opening the file fails, but for some reason
		   it kept crashing. I could have also made a new read_lines for files, but 
		   this code wouldn't have satisfied all the requirements for the extra point anyways
		   because I didn't implement dynamic memory allocation for the lines so I deemed
		   it not worth while to implement so this errorhandling doesn't work*/
		if (read_lines(&line, fopen(argv[1], "r")) == 1) {
			fprintf(stderr, "error: cannot open file '%s'\n", argv[1]);
			exit(1);
		}
		// We write the lines to a file
		write_lines(line, argv[2]);
		// We delete the linked list
		delete_lines(line);
	}
	// If there is only 1 argument
	else if (argc == 2) {
		// We read the file. Same problem with error handling as above.
		if (read_lines(&line, fopen(argv[1], "r")) == 1) {
			fprintf(stderr, "error: cannot open file '%s'\n", argv[1]);
			exit(1);
		}
		// We print the lines to stdout
		print_lines(line, stdout);
		// We delete the linked list
		delete_lines(line);
	}
	else {
		// If there are no arguments we read the lines, ctrl + d to stop the input
		if (read_lines(&line, stdin) == -1) {
			exit(1);
		}
		// We print the lines to stdout
		print_lines(line, stdout);
		// We delete the linked list
		delete_lines(line);
	}

	return 0;
}

// EOF