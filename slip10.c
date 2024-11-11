//1)Write a program that illustrates how to execute two commands concurrently with a pipe.
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
int main() {
 int pipefd[2];
 pid_t child_pid;
 
 if (pipe(pipefd) == -1) {
 perror("pipe");
 exit(EXIT_FAILURE);
}
 
 child_pid = fork();
 if (child_pid == -1) {
 perror("fork");
 exit(EXIT_FAILURE);
 }
 if (child_pid == 0) {
 
 close(pipefd[1]); 
 dup2(pipefd[0], 0);
 
 execlp("wc", "wc", "-l", NULL);
 perror("execlp");
 exit(EXIT_FAILURE);
 } else {

 close(pipefd[0]); 
 dup2(pipefd[1], 1);
 
 execlp("ls", "ls", NULL);
 perror("execlp");
 exit(EXIT_FAILURE);
 }
 
 close(pipefd[0]);
 close(pipefd[1]);

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
    int pipe_fd[2];  
    pid_t pid;
    char write_msg[] = "Hello from parent process!";
    char read_msg[BUF_SIZE];

    
    if (pipe(pipe_fd) == -1) {
        perror("pipe");
        exit(1);
    }

    
    pid = fork();
    if (pid == -1) {
        perror("fork");
        exit(1);
    }

    if (pid > 0) { 
        
        close(pipe_fd[0]);

        
        printf("Parent writing to pipe: %s\n", write_msg);
        if (write(pipe_fd[1], write_msg, strlen(write_msg) + 1) == -1) {
            perror("write");
            exit(1);
        }

        
        close(pipe_fd[1]);

        
        wait(NULL);
    } 
    else { 
        close(pipe_fd[1]);

        
        if (read(pipe_fd[0], read_msg, BUF_SIZE) == -1) {
            perror("read");
            exit(1);
        }

        
        printf("Child read from pipe: %s\n", read_msg);

        
        close(pipe_fd[0]);
    }

    return 0;
}

