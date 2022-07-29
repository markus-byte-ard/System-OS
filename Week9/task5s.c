#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include <time.h>
#include <errno.h>

#define MAXPATH 256

int list_dir(char * dir, int rec) {
	DIR * dirp;
	char path[MAXPATH];
	struct dirent *direntp;
	struct stat st;
	
	/* Here you should open the directory indicated by the given path */
	/* check functions opendir */
	if ((dirp = opendir(dir)) == NULL) {
		perror("opendir() error");
	} else {
		printf("Content of the current folder:\r\n");
		while ((direntp = readdir(dirp)) != NULL) {
			stat(direntp->d_name, &st);
			if (S_ISDIR(st.st_mode) != 0 && (strcmp(direntp->d_name, "..")) != 0 && (strcmp(direntp->d_name, ".")) != 0 && rec == 1) {
				printf("Opening directory: %s \r\n", direntp->d_name);
				strcpy(path, dir);
				strcat(path, "/");
				strcat(path, direntp->d_name);
				list_dir(path, rec);
			} 
      		printf("Name: %s	Links: %ld	Size: %ld	AccessPermissions: %d	LastModified: %ld \r\n", direntp->d_name, st.st_nlink, st.st_size, st.st_mode, st.st_mtime);
		} 
    } if (closedir(dirp) == -1) {
		perror(dir);
		return -1;
	}
	return 0;
}

int main(int argc, char * * argv) {
	int i = 1, rec = 0;
	
	if (argc > 1) {
		if (strcmp(argv[i], "-r") == 0) {
			rec = 1;
			i++;
		}
	}	
	while (i < argc) {
		if (list_dir(argv[i], rec) == -1) exit(1);
		i++;
	}
		
	return 0;
}
