#include <string.h>
#include <stdio.h>
#include <stdlib.h>

struct Node{
    int data;
    struct Node *left_child;
    struct Node *right_child;
};

struct Node *createNode(int data){
    struct Node *newNode = malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->left_child = newNode->right_child = NULL;

    return newNode;
}

void inOrderTraversal(struct Node *root){
    if (root != NULL)
    {
        inOrderTraversal(root->left_child);
        printf("%d ", root->data);
        inOrderTraversal(root->right_child);
    }
    
}

void preOrderTraversal(struct Node *root){
    if (root != NULL)
    {
        printf("%d ", root->data);
        inOrderTraversal(root->left_child);
        inOrderTraversal(root->right_child);
    }
    
}

void postOrderTraversal(struct Node *root){
    if (root != NULL)
    {
        inOrderTraversal(root->left_child);
        inOrderTraversal(root->right_child);
        printf("%d ", root->data);

    }
      
}


struct Node *searchNode(struct Node *root, int data){
    struct Node *current = root;
    printf("\nVisiting elements:  ");

    while (current->data != data)
    {
        printf("%d ", current->data);
        if(current != NULL){
            if(current->data > data){
                current = current->left_child;
            }
            else
            {
                current = current->right_child;
            }
            if(current == NULL){
                return NULL;
            }
        }


    }
    printf("\nFound: %d ", current->data);
    //return current;
}

void Insert(struct Node *root, int data){
    struct Node *temp_node = createNode(data);
    struct Node *current;
    struct Node *parent;

    if(root == NULL){
        root = temp_node;
    }
    else{
        current = root;
        parent = NULL;

        while (1)
        {
            parent = current;
            if(data < parent->data){
                current = current->left_child;
                if(current == NULL){
                    parent->left_child = temp_node;
                    return;
                }
            }
            else{
                current = current->right_child;
                if(current == NULL){
                    parent->right_child = temp_node;
                    return;
                }
            }
        }
        
    }
}

int main(int argc, char const *argv[])
{
    struct Node *root = NULL;

    root = createNode(100);
    int numbers[]= {34, 56, 483, 9378, 90, 77, 3784, 34, 873, 55};
    int size = sizeof(numbers)/sizeof(numbers[0]);

    for (int i = 0; i < size; i++)
    {
        Insert(root, numbers[i]);
    }
    
    Insert(root, 79);
    printf("\nIn order traversal:..");
    inOrderTraversal(root);
    printf("\n\nPre order: \n");
    preOrderTraversal(root);
    printf("\n\nPost order: ");
    postOrderTraversal(root);

    searchNode(root, 77);


    free(root);

    return 0;
}
