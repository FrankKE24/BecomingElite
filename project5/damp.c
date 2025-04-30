#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main(int argc, char const *argv[])
{
    char fileName[20];
    char buffer[256] =  {0}; // Initialize buffer to ensure it's null-terminated;
    puts("READ BINARY");
    printf("Filename: ");
    scanf("%19s", fileName);
    FILE *fileptr = fopen(strcat(fileName, ".dat"), "rb");
    if(fileptr == NULL){
        printf("\nError opening file");
        return EXIT_FAILURE;
    }
    if(fread(buffer, sizeof(buffer) - 1, 1, fileptr) != 1){
        printf("\nError reading from file");
        fclose(fileptr);
        return 1;      
    }
    
    printf("%s", buffer);
    puts("\nEnd of File");
    fclose(fileptr);

    return 0;
}

/*
The buffer is not guaranteed to be null-terminated after fread.
 If the file's content doesn't include a null character, 
 printf("%s", buffer) will read past the end of the buffer,
  potentially printing garbage or causing another segmentation fault*/