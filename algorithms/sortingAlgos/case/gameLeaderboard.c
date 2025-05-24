#include <stdio.h>

typedef struct{
    char name[50];
    int score;
}Player;

void sortPlayers(Player players[], int n){
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n-1; j++)
        {
            if(players[j].score < players[j+1].score){
                Player temp = players[j];
                players[j]  = players[j+1];
                players[j+1] = temp;
            }
        }
        
    }
    
}

void printLeaderBoard(Player players[], int n){
    printf("LEADERBOARD\n");
    for (int i = 0; i < n; i++){
        printf("Name: %s     Score: %d \n", players[i].name, players[i].score);
    }
    
}
int main(int argc, char const *argv[])
{
    /*Player player1 = {"Alfred Michie", 450};
    Player player2 = {"ABD Oswd", 480};
    Player player3 = {"David Ferry", 560};

    Player myPlayers[] = {player1, player2, player3};*/

    Player myPlayers[] = {{"Alfred Michie", 450}, 
                            {"Lee-Harvey Oswd", 480},
                             {"David Ferry", 560}};

    int size= sizeof(myPlayers)/sizeof(myPlayers[0]);

    sortPlayers(myPlayers, size);
    printLeaderBoard(myPlayers, size);

    return 0;
}
