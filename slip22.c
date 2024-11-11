//1) Write a C Program that demonstrates redirection of standard output to a file.

#include <stdio.h>
int main() {
 // Redirect standard output to a file
 freopen("krushna1.txt", "w", stdout);
 // Print to standard output (now redirected to "output.txt")
 printf("This is redirected standard output.\n");
 
 // Close the redirected file stream
 fclose(stdout);
 return 0;
}


