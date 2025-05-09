#include <stdio.h>
#include <stdlib.h>

// Function to merge two subarrays
void merge(int arr[], int left, int mid, int right) {
    int n1 = mid - left + 1; // Size of left subarray
    int n2 = right - mid;    // Size of right subarray

    // Create temporary arrays
    int L[n1], R[n2];

    // Copy data to temporary arrays
    for (int i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];

    // Merge the temporary arrays back into arr[left..right]
    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    // Copy remaining elements of L[], if any
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    // Copy remaining elements of R[], if any
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

// Function to perform merge sort
void mergeSort(int arr[], int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;

        // Recursively sort the first and second halves
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);

        // Merge the sorted halves
        merge(arr, left, mid, right);
    }
}

// Function to print an array
void printArray(int arr[], int size) {
    for (int i = 0; i < size; i++)
        printf("%d ", arr[i]);
    printf("\n");
}

// Main function
int main() {
    int n;

    /*printf("Enter the number of elements: ");
    scanf("%d", &n);

    int* arr = (int*)malloc(n * sizeof(int));
    if (!arr) {
        printf("Memory allocation failed.\n");
        return -1;
    }

    printf("Enter the elements:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    printf("Original array: ");
    printArray(arr, n);*/
    int scores[] = {53, 13, 14, 33, 40, 17, 45, 80, 90, 60};
    n = sizeof(scores)/sizeof(scores[0]);

    mergeSort(scores, 0, n - 1);

    printf("Sorted array: ");
    printArray(scores, n);

    //free(arr);
    return 0;
}





/*int mergeSort(int array[], int n ){
    if(n == 1) return array;

    int L[(n/2)];

    for (int i = 0; i < (n/2); i++){
        L[i] = array[i];
    }

    int R[(n/2)];
    for (int i = (n/2); i < (n); i++){
        R[i] = array[i];
    }
    mergeSort(L[(n/2)], sizeof(L));
    mergeSort(R[(n/2)], sizeof(R));

    return merge(L[(n/2)], R[(n/2)]);
    

}

int merge(int arrA[], int arrB[]){

    int arrayC[];
    while (arrA)
    {
        if(arrA[0]>arrB[0]){

        }
    }
    
}


int main(int argc, char const *argv[])
{
    int scores[] = {53, 13, 14, 33, 40, 17, 45, 80, 90, 60};
    int n = sizeof(scores)/sizeof(scores[0]);

    mergeSort(scores, n );
    for (int i = 0; i < n; i++){
        printf("%d \t" , scores[i]);
    }
    
    printf("\n");

    return 0;
}*/