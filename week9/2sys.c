# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

int main ( int argc, char *argv[], char **envp) {
	char str[150];
	int i;
	if (argc > 2) {
		strcpy(str, argv[1]);
		for (i=2; i<argc; i++) {
			strcat(str, " ");
			strcat(str, argv[i]);
		}
		printf("Tämä on string: %s\n", str);
		printf("STOP\n");
		system(str);
	} else {
		printf("Expected at least two arguments !");
	}
	return 0;
}
