//1)Write a C program to find whether a given file is present in current directory or not.

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
int main(int argc, char *argv[]) {
 if (argc != 2) {
 fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
 exit(EXIT_FAILURE);
 }
 const char *filename = argv[1];
 if (access(filename, F_OK) == 0) {
 printf("The file '%s' is present in the current directory.\n", filename);
 } else {
 printf("The file '%s' is not present in the current directory.\n", filename);
 }
 return 0;
}

//2)Write a C program to Identify the type (Directory, character device, Block device, Regular file,
//FIFO or pipe, symbolic link or socket) of given file using stat() system call.

#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        return EXIT_FAILURE;
    }

    struct stat file_info;
    if (stat(argv[1], &file_info) == -1) {
        perror("stat");
        return EXIT_FAILURE;
    }

    const char *file_type = "unknown";
    if (S_ISREG(file_info.st_mode)) file_type = "regular file";
    else if (S_ISDIR(file_info.st_mode)) file_type = "directory";
    else if (S_ISLNK(file_info.st_mode)) file_type = "symbolic link";
    else if (S_ISFIFO(file_info.st_mode)) file_type = "named pipe (FIFO)";
    else if (S_ISSOCK(file_info.st_mode)) file_type = "socket";
    else if (S_ISCHR(file_info.st_mode)) file_type = "character special file";
    else if (S_ISBLK(file_info.st_mode)) file_type = "block special file";

    printf("%s is a %s.\n", argv[1], file_type);
    return 0;
}

