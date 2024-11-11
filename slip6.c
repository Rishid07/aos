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


//2)Write a C program to create n child processes. When all n child processes terminates, Display
//total cumulative time children spent in user and kernel mode.

#include<sys/types.h>
#include<sys/wait.h>
#include<unistd.h>
#include<time.h>
#include<sys/times.h>
#include<stdio.h>
#include<stdlib.h>
int main(void)
{
int i, status;
pid_t pid;
time_t currentTime;
struct tms cpuTime;
if((pid = fork())==-1) //start child process
{
perror("\n fork error");
exit(EXIT_FAILURE);
}
else
if(pid==0) //child process
{
time(&currentTime);
printf("\nChild process started at %s",ctime(&currentTime));
for(i=0;i<5;i++)
{
printf("\nCounting= %dn",i); //count for 5 seconds
sleep(1);
}
time(&currentTime);
printf("\nChild process ended at %s",ctime(&currentTime));
exit(EXIT_SUCCESS);
}
else
{
//Parent process
time(&currentTime); // gives normal time
printf("\nParent process started at %s ",ctime(&currentTime));
if(wait(&status)== -1) //wait for child process
perror("\n wait error");
if(WIFEXITED(status))
printf("\nChild process ended normally");
else
printf("\nChild process did not end normally");
if(times(&cpuTime)<0) //Get process time
perror("\nTimes error");
else
{
// _SC_CLK_TCK: system configuration time:seconds clock tick
printf("\nParent process user time= %fn",((double) cpuTime.tms_utime));
printf("\nParent process system time = %fn",((double) cpuTime.tms_stime));
printf("\nChild process user time = %fn",((double) cpuTime.tms_cutime));
printf("\nChild process system time = %fn",((double) cpuTime.tms_cstime));
}
time(&currentTime);
printf("\nParent process ended at %s",ctime(&currentTime));
exit(EXIT_SUCCESS);
} }
