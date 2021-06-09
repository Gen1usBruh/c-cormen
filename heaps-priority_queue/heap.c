#include <stdio.h>
#include <limits.h>

// The (binary) heap data structure is an array object 
// that we can view as a nearly complete binary tree.
// There are two kinds of binary heaps: max-heaps and min-heaps.
// The maxHeapify procedure, which runs in O(lgn) time, is the key to maintaining
// the max-heap property.
// The buildMaxHeap procedure, which runs in linear time, produces a maxheap
// from an unordered input array.
// The heapSORT procedure, which runs in O(nlgn) time, sorts an array in place.

static int heap[9] = {5, 3, 17, 10, 84, 19, 6, 22, 9}; //unordered array

// helper functions
int left(int i){
    return 2*i + 1;
}
int right(int i){
    return 2*i + 2;
}

// assume that trees at left(i) and right(i) are max-heaps
// i - specify the position of node to be maxHeapify'd 
// (goes only in one direction after picking left or right child recursively)
void maxHeapify(int* a, int i, int length){
    int l = (i << 1) + 1; //left child position    //alternative to - int l = left(i);
    int r = (i << 1) + 2; //right child position   //int r = right(i);
    int largest = INT_MIN; //stores the position of node with highest value
    if(l <= length && a[l] > a[i]){
        largest = l;
    }
    else{
        largest = i;
    }
    if(r <= length && a[r] > a[largest]){
        largest = r;
    }
    if(largest != i){
        int tmp = a[i];
        a[i] = a[largest];
        a[largest] = tmp;
        maxHeapify(a, largest, length);
    }
}

// iterates over the remaining nodes and runs maxHeapify on each one 
// (since in array elements a[n/2+1...n] are leaves)
void buildMaxHeap(int* a, int length){
    for (int i = length/2; i >= 0; i--){
        maxHeapify(a, i, length);
    } 
}

// Heapsort can be thought of as an improved selection sort:
// like that algorithm, it divides its input into a sorted and an unsorted region,
// and it iteratively shrinks the unsorted region by extracting the largest element
// and moving that to the second region. The improvement consists of the use of a heap data structure
// rather than a linear-time search to find the maximum.
void heapSort(int* a, int length){
    buildMaxHeap(a, length);
    int heapSize = length - 1;
    for(int i = length - 1; i > 0; --i){
        int tmp = a[0];
        a[0] = a[i];
        a[i] = tmp;
        --heapSize;
        maxHeapify(a, 0, heapSize);
    }
}


int main(int argc, char* argv[]){

    int length = sizeof(heap)/sizeof(int);

    // ---Perform an operation--- //

    for (int i = 0; i < length; i++){
        printf("%d ", heap[i]);
    }
}
