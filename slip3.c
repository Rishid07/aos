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


//2)Write a C program which creates a child process to run linux/ unix command or any user defined
//program. The parent process set the signal handler for death of child signal and Alarm signal. If
//a child process does not complete its execution in 5 second then parent process kills child process.

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>
#include <string.h>

pid_t child_pid = -1;

void handle_child_death(int sig) {
    int status;
    pid_t pid = waitpid(child_pid, &status, WNOHANG);  
    if (pid == -1) {
        perror("waitpid");
        exit(1);
    }
    if (pid > 0) {
        if (WIFEXITED(status)) {
            printf("Child process %d terminated normally with exit status %d\n", pid, WEXITSTATUS(status));
        } else if (WIFSIGNALED(status)) {
            printf("Child process %d terminated by signal %d\n", pid, WTERMSIG(status));
        } else {
            printf("Child process %d terminated abnormally\n", pid);
        }
    }
}

void handle_alarm(int sig) {
    if (child_pid > 0) {
        printf("Timeout reached! Killing child process %d...\n", child_pid);
        kill(child_pid, SIGKILL);  
    }
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <command> [arguments...]\n", argv[0]);
        exit(1);
    }

    
    struct sigaction sa_child, sa_alarm;
    memset(&sa_child, 0, sizeof(sa_child));
    sa_child.sa_handler = handle_child_death;
    sigaction(SIGCHLD, &sa_child, NULL);

    memset(&sa_alarm, 0, sizeof(sa_alarm));
    sa_alarm.sa_handler = handle_alarm;
    sigaction(SIGALRM, &sa_alarm, NULL);

    
    child_pid = fork();
    if (child_pid < 0) {
        perror("fork");
        exit(1);
    }

    if (child_pid == 0) {
        
        printf("Child process started with PID %d. Executing command...\n", getpid());
        execvp(argv[1], &argv[1]);  
       
        perror("execvp");
        exit(1);
    } else {
        
        printf("Parent process waiting for child process...\n");

        
        alarm(5);
        pause();  
    }

    return 0;
}


