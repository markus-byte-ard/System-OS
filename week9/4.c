# include <stdio.h>
# include <stdlib.h>
# include <time.h>
# include <fcntl.h>
# include <sys/file.h>
# include <string.h>
# include <unistd.h>
# include <sys/wait.h>
# include <sys/types.h> 

int main ( int argc, char *argv[], char **envp) {
        pid_t pid;
        int status;

        switch (pid = fork()) {
                case 0:
                        if (strcmp(argv[1], "-")!=0) {
                                int filedes = open(argv[1], O_RDONLY);
                                if (filedes<0) {
                                        perror("open");
                                        exit(1);
                                }

                                dup2(filedes, STDIN_FILENO);
                                close(filedes);
                        } if (strcmp(argv[2], "-")!=0) {
                                /* note that open() could be here too, but fopen() used as an example */
                                FILE *f = fopen(argv[2], "w");
                                if (f==NULL) {
                                        perror("fopen");
                                        exit(1);
                                }
                                dup2(fileno(f), fileno(stdout));
                                fclose(f);
                        } if (execvp(argv[3], argv+3) == -1) {
                                perror("execvp");
                                exit(1);
                        }
                        break;
                default:
                        printf("Child %d was born, waiting...\n", pid);
                        if (wait(&status) == -1) {
                                perror("wait");
                                exit(1);
                        }
                        printf("Child died, status: 0x%X\n", status);
                        break;
        }
}
