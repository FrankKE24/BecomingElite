#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "records2.h"

void View_records();
void Search_record();
void Delete_record();
void Create_New_Record();
void Edit_record();

char  reg[12], filename[17];
int entries;

int main(int argc, char const *argv[])
{
    struct Lecturer lec1;
    //struct Student mystudents;

    int choiceA;
    char name[14], pwd[12];

    printf("<<<<<<<<<<GET STARTED>>>>>>>>>>>\n");
    label1:
    printf("\nDesignation");
    printf("\n1. Staff");
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
        printf("\n1. Create an account");
        printf("\n2. Login to your account");
        printf("\n3. Back");
        printf("\n4. Exit");
        printf("\nEnter choice: ");
        scanf("%d", &staffChoice);
        system("clear");

        if(staffChoice == 1){
            printf("\n...Enter your details");
            printf("\nName: ");
            scanf("%13s", lec1.name);
            printf("Set your password: ");
            scanf("%11s", lec1.passkey);

            char placeholder[17] = "@";
            char *username = strncat(placeholder, lec1.name, strlen(lec1.name));
            strcpy(filename, username);
            FILE *pfile = fopen(strcat(filename, ".dat"), "w");

            if(pfile == NULL){
                printf("Error creating  admin account!");
                EXIT_FAILURE;
            }
            if(fwrite(&lec1, sizeof(struct Lecturer), 1, pfile) != 1){
                printf("\nError creating account!");
                goto label1;
            }
            printf("\nAccount created successfully\n....logging you out\n");
            goto label1;
        }
        else if(staffChoice == 2){
            printf("\nYoure about to log in to your Account..");
            printf("\nUsername: ");
            scanf("%17s", name);
            printf("Password: ");
            scanf("%11s", pwd);
            strcpy(filename, name);
            FILE *ptrfile = fopen(strcat(filename, ".dat"), "r");
            if(ptrfile == NULL){
                printf("\nNo staff with such details is registered!");
                goto stafflabel;
            }

            fread(&lec1, sizeof(struct Lecturer), 1, ptrfile);
            if(strcmp(pwd, lec1.passkey) != 0){
                printf("\nWrong Pasword....\n.....-TRY AGAIN-.....");
                fclose(ptrfile);
                goto stafflabel;
            }
            fclose(ptrfile);
            system("clear");

            int staffChoice2;

            printf("\nsuccessfully logged in...\n...DATABASE ACTION\n");
            staffLabel2:
            printf("\n1. Enter new record/Update a record");
            printf("\n2. Edit a record");
            printf("\n3. Search for a record");
            printf("\n4. Delete a student record");
            printf("\n5. Display students' records");
            printf("\n6. Back");
            printf("\n7. EXIT");
            printf("\nEnter choice: ");
            scanf("%d", &staffChoice2);
            system("clear");

            if(staffChoice2 == 1){
                //Create_New_Record();
                            
                printf("\nNew record");
                printf("\nEnter number of entries to create: ");
                scanf("%d", &entries);
                struct Student mystudents[entries];
                
                for (int i = 0; i < entries; i++){                                    
                    printf("%d.", i+1);
                    printf("NAME: ");
                    getchar();
                    fgets(mystudents[i].full_name, 30, stdin);
                    mystudents[i].full_name[strlen(mystudents[i].full_name) - 1] = '\0';
                    //scanf("%19s", mystudents[i].full_name);
                    printf("Date of Birth: ");
                    scanf("%15s", mystudents[i].DoB);
                    printf("REG-NO: ");
                    scanf("%11s", mystudents[i].RegNo);
                    printf("STREAM: ");
                    scanf("%9s", mystudents[i].stream);
                    printf("GRADE: ");
                    scanf("%4s", mystudents[i].mean_grade);
                    
                    FILE *fileptr = fopen(strcat(mystudents[i].RegNo, ".dat"), "w");
                    if(fileptr == NULL){
                        printf("\nError creating Record!");
                        EXIT_FAILURE;
                    }
                    if(fwrite(&mystudents[i], sizeof(struct Student), 1, fileptr) != 1){
                        fclose(fileptr);
                        printf("\nError writing to Record!");
                    }
                    fclose(fileptr);
                }
            }
            else if(staffChoice2 == 2){
                //Edit a record
                struct Student student;
                printf("\nEdit a Student's record...\n\n");
                printf("REG-NO: ");
                scanf("%11s", reg);
                strcpy(filename, reg);
            
                FILE *pfile = fopen(strcat(filename, ".dat"), "r");
                if(pfile == NULL){
                    printf("\nNo student with Admission number %s is registered!", reg);
                    goto staffLabel2;
                }
            
                fread(&student, sizeof(struct Student), 1, pfile);
                printf("\nCurrent details\n");
                printf("------------FULL NAME-----------REGNo-------DoB--------STREAM------------MEAN GRADE----\n");
                printf( "%s\t       %s\t      %s\t       %s\t    %s\n", student.full_name, student.RegNo, student.DoB, student.stream, student.mean_grade);
                fclose(pfile);
                
                FILE *pfile2 = fopen(strcat(filename, ".dat"), "w");
                if(pfile2 == NULL){
                    printf("\nNo student with Admission number %s is registered!", reg);
                    goto staffLabel2;
                }

                fread(&student, sizeof(struct Student), 1, pfile);
                printf("Type in new details..\n");
                printf("NAME: ");
                fgets(student.full_name, 30, stdin);
                student.full_name[strlen(student.full_name) - 1] = '\0';
                //scanf("%19s", mystudents[i].full_name);
                printf("Date of Birth: ");
                scanf("%15s", student.DoB);
                printf("REG-NO: ");
                scanf("%11s", student.RegNo);
                printf("STREAM: ");
                scanf("%9s", student.stream);
                printf("GRADE: ");
                scanf("%4s", student.mean_grade);
                if(fwrite(&student, sizeof(struct Student), 1, pfile2) != 1){
                    printf("Error updating %s's record", student.full_name);
                    fclose(pfile2);
                    goto staffLabel2;
                }
                fclose(pfile2);
            }
            else if(staffChoice2 == 3){
                //Search_record();
                            
                struct Student student;
                printf("\nSearch for a Student record...\n\n");
                printf("REG-NO: ");
                scanf("%11s", reg);
                strcpy(filename, reg);

                FILE *pfile = fopen(strcat(filename, ".dat"), "r");
                if(pfile == NULL){
                    printf("\nNo student with Admission number %s is registered!", reg);
                    goto staffLabel2;
                }

                fread(&student, sizeof(struct Student), 1, pfile);
                printf("------------FULL NAME-----------REGNo-----------DoB--------STREAM------------MEAN GRADE----\n");
                printf( "%s\t       %s\t      %s\t      %s\t     %s\n", student.full_name, student.RegNo, student.DoB, student.stream, student.mean_grade);
                fclose(pfile);
            }
            else if(staffChoice2 == 4){
                //Delete_record();
                            
                struct Student student;
                printf("\nDELETE STUDENT RECORD....\n\n");
                printf("REG-NO: ");
                scanf("%11s", reg);
                strcpy(filename, reg);

                FILE *pfile = fopen(strcat(filename, ".dat"), "r");
                if(pfile == NULL){
                    printf("\nNo student with Admission number %s is registered!", reg);
                    goto staffLabel2;
                }

                fread(&student, sizeof(struct Student), 1, pfile);

                char *delete_file = strcat(reg, ".dat");
                char affirmation;
                printf("\nAre you sure you want to delete %s, the record of %s?", delete_file, student.full_name);
                printf("Y or N: ");
                scanf("%s", &affirmation);
                fclose(pfile);
                if(affirmation == 'Y' || 'y'){
                    if(remove(delete_file) == 0)
                        printf("\nRecord of %s successfully deleted", reg);
                    else
                        printf("\nUnable to delete the record");
                }
                else{
                    printf("\nYou cancelled!\n");
                    goto staffLabel2;
                }
            }
            else if(staffChoice == 5){
                printf("\nUNDEFINED FIELD!");
                exit(0);
            }
            else if(staffChoice == 6){
                goto label1;
            }
            else if(staffChoice == 7){
                puts("...EXITING...");
                exit(0);
            }
            else{
                printf("\nInvalid choice!");
                goto staffLabel2;
            }

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
        puts("...UNDEFINED FIELD...");
        exit(0);
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
