#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STRING_LEN 15

int main(int argc, char const *argv[])
{
    int size;
    printf("How many elements for your array: ");
    scanf("%d", &size);
    getchar();

    ///Allocate memory for the array itself
    char **array = malloc(size * sizeof(char *));
    if(array == NULL){
        puts("Error allocating memory!");
        return EXIT_FAILURE;
    }

    //Allocating memory for the strings
    for (int i = 0; i < size; i++)
    {
        array[i] = malloc(MAX_STRING_LEN * sizeof(char));
        if(array[i] == NULL){
            perror("Allocation for string failed!");
            for (int j = 0; j < i; j++)
            {
                free(array[j]);
            }
            free(array);
            return EXIT_FAILURE;
            
        }
    }
    
    printf("TYPE IN %d strings: ", size);
    for (int i = 0; i < size; i++){
        scanf("%14s", array[i]);
    }
    printf("\n");
    puts("Array elements");
    for (int i = 0; i < size; i++){
        printf("%s  ", array[i]);
    }

    printf("\n");

    /*int callocSize;
    puts("Calloc the array...");
    printf("Enter number of elements to calloc: ");
    scanf("%d", &callocSize);

    array = calloc(callocSize, sizeof(char *));
    if(array == NULL){
        perror("Calloc failed");
        return EXIT_FAILURE;
    }
    for (int i = 0; i < callocSize; i++){
        array[i] = calloc(MAX_STRING_LEN, sizeof(char));
        if(array[i] == NULL){
            perror("Calloc string failed");
            for (int j = 0; j < i; j++){
                free(array[j]);
            }
            free(array);
            
            return EXIT_FAILURE;
        }
    }
    puts("Elements initialized to zero using calloc...");
    for (int i = 0; i < size; i++){
        printf("%s  ,", array[i]);
    }
    /*When you print a string in C with printf("%s", str);, printing stops at the first null terminator ('\0').
    If you haven't written any characters to the string, it is just a null terminator at the start—so nothing is printed, just a blank line!
    */
    printf("\n");
    puts("Resize the array...");
    int realloc_size;
    printf("Enter number of elements: ");
    scanf("%d", &realloc_size);
    //Reallocating to a new size
    char **temp = realloc(array, realloc_size * sizeof(char *));

    if(temp == NULL){
        perror("Failed to reallocate memory");
        for (int i = 0; i < size; i++){
            free(array[i]);
            free(array);
            return EXIT_FAILURE;
        }
        
    }
    array = temp;

    if(realloc_size > size){
        for (int i = realloc_size; i < size; i++){
            array[i] = malloc(MAX_STRING_LEN * sizeof(char));
            if(array[i] == NULL){
                printf("Allocation for reallocated elements failed");
                for (int j = 0; j < i; j++)
                {
                    free(array[i]);
                }
                free(array);
                return EXIT_FAILURE;
                
            }
        }
        
    }
    
    for (int i = 0; i < size; i++){
        if(i < realloc_size){
            printf("%s  ", array[i]);
        } 
        else{
            printf(" Uninitialized");
        } 
      
    }

    /*for (int i = 0; i < size; i++){
        free(array[i]);
    }*/
    
    
    free(array);
    
    return 0;
}
