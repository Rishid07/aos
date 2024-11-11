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

//2)Write a C program to find file properties such as inode number, number of hard link, File
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

