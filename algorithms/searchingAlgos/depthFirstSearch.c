#include <stdio.h>
#include <stdlib.h>

//GRAPH- Adjacency list representation
typedef struct Node{
    int vertex;
    struct Node *next;
}Node;

typedef struct Graph{
    int numVertices;
    Node **adjLists;
    int *visited;
}Graph;

Node *createNode(int v){
    Node *newNode = malloc(sizeof(Node));
    newNode->next = NULL;
    newNode->vertex = v;
    return newNode;
}

Graph *createGraph(int vertices){
    Graph *graph = malloc(sizeof(Graph));
    graph->numVertices = vertices;
    graph->adjLists = malloc(vertices * sizeof(Node*));
    graph->visited = malloc(vertices * sizeof(int));

    for (int i = 0; i < vertices; i++){
        graph->adjLists[i] = NULL;
        graph->visited[i] = 0;
    }
    return graph;
    
}

//adds an undirected edge between two vertices(src and dest) in the adj list representation of the graph
void addEdge(Graph *graph, int source, int destination){
    //create a node for dest and insert it at the beginning of src's list
    Node *newNode = createNode(destination);
    newNode->next = graph->adjLists[source];
    graph->adjLists[source] = newNode;

    //create a node for src and add it to dest's list
    newNode = createNode(source);
    newNode->next = graph->adjLists[destination];
    graph->adjLists[destination] = newNode;
    //Makes the edge undirected, you can go from src to dest and from dest to src
}

void DFS(Graph *graph, int vertex){
    graph->visited[vertex] = 1;
    printf("Visited %d\n", vertex);

    Node *temp = graph->adjLists[vertex];
    while(temp){
        int connectedVertex = temp->vertex;
        if(!graph->visited[connectedVertex]){
            DFS(graph, connectedVertex);
        }
        temp = temp->next;
    }
}

void printGraph(Graph *graph, int vertices){
    printf("Adjacency list representation:\n");
    //printf("\nTT: -> %d ", graph->adjLists[2]->vertex);
    Node **temp = graph->adjLists;

    for (int i = 0; i < vertices; ++i){ 
        printf("Vertex %d.", i);
        while(*temp/*->next != NULL*/){
            printf("-> %d ", temp[i]->vertex);
            *temp = temp[i]->next;
        }  
        printf("\n");


    }

}

//gcc depthFirstSearch.c

int main(int argc, char const *argv[])
{
    int vertices = 12;
    Graph *graph = createGraph(vertices);

    addEdge(graph, 0, 1);
    addEdge(graph, 0, 2);
    addEdge(graph, 1, 3);
    addEdge(graph, 1, 4);
    addEdge(graph, 2, 5);
    addEdge(graph, 2, 6);
    addEdge(graph, 3, 7);
    addEdge(graph, 3, 8);
    addEdge(graph, 4, 9);
    addEdge(graph, 4, 10);
    addEdge(graph, 5, 11);
    addEdge(graph, 5, 12);
    puts("Depth First search starting  from vertex 0: ");
    DFS(graph, 0);
    printGraph(graph, 12);

    return 0;
}
