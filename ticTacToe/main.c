#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char const *argv[])
{
    char *phrase = "I hate feminists. Toxic women";
    char filename[20];

    printf("Enter name of the file: ");
    scanf("%19s", filename);

    FILE *fileptr = fopen(strcat(filename, ".txt"), "w");
    if(fileptr == NULL){
        printf("Error opening file");
        return EXIT_FAILURE;
    }

    fprintf(fileptr, phrase);
    fclose(fileptr);

    fopen(filename, "r");
    if(fileptr == NULL){
        printf("Error opening file");
        return EXIT_FAILURE;
    }
   
    char buffer[30];
    while (fgets(buffer, sizeof(buffer), fileptr)){
        printf("%s", buffer);
    }
    fclose(fileptr);

    return 0;
}
