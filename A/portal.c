#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "student.h"

void Record_results();

struct Lecturer{
    char passkey[12];
    char username[16];
    char name[14];
};

int main(int argc, char const *argv[])
{
    struct Lecturer lec1;
    struct Student student;

    int choiceA;
    char filename[16], name[14], pwd[12];

    printf("<<<<<<<<<<GET STARTED>>>>>>>>>>>\n");
    label1:
    printf("\nDesignation");
    printf("\n.1. Staff");
    printf("\n2. Student");
    printf("\n\n3.EXIT");
    printf("\nEnter choice: ");
    scanf("%d", &choiceA);

    system("clear");

    if(choiceA == 1){
        int staffChoice;

        printf("<<<<<<<<<<WELCOME TO THE ADMIN PLARTFORM>>>>>>>>>>>\n");
        stafflabel:
        printf("\nDesignation");
        printf("\n.1. Create an account");
        printf("\n2. Login to your account");
        printf("\n3. Back");
        printf("\n4. Exit");
        printf("\nEnter choice: ");
        scanf("%d", &staffChoice);
        system("clear");

        if(staffChoice == 1){
            printf("\n...Enter your details");
            printf("\nName: ");
            scanf("%14s", lec1.name);
            printf("Set your password: ");
            scanf("%12s", lec1.passkey);

            char placeholder[17] = "@";
            char *username = strncat(placeholder, lec1.name, strlen(lec1.name));
            strcpy(filename, username);
            FILE *pfile = fopen(strcat(filename, ".dat"), "w");

            if(pfile == NULL){
                printf("Error opening transcript!");
                EXIT_FAILURE;
            }
            if(fwrite(&lec1, sizeof(struct Lecturer), 1, pfile) != 1){
                printf("\nError creating account!");
                goto stafflabel;
            }
            printf("\nAccount created successfully\n");

        }
        else if(staffChoice == 2){
            printf("\nYoure about to log in to your Account..");
            printf("\nUsername: ");
            scanf("%14s", name);
            printf("Password: ");
            scanf("%12s", pwd);
            strcpy(filename, name);
            FILE *ptrfile = fopen(strcat(filename, ".dat"), "r");
            if(ptrfile == NULL){
                printf("\nNo staff with such details is registered!");
                goto stafflabel;
            }

            fread(&lec1, sizeof(struct Lecturer), 1, ptrfile);
            if(strcmp(pwd, lec1.passkey) != 0){
                printf("\nWrong Pasword....\n.....-TRY AGAIN-.....");
                goto stafflabel;
            }
            fclose(ptrfile);
            system("clear");
            printf("\n...RECORD RESULTS\n\n");
            Record_results();
        }
        else if(staffChoice == 3){
            goto label1;
        }
        else if(staffChoice == 4){
            puts("...EXITING...");
            exit(0);
        }
        else{
            printf("iNVALID CHOICE!");
            goto label1;
        }
    }
    else if(choiceA == 2){
        int studentChoice;
        
        printf("<<<<<<<<<<WELCOME TO THE STUDENT PLARTFORM>>>>>>>>>>>\n");
        studentlabel:
        printf("\n1. Create an account");
        printf("\n2. Login to your Student account");
        printf("\n3. Back");
        printf("\n4. Exit");
        printf("\nEnter choice: ");
        scanf("%d", &studentChoice);
        system("clear");

        if(studentChoice ==1 ){
            char filename[16];
            printf("\n...Enter your details");
            printf("\nName: ");
            scanf("%15s", student.name);
            printf("RegNo: ");
            scanf("%10s", student.RegNo);
            printf("Set your password: ");
            scanf("%10s", student.student_passwd);

            //strcpy(filename, student.RegNo);
            FILE *pfile = fopen(strcat(student.RegNo, ".dat"), "w");
            if (pfile == NULL){
                printf("\nError creating SStudents account!");
                //fclose(pfile);
                goto studentlabel;
            }
            
            if(fwrite(&student, sizeof(struct Student), 1, pfile) != 1){
                printf("\nError writing to login file!");
                fclose(pfile);
                goto studentlabel;
            }
            fclose(pfile);
            printf("...Student account created succcessfully\n...logging you out...\n");
            goto studentlabel;
        }
        else if(studentChoice == 2){
            char pwd[11], reg[12];
            printf("You are about to log in to your student account\n");
            printf("REG_No: ");
            scanf("%11s", reg);
            printf("Password: ");
            scanf("%10s", pwd);
            strcpy(filename, reg);

            FILE *pfile = fopen(strcat(filename, ".dat"), "r");
            if (pfile == NULL){
                printf("\nNo student account is registered under %s!", reg);
                //fclose(pfile);
                goto studentlabel;
            }

            fread(&student, sizeof(struct Student), 1, pfile);
            if(strcmp(student.student_passwd, pwd) !=0){
                printf("\nWRONG PASSWORD!\n...try again..\n");
                fclose(pfile);
                goto studentlabel;
            }

            fclose(pfile);
            printf("You have successfulyy logged into ypur Student Acount\n");
            printf("OPening transcript.......\n");
            View_results();
        }
        else if(studentChoice == 3){
            goto label1;
        }
        else if(studentChoice == 4){
            puts("...EXITING...");
            exit(0);
        }
        else{
            printf("iNVALID CHOICE!");
            goto label1;
        }

    }
    else if(choiceA == 3){
        puts("...EXITING...");
        exit(0);
    }
    else{
        printf("iNVALID CHOICE!");
    }
    return 0;
}

void Record_results(){
    int attendance;
    printf("Enter number of your students: ");
    scanf("%d", &attendance);

    struct Student mystudents[attendance];

    for (int i = 0; i < attendance; i++)
    {
        printf("%d.", i+1);
        printf("NAME: ");
        scanf("%19s", mystudents[i].name);
        printf("REG-NO: ");
        scanf("%11s", mystudents[i].RegNo);
        printf("GRADE: ");
        scanf("%4s", mystudents[i].grade);

        FILE *fileptr = fopen(strcat(mystudents[i].name, ".dat"), "w");
        if(fileptr == NULL){
            printf("\nError creating transcript!");
            EXIT_FAILURE;
        }
        if(fwrite(&mystudents[i], sizeof(struct Student), 1, fileptr) != 1){
            printf("\nError writing to transcript!");
        }
        fclose(fileptr);
    }

    printf("\nYou have successfully recorded students' results...\n");
    return;
    
}