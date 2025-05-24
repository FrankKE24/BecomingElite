///Sorting stock pricce using QUICKSORT
///Add more fields like stock prices, trade volumes, or other metrics to enable better insights.
#include <stdio.h>

void swap(double *x , double *y){
    int temp = *x;
    *x = *y;
    *y  = temp;
}

int partition(double array[], int low, int high){
    double pivot = array[high];
    int i = low -1;
    for (int j = low; j < high; j++)
    {
        if(array[j] < pivot){
            i++;
            swap(&array[i+1], &array[high]);

        }
    }
    swap(&array[i+1], &array[high]);
    return (i + 1);
}

void quickSort(double array[], int low, int high){
    if(low < high){
        int pivot = partition(array, low, high);
        quickSort(array, low, pivot -1);
        quickSort(array, pivot+1, high);
    }
}

void printArray(double arr[], int size) {
    for (int i = 0; i < size; i++) {
        printf("%.f ", arr[i]);
    }
    printf("\n");
}

int main(int argc, char const *argv[])
{
    double stock_prices[] = {3443.45, 54490.35, 9000.0, 854983.05, 45534.4};
    int size = sizeof(stock_prices)/sizeof(stock_prices[0]);

    quickSort(stock_prices, 0, size -1);
    printf("Sorted stock prices: \n");
    //printArray(stock_prices, size);
    for (int i = 0; i < size; i++) {
        printf("%.f ", stock_prices[i]);
    }
    return 0;
}
