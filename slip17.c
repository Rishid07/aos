//1) Read the current directory and display the name of the files, no of files in current directory.

#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
int main() {
 DIR *dir;
 struct dirent *entry;
 int fileCount = 0;
 if ((dir = opendir(".")) == NULL) {
 perror("opendir");
 return 1;
 }
 printf("Files in the current directory:\n");
 while ((entry = readdir(dir)) != NULL) {
 if (entry->d_type == DT_REG) { 
 printf("%s\n", entry->d_name);
 fileCount++;
 }
 }
 closedir(dir);
 printf("\nNumber of files in the current directory: %d\n", fileCount);
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
    sigaddset(&set, SIGINT);  
    sigaddset(&set, SIGQUIT);  
    sigprocmask(SIG_BLOCK, &set, NULL);
}

int main() {
    int pipe_fd[2];
    pid_t pid1, pid2;

   
    if (pipe(pipe_fd) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    
    block_signals();

    
    pid1 = fork();
    if (pid1 == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid1 == 0) {
        
        close(pipe_fd[0]);

        
        dup2(pipe_fd[1], STDOUT_FILENO);

       
        execlp("ls", "ls", "-l", NULL);
       
        perror("execlp ls");
        exit(EXIT_FAILURE);
    } else {
        
        pid2 = fork();
        if (pid2 == -1) {
            perror("fork");
            exit(EXIT_FAILURE);
        }

        if (pid2 == 0) {
            
            close(pipe_fd[1]);

            
            dup2(pipe_fd[0], STDIN_FILENO);

            
            execlp("wc", "wc", "-l", NULL);
           
            perror("execlp wc");
            exit(EXIT_FAILURE);
        } else {
           
            close(pipe_fd[0]);
            close(pipe_fd[1]);

            waitpid(pid1, NULL, 0);
            waitpid(pid2, NULL, 0);

            printf("Program finished.\n");
        }
    }

    return 0;
}

