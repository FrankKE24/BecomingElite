#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <unistd.h>

int main(int argc, char const *argv[])
{
    srand(time(NULL)); //seed the random number generator
    int randomNumber = rand(); //generate a random ni btween 0 and RAND_MAX

    int guessedNo;
    int randomInRange;
    int randomInRange2;
    int randomInRange3;
    int randomInRange4;
    int randomInRange5;
    int i = 0;

    //printf("%.0d\n" , randomNumber);

    //printf("Range: %d", randomInRange);

    do
    {
        randomInRange = rand() %10;
        randomInRange2 = rand() %10;
        randomInRange3 = rand() %10;
        randomInRange4 = rand() %10;
        randomInRange5 = rand() %10;

        int position[]  = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
        //int index = (rand() %5);
                /*int randomIndex0 = (rand() %5);
        int randomIndex1 = (rand() %5);
        int randomIndex2 = (rand() %5);
        int randomIndex3 = (rand() %5);
        int randomIndex4 = (rand() %5);*/


        printf("%d\n", randomInRange);

        printf("Guess a number between 0 and 10: ");
        scanf("%d", &guessedNo);
        getchar();
        printf("\n");

        if(i == 0){
            randomInRange = 0;
            position[randomInRange] = guessedNo;
        }
        /*else{
            position[randomInRange1] = randomInRange2;
            position[randomInRange] = randomInRange3;
            position[randomInRange3] = randomInRange4;
            position[randomInRange4] = randomInRange5;

        }*/

        if(i == 1){
            randomInRange2 = 1;
            position[randomInRange2] = guessedNo;
        }
        /*else{
            position[randomInRange] = randomInRange;
            position[randomInRange] = randomInRange3;
            position[randomInRange3] = randomInRange4;
            position[randomInRange4] = randomInRange5;
        }*/

        if(i == 2){
            randomInRange3 = 2;
            position[randomInRange3] = guessedNo;  
        }
        /*else{
            position[randomInRange] = randomInRange;
            position[randomInRange1] = randomInRange2;
            position[randomInRange3] = randomInRange4;
            position[randomInRange4] = randomInRange5;
        }*/
        if(i == 3){
            randomInRange4 = 3;
            position[randomInRange4] = guessedNo;
        }
        /*else{
            position[randomInRange] = randomInRange;
            position[randomInRange1] = randomInRange2;
            position[randomInRange] = randomInRange3;
            position[randomInRange4] = randomInRange5;
        }*/
        if(i == 4){
            randomInRange5 = 4;
            position[randomInRange5] = guessedNo;
        }
        /*else{
            position[randomInRange] = randomInRange;
            position[randomInRange1] = randomInRange2;
            position[randomInRange] = randomInRange3;
            position[randomInRange3] = randomInRange4;
        }*/
        //position[index] = guessedNo;
        //position[indexComp] = randomInRange;


        printf("   %d   |    |    %d     \n",  position[randomInRange], position[randomInRange2]);
        printf("-------|----|---------\n");
        printf("       | %d  |         \n",  position[randomInRange3]);
        printf("-------|----|--------\n");
        printf("   %d   |    |    %d     \n", position[randomInRange4], position[randomInRange5]);  

        i++;
        if(i > 4){
            i= 0;
        }
        //sleep(2);
        //system("clear");
        if((position[randomInRange] == position[randomInRange3] == position[randomInRange5]) || (position[randomInRange2] == position[randomInRange3] == position[randomInRange4])){
            break;
        }
    } while (1);
    puts("You win");
    

    

    

    return 0;
}
