// how to list env
// https://stackoverflow.com/questions/2085302/printing-all-environment-variables-in-c-c

#include <stdio.h>

int main( int argc, char *argv[], char **envp )  {

	if (argc < 2 ) {
   		printf("Expected at least one argument!\r\n");
	} else {
		int i = 1;
		while (i < argc) {
			printf("Argument %d: %s\r\n", i, argv[i]);
			i++;
		}
		for (char **env = envp; *env != 0; env++) {
    		char *thisEnv = *env;
    		printf("%s\n", thisEnv);    
 		 }
	
	}
	return 0;
}
