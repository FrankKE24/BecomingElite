#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char const *argv[])
{
    //printf*"==="
    char *filename;
    char buffer[100], typedInput[50];
    puts("APPEND-MODE");
    char full_filename[200];
    printf("Enter name of your file: ");
    scanf("%s", filename);
    snprintf(full_filename, sizeof(full_filename), "%s.txt", filename);
    FILE *file_ptr = fopen(full_filename, "a+");
    /*if(setvbuf(file_ptr, buffer, _IOLBF, 100) != 0){
        printf("nRequest could not be honoured");
    }*/

    if(file_ptr == NULL){
        printf("File not found\n");
    }

    while(fgets(buffer, 100, file_ptr)){
        printf("%s", buffer);
    }

    int count = 0;
    printf("\nContinue typing....  ");
    while(count < sizeof(typedInput)){
        int ch = getchar();
        if(ch != EOF){
            typedInput[count++] = (char)ch;
        }
    }
    typedInput[count] = '\0';
    printf("\nYou typed %s\n", typedInput);

    //fgets(typedInput, 10, stdin);

    //typedInput[strlen(typedInput) -1] = '\0';
    fprintf(file_ptr, "%s", typedInput);
    fclose(file_ptr);
    return 0;
}
