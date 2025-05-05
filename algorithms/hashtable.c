#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NULL ((void *)0)

#define TABLE_SIZE 10

struct List{
    char *string;
    struct List *next;
};

//define the structure of the hash table
struct Hash_table{
    struct List **table; //Array of linked lists
    int size; //siz epf th e table
};

//Create a new hasg table
struct Hash_table *create_hash_table(int size){
    struct Hash_table *newTable = malloc(sizeof(struct Hash_table));
    if(newTable == NULL){
        perror("Allocation failed\n");
        return NULL;
    }
    newTable->size = size;
    newTable->table = malloc(sizeof(struct List *) * size);

    for (int i = 0; i < size; i++)
    {
        newTable->table[i] = NULL;  //initialize each slot to null
    }
    return newTable;
}

//hash function
unsigned int hash(struct Hash_table *hashtable, char *str){
    unsigned int hashvalue = 0;

    while (*str != '\0')
    {
        hashvalue += *str++;
    }
    
    return (hashvalue % hashtable->size);
}

//add a new string to the hash table
int add_string(struct Hash_table *hashtable, char *str){
    unsigned int index = hash(hashtable, str);

    struct List *new_list  = malloc(sizeof(struct List));
    if(new_list == NULL){
        perror("Allocation failed\n");
        return EXIT_FAILURE;
            //return 1;
    }

    new_list->string = strdup(str);  //duplicate string
    new_list->next = hashtable->table[index];  //insert at the end of the linked list
    hashtable->table[index] = new_list;

    return 0;
}

//Function to lookup for a string
struct List *lookup_string(struct Hash_table *hashtable, char *str){
    unsigned int index = hash(hashtable, str);

    struct List *currentList = hashtable->table[index];

    while (currentList != NULL)
    {
        if(strcmp(currentList->string, str) == 0){
            return currentList;
        }
        currentList = currentList->next;
    }
    return NULL;
}

void display_hash_table(struct Hash_table *hashtable){
    int i = 0;

    while ( i< hashtable->size)
    {
        struct List *templist = hashtable->table[i];
        printf("Index %d: ", i);

        while(templist != NULL)
        {
            printf("%s -> ", templist->string);
            templist = templist->next;
        }
        printf("NULL\n");
        i++ ;  
    }

    return;
    
}

int main(int argc, char const *argv[])
{
    struct Hash_table *my_hash_table = create_hash_table(TABLE_SIZE);

    add_string(my_hash_table, "chicken");
    add_string(my_hash_table, "pork");
    add_string(my_hash_table, "fish");
    add_string(my_hash_table, "fish");
    add_string(my_hash_table, "game-meat");
    add_string(my_hash_table, "fillet");
    add_string(my_hash_table, "liver");
    add_string(my_hash_table, "mutton");
    add_string(my_hash_table, "nile-perch");
    add_string(my_hash_table, "tilappia");
    add_string(my_hash_table, "dolphin");
    add_string(my_hash_table, "jelly-fish");
    add_string(my_hash_table, "whale");
    add_string(my_hash_table, "shark");
    add_string(my_hash_table, "eel");

    puts("Hash table contents: \n");
    display_hash_table(my_hash_table);

    char key[13];
    printf("\nEnter item to find: ");
    scanf("%12s", key);

    struct List *item_to_find = lookup_string(my_hash_table, key);
    if(item_to_find){
        printf("\nFound: %s\n", item_to_find->string);
    }
    else{
        printf("\nNot found");
    }

    free(my_hash_table);
    return 0;
}
