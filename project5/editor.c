#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void textFileEditor();
void binaryFileEditor();

int length;
int fileChoice;
char fileName[20];
char buffer[256];

int main(int argc, char const *argv[])
{
    int choice;
    puts("1. TEXT File");
    puts("2. BinARY FILE");

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
    

    if(choice == 1){
        textFileEditor();
    }
    else if(choice == 2){
        binaryFileEditor();
    }
    else{
        puts("Invalid choice");
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
    puts("1. Read");
    puts("2. Write");
    puts("3. Append");
    printf("Select file mode: ");
    scanf("%d", &fileChoice);

    if(fileChoice == 1){
        printf("Filename: ");
        scanf("%19s", fileName);

        FILE *fileptr = fopen(strcat(fileName, ".txt"), "r");
        if(fileptr == NULL){
            printf("\nError opening file");
            exit(EXIT_FAILURE);
        }
        while (fgets(buffer, sizeof(buffer), fileptr)){
            printf("%s", buffer);
        }

        puts("\nEnd of File");
        fclose(fileptr);

    }
    else if(fileChoice == 2){
        puts("WRITE");
        printf("Filename: ");
        scanf("%19s", fileName);

        printf("Enter the length of characters you wish to write: ");
        scanf("%d", &length);
        char *text = malloc((length +1) * sizeof(char));
        printf("Entger the text: ");
        int count = 0;
        // Read characters one at a time
        while (count < length) {
            int ch = getchar(); // Read a single character
            if (ch != '\n' || ch != EOF) { // Ignore newline characters
                text[count++] = ch; // Store the character in the buffer
            }
        }
        text[count] = '\0'; // Null-terminate the string

        FILE *fileptr = fopen(strcat(fileName, ".txt"), "w");
        if(fileptr == NULL){
            printf("\nError opening file");
            exit(EXIT_FAILURE);
        }
        
    
        fprintf(fileptr, "%s", text);
        puts("\nFile successfully written");
        fclose(fileptr);

    }
    else if(fileChoice == 3){
        printf("Enter the length of characters you wish to append: ");
        scanf("%d", &length);
        printf("Filename: ");
        scanf("%19s", fileName);
        char *text = malloc((length +1) * sizeof(char));
        printf("Entger the text: ");
        int count = 0;
        // Read characters one at a time
        while (count < length) {
            int ch = getchar(); // Read a single character
            if (ch != '\n' || ch != EOF) { // Ignore newline characters
                text[count++] = ch; // Store the character in the buffer
            }
        }
        text[count] = '\0'; // Null-terminate the string
    
        FILE *file_ptr = fopen(strcat(fileName, ".txt"), "a+");
        if(file_ptr == NULL){
            printf("File not found\n");
        }
    
        fprintf(file_ptr, "%s", text);
        fclose(file_ptr);
        printf("\nThis is what was appended");
        printf("\n%s", text);
    }
}

void binaryFileEditor(){

}