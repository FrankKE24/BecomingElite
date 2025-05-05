#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

char board[3][3];
const char PLAYER = '$';
const char COMP = 'O';

void resetBoard();
void printBoard();
int checkFreeSpaces();
void playerMove();
void computerMove();
char checkWinner();
void printWinner(char);

int main(int argc, char const *argv[])
{

    char response;

    resetBoard();
    do
    {
        char winner = ' ';
        while (winner == ' ' && checkFreeSpaces() != 0)
        {
            printBoard();
            playerMove(); 
            
            winner = checkWinner();
            if(winner != ' ' || checkFreeSpaces() == 0){
                break;
            }
    
            computerMove();
            winner = checkWinner();
            if(winner != ' ' || checkFreeSpaces() == 0){
                break;
            }
            while(getchar() != '\n');

        }
        
        printBoard();
        printWinner(winner);
        printf("Do you wish to play again..(Y/N): ");
        getchar();
        scanf("%c", &response);
        response = toupper(response);
        resetBoard();
        getchar();
        system("clear");

    } while (response == 'Y');
    return 0;
}

void resetBoard(){
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            board[i][j] = ' ';
        }
        
    }
    
}

void printBoard(){

    printf("   %c  |  %c |    %c     \n", board[0][0], board[0][1], board[0][2]);
    printf("------|----|---------\n");
    printf("   %c  |  %c |    %c     \n",  board[1][0], board[1][1], board[1][2]);
    printf("------|----|--------\n");
    printf("   %c  |  %c |    %c     \n", board[2][0], board[2][1], board[2][2]);
}

int checkFreeSpaces(){
    int freeSpaces = 9;

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if(board[i][j] != ' '){
                freeSpaces--;
            }
        }
        
    }

    return freeSpaces;
}

void playerMove(){
    int x, y;

    do
    {
        printf("Enter row number #x(1-3): ");
        scanf("%d", &x);
        x--;
        printf("Enter column number #y(1-3): ");
        scanf("%d", &y);
        y--;
    
        if (checkFreeSpaces() != 0)
        {
            if(board[x][y] == ' '){
                board[x][y] = PLAYER;
                break;
            }
            if(board[y][y] != ' '){
                puts("Invalid Move!");
            }
        }
        else{

            break;
        }    
    } while (board[x][y] != ' ');
    

}

void computerMove(){
    srand(time(0));
    int x, y;

    if(checkFreeSpaces != 0){
        do
        {
            x = rand() %3;
            y = rand() % 3;
        } while (board[x][y] != ' ');
        
    }
    board[x][y] = COMP;

}

char checkWinner(){
    //check rows
    for (int i = 0; i < 3; i++)
    {
        if(board[i][0] == board[i][1] && board[i][0] == board[i][2]){
            return board[i][0];
        }
    }
    //check columns
    for (int i = 0; i < 3; i++)
    {
        if(board[0][i] == board[1][i] && board[0][i] == board[2][i]){
            return board[0][i];
        }
    }

    //check diagonals
    if(board[0][0] == board[1][1] && board[0][0] == board[2][2]){
        return board[0][0];
    }
    if(board[0][2] == board[1][1] && board[0][2] == board[2][0]){
        return board[2][0];
    }
    
    return ' ';
}

void printWinner(char winner){
    if(winner == PLAYER){
        puts("YOU WIN");
    }
    else if(winner == COMP){
        puts("YOU LOSE");
    }
    else{
        puts("ITS A TIE!");
    }
}
