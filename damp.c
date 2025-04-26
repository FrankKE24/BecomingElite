#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char const *argv[])
{
    char next[2];
    char menu_choice[2];

    
    printf("Press any key to return to main menu: ");
    scanf("%s", menu_choice);
    if (menu_choice != NULL ){
        printf("Alright");
        exit(0);
    }
    
    char text[] = "myfile";
    //char *delete_file = strcat(text, ".dat");
    //remove(delete_file);
    //free(*delete_file);
    /*FILE *pfile = fopen("myfile.dat", "r+b");
    if(pfile == NULL){
        printf("\nFile not found");
        EXIT_FAILURE;
    }

    printf("Enter some text: ");
    fgets(text, 20, stdin);
    text[strlen(text) - 1] = '\0';

    //long offset = sizeof(char) * 3;
    //fseek(pfile, offset, SEEK_SET);
    if(fwrite(text, sizeof(text), 1, pfile) != 1){
        puts("Error writing to file");
        EXIT_FAILURE;
    }
    fclose(pfile);

    char buffer[20];
    FILE *pfile2 = fopen("myfile.dat", "r+b");
    if(pfile2 == NULL){
        printf("\nFile not found");
        EXIT_FAILURE;
    }

    fread(&buffer, sizeof(text), 1, pfile2);
    printf("%s\n", buffer);
    fclose(pfile2);*/

    return 0;
}
