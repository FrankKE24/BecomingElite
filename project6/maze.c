#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#define COLOR_RED "\x1b[31m"
#define COLOR_GREEN "\x1b[32m"
#define COLOR_YELLOW "\x1b[33m"
#define COLOR_BLUE "\x1b[34m"
#define COLOR_MAGENTA "\x1b[35m"
#define COLOR_CYAN "\x1b[36m"
#define COLOR_RESET "\x1b[0m"

#define ROWS 6
#define COLS 5

int maze[ROWS][COLS] = {{0, 1, 0, 0, 0},
                        {0, 1, 0, 1, 0},
                        {0, 0, 0, 1, 0},
                        {0, 1, 0, 1, 0},
                        {1, 1, 1, 1, 0},
                        {0, 0, 0, 0, 0}};

int visited[ROWS][COLS] = {0};

void printMaze(int array[ROWS][COLS]){
    for (int i = 0; i < ROWS; i++)
    {
        for (int j = 0; j < COLS; j++)
        {
            if(array[i][j] == 0){
                printf(COLOR_BLUE "%d ", array[i][j]);
                printf(COLOR_RESET);
            }
            else{
                printf("%d ", array[i][j]);
            }
        }
        printf("\n");
        
    }
    
}

int isSafe(int x, int y){
    return (x >= 0 && x < ROWS && y >=0 && y < COLS && maze[x][y] == 0 && visited[x][y] == 0);
}

int DFS(int x, int y, int goalX, int goalY){
    if(x == goalX && y == goalY){
        printf("(%d, %d)\n", x, y);
        return 1;
    }

    if(!isSafe(x, y)) return 0;

    printf(COLOR_GREEN);
    visited[x][y] = 1;
    printf(COLOR_RESET);

    //Move directions: right, down , left,  up
    int dirX[] = {0, 1, 0, -1};
    int dirY[] = {1, 0, -1, 0};

    for (int i = 0; i < 4; i++)
    {
        int newX = x + dirX[i];
        int newY  = y + dirY[i];

        if(DFS(newX, newY, goalX, goalY)){
            printf("(%d, %d)\n", x, y); //print path in reverse order
            return 1;
        }
    }
    return 0;

}

int main(int argc, char const *argv[])
{
    int startX = 0, startY   = 0;
    int goalX = 4, goalY = 4;

    if(!DFS(startX, startY, goalX, goalY)){
        printf("No path found.\n");
    }

    printMaze(maze);

    return 0;
}


/*int main(int argc, char const *argv[])

{
    char maze[][20] = { "WRHUFHERFWUETHRRXT",
                         "WRHRUIJDWETHRTPRII", 
                         "WRHUQWXYEWWMMQEEXS", 
                         "WPPOLPMXCRFWUETHRT", 
                         "WRHUYUIVSFGAJERTLLL",
                         "AABFEGGWJDWEWAAQQR",
                         "MHDJQPRTXMCVPOEEEE",
                         "ABDGHTPELJFWUETHRT",
                         "WRPLFGTEEMSAQETHRT", 
                         "WRHUFHERFWUETHRTFF",
                         "WRHUFHERFWUETHRTBV",
                         "WRHUFHERFWUETHRTBB"};

    int n  = sizeof(maze)/sizeof(maze[0]);
    for (int i = 0; i < n; i++){
        printf("|");
        for (int j = 0; j <= strlen(maze[i]); j++)
        {
            printf("%c|", maze[i][j]);

        }
        printf("\n______________________________________\n");

        
    }


    printf(COLOR_RED "│ " );

    char wordToFind[] = "AVOCADO";
    char inputChar;

    puts("Starting from row 1:");
    printf("First character: ");
    scanf("%c", &inputChar);
    maze[0][5] = ' ';

    getchar();

    printf(COLOR_RESET);

    do
    {
            printf("Second character: ");
            scanf("%c", &inputChar);
            maze[1][5] = ' ';

            getchar();

        if(inputChar == maze[2][5] || inputChar == maze[3][4] || inputChar == maze[2][6]){
            printf("Third character: ");
            scanf("%c", &inputChar);
            maze[2][5] = ' ';
            getchar();

            if(inputChar == maze[4][5] || inputChar == maze[3][4] || inputChar == maze[3][6]){
                printf("Forth character: ");
                scanf("%c", &inputChar);
                maze[3][5] = ' ';
                getchar();

                if(inputChar == maze[5][6] || inputChar == maze[4][5] || inputChar == maze[4][3]){
                    printf("Fifth character: ");
                    scanf("%c", &inputChar);
                    maze[4][4] = ' ';
                    getchar();
                    break;
                }
                else{
                    puts("Obstacle");
                    continue;
                }
            }
            else{
                puts("Obstacle");
                continue;
            }
        }
        else{
            puts("Obstacle");
            continue;
        }
    } while (1);
    

    for (int i = 0; i < n; i++){
        printf("|");
        for (int j = 0; j <= strlen(maze[i]); j++){
            printf("%c|", maze[i][j]);

        }
        printf("\n______________________________________\n");


    }

    


    /*puts("|X|X|X|X|X|X|X|X|X|X|X|");
    puts("|X|X|X|X|X|X|X|X|X|X|X|");
    puts("|X|X|X|X|X|X|X|X|X|X|X|");
    puts("|X|X|X|X|X|X|X|X|X|X|X|");
    puts("|X|X|X|X|X|X|X|X|X|X|X|");
    puts("|X|X|X|X|X|X|X|X|X|X|X|");

    maze[3][0][0] = "S";
    maze[0][2] = "R4";
    maze[0][3] = "R4";
    maze[1][2] = "R4";
    maze[1][4] = "R5";
    maze[2][3] = "R4";
    maze[3][2] = "R4";
    maze[4][1] = "R4";
    maze[5][1] = "R4";
    maze[6][2] = "E";




    return 0;
}
*/