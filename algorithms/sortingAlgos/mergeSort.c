#include <stdio.h>

//L and R are the left and the right sub  arrays
void merge(int arr[], int l, int m, int r){
    int n1 = m - l + 1;
    int n2 = r- m;
    int L[n1], R[n2];
    //printf("l1");

    for (int i = 0; i < n1; i++)
    {
        L[i] = arr[l+i];
    }
   // printf("l6");

    for (int j = 0; j < n2; j++)
    {
        R[j] = arr[m+1+j];
    }

        // Merge the temporary arrays back into arr[left..right]
    int i=0, j=0, k=l; //
    while((i<n1) && (j<n2)){
        if(L[i] <= R[j]){
            arr[k] = L[i];
            i++;
        }
        else{
            arr[k] = R[j];
            j++;
        }
        k++;
    }

        // Copy remaining elements of L[], if any
    while (i < n1){
        arr[k] = L[i];
        i++;
        k++;
    }

        // Copy remaining elements of R[], if any
    while(j < n2){
        arr[k] = R[j];
        j++;
        k++;
    }
    
}

void mergeSort(int arr[], int l, int r){

    if(l == r){
        return;
    }
    if(l< r){
        int m = l+(r-l)/2;  //
        //sort first and second halves
        mergeSort(arr, l, m);
        mergeSort(arr, m+1, r);
        printf("l2");

        //merge sorted halves
        merge(arr, l, m, r);
    }
}


int main(int argc, char const *argv[])
{
    int scores[] = {53, 13, 14, 33, 40, 17, 45, 80, 90, 60};
    int n = sizeof(scores)/sizeof(scores[0]);
    //printf("%d\n", scores[1.5]);

    mergeSort(scores, 0, n -1);
    for (int i = 0; i < n; i++){
        printf("%d \t" , scores[i]);
    }
    
    printf("\n");

    return 0;
}