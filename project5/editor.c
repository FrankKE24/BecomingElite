#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void textFileEditor();
void binaryFileEditor();

int length;
int fileChoice;
char fileName[20];
char buffer[256];

int main(int argc, char const *argv[])
{
    int choice;

    label1:
    puts("<<<<<<<<<<<<<<<<<<<<<FILE   EDITOR>>>>>>>>>>>>>>>>>>>>>>>.");
    puts("1. TEXT File");
    puts("2. BINARY FILE");

    while (1){
        printf("Choice: ");
        if(scanf("%d", &choice) == 1 && choice > 0){
            break;
        }    
        else{
            printf("Invalid input. Please enter a positive integer: ");
        }
        while (getchar() != '\n');
        //getchar();
        
    } 
    
    system("clear");


    if(choice == 1){
        textFileEditor();
    }
    else if(choice == 2){
        binaryFileEditor();
    }
    else{
        puts("Invalid choice");
        goto label1;
    }
    return 0;
}

/*
getchar() Reads One Character at a Time:

The getchar() function reads one character from the input 
buffer (e.g., the text you typed at the keyboard).
Check if the Character is Not a Newline ('\n):

The condition getchar() != '\n' checks if the character read 
is not the newline character ('\n), which is added when you press the "Enter" key.
Keep Reading Until a Newline is Found:

The loop keeps calling getchar() and discarding characters one
 by one until it reaches the newline character ('\n).
Once the newline is found, the loop stops.
Purpose: Clear the Input Buffer:

This is often used to "flush" or clear leftover characters from 
the input buffer when invalid or extra input is provided. For example:
If you expect the user to type a number but they type abc instead, 
this loop will discard all the characters (a, b, c) and the newline (\n) 
so the input buffer is clean for the next input.*/

void textFileEditor(){
    do
    {
        puts("MENU");
        puts("1. Read");
        puts("2. Write");
        puts("3. Append");
        puts("4. EXIT");
        printf("Select file mode: ");
        scanf("%d", &fileChoice);
        getchar();
    
        int proceed = 1;

        if(fileChoice == 1){
            puts("              READ TEXT FILE");
            printf("Filename: ");
            scanf("%19s", fileName);
            getchar();
    
            FILE *fileptr = fopen(strcat(fileName, ".txt"), "r");
            if(fileptr == NULL){
                printf("\nError opening file\n");
                break;
                //continue;
            }
            while (fgets(buffer, sizeof(buffer), fileptr)){
                printf("%s", buffer);
            }
    
            puts("\nEnd of File");
            fclose(fileptr);
            sleep(2);
            system("clear");

        }
        else if(fileChoice == 2){
            puts("              WRITE TO TEXT FILE");
            puts("WRITE");
            printf("Filename: ");
            scanf("%19s", fileName);
    
            printf("Enter the length of characters you wish to write: ");
            scanf("%d", &length);
            getchar();
            char *text = malloc((length +1) * sizeof(char));
            if(text == NULL){
                printf("Errror allocating memory for text\n");
                break;
            }
            printf("Type the text..: ");
            int count = 0;
            // Read characters one at a time
            while (count < length) {
                int ch = getchar(); // Read a single character
                if (ch != '\n' || ch != EOF) { // Ignore newline characters
                    text[count++] = ch; // Store the character in the buffer
                }
            }
            text[count] = '\0'; // Null-terminate the string

            // Clear the input buffer again if there is overflow
            while (getchar() != '\n');

            FILE *fileptr = fopen(strcat(fileName, ".txt"), "w");
            if(fileptr == NULL){
                printf("\nError opening file");
                free(text);
                continue;
                //break;
            }
            
        
            fprintf(fileptr, "%s", text);
            puts("\nFile successfully written");
            fclose(fileptr);
            free(text);
            sleep(2);
            system("clear");

        }
        else if(fileChoice == 3){
            puts("              APPEND TEXT FILE");
            printf("Enter the length of characters you wish to append: ");
            scanf("%d", &length);
            getchar();
            printf("Filename: ");
            scanf("%19s", fileName);

            while(getchar() != '\n');

            char *text = malloc((length +1) * sizeof(char));
            if (text == NULL) {
                printf("Error allocating memory.\n");
                continue; // Return to the menu
            }

            printf("Type the text: ");
            int count = 0;
            // Read characters one at a time
            while (count < length) {
                int ch = getchar(); // Read a single character
                if(ch == EOF) break;
                if (ch != '\n') { // Ignore newline characters
                    text[count++] = ch; // Store the character in the buffer
                }
            }
            text[count] = '\0'; // Null-terminate the string

            while(getchar() != '\n');
        
            FILE *file_ptr = fopen(strcat(fileName, ".txt"), "a+");
            if(file_ptr == NULL){
                printf("File not found\n");
                free(text);
                EXIT_FAILURE;
                break;
                //return EXIT_FAILURE;
            }
        
            fprintf(file_ptr, "%s", text);
            fclose(file_ptr);

            printf("\nThis is what was appended");
            printf("\n%s \n", text);
            free(text);
            sleep(5);
            system("clear");
    
        }
        else if(fileChoice == 4){
            //break;
            exit(0);
        }
    
    } while (1);
    
    return;
}

void binaryFileEditor(){
    do{
        puts("1. Read");
        puts("2. Write");
        puts("3. Append");
        printf("Select file mode: ");
        scanf("%d", &fileChoice);
        getchar();

        if(fileChoice == 1){
            puts("              READ BINARY FILE");
            printf("Filename: ");
            scanf("%19s", fileName);
            FILE *fileptr = fopen(strcat(fileName, ".dat"), "rb");
            if(fileptr == NULL){
                printf("\nError opening file\n");
                continue;
            }
            if(fread(buffer, sizeof(buffer)- 1, 1, fileptr) != 1){
                printf("\nError reading file\n");
                fclose(fileptr);
                continue;
                //break;
            }
            
            printf("%s", buffer);
            puts("\nEnd of File");
            fclose(fileptr);
            sleep(2);
            system("clear");

        }
        else if(fileChoice == 2){
            puts("              WRITE TO A BINARY FILE");
            printf("Filename: ");
            scanf("%19s", fileName);
            printf("Enter the length of characters you wish to write: ");
            scanf("%d", &length);
            getchar();
            char *text = malloc((length +1) * sizeof(char));
            if(text == NULL){
                printf("Errror allocating memory for text\n");
                break;
            }

            printf("Entger the text: ");
            int count = 0;
            // Read characters one at a time
            while (count < length) {
                int ch = getchar(); // Read a single character
                if (ch != '\n' || ch != EOF) { // Ignore newline characters
                    text[count++] = ch; // Store the character in the buffer
                }
            }
            text[count] = '\0';

            while(getchar() != '\n');
    
            FILE *fileptr = fopen(strcat(fileName, ".dat"), "wb");
            if(fileptr == NULL){
                printf("\nError opening file");
                free(text);
                EXIT_FAILURE;
                break;
            }
            
            if(fwrite(text, sizeof(text), 1, fileptr) != 1){
                printf("Errror wrting to file");
                free(text);
                fclose(fileptr);
                return;
            }
            printf("%s", buffer);
            puts("\nFile written successfully\n");
            fclose(fileptr);
            free(text);
            sleep(2);
            system("clear");

        }
        else if(fileChoice == 3){
            puts("                  APPEND BINARY");
            printf("Enter the length of characters you wish to append: ");
            scanf("%d", &length);
            getchar();
            printf("Filename: ");
            scanf("%19s", fileName);

            FILE *fileptr = fopen(strcat(fileName, ".dat"), "rb");
            if(fileptr == NULL){
                printf("\nNo such file");
                EXIT_FAILURE;
                break;
            }
            fclose(fileptr);

            char *text = malloc((length +1) * sizeof(char));
            printf("Type the text: ");
            int count = 0;
            // Read characters one at a time
            while (count < length) {
                int ch = getchar(); // Read a single character
                if (ch != '\n' || ch != EOF) { // Ignore newline characters
                    text[count++] = ch; // Store the character in the buffer
                }
            }
            text[count] = '\0';

            while(getchar() != '\n');

            FILE *fileptr2 = fopen(fileName, "rb+");  //NO need to use strcat as we already did it when checking whether the file exosts
            printf("%s\n", fileName);
            if(fileptr2 == NULL){
                printf("\nError opening binary file to append");
                free(text);
                EXIT_FAILURE;
                break;
            }
            
            if(fwrite(text, sizeof(text), 1, fileptr2) != 1){
                printf("Errror appending to file");
                fclose(fileptr2);
                free(text);
                EXIT_FAILURE;
            }
            puts("This is what was appended:  ");
            printf("%s \n", text);
            fclose(fileptr2);
            free(text);
            sleep(5);
            system("clear");
        }
        else if(fileChoice == 5){
            printf("...Exiting.");
            exit(0);
        }
        else{
            puts("\nINvalid choice\n");
            continue;
        }
    }while(1);
 
    return;
}