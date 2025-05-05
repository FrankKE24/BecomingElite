#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <assert.h>

//#include "bank1.h"

struct Banker{
    char name[30];
    char phone_Number[11];
    char password[15];
    char ID_Number[9];
    double Account_Balance;

};

//sender- 0792085420, pwd-WERA002, ID- 41388870, WERAVUNUKA CAHRLES
//receiver- 0705977608- pwd- FOOD03, ID- 10920095, BARIU SAFO

int main(int argc, char const *argv[])
{
    struct Banker banker;
    int choiceA;
    char filename[9];
    //label1:
    while (1){
        printf("\n-------------BANKING Platform--------------\n");
        printf("\n1. Create Account");
        printf("\n2. Log in to your Banker's Account");
        printf("\n3. Exit");
        printf("\n\nEnter your Choice: ");
        //scanf("%d", &choiceA);
        if (scanf("%d", &choiceA) != 1) {
            printf("Invalid input. Please enter a number.\n");
            while (getchar() != '\n') // Clear input buffer
                continue;
        }
        getchar();

        system("clear");

        if(choiceA == 1){
            printf("\n....Create New Account");
            printf("\nYour Name: ");
            getchar();
            fgets(banker.name, 30, stdin);
            banker.name[strlen(banker.name) - 1] = '\0';
            printf("Phone Number: ");
            scanf("%10s", banker.phone_Number);
            printf("ID  NUmber: ");
            scanf("%8s", banker.ID_Number);
            printf("Set password: ");
            scanf("%14s", banker.password);
            strcpy(filename, banker.ID_Number);

            FILE *fileptr = fopen(strcat(filename, ".dat"), "w");
            if(fileptr == NULL){
                printf("\nError creating Account");
                break;
                //goto label1;
            }

            banker.Account_Balance = 0.00;

            if(fwrite(&banker, sizeof(struct Banker), 1, fileptr) != 1){
                printf("Error!");
                fclose(fileptr);
                break;
                //goto label1;
            }
            fclose(fileptr);

            puts("\nYour account has been successfully created!");
            puts("Logging you out...\n\n");
            break;
            //goto label1;
        }
        else if(choiceA == 2){
            char pwd[15],  ID[9];
            printf("\nLogin to your Banker's personal Account");
            printf("\nID  NUmber: ");
            scanf("%8s", ID);
            getchar();
            printf("Password: ");
            scanf("%14s", pwd);
            strcpy(filename, ID);

            FILE *fileptr = fopen(strcat(filename, ".dat"), "r");
            if(fileptr == NULL){
                printf("\nAccount doesn't Exist!  \nCreate an Account\n");
                break;
                //goto label1;
            }
            
            if(fread(&banker, sizeof(struct Banker), 1, fileptr) != 1){
                printf("\nError reading login file\n");
                fclose(fileptr);
                break;
            }
            fclose(fileptr);
            
            int attempts = 0;
            do
            {
                if(strcmp(banker.password, pwd) !=0){
                    printf("\nWRONG PASSWORD!\n...try again..\n");
                    printf("Password: ");
                    scanf("%14s", pwd);
                }
                attempts++;
                if(attempts == 4){
                    puts("Too many attempts!");
                    puts("Account locked");
                    fclose(fileptr);
                    
                    exit(-1);
                }        
            } while (strcmp(banker.password, pwd) !=0);

            int choiceB;
            system("clear");

            puts(">>>You have successfully logged into your Personal Banker's Account........");

            //label2:
            do{
                puts("\nSelect your option");
                puts("1. Deposit money");
                puts("2. Check Balance");
                puts("3. Withdraw money");
                puts("4. Send Money");
                puts("5. Update your Banker Acoount dEtails");
                puts("6. Back");
                puts("7. EXIT");
                printf("\nEnter your choice: ");
                scanf("%d", &choiceB);
                getchar();

                system("clear");

                double deposit_Amount, withdraw_Amount, send_amount;
                if (choiceB == 1)
                {
                    printf("\nYour current balance is Kshs%.2lf", banker.Account_Balance);
                    printf("\nEnter amount to deposit: Kshs. ");
                    scanf("%lf", &deposit_Amount);
                    getchar();
                    banker.Account_Balance += deposit_Amount;

                    fileptr = fopen(filename, "w");
                    if(fwrite(&banker, sizeof(struct Banker), 1, fileptr) != 1){
                        printf("Error making deposit!");
                        fclose(fileptr);
                        continue;
                    }
                    printf("\nYou have successsfully deposited Kshs%.2lf\n", deposit_Amount);
                    fclose(fileptr);
                }
                else if(choiceB == 2){
                    puts(">>>Check BALANCE");
                    printf("\nYour current account balance is %.2lf\n", banker.Account_Balance);
                    sleep(2);
                }
                else if(choiceB == 3){
                    puts("<<<<<WITHDRAW>>>>");
                    printf("Enter amount to Withdraw: ");
                    scanf("%lf", &withdraw_Amount);
                    getchar();

                    do
                    {
                    
                        if(withdraw_Amount > banker.Account_Balance){
                            printf("\nInsufficient funds in your Account to withdraw %lf\n", withdraw_Amount);
                            puts("Please try a lower amount");
                            printf("Enter amount to Withdraw: ");
                            scanf("%lf", &withdraw_Amount);
            
                        }            
                        while(getchar() != '\n');

                    } while (withdraw_Amount > banker.Account_Balance);
                    system("clear");

                    fileptr = fopen(filename, "w");
                    banker.Account_Balance -= withdraw_Amount;
                    if(fwrite(&banker, sizeof(struct Banker), 1, fileptr) != 1){
                        printf("\nError in withdrawal!\n");
                        fclose(fileptr);
                        continue;
                    }

                    printf("\nYou have  successfully withdrawn %lf", withdraw_Amount);
                    printf("\nCurrent balance is %.2lf", banker.Account_Balance);
                    fclose(fileptr);
                    //goto label2;

                }
                else if(choiceB == 4){
                    char receiverID[9];
                    struct Banker receiver;

                    puts("<<<Send Money>>>");
                    printf("ID number of receiver: ");
                    scanf("%8s", receiverID);
                    printf("Enter amount to send: ");
                    scanf("%lf", &send_amount);
                    strcpy(filename, receiverID);

                    fileptr = fopen(strcat(filename, ".dat"), "r");
                    if(fileptr == NULL){
                        printf("\nUser %s is not registered with our Banking service ", receiverID);
                        continue;
                        //goto label2;
                    }
                    if(fread(&receiver, sizeof(struct Banker), 1, fileptr) != 1){
                        printf("\nError reading receiver's file\n");
                        fclose(fileptr);
                        continue;
                    }
                    fclose(fileptr);
                    
                    do
                    {

                        if(send_amount > banker.Account_Balance){
                            printf("\nInsufficient funds in your Account to send %lf", send_amount);
                            puts("Please try a lower amount");
                            printf("Enter amount to send: ");
                            scanf("%lf", &send_amount);
            
                        }   
                        while(getchar() != '\n');
         
                    } while (send_amount > banker.Account_Balance);
                    system("clear");


                    //printf("name>>>%s\n", filename);
                    fileptr = fopen(filename, "w");
                    receiver.Account_Balance += send_amount;
                    if(fwrite(&receiver, sizeof(struct Banker), 1, fileptr) != 1){
                        printf("\nError perfoming transaction\n");
                        fclose(fileptr);
                        continue;
                    }
                    printf("Transaction successfull\n");
                    fclose(fileptr);

                    strcpy(filename, banker.ID_Number);
                    fileptr = fopen(strcat(filename, ".dat"), "w");
                    banker.Account_Balance -= send_amount;
                    if(fwrite(&banker, sizeof(struct Banker), 1, fileptr) != 1){
                        printf("\nError transaction\n");
                        fclose(fileptr);
                    }
                    fclose(fileptr); // 45249279.00
                    continue;

                }
                else if(choiceB == 5){
                    //You can change your ID number but username wont change
                    char newPWD[15], newName[30], newPhoneNo[11], newID[9];
                    puts("<<<<Edit your banker's details>>>>");
                    printf("\nEnter current password: ");
                    scanf("%14s", newPWD);

                    while (strcmp(banker.password, newPWD) !=0)
                    {
                        //if(strcmp(banker.password, newPWD) !=0){
                        printf("\nWRONG PASSWORD!\n...try again..\n");
                        printf("\nEnter current password: ");
                        scanf("%14s", newPWD);
                        //}                    
                    }
 
                    puts("These are your current details: ");
                    printf("\n%s", banker.name);
                    printf("\n%s", banker.ID_Number);
                    printf("\n%s", banker.phone_Number);
                    printf("\n%s", banker.password);
                    
                    fileptr = fopen(strcat(banker.ID_Number, ".dat"), "w");
                    if(fileptr == NULL){
                        printf("\nERROR");
                        exit(EXIT_FAILURE);
                        //goto label1;
                    }

                    printf("\nYour New name: ");
                    getchar();
                    fgets(newName, 30, stdin);
                    newName[strlen(newName) - 1] = '\0';
                    printf("New phone Number: ");
                    scanf("%10s", newPhoneNo);
                    printf("ID  NUmber: ");
                    scanf("%8s", newID); ///changing the id nummber has no effect as the file name doesn't change
                    printf("Set new password: ");
                    scanf("%14s", newPWD);

                    strcpy(banker.phone_Number, newPhoneNo);
                    strcpy(banker.password, newPWD);
                    strcpy(banker.name, newName);
                    strcpy(banker.ID_Number, newID);

                    if(fwrite(&banker, sizeof(struct Banker), 1, fileptr) != 1){
                        printf("Error updating details!");
                        fclose(fileptr);
                        continue;
                    }
                    fclose(fileptr);
            
                    puts("\nYour account details have been successfully changed!");
                    puts("Logging you out...");
                    exit(0);
                }
                else if(choiceB == 6){
                    break;
                }
                else if(choiceB == 7){
                    //fclose(fileptr);
                    exit(0);
                }
                else{
                    printf("Invalid OPTION!");
                    exit(-1);
                }
    
            }while (1);

            
        } 
        else if(choiceA == 3){
            exit(0);
        }
        else{
            printf("Undefined");
            EXIT_FAILURE;
        }

    }
    puts(".............GOODBYE");
    return 0;
}

