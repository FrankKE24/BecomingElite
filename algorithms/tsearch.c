#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <search.h>

int compare(const void *a, const void *b){
    return (*(int *)a - *(int *)b);
}

int main(int argc, char const *argv[])
{
    //A simple pointer of type void * initialized to NULL is a valid tree and can be extended or searched.
    void *root = NULL;
    int *item;
    for (int i = 0; i < 20; i++)
    {
        item = malloc(sizeof(int));
        *item = i;

        //insert item into th tree
        if(tsearch(item, &root, compare) == NULL){
            fprintf(stderr, "Error inserting %d\n", *item);
            //perror("Error inserting %d\n", *item);
            free(item);
        }

    }

    int insert_values[4];
    for (int i = 0; i < 4; i++)
    {               
        printf("Enter 4 values to insert in the tree: ");
        scanf("%d", &insert_values[i]);
        getchar();
    }
    for (int i = 0; i < 4; i++)
    {               
        tsearch(&insert_values[i], &root, compare);

    }



    //seaarching a value in th e tree
    int search_value = 66;
    int **found_item = tfind(&search_value, &root, compare);

    if(found_item != NULL){
        printf("Found: %d\n", **found_item);
    }
    else{
        printf("%d not found in the tree\n", search_value);
    }

    //deleting a value from the tree
    int delete_value = 90;
    if(tdelete(&delete_value, &root, compare) == NULL){
        printf("%d not found for deletion\n", delete_value);
    }
    else{
        printf("Deleted: %d\n", delete_value);
    }

    printf("%ld\n\n", sizeof(root));

    /*for (int i = 0; i < 24; i++)
    {               
        printf("%d \t", &root);
    }*/

    return 0;
}
