//1)Write a C program to find file properties such as inode number, number of hard link, File
//permissions, File size, File access and modification time and so on of a given file using stat()
//system call.

#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>
#include <time.h>
int main(int argc, char *argv[]) {
 if (argc != 2) {
 fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
 exit(EXIT_FAILURE);
 }
 const char *filename = argv[1];
 struct stat file_info;
if (stat(filename, &file_info) == -1) {
 perror("stat");
 exit(EXIT_FAILURE);
 }
 printf("File Properties for: %s\n", filename);
 printf("Inode Number: %ld\n", (long)file_info.st_ino);
 printf("Number of Hard Links: %ld\n", (long)file_info.st_nlink);
 printf("File Permissions: %o\n", file_info.st_mode & 0777);
 printf("File Size: %ld bytes\n", (long)file_info.st_size);
 
 char access_time_str[20];
 char mod_time_str[20];
 strftime(access_time_str, sizeof(access_time_str), "%Y-%m-%d %H:%M:%S", 
localtime(&file_info.st_atime));
 strftime(mod_time_str, sizeof(mod_time_str), "%Y-%m-%d %H:%M:%S", 
localtime(&file_info.st_mtime));
 printf("Access Time: %s\n", access_time_str);
 printf("Modification Time: %s\n", mod_time_str);
 return 0;
}


//2)Write a C program that catches the ctrl-c (SIGINT) signal for the first time and display the
//appropriate message and exits on pressing ctrl-c again.

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
void sigfun(int sig)
{
printf("You have presses Ctrl-C , please press again to exit");
(void) signal(SIGINT, SIG_DFL);
}
int main()
{
(void) signal(SIGINT, sigfun);
while(1) {
printf("Hello World!");
sleep(1);
}
return(0);
}

