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
        
        if (entry->d_type != DT_REG) {
            continue;
        }

        
        if (stat(entry->d_name, &file_stat) == -1) {
            perror("stat");
            continue;
        }

        
        struct tm *time_info = localtime(&file_stat.st_ctime);

        
        if (time_info->tm_mon + 1 == target_month) {  
            printf("%s\n", entry->d_name);
        }
    }

    closedir(dir);
}

int main() {
    char directory[256] = ".";
    int target_month;

    
    printf("Enter the month number (1-12): ");
    if (scanf("%d", &target_month) != 1 || target_month < 1 || target_month > 12) {
        printf("Invalid month number!\n");
        return 1;
    }

    
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
if((pid = fork())==-1) 
{
perror("\n fork error");
exit(EXIT_FAILURE);
}
else
if(pid==0) 
{
time(&currentTime);
printf("\nChild process started at %s",ctime(&currentTime));
for(i=0;i<5;i++)
{
printf("\nCounting= %dn",i); 
sleep(1);
}
time(&currentTime);
printf("\nChild process ended at %s",ctime(&currentTime));
exit(EXIT_SUCCESS);
}
else
{

time(&currentTime); 
printf("\nParent process started at %s ",ctime(&currentTime));
if(wait(&status)== -1) 
perror("\n wait error");
if(WIFEXITED(status))
printf("\nChild process ended normally");
else
printf("\nChild process did not end normally");
if(times(&cpuTime)<0) 
perror("\nTimes error");
else
{

printf("\nParent process user time= %fn",((double) cpuTime.tms_utime));
printf("\nParent process system time = %fn",((double) cpuTime.tms_stime));
printf("\nChild process user time = %fn",((double) cpuTime.tms_cutime));
printf("\nChild process system time = %fn",((double) cpuTime.tms_cstime));
}
time(&currentTime);
printf("\nParent process ended at %s",ctime(&currentTime));
exit(EXIT_SUCCESS);
} }
