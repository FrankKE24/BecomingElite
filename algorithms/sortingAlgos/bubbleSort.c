#include <stdio.h>

void bubbleSort(int arr[], int size){
    for (int i = 0; i < size - 1; i++)
    {
        for (int j = 0; j < size -1; j++)
        {
            if(arr[j] > arr[j +1]){
                int temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
            }
        }
        
    }
    
}

int main(int argc, char const *argv[])
{
    int scores[] = {53, 13, 14, 33, 40, 17, 31, 45, 80, 90, 60};
    int n = sizeof(scores)/sizeof(scores[0]);
    int target;
    bubbleSort(scores, n);
    for (int i = 0; i < n; i++){
        printf("%d \t" , scores[i]);
    }
    
    printf("\n");

    return 0;
}
