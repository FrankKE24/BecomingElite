#include <stdio.h>

///Recursive implementation of binary search, searches for an element in a sorted array
int binarySearch(int arr[], int first, int last, int target){
    if(first > last){
        return -1;
    }
    
    int mid = (first + last)/2;
    if(target == arr[mid]){
        return mid;
    }
    if(target > arr[mid]){
        return binarySearch(arr, mid +1, last, target);
    }
    if(target < arr[mid]){
        return binarySearch(arr, first, mid -1, target);
    }
}

void sortArray(int *arr, int size){
    //int newarray[size];
    printf("%d\n", *arr);

    for (int j = 0; j < size - 1; j++)
    {

        for (int i = 0; i < size -1; i++){
            if(*(arr + i) > *(arr+ i +1)){
                int temp = *(arr +i);
                *(arr + i) = *(arr+ i + 1);
                *(arr+i + 1) = temp;
            }
        }    
    }
    
   

    for (int i = 0; i < size-1; i++){
        printf("%d \t" , *(arr+i));
    }
    
}


int main(int argc, char const *argv[])
{
    int scores[] = {53, 13, 14, 33, 40, 17, 31, 45, 80, 90, 60};
    int *pscores = scores;
    int n = sizeof(scores)/sizeof(scores[0]);
    int target;
    sortArray(pscores, n);
    printf("\n");


    printf("Enter element to search for: ");
    scanf("%d", &target);
    int resultIterative = binarySearch(scores, 0, n-1, target);
    if (resultIterative == -1){
        printf("\nElement not found!\n");
    }
    else{
        printf("Element %d is found at index %d\n", target, resultIterative);
    }

    return 0;
}
