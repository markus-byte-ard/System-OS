// This is based on my Project 1 only simplified
// Author: Markus Taulu

# include <stdio.h>
# include <stdlib.h>

int main ( int argc, char *argv[]) {
	// First we check that there is at least one argument
	if (argc < 2) {
		printf("Expected at least one argument !\n");
		exit(0);
	} else {
		// Initializing
		FILE * file;
		int i = 1;
		// String size set to 100 could be bigger
		char temp[100];
		// While loop to read all given arguments
		while (i < argc) {
			printf("File %d: %s\r\n", i, argv[i]);
			printf("\n");
			// Opening the file
			file = fopen(argv[i], "r");
			// Error handling
			if (file == NULL) {
				fprintf(stderr, "my-cat: cannot open file '%s'\n", argv[i]);
				exit(1);
			}
			printf("**************BOF**************\n");
			// While loop to read all lines
			while (fgets(temp, 100, file) != NULL) {
			  	/* writing content to stdout */
			  	printf("%s", temp);
   			}
   			printf("**************EOF**************\n");
   			printf("\n");
			// Closing the file
			fclose(file);
			// Next argument
			i++;
		}	
	}
	return 0;
}

// EOF