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
