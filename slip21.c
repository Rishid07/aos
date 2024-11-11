//1) Read the current directory and display the name of the files, no of files in current directory.

#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
int main() {
 DIR *dir;
 struct dirent *entry;
 int fileCount = 0;
 if ((dir = opendir(".")) == NULL) {
 perror("opendir");
 return 1;
 }
 printf("Files in the current directory:\n");
 while ((entry = readdir(dir)) != NULL) {
 if (entry->d_type == DT_REG) { 
 printf("%s\n", entry->d_name);
 fileCount++;
 }
 }
 closedir(dir);
 printf("\nNumber of files in the current directory: %d\n", fileCount);
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
