#include <stdio.h>


// Bubble sort.
// Simple algorithm that repeatedly steps through the list to be sorted,
// compares each pair of adjacent items and swaps them if they are in the wrong order.
//
// Worst-case running time: θ(n^2)

void bubbleSort(int *arr, int length){
    for(int i = 0; i < length; i++){
        for(int j = length - 1; j > i; j--){
            if(arr[j] < arr[j - 1]){
                int temp = arr[j];
                arr[j] = arr[j - 1];
                arr[j - 1] = temp;
            }
        }
    }
} 


int main(int argc, char* argv[]){

    int arr[10] = {6, 2, 8, 5, 4, 9, 3, 10, 1, 7};

    int length = sizeof(arr)/sizeof(int);

    bubbleSort(arr, length);

    for (int i = 0; i < length; i++){
        printf("%d ", arr[i]);
    }

}
