//1) Write a C Program that demonstrates redirection of standard output to a file.

#include <stdio.h>
int main() {
 
 freopen("krushna1.txt", "w", stdout);
 
 printf("This is redirected standard output.\n");
 
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

