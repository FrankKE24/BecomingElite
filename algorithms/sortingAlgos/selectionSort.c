#include <stdio.h>

void selectionSort(int arr[], int size){

    for (int i = 0; i < size -1; i++)
    {
        int min = i;
        for (int j = (i+1); j < size; j++){
            if(arr[j] < arr[min]){
                min = j;
            }
        }

        if(arr[min] != i){
            int temp = arr[min];
            arr[min] = arr[i];
            arr[i] = temp;
        }
        
        
    }
    
}


int main(int argc, char const *argv[])
{
    int scores[] = {53, 13, 14, 33, 40, 17, 31, 45, 80, 90, 60};
    int n = sizeof(scores)/sizeof(scores[0]);
    int target;
    selectionSort(scores, n);
    for (int i = 0; i < n; i++){
        printf("%d \t" , scores[i]);
    }
    
    printf("\n");

    return 0;
}