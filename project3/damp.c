#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Student{
    char RegNo[12];
    char student_passwd[11];
    char full_name[30];
    char mean_grade[5];
    char stream[10];
    char DoB[16];
};

int main(int argc, char const *argv[])
{
    double principle;
    printf("Enyer ptimciple: ");
    scanf("%ld", &principle);

    printf("\n Yiur principle is %.2lf", principle);
    struct Student student;
    //char buffer[100];
    FILE *filePtr = fopen("14439PR.dat", "r");
    if(filePtr == NULL){
        printf("\nFile not found");
        EXIT_FAILURE;
    }

    fread(&student, sizeof(struct Student), 1, filePtr);
    printf("%s", student.RegNo);

        //printf("%s", buffer);
    
    
    fclose(filePtr);
    //char text[] = "myfile";
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
