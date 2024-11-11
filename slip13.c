//1)Write a C program that illustrates suspending and resuming processes using signal.

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
void suspendHandler(int signum) {
    printf("Process is suspended. Press Enter to resume...\n");
    fflush(stdout);
}
int main() {
    signal(SIGTSTP, suspendHandler); 

    printf("Process is running. Press Ctrl+Z to suspend...\n");
    fflush(stdout);

    while (1) {
    }
   return 0;
}


//2)Write a C program that a string as an argument and return all the files that begins with that name
//in the current directory. For example > ./a.out foo will return all file names that begins with foo.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
int main(int argc, char *argv[]) {
 if (argc != 2) {
 printf("Usage: %s <prefix>\n", argv[0]);
 return 1;
 }
 char *prefix = argv[1];
 int prefix_length = strlen(prefix);
 DIR *dir;
 struct dirent *entry;
 if ((dir = opendir(".")) == NULL) {
 perror("opendir");
 return 1;
 }
 printf("Files starting with '%s' in the current directory:\n", prefix);
 while ((entry = readdir(dir)) != NULL) {
 if (strncmp(entry->d_name, prefix, prefix_length) == 0) {
 printf("%s\n", entry->d_name);
 }
 }
 closedir(dir);
 return 0;
}
