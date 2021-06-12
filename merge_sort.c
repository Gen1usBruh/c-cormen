#include <stdio.h>


// Merge Sort closely follows divide-and-conquer paradigm.
// In most cases, there are two subroutines involved:
//  merge(), which runs in θ(n) time, is the key operation responsible for merging 
//  of two sorted sequences;
//  mergeSort() simply prepares the array for merging, where the recursive calls are made by dividing
//  the array into two subarrays until one (obviously sorted) element is left, and,
//  finally, the call to merge() is done.
// 
// Worst-case running time: θ(nlgn)

void merge(int* arr, int low, int mid, int high){

    const int n1 = mid - low + 1;
    const int n2 = high - mid;

    int L[n1], R[n2];

    for (int i = 0; i < n1; i++)
        L[i] = arr[low + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];

    int i = 0, j = 0, k = low;

    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        }
        else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    } 
}
void mergeSort(int* arr, int low, int high)
{
    if (low < high) {
        int mid = low + (high - low)/2;
        mergeSort(arr, low, mid);
        mergeSort(arr, mid + 1, high); 
        merge(arr, low, mid, high);
    }
}


int main(int argc, char* argv[]){

    int arr[10] = {6, 2, 8, 5, 4, 9, 3, 10, 1, 7};

    int length = sizeof(arr)/sizeof(int);

    mergeSort(arr, 0, length);

    for (int i = 0; i < length; i++){
        printf("%d ", arr[i]);
    }

}
