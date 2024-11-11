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


//2) Write a C program to implement the following unix/linux command (use fork, pipe and exec
//system call). Your program should block the signal Ctrl-C and Ctrl-\ signal during the execution.
//i. Ls –l | wc –l 
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>

void block_signals() {
    sigset_t set;
    sigemptyset(&set);
    sigaddset(&set, SIGINT);   // Block SIGINT (Ctrl-C)
    sigaddset(&set, SIGQUIT);  // Block SIGQUIT (Ctrl-\)
    sigprocmask(SIG_BLOCK, &set, NULL);
}

int main() {
    int pipe_fd[2];
    pid_t pid1, pid2;

    // Create a pipe
    if (pipe(pipe_fd) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    // Block Ctrl-C and Ctrl-\ signals
    block_signals();

    // Fork first child process for 'ls -l'
    pid1 = fork();
    if (pid1 == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid1 == 0) {
        // Child process 1 (ls -l)
        // Close write end of the pipe
        close(pipe_fd[0]);

        // Redirect stdout to the pipe
        dup2(pipe_fd[1], STDOUT_FILENO);

        // Execute 'ls -l'
        execlp("ls", "ls", "-l", NULL);
        // If exec fails
        perror("execlp ls");
        exit(EXIT_FAILURE);
    } else {
        // Fork second child process for 'wc -l'
        pid2 = fork();
        if (pid2 == -1) {
            perror("fork");
            exit(EXIT_FAILURE);
        }

        if (pid2 == 0) {
            // Child process 2 (wc -l)
            // Close the write end of the pipe
            close(pipe_fd[1]);

            // Redirect stdin to read from the pipe
            dup2(pipe_fd[0], STDIN_FILENO);

            // Execute 'wc -l'
            execlp("wc", "wc", "-l", NULL);
            // If exec fails
            perror("execlp wc");
            exit(EXIT_FAILURE);
        } else {
            // Parent process
            // Close both ends of the pipe
            close(pipe_fd[0]);
            close(pipe_fd[1]);

            // Wait for both child processes to complete
            waitpid(pid1, NULL, 0);
            waitpid(pid2, NULL, 0);

            printf("Program finished.\n");
        }
    }

    return 0;
}

