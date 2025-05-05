#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Banker{
    char name[30];
    char phone_Number[11];
    char password[15];
    char ID_Number[9];
    double Account_Balance;

};

int main(int argc, char const *argv[])
{
    char receiverID[9];
    struct Banker receiver;
    struct Banker banker;
    double send_amount;
    char filename[9];

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
        return EXIT_FAILURE;
    }
    
    if(fread(&banker, sizeof(struct Banker), 1, fileptr) != 1){
        printf("\nError reading login file\n");
        fclose(fileptr);
        return EXIT_FAILURE;
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


    puts("<<<Send Money>>>");
    printf("ID number of receiver: ");
    scanf("%8s", receiverID);

    fileptr = fopen(strcat(receiverID, ".dat"), "r");
    if(fileptr == NULL){
        printf("\nUser %s is not registered with our Banking service ", receiverID);
        exit(EXIT_FAILURE);
        //goto label2;
    }

    if(fread(&receiver, sizeof(struct Banker), 1, fileptr) != 1){
        printf("\nError reading receiver's file\n");
        fclose(fileptr);
        exit(EXIT_FAILURE);
    }
    fclose(fileptr);

    printf("\nEnter amount to send: ");
    scanf("%lf", &send_amount);
    getchar();
    
    do
    {
        printf("\nInsufficient funds in your Account to send %lf", send_amount);
        puts("Please try a lower amount");
        printf("Enter amount to send: ");
        scanf("%lf", &send_amount);
        while(getchar() != '\n');

    } while (send_amount > banker.Account_Balance);
    system("clear");

    //strcpy(filename, receiverID);
    fileptr = fopen(receiverID, "w");
    receiver.Account_Balance += send_amount;
    if(fwrite(&receiver, sizeof(struct Banker), 1, fileptr) !=1){
        puts("Error in Transaction");
        fclose(fileptr);
        exit(EXIT_FAILURE);
    }
    fclose(fileptr);
    printf("\nYou have successfully sent %lf to %s", send_amount, receiver.name);


    strcpy(filename, banker.ID_Number);
    fileptr = fopen(strcat(filename, ".dat"), "w");
    banker.Account_Balance -= send_amount;
    if(fwrite(&banker, sizeof(struct Banker), 1, fileptr) !=1){
        puts("Error updating Balance");
        fclose(fileptr);
        exit(EXIT_FAILURE);
    }
    printf("\nCurrent balance is %lf", banker.Account_Balance);
    fclose(fileptr);

    return 0;
}
