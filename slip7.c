//1) Write a C Program that demonstrates redirection of standard output to a file.

#include <stdio.h>
int main() {
 // Redirect standard output to a file
 freopen("krushna1.txt", "w", stdout);
 // Print to standard output (now redirected to "output.txt")
 printf("This is redirected standard output.\n");
 
 // Close the redirected file stream
 fclose(stdout);
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

    // Create the pipe
    if (pipe(pipe_fd) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    // Fork first child (ls -l)
    if ((pid1 = fork()) == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid1 == 0) {
        close(pipe_fd[0]);  // Close read end in child 1
        dup2(pipe_fd[1], STDOUT_FILENO);  // Redirect stdout to pipe's write end
        close(pipe_fd[1]);  // No longer need pipe write end
        execlp("ls", "ls", "-l", NULL);  // Execute ls -l
        perror("execlp");  // If exec fails
        exit(EXIT_FAILURE);
    }

    // Fork second child (wc -l)
    if ((pid2 = fork()) == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid2 == 0) {
        close(pipe_fd[1]);  // Close write end in child 2
        dup2(pipe_fd[0], STDIN_FILENO);  // Redirect stdin to pipe's read end
        close(pipe_fd[0]);  // No longer need pipe read end
        execlp("wc", "wc", "-l", NULL);  // Execute wc -l
        perror("execlp");  // If exec fails
        exit(EXIT_FAILURE);
    }

    // Parent process: Close both pipe ends and wait for children
    close(pipe_fd[0]);
    close(pipe_fd[1]);
    waitpid(pid1, NULL, 0);  // Wait for child 1
    waitpid(pid2, NULL, 0);  // Wait for child 2

    return 0;
}

