#include <stdio.h>
#include <limits.h>
#include <stdlib.h>

// A priority queue is a data structure for maintaining a set S of elements, each
// with an associated value called a key. A max-priority queue supports the following
// operations:
// maxHeapInsert(S, x), which runs in O(lgn), inserts the element x into the set S
// heapMax(S), which runs in θ(1), returns the element of S with the largest key
// heapExtractMax(S), which runs in O(lgn), removes and returns the element of S with the largest key
// heapIncreaseKey(S, x, k), which runs in O(lgn), increases the value of element x’s key to the new value k,
// which is assumed to be at least as large as x’s current key value.

static int heap[9] = {84, 22, 19, 10, 3, 17, 6, 5, 9}; //max-heap

// returns the parent-node
int parent(int i){
    return i/2;
}

int heapMax(int *a){
    return a[0];
}

int heapExtractMax(int* a, int length){
    if(length < 1){
        fprintf(stderr,"Heap underflow");
        exit(EXIT_FAILURE);
    } 
    int max = a[0];
    a[0] = a[length - 1];
    --length;
    maxHeapify(a, 0, length); //After extraction heap is re-heapify'd with the new root

    return max;
}

void heapIncreaseKey(int* a, int i, int key){
    if(key < a[i]){
        fprintf(stderr,"New key is smaller then current key");
        exit(EXIT_FAILURE);
    }
    a[i] = key;
    while(i > 0 && a[parent(i)] < a[i]){
        int tmp = a[i];
        a[i] = a[parent(i)];
        a[parent(i)] = tmp;
        i = parent(i);
    }
}

void maxHeapInsert(int* a, int key, int length){
    a[length] = INT_MIN;               //expand the heap by adding a new leaf
    heapIncreaseKey(a, length, key);   //set the key of this new node to its correct value and maintain the max-heap property
}


int main(int argc, char* argv[]){

    int length = sizeof(heap)/sizeof(int);

    // ---Perform an operation--- //

    for (int i = 0; i < length; i++){
        printf("%d ", heap[i]);
    }
}
