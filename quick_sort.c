#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Quicksort algorithm applies the divide-and-conquer paradigm in-place
// Steps:
//  1. Partition the array into two subarrays based on a pivot
//  2. Sort the subarrays by recursive calls to quicksort
//  3. Combine
// partition(A, p, r), which runs in θ(n), selects an element as a pivot, 
//  around which to rearrange the array with elements less than or equal to pivot
//  to the left, and elements bigger than or equal to to pivot to the right
// quickSort(A, p, r) calls the partition(), which in turn returns the pivot,
//  and recursive calls are made to quickSort() until one element is left
//
// The running time depends on whether the partitioning is balanced or unbalanced.
// The worst-case behavior for quicksort occurs when the partitioning routine produces
// one subproblem with n > 1 elements and one with 0 elements. Another case is when 
// the array is already sorted. 
// Thus, if the partitioning is maximally unbalanced at every recursive level of the
// algorithm, the running time is θ(n^2)
//
// The best-case behavior occurs when we equally balance the two sides of the partition 
// at every level of the recursion, yielding θ(nlgn)
//
// However, the average-case running time of quicksort is much closer to the best-case.
// The answer lies in understanding how the balance of the partitioning is reflected in the
// recurrence that describes the running time.
// In fact, any split of constant proportionality yields a recursion tree of depth θ(lgn), 
// where the cost at each level is O(n). The running time is therefore O(nlgn), whenever 
// the split has constant proportionality.
//
//
//

int partition(int* a, int low, int high){
    int x = a[high]; //pivot
    int i = low;     //partition index
    for(int j = low; j < high; j++){
        if(a[j] <= x){
            int tmp = a[i];
            a[i] = a[j];
            a[j] = tmp;
            ++i;
        } 
    }
    int tmp = a[i];
    a[i] = a[high];
    a[high] = tmp;

    return i;
}
void quickSort(int* a, int low, int high){
    if(low < high){
        int pIndex = partition(a, low, high);
        quickSort(a, low, pIndex - 1);
        quickSort(a, pIndex + 1, high);
    }
}


// We can sometimes add randomization to an algorithm in order to
// obtain good expected performance over all inputs. 
// For quicksort it is called "random sampling":
//  Instead of choosing the last element of the array as a pivot, 
//  we will select a randomly chosen element. 
// Because we randomly choose the pivot element, we expect the split of
// the input array to be reasonably well balanced on average. 

int randPartition(int* a, int low, int high){
    srand(time(NULL));
    int i = low + rand() % (high - low);
    int tmp = a[i];
    a[i] = a[high];
    a[high] = tmp;
    return partition(a, low, high);
}
void randQuickSort(int* a, int low, int high){
    if(low < high){
        int pIndex = randPartition(a, low, high);
        randQuickSort(a, low, pIndex - 1);
        randQuickSort(a, pIndex + 1, high);
    }
}


int main(int argc, char* argv[]){
  
    int arr[10] = {6, 2, 8, 5, 4, 9, 3, 10, 1, 7};

    int length = sizeof(arr)/sizeof(int);

    quickSort(arr, 0, length - 1);
//     randQuickSort(arr, 0, length - 1);

    for (int i = 0; i < length; i++){
        printf("%d ", arr[i]);
    }

}
