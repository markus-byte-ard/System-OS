# include <stdio.h>
# include <stdlib.h>
# include <time.h>
# include <fcntl.h>
# include <sys/file.h>

int main ( int argc, char *argv[], char **envp) {
    time_t t;
    pid_t pid;

	if (argc < 2) {
		printf("Expected at least one argument !");
	} else {
		// Opening the file
		int fd = open(argv[1], O_RDWR);
		    if(fd == -1) {
		    	printf("Unable to open the file\n");
		        exit(1);
		    } else {
		    	// Locking the file and printing
		    	time(&t);
				printf("pid: %3d, getting exclusive lock at %s\n", pid, ctime(&t));
				flock(fd, LOCK_EX);
				time(&t);
				printf("pid: %4d, exclusive locked at %s\n", pid, ctime(&t));
				sleep(20);
				
				// Unlocking 
				flock(fd, LOCK_UN);
				time(&t);
				printf("pid: %4d, unlocked at %s\n", pid, ctime(&t));  
		    }
    }
	return 0;
}
