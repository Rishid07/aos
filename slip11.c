//1)Write a C program to get and set the resource limits such as files, memory associated with a
//process
#include <stdio.h>
#include <stdlib.h>
#include <sys/resource.h>

void print_and_set_limit(int resource, long long new_limit) {
    struct rlimit limits;

    // Get the current limit
    if (getrlimit(resource, &limits) == -1) {
        perror("getrlimit");
        exit(EXIT_FAILURE);
    }

    // Print the current limit
    printf("Current limit: %lld bytes\n", (long long)limits.rlim_cur);

    // Set the new limit
    limits.rlim_cur = new_limit;
    if (setrlimit(resource, &limits) == -1) {
        perror("setrlimit");
        exit(EXIT_FAILURE);
    }

    // Get and print the updated limit
    if (getrlimit(resource, &limits) == -1) {
        perror("getrlimit");
        exit(EXIT_FAILURE);
    }
    printf("Updated limit: %lld bytes\n\n", (long long)limits.rlim_cur);
}

int main() {
    // File descriptor limit (RLIMIT_NOFILE)
    print_and_set_limit(RLIMIT_NOFILE, 1024);

    // Virtual memory limit (RLIMIT_AS) - 1 GB
    print_and_set_limit(RLIMIT_AS, 1024 * 1024 * 1024);

    // Stack size limit (RLIMIT_STACK) - 8 MB
    print_and_set_limit(RLIMIT_STACK, 8 * 1024 * 1024);

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

