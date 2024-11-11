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
            continue; // Skip the file if stat() fails
        }
        printf("File: %s\nInode: %ld\n", argv[i], (long)file_info.st_ino);
        print_file_type(file_info.st_mode); // Print file type
        printf("---------------\n");
    }
    return 0;
}

//2) Write a C program to send SIGALRM signal by child process to parent process and parent process 
//make a provision to catch the signal and display alarm is fired.(Use Kill, fork, signal and sleep 
//system call)

#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include<signal.h>
#include<sys/types.h>
#include<sys/wait.h>
#include <stdlib.h>
void Dingdong()
{
printf("Ding!");
exit(1);
}
int main(int argc, char *argv[])
{ if (argc!=3)
{
printf("How much seconds you want to sleep the child process\n");
}
int PauseSecond=(argv[1]);
{
if(fork()==0)
{
printf("waiting for alarm to go off\n");
printf("%dsecond pause",PauseSecond);
sleep(PauseSecond);
kill(getpid(),SIGALRM);
}
else{
printf("Alarm application starting\n", getpid());
signal(SIGALRM,Dingdong);
printf("done");
}}}
