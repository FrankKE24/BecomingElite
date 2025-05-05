#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

#define FILENAME "plcss.txt"
#define BUFFER_SIZE 1000

int main() {
    // Open the file for reading and writing
    int filedes = open(FILENAME, O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);

    if (filedes == -1) {
        perror("Error opening file");
        return EXIT_FAILURE;
    }

    // Write some data to the file
    //const char *data = "Hallo, World!, today is Wednesday.";
    //write(filedes, data, 35);

    // Use lseek to set the file position
    off_t new_position = lseek(filedes, 10, SEEK_CUR);
    if (new_position == -1) {
        perror("Error seeking in file");
        close(filedes);
        return EXIT_FAILURE;
    }

    // Read from the new position
    char buffer[BUFFER_SIZE];
    ssize_t bytes_read = read(filedes, buffer, sizeof(buffer) - 1);
    if (bytes_read == -1) {
        perror("Error reading from file");
        close(filedes);
        return EXIT_FAILURE;
    }
    
    buffer[bytes_read] = '\0'; // Null-terminate the string
    printf("Read from file: %s\n", buffer);

    printf("%ld", strlen(buffer));

    /*// Use lseek64 for large files (if applicable)
#ifndef __USE_FILE_OFFSET64
    off64_t new_position64 = lseek64(filedes, 0, SEEK_SET);
    if (new_position64 == -1) {
        perror("Error seeking in large file");
        close(filedes);
        return EXIT_FAILURE;
    }
    
    // Read again using lseek64
    bytes_read = read(filedes, buffer, sizeof(buffer) - 1);
#else
   printf("lseek64 is not supported on this system.\n");
#endif*/

   // Close the file descriptor
   close(filedes);

   return EXIT_SUCCESS;
}