#include <stdio.h>
#include <limits.h>

#define max(a,b) \
   ({ __typeof__ (a) _a = (a); \
       __typeof__ (b) _b = (b); \
     _a > _b ? _a : _b; })

// Maximum subarray problem is about finding the nonempty, contiguous subarray 
// of array A whose values have the largest sum.
// There are several solutions:
// maxSumSubArrayN3(A), which runs in O(n^3), and called a "brute-force" solution
// and we simply iterate over all the possible subarrays and compare the resultant sum
// maxSumSubArrayN2(A), which runs in O(n^2), can also be considered "brute-force
// however, in this case we "remember" the sum and add the last element
// maxSumSubArrayNLogN(A), which runs in O(nlgn), uses "divide-and-conquer" strategy, 
// but in this version we have a helper function maxCrossingSubArray(A), which runs in linear time
// maxSumSubArrayN(A), which runs in O(n), also called Kadane's algorithm

static int arr[16] = {13, -3, -25, 20, -3, -16, -23, 18, 20, -7, 12, -5, -22, 15, -4, 7};


int maxSumSubArrayN3(int* arr, int length){
	int ans = INT_MIN;						
	for(int sub_array_size = 1; sub_array_size <= length; ++sub_array_size){
		for(int index_start = 0; index_start < length; ++index_start){
			if(index_start + sub_array_size > length){
				break;
      }    
			int sum = 0;
			for(int i = index_start; i < (index_start + sub_array_size); i++){	
				sum += arr[i];
      }
			ans = max(ans,sum);
		}
	}
	return ans;
}


int maxSumSubArrayN2(int* arr, int length){
	int ans = INT_MIN;
	for(int index_start = 0; index_start < length; ++index_start){
		int sum = 0;
		for(int sub_array_size = 1; sub_array_size <= length; ++sub_array_size){
			if(index_start + sub_array_size > length){	
				break;
            }
			sum += arr[index_start + sub_array_size - 1];
			ans = max(ans, sum);
		}
	}
	return ans;
}


// In this version indices of subarray along with sum are also returned
typedef struct sub{
    int maxLeft; 
    int maxRight; 
    int totalSum;
} subArray;

subArray maxCrossingSubArray(int* a, int low, int mid, int high){
    int leftSum = INT_MIN;
    int sum = 0;
    int maxLeft = INT_MIN, maxRight = INT_MIN;
    for (int i = mid; i >= low; --i){
        sum += a[i];
        if(sum > leftSum){
            leftSum = sum;
            maxLeft = i;
        }
    }
    int rightSum = INT_MIN;
    sum = 0;
    for (int j = mid + 1; j <= high; ++j){
        sum += a[j];
        if(sum > rightSum){
            rightSum = sum;
            maxRight = j;
        }
    }
    subArray s = {maxLeft, maxRight, leftSum + rightSum};
    return s;
}

subArray maxSumSubArrayNLogN(int* a, int low, int high){  
    if(high == low){
        subArray equal = {low, high, a[low]};
        return equal;
    }
    else{
        int mid = (low + high)/2;
        subArray left = maxSumSubArrayNLogN(a, low, mid);
        subArray right = maxSumSubArrayNLogN(a, mid + 1, high);
        subArray cross = maxCrossingSubArray(a, low, mid, high);
        if(left.totalSum >= right.totalSum && left.totalSum >= cross.totalSum){
            return left;
        }
        else if(right.totalSum >= left.totalSum && right.totalSum >= cross.totalSum){
            return right;
        }
        else{
            return cross;
        }
    }
}


int maxSumSubArrayN(int* arr, int n){
	int ans = arr[0], sum = 0;
	for(int i = 1; i < n; ++i){
		ans = max(ans,arr[i]);
  }	
	if(ans < 0){				
		return ans; // here we check whether the max subarray is a negative number
  }             // and if so, we return it
	ans = 0;
	for(int i = 0; i < n; ++i){
		if(sum + arr[i] > 0){
			sum += arr[i];
    }    
		else{
			sum  = 0;
    }    
		ans = max(ans, sum);	
	}
	return ans;
}


int main(int argc, char* argv[]){
  int length = sizeof(arr)/sizeof(int);
  
  // ---Perform an operation--- //
  
  printf("%d\n", maxSumSubArrayN3(arr, length));
  
  printf("%d\n", maxSumSubArrayN2(arr, length));
  
  subArray res = maxSumSubArrayNLogN(arr, 0, length);
  printf("%d %d %d\n", res.maxLeft, res.maxRight, res.totalSum);
  
  printf("%d\n", maxSumSubArrayN(arr, length));

}
