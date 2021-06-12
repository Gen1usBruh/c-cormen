#include <stdio.h>


// Selection sort.
// The algorithm divides the input list into two parts:
// the sublist of items already sorted, which is built up from left to right at the front of the list,
// and the sublist of items remaining to be sorted that occupy the rest of the list.
// Initially, the sorted list is empty and the unsorted sublist is the entire input list.
// The algorithm proceeds by finding the smallest element in the unsorted list,
// exchanging it with the leftmost unsorted element, and moving the sublist boundaries one element to the right.
//
// Worst-case and best-case running times: θ(n^2) 

void selectionSort(int* a, int length){
    for(int i = 0; i < length - 1; i++){
        int min = i;
        for(int j = i + 1; j < length; j++){
            if(a[j] < a[min]){
                min = j;
            }
        }
        int tmp = a[i];
        a[i] = a[min];
        a[min] = tmp;
    }   
}


int main(int argc, char* argv[]){

    int arr[10] = {6, 2, 8, 5, 4, 9, 3, 10, 1, 7};

    int length = sizeof(arr)/sizeof(int);

    selectionSort(arr, length);

    for (int i = 0; i < length; i++){
        printf("%d ", arr[i]);
    }

}
