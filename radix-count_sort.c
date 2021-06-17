#include <stdio.h>
#include <math.h>

// Counting sort assumes that each of the n input elements is an integer in the range
// 0 to k, for some integer k. It operates by counting the number of elements that have 
// each distinct key value, and using arithmetic on those counts to determine the 
// positions of each key value in the output sequence.
// Its running time is linear in the number of items and the difference between
// the maximum and minimum key values, so it is only suitable for direct use in situations
// where the variation in keys is not significantly greater than the number of items.
// However, it is often used as a subroutine in radix sort, that can handle larger keys more efficiently.
//
// Overall time complexity is θ(k + n). In practice, we usually use counting sort 
// when we have k = O(n), in which case the running time is θ(n).

//classic implementation
void countingSort(int* a, int* b, int k, int length){
    int c[k + 1];   //for temporary work
    for(int i = 0; i <= k; i++){
        c[i] = 0;
    }
    for(int j = 0; j < length; j++){
        ++c[a[j]];
    }
    for(int i = 1; i <= k; i++){
        c[i] += c[i - 1];
    }
    for(int j = length - 1; j >= 0; j--){
        b[c[a[j]] - 1] = a[j];
        --c[a[j]];
    }
}


int main(int argc, char* argv[]){
  
    int arr[10] = {6, 2, 8, 5, 4, 9, 3, 10, 1, 7};

    int length = sizeof(arr)/sizeof(int);

    int b[length];   //for final output

    countingSort(arr, b, 10, length); //10(k) is the biggest number in the array

    for (int i = 0; i < length; i++){
        printf("%d ", b[i]);
    }

}


// Radix sort avoids comparison by creating and distributing elements into buckets according
// to their base(radix). For elements with more than one significant digit, this bucketing process 
// is repeated for each digit, while preserving the ordering of the prior step, until all digits have been considered.
// In simple words, we need a stable sort used as an intermediate sorting algorithm: counting sort is the very one.
//    
// Running time: θ(d(n + k))
// Given n d-digit numbers in which each digit can take on up to k possible values,
// radix sort correctly sorts these numbers in θ(d(n + k)) time if the stable sort
// it uses takes θ(k + n) time.

// This implementation sorts number in base 10, and differs from canonical one
void countingSort(int* a, int k, int length, int fact){
    int b[length];
    int c[k + 1];
    for(int i = 0; i <= k; i++){
        c[i] = 0;
    }
    for(int j = 0; j < length; j++){
        ++c[(a[j]/fact)%10];
    }
    for(int i = 1; i <= k; i++){
        c[i] += c[i - 1];
    }
    for(int j = length - 1; j >= 0; j--){
        b[c[(a[j]/fact)%10] - 1] = a[j];
        --c[(a[j]/fact)%10];
    }
    for(int i = 0; i < length; i++){   //additional loop for copying
        a[i] = b[i]; 
    }
}
void radixSort(int* a, int d, int length){
    for(int i = 1; i < pow(10, d); i*=10){   // In order to extract only a specific digit from d-digit number, we use factor i
        countingSort(a, 9, length, i);   //k is always 9
    }
}


int main(int argc, char* argv[]){

    int arr[10] = {6, 2, 7234, 5, 44, 9, 334, 10, 1, 77};

    int length = sizeof(arr)/sizeof(int);

    radixSort(arr, 4, length);   //4 is number of digits

    for (int i = 0; i < length; i++){
        printf("%d ", arr[i]);
    }

}
