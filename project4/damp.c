#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main() {
    char filename[9];
    char name[9];

    printf("Enter file name: ");
    scanf("%8s", filename);

    strcpy(name, filename);
    FILE *fileptr = fopen(strcat(name, ".dat"), "r");

    if(fileptr == NULL){
        printf("Error opening file");
    }
    printf("\nIt was successful");
    /*int number; // Variable to store the user's input
    char term;  // Variable to check for invalid characters
    int validInput;

    while (1) {
        printf("Enter a number: ");

        // Read and validate input
        validInput = scanf("%d%c", &number, &term);

        // Check if the input is valid:
        // - `validInput == 2`: scanf successfully reads an integer (`%d`) followed by a character (`%c`)
        // - `term == '\n'`: Ensures that no extra characters were entered after the number
        if (validInput == 2 && term == '\n') {
            break; // Valid input, exit the loop
        } else {
            printf("Invalid input. Please enter a valid number.\n");

            // Clear the input buffer to prevent infinite loops
            while (getchar() != '\n');
            //getchar();
        }
    }

    printf("You entered: %d\n", number);*/

    /*
        char c;

    printf("Press any key to continue...\n");
    c = getchar(); // Waits for the user to type a character
    printf("You pressed: %c\n", c);

    // Continue executing
    printf("Continuing program execution...\n");*/
    return 0;
}
/*
Manual Tracking

#include <stdio.h>

int open_file_count = 0;

FILE* track_fopen(const char* filename, const char* mode) {
    open_file_count++;
    return fopen(filename, mode);
}

void track_fclose(FILE* file) {
    if (file) {
        open_file_count--;
        fclose(file);
    }
}

int main() {
    FILE* file = track_fopen("example.txt", "r");
    // Forgetting to call track_fclose will leave open_file_count > 0
    printf("Open files: %d\n", open_file_count);
    return 0;
}
    

#include <stdio.h>
#include <stdlib.h>

FILE* file;

void cleanup() {
    if (file) fclose(file);
}

int main() {
    atexit(cleanup);
    file = fopen("example.txt", "r");
    // If fclose is forgotten, cleanup will still close the file.
    return 0;
}*/