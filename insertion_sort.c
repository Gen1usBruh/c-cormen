#include <stdio.h>

// Insertion sort is an efficient algorithm for sorting a small number of elements.
// It inserts array[i] (or key) into sorted array[0, i - 1] by pairwise swaps
// down to the correct position.
// It works the way many people sort a hand of playing cards.  
// 
// Worst-case running time: θ(n^2).
// Best-case running time: O(n). Ex: already sorted array.
void insertSort(int* arr, int length){
    for(int i = 1; i < length; ++i){
        int key = arr[i];
        int j = i - 1;
        while(j >= 0 && arr[j] > key){
            arr[j + 1] = arr[j];
            --j;
        }
        arr[j + 1] = key;
    }
}


int main(int argc, char* argv[]){

    int arr[10] = {6, 2, 8, 5, 4, 9, 3, 10, 1, 7};

    int length = sizeof(arr)/sizeof(int);

    insertSort(arr, length);

    for (int i = 0; i < length; i++){
        printf("%d ", arr[i]);
    }

}
