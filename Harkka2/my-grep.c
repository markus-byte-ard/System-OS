// Perustaa suurimmaksi osalta Project 1, mutta yksinkertaistettuna sekä miten käyttää strstr osoitteesta:
// https://www.delftstack.com/howto/c/string-contains-in-c/#use-the-strstr-function-to-check-if-a-string-contains-a-substring-in-c
// Author: Markus Taulu

# include <stdio.h>
# include <stdlib.h>
# include <string.h>

int main ( int argc, char *argv[]) {
	// First we check if there is at least one argument
    if (argc < 2) {
		printf("my-grep: searchterm [file ...]\n");
		exit(1);
	} else if (argc == 2) {
		// If there are 2 arguments we read the standard input
        char temp[1024];
        char *compare;
		// While loop to compare lines that are not empty
        while (fgets(temp, 1024, stdin) != NULL) {
            // strstr return NULL if substring was not found
            compare = strstr(temp, argv[1]);
            if (compare) {
				// If substring was found on the line we print the whole line
                printf("%s", temp);
            }  	
   		}

    } else {
		// If there are more than 1 argument we are readin all given files
		FILE * file;
		int i = 2;
		char temp[1024];
        char *compare;
		// While loop to go through all files given
		while (i < argc) {
			printf("File %d: %s\n", i-1, argv[i]);
            printf("Looking for: %s\n", argv[1]);
			printf("\n");
			// Opening the file
			file = fopen(argv[i], "r");
			// Error handling
			if (file == NULL) {
				fprintf(stderr, "my-grep: cannot open file '%s'\n", argv[i]);
				exit(0);
			}
			printf("**************BOF**************\n");
			// Same as above 
			while (fgets(temp, 1024, file) != NULL) {
                compare = strstr(temp, argv[1]);
                if (compare) {
                    printf("%s", temp);
                }
			  	
   			}
   			printf("**************EOF**************\n");
   			printf("\n");
			// Closing the file
			fclose(file);
			// Starting the next argument
			i++;
		}	
	}
	return 0;
}

// EOF