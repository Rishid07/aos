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
            continue; 
        }
        printf("File: %s\nInode: %ld\n", argv[i], (long)file_info.st_ino);
        print_file_type(file_info.st_mode); 
        printf("---------------\n");
    }
    return 0;
}


//2)Write a C program which creates a child process to run linux/ unix command or any user defined
//program. The parent process set the signal handler for death of child signal and Alarm signal. If
//a child process does not complete its execution in 5 second then parent process kills child process.

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>
#include <string.h>

pid_t child_pid = -1;

void handle_child_death(int sig) {
    int status;
    pid_t pid = waitpid(child_pid, &status, WNOHANG);  
    if (pid == -1) {
        perror("waitpid");
        exit(1);
    }
    if (pid > 0) {
        if (WIFEXITED(status)) {
            printf("Child process %d terminated normally with exit status %d\n", pid, WEXITSTATUS(status));
        } else if (WIFSIGNALED(status)) {
            printf("Child process %d terminated by signal %d\n", pid, WTERMSIG(status));
        } else {
            printf("Child process %d terminated abnormally\n", pid);
        }
    }
}

void handle_alarm(int sig) {
    if (child_pid > 0) {
        printf("Timeout reached! Killing child process %d...\n", child_pid);
        kill(child_pid, SIGKILL);  
    }
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <command> [arguments...]\n", argv[0]);
        exit(1);
    }

    
    struct sigaction sa_child, sa_alarm;
    memset(&sa_child, 0, sizeof(sa_child));
    sa_child.sa_handler = handle_child_death;
    sigaction(SIGCHLD, &sa_child, NULL);

    memset(&sa_alarm, 0, sizeof(sa_alarm));
    sa_alarm.sa_handler = handle_alarm;
    sigaction(SIGALRM, &sa_alarm, NULL);

    
    child_pid = fork();
    if (child_pid < 0) {
        perror("fork");
        exit(1);
    }

    if (child_pid == 0) {
        
        printf("Child process started with PID %d. Executing command...\n", getpid());
        execvp(argv[1], &argv[1]);  
       
        perror("execvp");
        exit(1);
    } else {
        
        printf("Parent process waiting for child process...\n");

        
        alarm(5);
        pause();  
    }

    return 0;
}




// 1) Write a C program to find whether a given files passed through command line arguments are
//present in current directory or not.

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
int main(int argc, char *argv[]) {
 if (argc != 2) {
 fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
 exit(EXIT_FAILURE);
 }
 const char *filename = argv[1];
 if (access(filename, F_OK) == 0) {
 printf("The file '%s' is present in the current directory.\n", filename);
 } else {
 printf("The file '%s' is not present in the current directory.\n", filename);
 }
 return 0;
}


// 2) Write a C program which creates a child process and child process catches a signal SIGHUP,
//SIGINT and SIGQUIT. The Parent process send a SIGHUP or SIGINT signal after every 3
//seconds, at the end of 15 second parent send SIGQUIT signal to child and child terminates by
//displaying message "My Papa has Killed me!!!”


#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
void sighup();
void sigint();
void sigquit();

int main() {
    int pid, i, j;
    
    if ((pid = fork()) < 0) {
        perror("fork");
        exit(1);
    }

    if (pid == 0) { 
        
        signal(SIGHUP, sighup);
        signal(SIGINT, sigint);
        signal(SIGQUIT, sigquit);
        

        for (;;) {
            pause(); 
        }
    } else { 
        j = 0;
        for (i = 1; i <= 5; i++) {
            j++;
            printf("PARENT: sending SIGHUP Signal : %d\n", j);
            kill(pid, SIGHUP);  
            sleep(3);
            
            printf("PARENT: Sending SIGINT Signal : %d\n", j);
            kill(pid, SIGINT); 
            sleep(3);
        }
        
        sleep(3);
        printf("Parent sending SIGQUIT\n");
        kill(pid, SIGQUIT); 
    }

    return 0; 
}

void sighup() {
   
    printf("Child: I have received SIGHUP\n");
}

void sigint() {
   
    printf("Child: I have received SIGINT\n");
}

void sigquit() {
    printf("My daddy has killed me\n");
    exit(0);  
}




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
 if (entry->d_type == DT_REG) { // Check if it's a regular file
 printf("%s\n", entry->d_name);
 fileCount++;
 }
 }
 closedir(dir);
 printf("\nNumber of files in the current directory: %d\n", fileCount);
 return 0;
}



// 2) Write a C program to create an unnamed pipe. The child process will write following three
//messages to pipe and parent process display it.
//Message1 = “Hello World”
//Message2 = “Hello SPPU”
//Message3 = “Linux is Funny.

#include<stdio.h>
#include<unistd.h>
int main()
{
int pipefds[2];
int returnstatus;
char writemessages[3][20]={"Hello World", "Hello SPPU","Linux isFunny"};
char readmessage[20];
returnstatus = pipe(pipefds);
if (returnstatus == -1) {
printf("Unable to create pipe\n");
return 1;
}
int child = fork();
if(child==0){
printf("Child is Writing to pipe - Message 1 is %s\n", writemessages[0]);
write(pipefds[1], writemessages[0], sizeof(writemessages[0]));
printf("Child is Writing to pipe - Message 2 is %s\n", writemessages[1]);
write (pipefds[1],writemessages[1], sizeof(writemessages[1]));
printf("Child is Writing to pipe - Message 3 is %s\n", writemessages[2]);
write(pipefds[1], writemessages[2], sizeof(writemessages[2]));
}
else {
read(pipefds[0], readmessage, sizeof(readmessage));
printf("Parent Process is Reading from pipe – Message 1 is %s\n",readmessage);
read(pipefds[0], readmessage, sizeof(readmessage));
printf("Parent Process is Reading from pipe – Message 2 is %s\n",readmessage);
read(pipefds[0], readmessage, sizeof(readmessage));
printf("Parent Process is Reading from pipe – Message 3 is %s\n",readmessage);
}
}




//1)Display all the files from current directory which are created in particular month.
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <time.h>
#include <string.h>

void list_files_created_in_month(const char *directory, int target_month) {
    struct dirent *entry;
    struct stat file_stat;
    DIR *dir = opendir(directory);

    if (!dir) {
        perror("opendir");
        return;
    }

    printf("Files created in month %d:\n", target_month);

    while ((entry = readdir(dir)) != NULL) {
        
        if (entry->d_type != DT_REG) {
            continue;
        }

        
        if (stat(entry->d_name, &file_stat) == -1) {
            perror("stat");
            continue;
        }

        
        struct tm *time_info = localtime(&file_stat.st_ctime);

        
        if (time_info->tm_mon + 1 == target_month) {  
            printf("%s\n", entry->d_name);
        }
    }

    closedir(dir);
}

int main() {
    char directory[256] = ".";
    int target_month;

    
    printf("Enter the month number (1-12): ");
    if (scanf("%d", &target_month) != 1 || target_month < 1 || target_month > 12) {
        printf("Invalid month number!\n");
        return 1;
    }

    
    list_files_created_in_month(directory, target_month);

    return 0;
}


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
if((pid = fork())==-1) 
{
perror("\n fork error");
exit(EXIT_FAILURE);
}
else
if(pid==0) 
{
time(&currentTime);
printf("\nChild process started at %s",ctime(&currentTime));
for(i=0;i<5;i++)
{
printf("\nCounting= %dn",i); 
sleep(1);
}
time(&currentTime);
printf("\nChild process ended at %s",ctime(&currentTime));
exit(EXIT_SUCCESS);
}
else
{

time(&currentTime); 
printf("\nParent process started at %s ",ctime(&currentTime));
if(wait(&status)== -1) 
perror("\n wait error");
if(WIFEXITED(status))
printf("\nChild process ended normally");
else
printf("\nChild process did not end normally");
if(times(&cpuTime)<0) 
perror("\nTimes error");
else
{

printf("\nParent process user time= %fn",((double) cpuTime.tms_utime));
printf("\nParent process system time = %fn",((double) cpuTime.tms_stime));
printf("\nChild process user time = %fn",((double) cpuTime.tms_cutime));
printf("\nChild process system time = %fn",((double) cpuTime.tms_cstime));
}
time(&currentTime);
printf("\nParent process ended at %s",ctime(&currentTime));
exit(EXIT_SUCCESS);
} }




//1) Write a C Program that demonstrates redirection of standard output to a file.

#include <stdio.h>
int main() {
 
 freopen("krushna1.txt", "w", stdout);
 
 printf("This is redirected standard output.\n");
 
 fclose(stdout);
 return 0;
}


//2)Implement the following unix/linux command (use fork, pipe and exec system call)
//ls –l | wc –l. 

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    int pipe_fd[2];
    pid_t pid1, pid2;


    if (pipe(pipe_fd) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    
    if ((pid1 = fork()) == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid1 == 0) {
        close(pipe_fd[0]);  
        dup2(pipe_fd[1], STDOUT_FILENO);  
        close(pipe_fd[1]);  
        execlp("ls", "ls", "-l", NULL);  
        perror("execlp");  
        exit(EXIT_FAILURE);
    }

    
    if ((pid2 = fork()) == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid2 == 0) {
        close(pipe_fd[1]);  
        dup2(pipe_fd[0], STDIN_FILENO);  
        close(pipe_fd[0]);  
        execlp("wc", "wc", "-l", NULL);  
        perror("execlp");  
        exit(EXIT_FAILURE);
    }

    
    close(pipe_fd[0]);
    close(pipe_fd[1]);
    waitpid(pid1, NULL, 0);  
    waitpid(pid2, NULL, 0);  
    

    return 0;
}




// 1)Write a C program that redirects standard output to a file output.txt. (use of dup and open system
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

//2)Implement the following unix/linux command (use fork, pipe and exec system call)
//ls –l | wc –l. 

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    int pipe_fd[2];
    pid_t pid1, pid2;

    
    if (pipe(pipe_fd) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    
    if ((pid1 = fork()) == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid1 == 0) {
        close(pipe_fd[0]);  
        dup2(pipe_fd[1], STDOUT_FILENO);  
        close(pipe_fd[1]);  
        execlp("ls", "ls", "-l", NULL);  
        perror("execlp"); 
        exit(EXIT_FAILURE);
    }

    
    if ((pid2 = fork()) == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid2 == 0) {
        close(pipe_fd[1]);  
        dup2(pipe_fd[0], STDIN_FILENO);  
        close(pipe_fd[0]);  
        execlp("wc", "wc", "-l", NULL);  
        perror("execlp");  
        exit(EXIT_FAILURE);
    }

    
    close(pipe_fd[0]);
    close(pipe_fd[1]);
    waitpid(pid1, NULL, 0);  
    waitpid(pid2, NULL, 0); 

    return 0;
}



//1)Generate parent process to write unnamed pipe and will read from it

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

int main() {
    int fd[2];  
    pid_t pid;
    char write_msg[] = "Hello from parent!";
    char read_msg[100];

   
    if (pipe(fd) == -1) {
        perror("pipe");
        exit(1);
    }

    
    pid = fork();
    if (pid < 0) {
        perror("fork");
        exit(1);
    }

    if (pid > 0) {
        
        close(fd[0]);

        
        printf("Parent: Writing to pipe\n");
        write(fd[1], write_msg, strlen(write_msg) + 1);

        
        close(fd[1]);

        
        wait(NULL);

        
        close(fd[1]);  
        read(fd[0], read_msg, sizeof(read_msg));
        printf("Parent: Read from pipe: %s\n", read_msg);

        
        close(fd[0]);
    } 
    else {
        
        close(fd[1]);

        
        read(fd[0], read_msg, sizeof(read_msg));
        printf("Child: Read from pipe: %s\n", read_msg);

       
        close(fd[0]);

        
        close(fd[0]);  
        write(fd[1], "Hello from child!", strlen("Hello from child!") + 1);
        
        
        close(fd[1]);
    }

    return 0;
}
   


//2)Write a C program to Identify the type (Directory, character device, Block device, Regular file,
//FIFO or pipe, symbolic link or socket) of given file using stat() system call.
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        return EXIT_FAILURE;
    }

    struct stat file_info;
    if (stat(argv[1], &file_info) == -1) {
        perror("stat");
        return EXIT_FAILURE;
    }

    const char *file_type = "unknown";
    if (S_ISREG(file_info.st_mode)) file_type = "regular file";
    else if (S_ISDIR(file_info.st_mode)) file_type = "directory";
    else if (S_ISLNK(file_info.st_mode)) file_type = "symbolic link";
    else if (S_ISFIFO(file_info.st_mode)) file_type = "named pipe (FIFO)";
    else if (S_ISSOCK(file_info.st_mode)) file_type = "socket";
    else if (S_ISCHR(file_info.st_mode)) file_type = "character special file";
    else if (S_ISBLK(file_info.st_mode)) file_type = "block special file";

    printf("%s is a %s.\n", argv[1], file_type);
    return 0;
}



//1)Write a program that illustrates how to execute two commands concurrently with a pipe.
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
int main() {
 int pipefd[2];
 pid_t child_pid;
 
 if (pipe(pipefd) == -1) {
 perror("pipe");
 exit(EXIT_FAILURE);
}
 
 child_pid = fork();
 if (child_pid == -1) {
 perror("fork");
 exit(EXIT_FAILURE);
 }
 if (child_pid == 0) {
 
 close(pipefd[1]); 
 dup2(pipefd[0], 0);
 
 execlp("wc", "wc", "-l", NULL);
 perror("execlp");
 exit(EXIT_FAILURE);
 } else {

 close(pipefd[0]); 
 dup2(pipefd[1], 1);
 
 execlp("ls", "ls", NULL);
 perror("execlp");
 exit(EXIT_FAILURE);
 }
 
 close(pipefd[0]);
 close(pipefd[1]);

 wait(NULL);
 return 0;
}


//2)Generate parent process to write unnamed pipe and will write into it. Also generate child process
//which will read from pipe.
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define BUF_SIZE 100

int main() {
    int pipe_fd[2];  
    pid_t pid;
    char write_msg[] = "Hello from parent process!";
    char read_msg[BUF_SIZE];

    
    if (pipe(pipe_fd) == -1) {
        perror("pipe");
        exit(1);
    }

    
    pid = fork();
    if (pid == -1) {
        perror("fork");
        exit(1);
    }

    if (pid > 0) { 
        
        close(pipe_fd[0]);

        
        printf("Parent writing to pipe: %s\n", write_msg);
        if (write(pipe_fd[1], write_msg, strlen(write_msg) + 1) == -1) {
            perror("write");
            exit(1);
        }

        
        close(pipe_fd[1]);

        
        wait(NULL);
    } 
    else { 
        close(pipe_fd[1]);

        
        if (read(pipe_fd[0], read_msg, BUF_SIZE) == -1) {
            perror("read");
            exit(1);
        }

        
        printf("Child read from pipe: %s\n", read_msg);

        
        close(pipe_fd[0]);
    }

    return 0;
}





//1)Write a C program to get and set the resource limits such as files, memory associated with a
//process
#include <stdio.h>
#include <stdlib.h>
#include <sys/resource.h>

void print_and_set_limit(int resource, long long new_limit) {
    struct rlimit limits;

    
    if (getrlimit(resource, &limits) == -1) {
        perror("getrlimit");
        exit(EXIT_FAILURE);
    }

    
    printf("Current limit: %lld bytes\n", (long long)limits.rlim_cur);

    
    limits.rlim_cur = new_limit;
    if (setrlimit(resource, &limits) == -1) {
        perror("setrlimit");
        exit(EXIT_FAILURE);
    }

    
    if (getrlimit(resource, &limits) == -1) {
        perror("getrlimit");
        exit(EXIT_FAILURE);
    }
    printf("Updated limit: %lld bytes\n\n", (long long)limits.rlim_cur);
}

int main() {
    
    print_and_set_limit(RLIMIT_NOFILE, 1024);

    
    print_and_set_limit(RLIMIT_AS, 1024 * 1024 * 1024);

    
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

//2)Write a C program which creates a child process to run linux/ unix command or any user defined
//program. The parent process set the signal handler for death of child signal and Alarm signal. If
//a child process does not complete its execution in 5 second then parent process kills child process.

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>
#include <string.h>

pid_t child_pid = -1;

void handle_child_death(int sig) {
    int status;
    pid_t pid = waitpid(child_pid, &status, WNOHANG);  // Non-blocking wait
    if (pid == -1) {
        perror("waitpid");
        exit(1);
    }
    if (pid > 0) {
        if (WIFEXITED(status)) {
            printf("Child process %d terminated normally with exit status %d\n", pid, WEXITSTATUS(status));
        } else if (WIFSIGNALED(status)) {
            printf("Child process %d terminated by signal %d\n", pid, WTERMSIG(status));
        } else {
            printf("Child process %d terminated abnormally\n", pid);
        }
    }
}

void handle_alarm(int sig) {
    if (child_pid > 0) {
        printf("Timeout reached! Killing child process %d...\n", child_pid);
        kill(child_pid, SIGKILL);  // Kill the child process after 5 seconds
    }
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <command> [arguments...]\n", argv[0]);
        exit(1);
    }

    
    struct sigaction sa_child, sa_alarm;
    memset(&sa_child, 0, sizeof(sa_child));
    sa_child.sa_handler = handle_child_death;
    sigaction(SIGCHLD, &sa_child, NULL);

    memset(&sa_alarm, 0, sizeof(sa_alarm));
    sa_alarm.sa_handler = handle_alarm;
    sigaction(SIGALRM, &sa_alarm, NULL);

    
    child_pid = fork();
    if (child_pid < 0) {
        perror("fork");
        exit(1);
    }

    if (child_pid == 0) {
        
        printf("Child process started with PID %d. Executing command...\n", getpid());
        execvp(argv[1], &argv[1]);  
        
        perror("execvp");
        exit(1);
    } else {
        
        printf("Parent process waiting for child process...\n");

        
        alarm(5);

        
        pause();  
    }

    return 0;
}



//1)Display all the files from current directory which are created in particular month.
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <time.h>
#include <string.h>

void list_files_created_in_month(const char *directory, int target_month) {
    struct dirent *entry;
    struct stat file_stat;
    DIR *dir = opendir(directory);

    if (!dir) {
        perror("opendir");
        return;
    }

    printf("Files created in month %d:\n", target_month);

    while ((entry = readdir(dir)) != NULL) {
        
        if (entry->d_type != DT_REG) {
            continue;
        }

       
        if (stat(entry->d_name, &file_stat) == -1) {
            perror("stat");
            continue;
        }

       
        struct tm *time_info = localtime(&file_stat.st_ctime);

        
        if (time_info->tm_mon + 1 == target_month) { 
            printf("%s\n", entry->d_name);
        }
    }

    closedir(dir);
}

int main() {
    char directory[256] = ".";
    int target_month;

    
    printf("Enter the month number (1-12): ");
    if (scanf("%d", &target_month) != 1 || target_month < 1 || target_month > 12) {
        printf("Invalid month number!\n");
        return 1;
    }

    
    list_files_created_in_month(directory, target_month);

    return 0;
}



// 2) Write a C program which creates a child process and child process catches a signal SIGHUP,
//SIGINT and SIGQUIT. The Parent process send a SIGHUP or SIGINT signal after every 3
//seconds, at the end of 15 second parent send SIGQUIT signal to child and child terminates by
//displaying message "My Papa has Killed me!!!”


#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
void sighup();
void sigint();
void sigquit();

int main() {
    int pid, i, j;
    
    if ((pid = fork()) < 0) {
        perror("fork");
        exit(1);
    }

    if (pid == 0) { 
        
        signal(SIGHUP, sighup);
        signal(SIGINT, sigint);
        signal(SIGQUIT, sigquit);
        

        for (;;) {
            pause(); 
        }
    } else { 
        j = 0;
        for (i = 1; i <= 5; i++) {
            j++;
            printf("PARENT: sending SIGHUP Signal : %d\n", j);
            kill(pid, SIGHUP);  
            sleep(3);
            
            printf("PARENT: Sending SIGINT Signal : %d\n", j);
            kill(pid, SIGINT); 
            sleep(3);
        }
        
        sleep(3);
        printf("Parent sending SIGQUIT\n");
        kill(pid, SIGQUIT); 
    }

    return 0; 
}

void sighup() {
   
    printf("Child: I have received SIGHUP\n");
}

void sigint() {
   
    printf("Child: I have received SIGINT\n");
}

void sigquit() {
    printf("My daddy has killed me\n");
    exit(0);  
}



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


//2) Write a C program to implement the following unix/linux command (use fork, pipe and exec
//system call). Your program should block the signal Ctrl-C and Ctrl-\ signal during the execution.
//i. Ls –l | wc –l 
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>

void block_signals() {
    sigset_t set;
    sigemptyset(&set);
    sigaddset(&set, SIGINT);  
    sigaddset(&set, SIGQUIT);  
    sigprocmask(SIG_BLOCK, &set, NULL);
}

int main() {
    int pipe_fd[2];
    pid_t pid1, pid2;

   
    if (pipe(pipe_fd) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    
    block_signals();

    
    pid1 = fork();
    if (pid1 == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid1 == 0) {
        
        close(pipe_fd[0]);

        
        dup2(pipe_fd[1], STDOUT_FILENO);

       
        execlp("ls", "ls", "-l", NULL);
       
        perror("execlp ls");
        exit(EXIT_FAILURE);
    } else {
        
        pid2 = fork();
        if (pid2 == -1) {
            perror("fork");
            exit(EXIT_FAILURE);
        }

        if (pid2 == 0) {
            
            close(pipe_fd[1]);

            
            dup2(pipe_fd[0], STDIN_FILENO);

            
            execlp("wc", "wc", "-l", NULL);
           
            perror("execlp wc");
            exit(EXIT_FAILURE);
        } else {
           
            close(pipe_fd[0]);
            close(pipe_fd[1]);

            waitpid(pid1, NULL, 0);
            waitpid(pid2, NULL, 0);

            printf("Program finished.\n");
        }
    }

    return 0;
}



//1)Write a C program to find whether a given file is present in current directory or not.

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
int main(int argc, char *argv[]) {
 if (argc != 2) {
 fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
 exit(EXIT_FAILURE);
 }
 const char *filename = argv[1];
 if (access(filename, F_OK) == 0) {
 printf("The file '%s' is present in the current directory.\n", filename);
 } else {
 printf("The file '%s' is not present in the current directory.\n", filename);
 }
 return 0;
}

// 2) Write a C program to create an unnamed pipe. The child process will write following three
//messages to pipe and parent process display it.
//Message1 = “Hello World”
//Message2 = “Hello SPPU”
//Message3 = “Linux is Funny.

#include<stdio.h>
#include<unistd.h>
int main()
{
int pipefds[2];
int returnstatus;
char writemessages[3][20]={"Hello World", "Hello SPPU","Linux isFunny"};
char readmessage[20];
returnstatus = pipe(pipefds);
if (returnstatus == -1) {
printf("Unable to create pipe\n");
return 1;
}
int child = fork();
if(child==0){
printf("Child is Writing to pipe - Message 1 is %s\n", writemessages[0]);
write(pipefds[1], writemessages[0], sizeof(writemessages[0]));
printf("Child is Writing to pipe - Message 2 is %s\n", writemessages[1]);
write (pipefds[1],writemessages[1], sizeof(writemessages[1]));
printf("Child is Writing to pipe - Message 3 is %s\n", writemessages[2]);
write(pipefds[1], writemessages[2], sizeof(writemessages[2]));
}
else {
read(pipefds[0], readmessage, sizeof(readmessage));
printf("Parent Process is Reading from pipe – Message 1 is %s\n",readmessage);
read(pipefds[0], readmessage, sizeof(readmessage));
printf("Parent Process is Reading from pipe – Message 2 is %s\n",readmessage);
read(pipefds[0], readmessage, sizeof(readmessage));
printf("Parent Process is Reading from pipe – Message 3 is %s\n",readmessage);
}
}



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
            continue; 
        }
        printf("File: %s\nInode: %ld\n", argv[i], (long)file_info.st_ino);
        print_file_type(file_info.st_mode); 
        printf("---------------\n");
    }
    return 0;
}

//2)Implement the following unix/linux command (use fork, pipe and exec system call)
//ls –l | wc –l. 

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    int pipe_fd[2];
    pid_t pid1, pid2;

   
    if (pipe(pipe_fd) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    if ((pid1 = fork()) == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid1 == 0) {
        close(pipe_fd[0]); 
        dup2(pipe_fd[1], STDOUT_FILENO); 
        close(pipe_fd[1]); 
        execlp("ls", "ls", "-l", NULL); 
        perror("execlp"); 
        exit(EXIT_FAILURE);
    }

   
    if ((pid2 = fork()) == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid2 == 0) {
        close(pipe_fd[1]); 
        dup2(pipe_fd[0], STDIN_FILENO); 
        close(pipe_fd[0]); 
        execlp("wc", "wc", "-l", NULL);  
        perror("execlp"); 
        exit(EXIT_FAILURE);
    }

   
    close(pipe_fd[0]);
    close(pipe_fd[1]);
    waitpid(pid1, NULL, 0); 
    waitpid(pid2, NULL, 0); 

    return 0;
}



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



   
//2)Write a C program to Identify the type (Directory, character device, Block device, Regular file,
//FIFO or pipe, symbolic link or socket) of given file using stat() system call.

#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        return EXIT_FAILURE;
    }

    struct stat file_info;
    if (stat(argv[1], &file_info) == -1) {
        perror("stat");
        return EXIT_FAILURE;
    }

    const char *file_type = "unknown";
    if (S_ISREG(file_info.st_mode)) file_type = "regular file";
    else if (S_ISDIR(file_info.st_mode)) file_type = "directory";
    else if (S_ISLNK(file_info.st_mode)) file_type = "symbolic link";
    else if (S_ISFIFO(file_info.st_mode)) file_type = "named pipe (FIFO)";
    else if (S_ISSOCK(file_info.st_mode)) file_type = "socket";
    else if (S_ISCHR(file_info.st_mode)) file_type = "character special file";
    else if (S_ISBLK(file_info.st_mode)) file_type = "block special file";

    printf("%s is a %s.\n", argv[1], file_type);
    return 0;
}




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



//1) Write a C Program that demonstrates redirection of standard output to a file.

#include <stdio.h>
int main() {
 
 freopen("krushna1.txt", "w", stdout);
 
 printf("This is redirected standard output.\n");
 
 
 fclose(stdout);
 return 0;
}


//2) Write a C program to implement the following unix/linux command (use fork, pipe and exec
//system call). Your program should block the signal Ctrl-C and Ctrl-\ signal during the execution.
//i. Ls –l | wc –l 
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>

void block_signals() {
    sigset_t set;
    sigemptyset(&set);
    sigaddset(&set, SIGINT);  
    sigaddset(&set, SIGQUIT);  
    sigprocmask(SIG_BLOCK, &set, NULL);
}

int main() {
    int pipe_fd[2];
    pid_t pid1, pid2;

    
    if (pipe(pipe_fd) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    
    block_signals();

    
    pid1 = fork();
    if (pid1 == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid1 == 0) {
        
        close(pipe_fd[0]);

        dup2(pipe_fd[1], STDOUT_FILENO);

        
        execlp("ls", "ls", "-l", NULL);
        
        perror("execlp ls");
        exit(EXIT_FAILURE);
    } else {
        
        pid2 = fork();
        if (pid2 == -1) {
            perror("fork");
            exit(EXIT_FAILURE);
        }

        if (pid2 == 0) {
            
            close(pipe_fd[1]);

            
            dup2(pipe_fd[0], STDIN_FILENO);

            
            execlp("wc", "wc", "-l", NULL);
           
            perror("execlp wc");
            exit(EXIT_FAILURE);
        } else {
            
            close(pipe_fd[0]);
            close(pipe_fd[1]);

            
            waitpid(pid1, NULL, 0);
            waitpid(pid2, NULL, 0);

            printf("Program finished.\n");
        }
    }

    return 0;
}




//1)Write a C program to find whether a given file is present in current directory or not.

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
int main(int argc, char *argv[]) {
 if (argc != 2) {
 fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
 exit(EXIT_FAILURE);
 }
 const char *filename = argv[1];
 if (access(filename, F_OK) == 0) {
 printf("The file '%s' is present in the current directory.\n", filename);
 } else {
 printf("The file '%s' is not present in the current directory.\n", filename);
 }
 return 0;
}

//2)Write a C program to Identify the type (Directory, character device, Block device, Regular file,
//FIFO or pipe, symbolic link or socket) of given file using stat() system call.

#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        return EXIT_FAILURE;
    }

    struct stat file_info;
    if (stat(argv[1], &file_info) == -1) {
        perror("stat");
        return EXIT_FAILURE;
    }

    const char *file_type = "unknown";
    if (S_ISREG(file_info.st_mode)) file_type = "regular file";
    else if (S_ISDIR(file_info.st_mode)) file_type = "directory";
    else if (S_ISLNK(file_info.st_mode)) file_type = "symbolic link";
    else if (S_ISFIFO(file_info.st_mode)) file_type = "named pipe (FIFO)";
    else if (S_ISSOCK(file_info.st_mode)) file_type = "socket";
    else if (S_ISCHR(file_info.st_mode)) file_type = "character special file";
    else if (S_ISBLK(file_info.st_mode)) file_type = "block special file";

    printf("%s is a %s.\n", argv[1], file_type);
    return 0;
}

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
            continue;
        }
        printf("File: %s\nInode: %ld\n", argv[i], (long)file_info.st_ino);
        print_file_type(file_info.st_mode); 
        printf("---------------\n");
    }
    return 0;
}


//2)Write a C program which creates a child process to run linux/ unix command or any user defined
//program. The parent process set the signal handler for death of child signal and Alarm signal. If
//a child process does not complete its execution in 5 second then parent process kills child process.

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>
#include <string.h>

pid_t child_pid = -1;

void handle_child_death(int sig) {
    int status;
    pid_t pid = waitpid(child_pid, &status, WNOHANG); 
    if (pid == -1) {
        perror("waitpid");
        exit(1);
    }
    if (pid > 0) {
        if (WIFEXITED(status)) {
            printf("Child process %d terminated normally with exit status %d\n", pid, WEXITSTATUS(status));
        } else if (WIFSIGNALED(status)) {
            printf("Child process %d terminated by signal %d\n", pid, WTERMSIG(status));
        } else {
            printf("Child process %d terminated abnormally\n", pid);
        }
    }
}

void handle_alarm(int sig) {
    if (child_pid > 0) {
        printf("Timeout reached! Killing child process %d...\n", child_pid);
        kill(child_pid, SIGKILL); 
    }
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <command> [arguments...]\n", argv[0]);
        exit(1);
    }

    
    struct sigaction sa_child, sa_alarm;
    memset(&sa_child, 0, sizeof(sa_child));
    sa_child.sa_handler = handle_child_death;
    sigaction(SIGCHLD, &sa_child, NULL);

    memset(&sa_alarm, 0, sizeof(sa_alarm));
    sa_alarm.sa_handler = handle_alarm;
    sigaction(SIGALRM, &sa_alarm, NULL);

    
    child_pid = fork();
    if (child_pid < 0) {
        perror("fork");
        exit(1);
    }

    if (child_pid == 0) {
        
        printf("Child process started with PID %d. Executing command...\n", getpid());
        execvp(argv[1], &argv[1]); 
        
        perror("execvp");
        exit(1);
    } else {
        
        printf("Parent process waiting for child process...\n");

       
        alarm(5);

       
        pause(); 
    }

    return 0;
}




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



