//1)Display all the files from current directory which are created in particular month.
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <time.h>
#include <string.h>

void list_files_created_in_month(const char *directory, int target_month) {
    struct dirent *entry;
    struct stat file_stat;
    DIR *dir = opendir(directory);

    if (!dir) {
        perror("opendir");
        return;
    }

    printf("Files created in month %d:\n", target_month);

    while ((entry = readdir(dir)) != NULL) {
        // Skip directories (we only want files)
        if (entry->d_type != DT_REG) {
            continue;
        }

        // Get file stats
        if (stat(entry->d_name, &file_stat) == -1) {
            perror("stat");
            continue;
        }

        // Convert the creation time to struct tm
        struct tm *time_info = localtime(&file_stat.st_ctime);

        // Check if the file's creation month matches the target month
        if (time_info->tm_mon + 1 == target_month) {  // tm_mon is 0-indexed, so add 1
            printf("%s\n", entry->d_name);
        }
    }

    closedir(dir);
}

int main() {
    char directory[256] = ".";
    int target_month;

    // Ask user for the month (1-12)
    printf("Enter the month number (1-12): ");
    if (scanf("%d", &target_month) != 1 || target_month < 1 || target_month > 12) {
        printf("Invalid month number!\n");
        return 1;
    }

    // List files created in the target month in the current directory
    list_files_created_in_month(directory, target_month);

    return 0;
}



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

