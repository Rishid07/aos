//1) Take multiple files as command Line argument and print their inode numbers and file types

#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
void print_file_type(mode_t mode) {
    if (S_ISREG(mode)) printf("Type: Regular File\n");
    else if (S_ISDIR(mode)) printf("Type: Directory\n");
    else if (S_ISLNK(mode)) printf("Type: Symbolic Link\n");
    else if (S_ISCHR(mode)) printf("Type: Character Device\n");
    else if (S_ISBLK(mode)) printf("Type: Block Device\n");
    else if (S_ISFIFO(mode)) printf("Type: FIFO (Named Pipe)\n");
    else if (S_ISSOCK(mode)) printf("Type: Socket\n");
    else printf("Type: Unknown\n");
}
int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <file1> <file2> ... <fileN>\n", argv[0]);
        return EXIT_FAILURE;
    }
    for (int i = 1; i < argc; i++) {
        struct stat file_info;
        if (stat(argv[i], &file_info) == -1) {
            perror("stat");
            continue; 
        }
        printf("File: %s\nInode: %ld\n", argv[i], (long)file_info.st_ino);
        print_file_type(file_info.st_mode); 
        printf("---------------\n");
    }
    return 0;
}

//2)Implement the following unix/linux command (use fork, pipe and exec system call)
//ls –l | wc –l. 

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    int pipe_fd[2];
    pid_t pid1, pid2;

   
    if (pipe(pipe_fd) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    if ((pid1 = fork()) == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid1 == 0) {
        close(pipe_fd[0]); 
        dup2(pipe_fd[1], STDOUT_FILENO); 
        close(pipe_fd[1]); 
        execlp("ls", "ls", "-l", NULL); 
        perror("execlp"); 
        exit(EXIT_FAILURE);
    }

   
    if ((pid2 = fork()) == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid2 == 0) {
        close(pipe_fd[1]); 
        dup2(pipe_fd[0], STDIN_FILENO); 
        close(pipe_fd[0]); 
        execlp("wc", "wc", "-l", NULL);  
        perror("execlp"); 
        exit(EXIT_FAILURE);
    }

   
    close(pipe_fd[0]);
    close(pipe_fd[1]);
    waitpid(pid1, NULL, 0); 
    waitpid(pid2, NULL, 0); 

    return 0;
}

