#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "bank1.h"

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
    label1:
    printf("\n-------------BANKING Platform--------------\n");
    printf("\n1. Create Account");
    printf("\n2. Log in to your Banker's Account");
    printf("\n4. Exit");
    printf("\n\nEnter your Choice: ");
    scanf("%d", &choiceA);

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
            goto label1;
        }

        banker.Account_Balance = 0.00;

        if(fwrite(&banker, sizeof(struct Banker), 1, fileptr) != 1){
            printf("Error!");
            goto label1;
        }
        fclose(fileptr);

        puts("\nYour account has been successfully created!");
        puts("Logging you out...");
        goto label1;
    }
    else if(choiceA == 2){
        char pwd[15],  ID[9];
        printf("\nLogin to your Banker's personal Account");
        printf("\nID  NUmber: ");
        scanf("%8s", ID);
        printf("Password: ");
        scanf("%14s", pwd);
        strcpy(filename, ID);

        FILE *fileptr = fopen(strcat(filename, ".dat"), "r");
        if(fileptr == NULL){
            printf("\nAccount doesn't Exist!");
            goto label1;
        }
        
        fread(&banker, sizeof(struct Banker), 1, fileptr);
        
        int attempts =0;
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

        puts(">>>You have successfully logged into your Personal Bnaker's Account........");
        label2:
        puts("Select your optoin");
        puts("1. Deposit money");
        puts("2. Check Balance");
        puts("3. Withdraw money");
        puts("4. Send  Money");
        puts("5. Edit your Banker Acoount dEtails");
        puts("6. Back");
        puts("7. EXIT");
        printf("\nEnter your choice: ");
        scanf("%d", &choiceB);
        system("clear");

        double deposit_Amount, withdraw_Amount, send_amount;
        if (choiceB == 1)
        {
            printf("Your current balance is Kshs%.2lf", banker.Account_Balance);
            printf("Enter amount to deposit");
            scanf("%lf", &deposit_Amount);

            banker.Account_Balance += deposit_Amount;
            printf("You have successsfully deposited Kshs%.2lf", deposit_Amount);
            fclose(fileptr);
            goto label2;
        }
        else if(choiceB == 2){
            puts("Check BALANCE");
            printf("Your current account balance is %.2lf", banker.Account_Balance);
            fclose(fileptr);
            goto label2;
        }
        else if(choiceB == 3){
            puts("<<<<<WITHDRAW>>>>");
            printf("Enter amount to Withdraw: ");
            scanf("%lf", &withdraw_Amount);

            do
            {
            
                if(withdraw_Amount > banker.Account_Balance){
                    printf("\nInsufficient funds in your Account to withdraw %lf\n", withdraw_Amount);
                    puts("Please try a lower amount");
                    printf("Enter amount to Withdraw: ");
                    scanf("%lf", &withdraw_Amount);
    
                }            
            } while (withdraw_Amount > banker.Account_Balance);
            system("clear");


            banker.Account_Balance -= withdraw_Amount;
            printf("\nYou have  successfully wuthdrawn %lf", withdraw_Amount);
            printf("\nCurrent balance is %.2lf", banker.Account_Balance);
            fclose(fileptr);
            goto label2;

        }
        else if(choiceB == 4){
            char receiverID[9];
            struct Banker receiver;
            puts("<<<Send Money>>>");
            printf("ID number of receiver: ");
            scanf("%8s", receiverID);

            FILE *pfile = fopen(strcat(receiverID, ".dat"), "r");
            if(pfile == NULL){
                printf("\nUser %s is not registered with our Banking service ", receiverID);
                goto label2;
            }
            fclose(pfile);

            pfile = fopen(strcat(receiverID, ".dat"), "a+b");
            if(pfile == NULL){
                printf("\nError performing the transaction");
                goto label2;
            }
            fread(&receiver, sizeof(struct Banker), 1, pfile);

            printf("Enter amount to send: ");
            scanf("%lf", &send_amount);
            
            do
            {

                if(send_amount > banker.Account_Balance){
                    printf("\nInsufficient funds in your Account to send %lf", send_amount);
                    puts("Please try a lower amount");
                    printf("Enter amount to send: ");
                    scanf("%lf", &send_amount);
    
                }            
            } while (send_amount > banker.Account_Balance);
            system("clear");

            printf("\nYou have successfully sent %lf to %s", send_amount, receiver.name);
            printf("\nCurrent balance is %lf", banker.Account_Balance);
            fclose(pfile);
            fclose(fileptr);

        }
        else if(choiceB == 5){
            //You cant change your ID number
            char newPWD[15], newName[30], newPhoneNo[11], newID[9];
            puts("<<<<Edit your banker's details>>>>");
            printf("\nEnter current password: ");
            if(strcmp(banker.password, newPWD) !=0){
                printf("\nWRONG PASSWORD!\n...try again..\n");
                goto label2;
            }
            fclose(fileptr);
            
            fileptr = fopen(strcat(filename, ".dat"), "w");
            if(fileptr == NULL){
                printf("\nAccount doesn't Exist!");
                goto label1;
            }

            printf("Your New name: ");
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
                printf("Error!");
                goto label1;
            }
            fclose(fileptr);
    
            puts("\nYour account ddetails have been successfully chnaged!");
            puts("Logging you out...");
            goto label1;
        }
        else if(choiceB == 6){
            goto label1;
        }
        else if(choiceB == 7){
            exit(0);
        }
        else{
            printf("Invalid OPTION!");
            exit(-1);
        }

    }
    else if(choiceA == 4){
        exit(0);
    }
    else{
        printf("Undefined");
        EXIT_FAILURE;
    }
    
    return 0;
}

