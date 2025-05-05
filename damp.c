#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define MAX_VERTICES 100

void displayGraph(int graph[MAX_VERTICES][MAX_VERTICES], int vertices){
    printf("Adjacency Matrix:");
    int i, j;
    for(i=0; i<vertices; i++){
        for(j=0; j<vertices; i++){
            printf("%d ", graph[i][j]);
        }
        printf("\n");
    }
}

//Add an edge to the graph
void addEdge(int graph[MAX_VERTICES][MAX_VERTICES], int start, int end){
    graph[start][end] = 1;
    graph[end][start] = 1; //For undirected graph
}

int main(){
    int vertices, edges;

    printf("Enter the number of vertices: ");
    scanf("%d ", &vertices);
    getchar();


    if(vertices<=0 || vertices > MAX_VERTICES){
        printf("Invalid number of vertices!Exiting...\n");
        return 1;
    }

    //Initialize the adjacency matix with zeros
    int graph[MAX_VERTICES][MAX_VERTICES] = {0};

    printf("Enter the number of edges: ");
    scanf("%d\n", &edges);

    if(edges < 0 || edges > vertices * (vertices -1)/2){
        printf("Invalid number of edges!Exiting");
        return 1;
    }

    //Input edges and construct the adjacency maatrix
    int i;
    for(i=0; i<edges; i++){
        int start, end;
        printf("Enter edge %d (start end): ", i+1);
        scanf("%d %d", &start, &end);
        getchar();

        //Validate input vertices
        if(start < 0 || start >= vertices || end <0 || end >= vertices){
            printf("Invalid vertices. Try again.\n");
            i--;
            continue;
        }

        addEdge(graph, start, end);
    }

    displayGraph(graph, vertices);

    return 0;
}
/*int main(int argc, char const *argv[])
{
    char next[2];
    char menu_choice[2];

    
    printf("Press any key to return to main menu: ");
    scanf("%s", menu_choice);
    if (menu_choice != NULL ){
        printf("Alright");
        exit(0);
    }
    
    char text[] = "myfile";
    //char *delete_file = strcat(text, ".dat");
    //remove(delete_file);
    //free(*delete_file);
    /*FILE *pfile = fopen("myfile.dat", "r+b");
    if(pfile == NULL){
        printf("\nFile not found");
        EXIT_FAILURE;
    }

    printf("Enter some text: ");
    fgets(text, 20, stdin);
    text[strlen(text) - 1] = '\0';

    //long offset = sizeof(char) * 3;
    //fseek(pfile, offset, SEEK_SET);
    if(fwrite(text, sizeof(text), 1, pfile) != 1){
        puts("Error writing to file");
        EXIT_FAILURE;
    }
    fclose(pfile);

    char buffer[20];
    FILE *pfile2 = fopen("myfile.dat", "r+b");
    if(pfile2 == NULL){
        printf("\nFile not found");
        EXIT_FAILURE;
    }

    fread(&buffer, sizeof(text), 1, pfile2);
    printf("%s\n", buffer);
    fclose(pfile2);

    return 0;
}*/
