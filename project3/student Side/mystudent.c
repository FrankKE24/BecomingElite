#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "records2.h"

void View_record(char []);
void Student_function();

char menu_choice[2];


void Student_function(){
    char filename[11];
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
        char filename[16], passwd[11], name[30], RegNo[12];//I'm declaring name and RegNo instead of using student.name anfd sstudent.RegNo to avoid appending a name
        //onto the existing name created by staff
        printf("\n...Enter your details To Create an Account");
        printf("\nName: ");
        getchar();
        fgets(name, 30, stdin);
        name[strlen(name) - 1] = '\0';
        printf("RegNo: ");
        scanf("%11s", RegNo);
        printf("Set your password: ");
        scanf("%10s", passwd);
        strcpy(student.student_passwd, passwd);

        //you can only create an account if your record already existss in the system
        char *fileA = strcat(RegNo, ".dat");
        printf("\n%s", fileA);
        FILE *pfile = fopen(fileA, "rb");
        if(pfile == NULL){
            printf("\nYou cannot create an Student's account");
            goto studentlabel;
        }
        fclose(pfile);

        //strcpy(filename, student.RegNo);
        pfile = fopen(fileA, "ab");
        if (pfile == NULL){
            printf("\nError creating account!");
            //fclose(pfile);
            goto studentlabel;
        }

        if (fwrite(&student, sizeof(struct Student), strlen(student.student_passwd), pfile) != 1)
        {
            printf("\nError writing to login file!");
            fclose(pfile);
            goto studentlabel;       
        }
        
        
        /*if(fwrite(&student, sizeof(struct Student), 1, pfile) != 1){
            printf("\nError writing to login file!");
            fclose(pfile);
            goto studentlabel;
        }*/
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

        int attempts = 0;
        fread(&student, sizeof(struct Student), 1, pfile);
        printf("%s", student.student_passwd);
        printf("HERE");

        do
        {
            if(strcmp(student.student_passwd, pwd) !=0){
                printf("\nWRONG PASSWORD!\n...try again..\n");
                printf("Password: ");
                scanf("%10s", pwd);
            }
            attempts++;
            if(attempts == 4){
                puts("Too many attempts!");
                puts("Account locked");
                
                exit(-1);
            }        
        } while (strcmp(student.student_passwd, pwd) !=0);


        fclose(pfile);
        printf("You have successfulyy logged into ypur Student Acount\n");
        printf("Opening your record.......\n");
        View_record(reg);

        printf("\n%s", student.student_passwd);

        printf("\nPress any key to return to main menu: ");
        scanf("%1s", menu_choice);
        if (menu_choice != NULL){
            goto studentlabel;
        }

        system("clear");
    }
    else if(studentChoice == 3){
        goto studentlabel;
    }
    else if(studentChoice == 4){
        puts("...EXITING...");
        exit(0);
    }
    else{
        printf("iNVALID CHOICE!");
        EXIT_FAILURE;
    }
}



void View_record(char reg[]){
    //toupper(name);

    FILE *filePtr = fopen(strcat(reg, ".dat"), "r");
    if(filePtr == NULL){
        printf("Error opening record!");
        EXIT_FAILURE;
    }
    fread(&student, sizeof(struct Student), 1, filePtr);
    printf("----NAME----REGNo------DoB-----STREAM----------GRADE----\n");
    printf( "%s\t   %s\t    %s\t   %s\t  %s\n", student.full_name, student.RegNo, student.DoB, student.stream, student.mean_grade);
    fclose(filePtr);


    return;
}