//1)Display all the files from current directory whose size is greater that n Bytes Where n is accept
//from user. 

#include <stdio.h>
#include <dirent.h>
#include <sys/stat.h>
#include <string.h>
int main() {
 DIR *dir;
 struct dirent *entry;
 struct stat fileStat;
 char path[1000];
 unsigned long long n;
 
 printf("Enter the minimum file size (in bytes): ");
 scanf("%llu", &n);
 
 dir = opendir(".");
 if (dir == NULL) {
 perror("opendir");
 return 1;
 }

 while ((entry = readdir(dir)) != NULL) {
 snprintf(path, sizeof(path), "%s", entry->d_name);
 if (stat(path, &fileStat) < 0) {
 perror("stat");
 continue;
 }
 if (S_ISREG(fileStat.st_mode) && fileStat.st_size > n) {
 printf("%s (%llu bytes)\n", path, fileStat.st_size);
 }
 }
 closedir(dir);
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
    pid_t pid = waitpid(child_pid, &status, WNOHANG);  // Non-blocking wait
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
        kill(child_pid, SIGKILL);  // Kill the child process after 5 seconds
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

