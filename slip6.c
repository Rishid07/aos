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
