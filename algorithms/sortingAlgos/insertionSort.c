#include <stdio.h>

void insertionSort(int arr[], int size){
    int holePosition, valueToInsert;

    for (int i = 0; i <= size; i++)
    {
        valueToInsert = arr[i];
        holePosition = i;
        while ((holePosition > 0 ) && (arr[holePosition -1] > valueToInsert)){
        arr[holePosition] = arr[holePosition - 1];
        holePosition = holePosition -1;
        }
        arr[holePosition] = valueToInsert;
         
        
    }
    
}

int main(int argc, char const *argv[])
{
    int scores[] = {53, 13, 14, 33, 40, 17, 31, 45, 80, 90, 60};
    int n = sizeof(scores)/sizeof(scores[0]);
    int target;
    insertionSort(scores, n);
    for (int i = 0; i < n; i++){
        printf("%d \t" , scores[i]);
    }
    
    printf("\n");

    return 0;
}