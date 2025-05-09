#include <stdio.h>

void swap(int *x, int *y){
    int temp = *x;
    *x = *y;
    *y = temp;
}

int partition(int arr[], int low, int high){
    int pivot = arr[high];
    int i = (low - 1);
    int j;

    for ( j = low; j < high; j++)
    {
        if(arr[j] <= pivot){
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + i], &arr[high]);
    return (i+1);
    
}


void quickSort(int arr[], int low, int high){
    if(low < high){
        int pi = partition(arr, low, high);
        
        quickSort(arr, low, pi -1);
        quickSort(arr, pi + 1, high);
    }
}

int main(int argc, char const *argv[])
{
    int scores[] = {53, 13, 14, 33, 45, 40, 17, 45, 80, 90, 60};
    int n = sizeof(scores)/sizeof(scores[0]);

    quickSort(scores, 0, n-1);
    for (int i = 0; i < n; i++){
        printf("%d \t" , scores[i]);
    }
    
    printf("\n");

    return 0;
}