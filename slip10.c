//1)Write a program that illustrates how to execute two commands concurrently with a pipe.
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
int main() {
 int pipefd[2];
 pid_t child_pid;
 // Create a pipe
 if (pipe(pipefd) == -1) {
 perror("pipe");
 exit(EXIT_FAILURE);
}
 // Fork a child process
 child_pid = fork();
 if (child_pid == -1) {
 perror("fork");
 exit(EXIT_FAILURE);
 }
 if (child_pid == 0) {
 // Child process (command 2)
 close(pipefd[1]); // Close the write end of the pipe
 // Redirect stdin to read from the pipe
 dup2(pipefd[0], 0);
 // Execute the second command (e.g., "wc -l" to count lines)
 execlp("wc", "wc", "-l", NULL);
 perror("execlp");
 exit(EXIT_FAILURE);
 } else {
 // Parent process (command 1)
 close(pipefd[0]); // Close the read end of the pipe
 // Redirect stdout to write to the pipe
 dup2(pipefd[1], 1);
 // Execute the first command (e.g., "ls" to list files)
 execlp("ls", "ls", NULL);
 perror("execlp");
 exit(EXIT_FAILURE);
 }
 // Close the remaining file descriptors
 close(pipefd[0]);
 close(pipefd[1]);
// Wait for the child process to complete
 wait(NULL);
 return 0;
}


//2)Generate parent process to write unnamed pipe and will write into it. Also generate child process
//which will read from pipe.
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define BUF_SIZE 100

int main() {
    int pipe_fd[2];  // pipe file descriptors: pipe_fd[0] = read end, pipe_fd[1] = write end
    pid_t pid;
    char write_msg[] = "Hello from parent process!";
    char read_msg[BUF_SIZE];

    // Create an unnamed pipe
    if (pipe(pipe_fd) == -1) {
        perror("pipe");
        exit(1);
    }

    // Fork a child process
    pid = fork();
    if (pid == -1) {
        perror("fork");
        exit(1);
    }

    if (pid > 0) { // Parent process
        // Close the unused read end of the pipe
        close(pipe_fd[0]);

        // Write a message to the pipe
        printf("Parent writing to pipe: %s\n", write_msg);
        if (write(pipe_fd[1], write_msg, strlen(write_msg) + 1) == -1) {
            perror("write");
            exit(1);
        }

        // Close the write end after writing
        close(pipe_fd[1]);

        // Wait for child to finish
        wait(NULL);
    } 
    else { // Child process
        // Close the unused write end of the pipe
        close(pipe_fd[1]);

        // Read the message from the pipe
        if (read(pipe_fd[0], read_msg, BUF_SIZE) == -1) {
            perror("read");
            exit(1);
        }

        // Print the message read from the pipe
        printf("Child read from pipe: %s\n", read_msg);

        // Close the read end after reading
        close(pipe_fd[0]);
    }

    return 0;
}

