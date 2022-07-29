# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

int main ( int argc, char *argv[], char **envp) {
	if (argc > 2) {
		execvp(argv[1], argv+1);
		printf("STOP\n");
	} else {
		printf("Expected at least two arguments !");
	}
	return 0;
}
