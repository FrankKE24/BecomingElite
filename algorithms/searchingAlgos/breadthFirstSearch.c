#include <stdio.h>
#include <stdlib.h>

//BFS of Graph in AdjacencyList representation
#define MAX_VERTICES 100

struct Node{
    int vertex;
    struct Node *next;
};

struct Queue{
    int items[MAX_VERTICES];
    int front, rear;
};

struct Node *createNode(int v){
    struct Node *newNode = malloc(sizeof(struct Node));
    newNode->next = NULL;
    newNode->vertex  = v;

    return newNode;
}

void addEdge(struct Node *adjList[], int src, int dest){
    struct Node *newNode = createNode(dest);
    newNode->next = adjList[src];
    adjList[src] = newNode;

    newNode = createNode(src);
    newNode->next = adjList[dest];
    adjList[dest]  = newNode;
}

struct Queue *creatQueue(){
    struct Queue *q = malloc(sizeof(struct Queue));
    q->front = -1;
    q->rear = -1;
    return q;
}

int isEmpty(struct Queue *q){
    return q->rear == -1;
}

void enqueue(struct Queue *q, int value){
    if(q->rear == MAX_VERTICES -1) return;
    if(q->front == -1) q->front = 0;
    q->rear++;
    q->items[q->rear] = value;
}

int dequeue(struct Queue *q){
    if(isEmpty(q)) return -1;
    int item = q->items[q->front];
    q->front++;
    if(q->front > q->rear){
        q->front = q->rear = -1;
    }
    return item;
}

void BFS(struct Node *adjList[], int startVertex, int numVertices){
    int visited[MAX_VERTICES] = {0};
    struct Queue *q = creatQueue();

    visited[startVertex] = 1;
    enqueue(q, startVertex);

    printf("BFS Traversal: ");
    while(!isEmpty(q)){
        int current = dequeue(q);
        printf("%d ", current);

        struct Node *temp = adjList[current];
        while(temp){
            int adjVertex = temp->vertex;
            if(!visited[adjVertex]){
                visited[adjVertex] = 1;
                enqueue(q, adjVertex);
            }
            temp = temp->next;
        }
    }
    printf("\n");
}

//gcc breadthFirstSearch.c

int main(int argc, char const *argv[])
{
    int vertices = 6;
    struct Node *adjacentList[MAX_VERTICES] = {NULL};

    addEdge(adjacentList, 0, 1);
    addEdge(adjacentList, 0, 2);
    addEdge(adjacentList, 1, 3);
    addEdge(adjacentList, 1, 4);
    addEdge(adjacentList, 2, 5);
    addEdge(adjacentList, 2, 6);

    BFS(adjacentList, 0, vertices);

    return 0;
}
