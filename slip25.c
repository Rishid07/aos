//1) Write a C Program that demonstrates redirection of standard output to a file.

#include <stdio.h>
int main() {
 
 freopen("krushna1.txt", "w", stdout);
 
 printf("This is redirected standard output.\n");
 
 
 fclose(stdout);
 return 0;
}

// 2)Write a C program that redirects standard output to a file output.txt. (use of dup and open system
//call).
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main() {
    int fd = open("krushna1.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd == -1) {
        perror("Failed to open file");
        return 1;
    }

    if (dup2(fd, STDOUT_FILENO) == -1) {
        perror("Failed to redirect stdout");
        close(fd);
        return 1;
    }

    printf("This is redirected standard output\n");

    
    close(fd);

    return 0;
}



