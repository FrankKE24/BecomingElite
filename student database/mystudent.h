#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

struct Student{
    char RegNo[12];
    char student_passwd[11];
    char name[16];
    char grade[5];
};

void View_results(){
    char name[15];
    printf("NAME: ");
    scanf("%14s", name);
    //toupper(name);

    struct Student student;
    FILE *filePtr = fopen(strcat(name, ".dat"), "r");
    if(filePtr == NULL){
        printf("Error opening transcript!");
        EXIT_FAILURE;
    }
    fread(&student, sizeof(struct Student), 1, filePtr);
    printf("----NAME----REGNo-----GRADE----\n");
    printf( " %s\t   %s\t  %s\n", name, student.RegNo, student.grade);
    fclose(filePtr);
    
    return;
}