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
 // Prompt the user for the minimum file size
 printf("Enter the minimum file size (in bytes): ");
 scanf("%llu", &n);
 // Open the current directory
 dir = opendir(".");
 if (dir == NULL) {
 perror("opendir");
 return 1;
 }
// Iterate through the directory entries
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


