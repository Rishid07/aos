//1)Write a C program that print the exit status of a terminated child process.

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
int main() {
 pid_t child_pid;
 int status;
child_pid = fork();
 if (child_pid == -1) {
 perror("fork");
 exit(EXIT_FAILURE);
 }
 if (child_pid == 0) {

 printf("Child process (PID %d) is running.\n", getpid());
 sleep(2);
 
 exit(42);
 } else {
 
 printf("Parent process (PID %d) is waiting for the child.\n", getpid());
 wait(&status);
 if (WIFEXITED(status)) {
 int exit_status = WEXITSTATUS(status);
 printf("Child process (PID %d) exited with status %d.\n", child_pid, 
exit_status);
 } else {
 printf("Child process (PID %d) did not exit normally.\n", child_pid);
 }
 }
 return 0;
}

//2)Write a C program which receives file names as command line arguments and display those
//filenames in ascending order according to their sizes. I) (e.g $ a.out a.txt b.txt c.txt, …)

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

struct FileInfo {
char *filename;
off_t size;
};

int compareFileInfo(const void *a, const void *b) {
return ((struct FileInfo*)a)->size - ((struct FileInfo*)b)->size;
}int main(int argc, char *argv[]) {
if (argc < 2) {
fprintf(stderr, "Usage: %s <file1> <file2> ...\n", argv[0]);
return 1;
}

struct FileInfo *fileInfoArray = (struct FileInfo*)malloc((argc - 1) * sizeof(struct
FileInfo));
if (!fileInfoArray) {
perror("malloc");
return 1;
}

for (int i = 1; i < argc; i++) {
struct stat fileStat;
if (stat(argv[i], &fileStat) == -1) {
perror("stat");
return 1;
}
fileInfoArray[i - 1].filename = argv[i];
fileInfoArray[i - 1].size = fileStat.st_size;
}

qsort(fileInfoArray, argc - 1, sizeof(struct FileInfo), compareFileInfo);

printf("Filenames in ascending order according to their sizes:\n");
for (int i = 0; i < argc - 1; i++) {
printf("%s - %ld bytes\n", fileInfoArray[i].filename, fileInfoArray[i].size);
}

free(fileInfoArray);
return 0;
}
