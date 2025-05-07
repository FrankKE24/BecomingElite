#include <stdio.h>
#include <stdlib.h>

struct Node
{
    int data;
    struct Node *leftChild;
    struct Node *rightChild;
};

struct Node* createNode(int data){
    struct Node *newNode = malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->leftChild = newNode->rightChild = NULL;
    return newNode;
};

void inOrderTraversal(struct Node *root){
    if (root != NULL){
        inOrderTraversal(root->leftChild);
        printf("%d ", root->data);
        inOrderTraversal(root->rightChild);
    }
    
}

void preOrderTraversal(struct Node *root){
    if (root != NULL)
    {
        printf("%d ", root->data);
        preOrderTraversal(root->leftChild);
        preOrderTraversal(root->rightChild);

    }
    
}

void postOrderTraversal(struct Node *root){
    if (root != NULL)
    {
        postOrderTraversal(root->leftChild);
        postOrderTraversal(root->rightChild);
        printf("%d ", root->data);
    }
    
}

struct Node *search(struct Node *root, int data){
    struct Node *current = root;
    printf("\nVisiting elements: ");

    while (current->data != data)
    {
        if (current != NULL)
        {
            printf("%d ", current->data);
            if (current->data > data)
            {
                current = current->leftChild;
            }
            else
            {
                current = current->rightChild;
            }
            if (current == NULL)
            {
                return NULL;
            }
            
        }
        
    }

    return current;
    
}

void Insert(struct Node *root, int data){
    struct Node *tempNode = malloc(sizeof(struct Node));
    struct Node *current;
    struct Node *parent;

    tempNode->data = data;
    tempNode->leftChild = NULL;
    tempNode->rightChild = NULL;

    if (root == NULL)
    {
        root = tempNode;
    }
    else{
        current = root;
        parent = NULL;
        while (1)
        {
            parent = current;
            if(data < parent->data){
                current = current->leftChild;  //Insert to left

                if(current == NULL){
                    parent->leftChild = tempNode;
                    return;
                }
            }
            else{       //Go to the right
                current = current->rightChild;
                
                if(current == NULL){        //Insert to the right
                    parent->rightChild = tempNode;
                    return;
                }
            }

        }
    }
    
}

int main(){
    struct Node *root = NULL;

    root = createNode(100);
    root->leftChild = createNode(49);
    root->leftChild->leftChild = createNode(55);
    root->leftChild->leftChild->leftChild = createNode(75);
    root->leftChild->leftChild->leftChild->leftChild = createNode(95);
    root->rightChild  = createNode(168);
    root->rightChild->rightChild = createNode(258);
    root->rightChild->rightChild->rightChild = createNode(448);
    root->rightChild->rightChild->rightChild->rightChild = createNode(428);
    root->rightChild->rightChild->rightChild->rightChild->rightChild = createNode(666);


    printf("In order: \n");
    inOrderTraversal(root);
    printf("\n\nPre order: \n");
    preOrderTraversal(root);
    printf("\n\nPost order: ");
    postOrderTraversal(root);

    search(root, 666);



    return 0;
}