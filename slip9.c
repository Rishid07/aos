//1)Generate parent process to write unnamed pipe and will read from it

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

int main() {
    int fd[2];  // Array to store the file descriptors for the pipe
    pid_t pid;
    char write_msg[] = "Hello from parent!";
    char read_msg[100];

    // Create an unnamed pipe
    if (pipe(fd) == -1) {
        perror("pipe");
        exit(1);
    }

    // Fork a child process
    pid = fork();
    if (pid < 0) {
        perror("fork");
        exit(1);
    }

    if (pid > 0) {
        // Parent process

        // Close the unused read end of the pipe
        close(fd[0]);

        // Write to the pipe
        printf("Parent: Writing to pipe\n");
        write(fd[1], write_msg, strlen(write_msg) + 1);

        // Close the write end of the pipe after writing
        close(fd[1]);

        // Wait for the child to finish
        wait(NULL);

        // Open the read end of the pipe to read the message from child
        // In this example, we're assuming the child writes something to the pipe
        // (the child writes "Hello from child!")
        close(fd[1]);  // Close the write end in parent
        read(fd[0], read_msg, sizeof(read_msg));
        printf("Parent: Read from pipe: %s\n", read_msg);

        // Close the read end of the pipe
        close(fd[0]);
    } 
    else {
        // Child process

        // Close the unused write end of the pipe
        close(fd[1]);

        // Read the message from parent
        read(fd[0], read_msg, sizeof(read_msg));
        printf("Child: Read from pipe: %s\n", read_msg);

        // Close the read end after reading
        close(fd[0]);

        // Open the write end of the pipe to write a message back to the parent
        close(fd[0]);  // Ensure the read end is closed
        write(fd[1], "Hello from child!", strlen("Hello from child!") + 1);
        
        // Close the write end after writing
        close(fd[1]);
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

