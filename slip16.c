// 2) Write a C program which creates a child process and child process catches a signal SIGHUP,
//SIGINT and SIGQUIT. The Parent process send a SIGHUP or SIGINT signal after every 3
//seconds, at the end of 15 second parent send SIGQUIT signal to child and child terminates by
//displaying message "My Papa has Killed me!!!”


#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
void sighup();
void sigint();
void sigquit();

int main() {
    int pid, i, j;
    
    if ((pid = fork()) < 0) {
        perror("fork");
        exit(1);
    }

    if (pid == 0) { 
        
        signal(SIGHUP, sighup);
        signal(SIGINT, sigint);
        signal(SIGQUIT, sigquit);
        

        for (;;) {
            pause(); 
        }
    } else { 
        j = 0;
        for (i = 1; i <= 5; i++) {
            j++;
            printf("PARENT: sending SIGHUP Signal : %d\n", j);
            kill(pid, SIGHUP);  
            sleep(3);
            
            printf("PARENT: Sending SIGINT Signal : %d\n", j);
            kill(pid, SIGINT); 
            sleep(3);
        }
        
        sleep(3);
        printf("Parent sending SIGQUIT\n");
        kill(pid, SIGQUIT); 
    }

    return 0; 
}

void sighup() {
   
    printf("Child: I have received SIGHUP\n");
}

void sigint() {
   
    printf("Child: I have received SIGINT\n");
}

void sigquit() {
    printf("My daddy has killed me\n");
    exit(0);  
}

