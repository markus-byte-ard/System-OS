#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXLEN 1024

struct lines {
	char * string;
	struct lines * prev;
	struct lines * next;
};

int read_lines(struct lines ** line, FILE * stream) {
	char tmp[MAXLEN];
	struct lines * lp;
	struct lines * temp;
	
	while (fgets(tmp, MAXLEN, stream) != NULL) {
		
		if (*line == NULL) {
			if ((*line = lp = malloc(sizeof(struct lines))) == NULL) {
				fprintf(stderr, "ERROR: could not allocate memory\n");
				return -1;
			}
			lp->prev = lp->next = NULL;
		} else {
			if ( (lp->next = malloc(sizeof(struct lines))) == NULL) {
				fprintf(stderr, "ERROR: could not allocate memory\n");
				return -1;
			}

			/* Here you should insert the lines that link the list correctly */

			lp->next->next = NULL;
			temp = lp;
			lp = lp->next;
			lp->prev = temp;
			*line = lp;
		}
		if ( (lp->string = malloc(strlen(tmp) + 1)) == NULL) {
				fprintf(stderr, "ERROR: could not allocate memory\n");
				return -1;
		}
		strcpy(lp->string, tmp);
	}
	
	return 0;
}

void print_lines(struct lines * line, FILE * stream) {
	struct lines * lp = line;
	
	/* Here you should implement a loop that prints the lines in reverse order. 	*/
	/* First you need to follow the links from the first node to the last node.	*/ 	

	while(lp->next != NULL) {
    	lp = lp->next;
	}
	printf("%s", lp->string);
	while(lp->prev != NULL) {	
    	lp = lp->prev;
		printf("%s", lp->string);
	}
}

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

int main(void) {
	struct lines * line = NULL;
	
	if (read_lines(&line, stdin) == -1)
		exit(1);
	print_lines(line, stdout);
	delete_lines(line);
	
	return 0;
}
