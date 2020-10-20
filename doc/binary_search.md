<!-- START doctoc generated TOC please keep comment here to allow auto update -->
<!-- DON'T EDIT THIS SECTION, INSTEAD RE-RUN doctoc TO UPDATE -->
**Table of Contents**  *generated with [DocToc](https://github.com/thlorenz/doctoc)*

- [Binary search](#binary-search)
  - [Framework 1: Binary Search for target](#framework-1-binary-search-for-target)
    - [Key points](#key-points)
    - [Distinguishing Syntax:](#distinguishing-syntax)
  - [Framework 2: Boundary in Binary Search](#framework-2-boundary-in-binary-search)
      - [Find Ceiling (Lower bound)](#find-ceiling-lower-bound)
      - [Find Floor (Higher bound )](#find-floor-higher-bound-)
      - [Find left Boundary](#find-left-boundary)
      - [Find right Boundary](#find-right-boundary)
    - [First bad version](#first-bad-version)
    - [Search number range](#search-number-range)
    - [Search in a sorted infinity Array](#search-in-a-sorted-infinity-array)
    - [Minimum Difference with Key](#minimum-difference-with-key)
    - [Find K Closest Elements](#find-k-closest-elements)
  - [Bitonic(Monotonic increasing then decreasing)](#bitonicmonotonic-increasing-then-decreasing)
    - [Find Peak/Max Element](#find-peakmax-element)
    - [Fine Element in Bitonic](#fine-element-in-bitonic)
    - [Find Minimum in rotated array](#find-minimum-in-rotated-array)
      - [Find minimum with duplicate](#find-minimum-with-duplicate)
    - [Search in rotated sorted array](#search-in-rotated-sorted-array)
      - [Search in rotated array with Duplicate](#search-in-rotated-array-with-duplicate)
    - [Local Minimum](#local-minimum)
  - [Other example](#other-example)
    - [Square Calculation](#square-calculation)
    - [Find K-th Smallest Pair Distance](#find-k-th-smallest-pair-distance)
    - [Median of Two Sorted Arrays](#median-of-two-sorted-arrays)

<!-- END doctoc generated TOC please keep comment here to allow auto update -->

# Binary search

Anything that can split the Search space can use Binary search


## Framework 1: Binary Search for target

```CPP
int binarySearch(int[] nums, int target) {
    int left = 0; 
    int right = nums.length - 1; // length

    while(left <= right) {
        int mid = left + (right - left) / 2;
        if(nums[mid] == target)
            return mid; 
        else if (nums[mid] < target)
            left = mid + 1; // 
        else if (nums[mid] > target)
            right = mid - 1; // 
    }
    return -1;
}
```

### Key points


* Most basic and elementary form of Binary Search
* Search Condition can be determined without comparing to the element's neighbors (or use specific elements around it)
* No post-processing required because at each step, you are checking to see if the element has been found. If you reach the end, then you know the element is not found

### Distinguishing Syntax:

```
Initial Condition: left = 0, right = length-1
Termination: left > right
Searching Left: right = mid-1
Searching Right: left = mid+1
```

## Framework 2: Boundary in Binary Search

https://www.educative.io/courses/grokking-the-coding-interview/qA5wW7R8ox7


#### Find Ceiling (Lower bound)

```CPP
static int searchCeilingOfANumber(const vector<int>& arr, int key) {
    if (key > arr[arr.size() - 1]) {  // if the 'key' is bigger than the biggest element
      return -1;
    }

    int start = 0, end = arr.size() - 1;
    while (start <= end) {
      int mid = start + (end - start) / 2;
      if (key < arr[mid]) {
        end = mid - 1;
      } else if (key > arr[mid]) {
        start = mid + 1;
      } else {  // found the key
        return mid;
      }
    }
    // since the loop is running until 'start <= end', so at the end of the while loop, 'start ==
    // end+1' we are not able to find the element in the given array, so the next big number will be
    // arr[start]
    return start;
  }
```


#### Find Floor (Higher bound )

```CPP
static int searchFloorOfANumber(const vector<int>& arr, int key) {
    if (key < arr[0]) {  // if the 'key' is smaller than the smallest element
      return -1;
    }

    int start = 0, end = arr.size() - 1;
    while (start <= end) {
      int mid = start + (end - start) / 2;
      if (key < arr[mid]) {
        end = mid - 1;
      } else if (key > arr[mid]) {
        start = mid + 1;
      } else {  // found the key
        return mid;
      }
    }
    // since the loop is running until 'start <= end', so at the end of the while loop, 'start ==
    // end+1' we are not able to find the element in the given array, so the next smaller number
    // will be arr[end]
    return end;
  }
```

#### Find left Boundary

```CPP
static int searchLeftBoudary(const vector<int>& nums, int key) {
    if (key < nums[0]) {  // if the 'key' is smaller than the smallest element
      return -1;
    }

    int start = 0, end = nums.size() - 1;
    while (start <= end) {
      int mid = start + (end - start) / 2;
      if (key < arr[mid]) {
        end = mid - 1;
      } else if (key > nums[mid]) {
        start = mid + 1;
      } else {  // found the key, still move to left
        end = mid-1;
      }
    }
    //ending condition will be start = end+1, so start will be first index or key
    return start;
  }
```

#### Find right Boundary

```CPP
static int searchRightBoudary(const vector<int>& nums, int key) {
    if (key > nums[nums.size()-1]) {  // if the 'key' is larger than the smallest element
      return -1;
    }

    int start = 0, end = nums.size() - 1;
    while (start <= end) {
      int mid = start + (end - start) / 2;
      if (key < arr[mid]) {
        end = mid - 1;
      } else if (key > nums[mid]) {
        start = mid + 1;
      } else {  // found the key, still move to right
        start = mid+1;
      }
    }
    //ending condition will be start = end+1, so end will be last index or key
    return end;
  }
```


### First bad version

https://leetcode.com/problems/first-bad-version/

You are a product manager and currently leading a team to develop a new product. Unfortunately, the latest version of your product fails the quality check. Since each version is developed based on the previous version, all the versions after a bad version are also bad.

Suppose you have n versions [1, 2, ..., n] and you want to find out the first bad one, which causes all the following ones to be bad.

You are given an API bool isBadVersion(version) which will return whether version is bad. Implement a function to find the first bad version. You should minimize the number of calls to the API.
```
Example:

Given n = 5, and version = 4 is the first bad version.

call isBadVersion(3) -> false
call isBadVersion(5) -> true
call isBadVersion(4) -> true

Then 4 is the first bad version. 
```

```CPP
int firstBadVersion(int n) {
    int l = 1;
    int r = n;
    
    int ret = l;
    

    while(l<=r){
        int mid = l+(r-l)/2;
        //equal, find left 
        if (isBadVersion(mid)) {
            r = mid-1;
        }else {
            l = mid+1;
        }
    }
    //ending condition is l=r+1, l is first bad, r is good
    return l;
}
```

### Search number range

https://www.educative.io/courses/grokking-the-coding-interview/R1B78K9oBEz

https://leetcode.com/problems/find-first-and-last-position-of-element-in-sorted-array/

Given an array of numbers sorted in ascending order, find the range of a given number ‘key’. The range of the ‘key’ will be the first and last position of the ‘key’ in the array.

Write a function to return the range of the ‘key’. If the ‘key’ is not present return [-1, -1].

```
Example 1:

Input: [4, 6, 6, 6, 9], key = 6
Output: [1, 3]
Example 2:

Input: [1, 3, 8, 10, 15], key = 10
Output: [3, 3]
```

```CPP
    vector<int> searchRange(vector<int>& nums, int target) {
        vector<int> result(2,-1);
        int left = -1;
        int right = -1;
        left = search(nums, target, false);
        if (left != -1) {  // no need to search if lower bound is not there
          right = search(nums, target, true);
        }else{
            return result;
            
        }
        result[0] = left;
        result[1] = right;
        return result;
    }
    
    int search(const vector<int> &nums, int target, bool upper_bound) {
        int index = -1;
        int start = 0, end = nums.size() - 1;
        while (start <= end) {
          int mid = start + (end - start) / 2;
          if (target < nums[mid]) {
            end = mid - 1;
          } else if (target > nums[mid]) {
            start = mid + 1;
          } else {  // target == nums[mid]
            index = mid;
            if (upper_bound) {
              start = mid + 1;  // search ahead to find the last index of 'key'
            } else {
              end = mid - 1;  // search behind to find the first index of 'key'
            }
          }
        }
        return index;
  }
```

### Search in a sorted infinity Array

https://www.educative.io/courses/grokking-the-coding-interview/B1ZW38kXJB2

Since it is not possible to define an array with infinite (unknown) size, you will be provided with an interface ArrayReader to read elements of the array. ArrayReader.get(index) will return the number at index; if the array’s size is smaller than the index, it will return Integer.MAX_VALUE.

```CPP
static int search(ArrayReader *reader, int key) {
    // find the proper bounds first
    int start = 0, end = 1;
    while (reader->get(end) < key) {
      int newStart = end + 1;
      end += (end - start + 1) * 2;  // increase to double the bounds size
      start = newStart;
    }
    return binarySearch(reader, key, start, end);
  }

  static int binarySearch(ArrayReader *reader, int key, int start, int end) {
    while (start <= end) {
      int mid = start + (end - start) / 2;
      if (key < reader->get(mid)) {
        end = mid - 1;
      } else if (key > reader->get(mid)) {
        start = mid + 1;
      } else {  // found the key
        return mid;
      }
    }

    return -1;
  }
```

### Minimum Difference with Key

https://www.educative.io/courses/grokking-the-coding-interview/mymvP915LY9

Given an array of numbers sorted in ascending order, find the element in the array that has the minimum difference with the given ‘key’.

```
Example 1:

Input: [4, 6, 10], key = 7
Output: 6
Explanation: The difference between the key '7' and '6' is minimum than any other number in the array 
```

```CPP
  static int searchMinDiffElement(const vector<int>& arr, int key) {
    if (key < arr[0]) {
      return arr[0];
    }
    if (key > arr[arr.size() - 1]) {
      return arr[arr.size() - 1];
    }

    int start = 0, end = arr.size() - 1;
    while (start <= end) {
      int mid = start + (end - start) / 2;
      if (key < arr[mid]) {
        end = mid - 1;
      } else if (key > arr[mid]) {
        start = mid + 1;
      } else {
        return arr[mid];
      }
    }

    // at the end of the while loop, 'start == end+1'
    // we are not able to find the element in the given array
    // return the element which is closest to the 'key'
    if ((arr[start] - key) < (key - arr[end])) {
      return arr[start];
    }
    return arr[end];
  }
```


### Find K Closest Elements

Given a sorted array arr, two integers k and x, find the k closest elements to x in the array. The result should also be sorted in ascending order. If there is a tie, the smaller elements are always preferred.

 
```
Example 1:

Input: arr = [1,2,3,4,5], k = 4, x = 3
Output: [1,2,3,4]
Example 2:

Input: arr = [1,2,3,4,5], k = 4, x = -1
Output: [1,2,3,4]
```

```CPP
class Solution {
public:
    vector<int> findClosestElements(vector<int>& arr, int k, int x) {
        //linear search is OK, but more efficiently we should run Binary Search
        //Assume we are taking A[i] ~ A[i + k -1].
        //We can binary research i
        //We compare the distance between x - A[mid] and A[mid + k] - x
        
        /*
        case 1: x - A[mid] < A[mid + k] - x, need to move window go left
-------x----A[mid]-----------------A[mid + k]----------

case 2: x - A[mid] < A[mid + k] - x, need to move window go left again
-------A[mid]----x-----------------A[mid + k]----------

case 3: x - A[mid] > A[mid + k] - x, need to move window go right
-------A[mid]------------------x---A[mid + k]----------

case 4: x - A[mid] > A[mid + k] - x, need to move window go right
-------A[mid]---------------------A[mid + k]----x------

If x - A[mid] > A[mid + k] - x,
it means A[mid + 1] ~ A[mid + k] is better than A[mid] ~ A[mid + k - 1],
and we have mid smaller than the right i.
So assign left = mid + 1.
        
        */
        
        int l =0;
        int r = arr.size()-k;
        
        while(l<r){
            int mid = (l + r) / 2;
            if (x - arr[mid] > arr[mid + k] - x)
                l = mid + 1;
            else
                r = mid;
        }
        
        
        return vector<int>(arr.begin() + l, arr.begin() + l + k);
        
    }
};
```

## Bitonic(Monotonic increasing then decreasing)



### Find Peak/Max Element

https://leetcode.com/problems/find-peak-element/

https://www.educative.io/courses/grokking-the-coding-interview/RMyRR6wZoYK

A peak element is an element that is greater than its neighbors.
Given an input array nums, where nums[i] ≠ nums[i+1], find a peak element and return its index.
The array may contain multiple peaks, in that case return the index to any one of the peaks is fine.
You may imagine that nums[-1] = nums[n] = -∞.

```
Example 1:
Input: nums = [1,2,3,1]
Output: 2
Explanation: 3 is a peak element and your function should return the index number 2.

Example 2:
Input: nums = [1,2,1,3,5,6,4]
Output: 1 or 5 
```

whenever we calculate the middle, we can compare the numbers pointed out by the index middle and middle+1 to find if we are in the ascending or the descending part. So:

1. If arr[middle] > arr[middle + 1], we are in the second (descending) part of the bitonic array. Therefore, our required number could either be pointed out by middle or will be before middle. This means we will be doing: end = middle.


2. If arr[middle] < arr[middle + 1], we are in the first (ascending) part of the bitonic array. Therefore, the required number will be after middle. This means we will be doing: start = middle + 1.


```CPP
int findPeakElement(vector<int>& nums) {
    int len=nums.size();
    int l =0;
    int r =len-1;
    //check both monotonically increase or decrease order
    while(l<r) {
        int mid = l+(r-l)/2;
        if(nums[mid]<nums[mid+1]){
            //local max is right
            l = mid+1;

        }else{
            r = mid;
        }
    }
    
    return l;
}
```

### Fine Element in Bitonic 

https://www.educative.io/courses/grokking-the-coding-interview/7n3BlOvqW0r

Given a Bitonic array, find if a given ‘key’ is present in it. An array is considered bitonic if it is monotonically increasing and then monotonically decreasing. Monotonically increasing or decreasing means that for any index i in the array arr[i] != arr[i+1].

```CPP

/*
1. find max
2. search for both 0->max and max+1->end
*/

int search(const vector<int> &arr, int key) {
    int maxIndex = findMax(arr);
    int keyIndex = binarySearch(arr, key, 0, maxIndex);
    if (keyIndex != -1) {
      return keyIndex;
    }
    return binarySearch(arr, key, maxIndex + 1, arr.size() - 1);
}

// find index of the maximum value in a bitonic array
int findMax(const vector<int> &arr) {
    int start = 0, end = arr.size() - 1;
    while (start < end) {
      int mid = start + (end - start) / 2;
      if (arr[mid] > arr[mid + 1]) {
        end = mid;
      } else {
        start = mid + 1;
      }
}

int binarySearch(const vector<int> &arr, int key, int start, int end){
    int ret = -1;
    while(start<=end){
        int mid = start + (end - start) / 2;

        if (key == arr[mid]) {
            return mid;
        }

        if (arr[start] < arr[end]) {  // ascending order
            if (key < arr[mid]) {
              end = mid - 1;
            } else {  // key > arr[mid]
              start = mid + 1;
            }
        }else{//decending
            if (key > arr[mid]) {
              end = mid - 1;
            } else {  // key > arr[mid]
              start = mid + 1;
            }
        }
    }

    return ret;

}

```

### Find Minimum in rotated array

https://leetcode.com/problems/find-minimum-in-rotated-sorted-array/

```CPP
    int findMin(vector<int>& nums) {
        int begin = 0;
        int len = nums.size();
        int end = len-1;
        int ret = INT_MAX;

        //rotation point is minimum
        
        while(begin<end){
            int mid = begin + (end-begin)/2;
            if(nums[mid]>nums[end]){//rotation point in right
                begin = mid+1;
            }else if(nums[mid]<nums[end]){//rotation point is right
                end = mid;
            }
        }
        
        return nums[end];
    }
```

#### Find minimum with duplicate

```CPP
    int findMin(vector<int>& nums) {
        int begin = 0;
        int len = nums.size();
        int end = len-1;
        
        while(begin<end){
            int mid = begin + (end-begin)/2;
            if(nums[mid]>nums[end]){
                begin = mid+1;
            }else if(nums[mid]<nums[end]){
                end = mid;
            }else{
                //num[mid] == num[hi], we couldn't sure the position of minimum in mid's left or right, so reduce one high
                end--;
            }
        }
        
        return nums[begin];
    }

```

### Search in rotated sorted array

https://www.educative.io/courses/grokking-the-coding-interview/N8XZQ1q1O46

https://leetcode.com/problems/search-in-rotated-sorted-array/

Given an array of numbers which is sorted in ascending order and also rotated by some arbitrary number, find if a given ‘key’ is present in it.

```CPP
/*
If arr[start] <= arr[middle], the numbers from start to middle are sorted in ascending order.
Else, the numbers from middle+1 to end are sorted in ascending order.
*/

int search(vector<int>& arr, int key) {
    int start = 0, end = arr.size() - 1;
    while (start <= end) {
      int mid = start + (end - start) / 2;
      if (arr[mid] == key) {
        return mid;
      }

      if (arr[start] <= arr[mid]) {  // left side is sorted in ascending order
        if (key >= arr[start] && key < arr[mid]) {
          end = mid - 1;
        } else {  // key > arr[mid]
          start = mid + 1;
        }
      } else {  // right side is sorted in ascending order
        if (key > arr[mid] && key <= arr[end]) {
          start = mid + 1;
        } else {
          end = mid - 1;
        }
      }
    }

    // we are not able to find the element in the given array
    return -1;
}
```

#### Search in rotated array with Duplicate

```CPP
bool search(vector<int>& arr, int key) {
        int start = 0, end = arr.size() - 1;
        while (start <= end) {
          int mid = start + (end - start) / 2;
          if (arr[mid] == key) {
            return true;
          }

          // the only difference from the previous solution,
          // if numbers at indexes start, mid, and end are same, we can't choose a side
          // the best we can do, is to skip one number from both ends as key != arr[mid]
          if ((arr[start] == arr[mid]) && (arr[end] == arr[mid])) {
            ++start;
            --end;
          } else if (arr[start] <= arr[mid]) {  // left side is sorted in ascending order
            if (key >= arr[start] && key < arr[mid]) {
              end = mid - 1;
            } else {  // key > arr[mid]
              start = mid + 1;
            }
          } else {  // right side is sorted in ascending order
            if (key > arr[mid] && key <= arr[end]) {
              start = mid + 1;
            } else {
              end = mid - 1;
            }
          }
        }

        // we are not able to find the element in the given array
        return false;
    }
```


### Local Minimum

Local minimum
Find array if there is local min(left and right is larger) and return index

//Binary search
```CPP
int localMin(vector<int> nums){
  int len=nums.size();
  if(nums[0]<nums[1] || len==1 )
    return 0;
  if(nums[len-1]<nums[len-2])
    return len-1;

  int left = 1;
  int right = len-2;
  int mid = 0;
  while(left<right){
    mid = left+(right-left)/2;
    if(nums[mid]>nums[mid+1]){
      left = mid+1;  //there will be local min right half
    }else if(nums[mid]>nums[mid-1]){
      right = mid-1;
    }else{
      return mid;
    }
  }
  return left;

}
```


## Other example

### Square Calculation
https://leetcode.com/problems/sum-of-square-numbers/#/description

Given a non-negative integer c, your task is to decide whether there're two integers a and b such that a2 + b2 = c.

Example 1:
Input: 5
Output: True
Explanation: 1 * 1 + 2 * 2 = 5
Example 2:
Input: 3
Output: False

```CPP
bool judgeSquareSum(int c) {
    if (c < 0) {
        return false;
    }
    int left = 0, right = sqrt(c);
    while (left <= right) {
        int cur = left * left + right * right;
        if (cur < c) {
            left++;
        } else if (cur > c) {
            right--;
        } else {
            return true;
        }
    }
    return false;
}
```

### Find K-th Smallest Pair Distance

https://leetcode.com/problems/find-k-th-smallest-pair-distance/

Given an integer array, return the k-th smallest distance among all the pairs. The distance of a pair (A, B) is defined as the absolute difference between A and B.

```
Example 1:
Input:
nums = [1,3,1]
k = 1
Output: 0 
Explanation:
Here are all the pairs:
(1,3) -> 2
(1,1) -> 0
(3,1) -> 2
Then the 1st smallest distance pair is (1,1), and its distance is 0.
```

```CPP
int smallestDistancePair(vector<int>& nums, int k) {
    sort(nums.begin(), nums.end());
    //lowest distance
    
    int low = INT_MAX;
    int len = nums.size();
    for(int i=0;i<len-1;i++){
        low = min(low, nums[i+1]-nums[i]);
    }
    //highest distance from end - start
    int high = nums[len - 1] - nums[0];
    
    //calculate how many pairs
    while(low<high){
        int mid = low + (high - low) / 2;
        if (countDistance(nums, mid, len) < k)
            low = mid + 1;
        else
            high = mid;
    }
    
    return low;
   
}

//how many pairs with distance <= pivot
int countDistance(vector<int>& nums, int pivot, int len){
    int res = 0;
    for (int i = 0; i < len; ++i) {
        int j = i;
        while (j < len && nums[j] - nums[i] <= pivot) 
            j++;
        res += j - i - 1;
    }
    return res;
    
}
```

quicker way

```CPP
int smallestDistancePair(vector<int>& nums, int k) {
    sort(nums.begin(),nums.end());
    
    //For every possible right, we maintain the loop invariant: left is the smallest value such that nums[right] - nums[left] <= guess. Then, the number of pairs with right as it's right-most endpoint is right - left, and we add all of these up.

    int lo = 0;
    int hi = nums[nums.size() - 1] - nums[0];
    while (lo < hi) {
        int mid = lo + (hi-lo) / 2;
        int count = 0, left = 0;
        for (int right = 0; right < nums.size(); ++right) {
            while (nums[right] - nums[left] > mid) 
                left++;
            count += right - left;
        }
        //count = number of pairs with distance <= mi
        if (count >= k) 
            hi = mid;
        else 
            lo = mid + 1;
    }
    return lo;
   
}
```



### Median of Two Sorted Arrays

https://leetcode.com/problems/median-of-two-sorted-arrays/

Given two sorted arrays nums1 and nums2 of size m and n respectively.
Return the median of the two sorted arrays. Follow up: The overall run time complexity should be O(log (m+n)).

 
```
Example 1:

Input: nums1 = [1,3], nums2 = [2]
Output: 2.00000
Explanation: merged array = [1,2,3] and median is 2.
Example 2:

Input: nums1 = [1,2], nums2 = [3,4]
Output: 2.50000
Explanation: merged array = [1,2,3,4] and median is (2 + 3) / 2 = 2.5.
Example 3:

Input: nums1 = [0,0], nums2 = [0,0]
Output: 0.00000
Example 4:

Input: nums1 = [], nums2 = [1]
Output: 1.00000
Example 5:

Input: nums1 = [2], nums2 = []
Output: 2.00000
```

```CPP
double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        int m = nums1.size(), n = nums2.size();
        int k = (m + n) / 2;
        int num1 = findKth(nums1, 0, m, nums2, 0, n, k + 1);
        if ((n + m) % 2 == 0)
        {
            int num2 = findKth(nums1, 0, m, nums2, 0, n, k);
            return (num1 + num2) / 2.0;
        }
        else return num1;
    }
    int findKth(vector<int> & nums1, int nums1_left, int nums1_right, vector<int>& nums2, int nums2_left, int nums2_right, int k)
    {
        int m = nums1_right - nums1_left;
        int n = nums2_right - nums2_left;
        if (m > n) return findKth(nums2, nums2_left, nums2_right, nums1, nums1_left, nums1_right, k);
        else if (m == 0)
            return nums2[nums2_left + k - 1];
        else if (k == 1)
            return min(nums1[nums1_left], nums2[nums2_left]);
        else {
            int s1LeftCount = min (k / 2, m);
            int s2LeftCount = k - s1LeftCount;
            if (nums1[nums1_left + s1LeftCount - 1] == nums2[nums2_left + s2LeftCount - 1])
                return nums1[nums1_left + s1LeftCount - 1];
            else if (nums1[nums1_left + s1LeftCount - 1] < nums2[nums2_left + s2LeftCount - 1])
                return findKth(nums1, nums1_left + s1LeftCount, nums1_right, nums2, nums2_left, nums2_right, k - s1LeftCount);
            else
            return findKth(nums1, nums1_left, nums1_right, nums2, nums2_left + s2LeftCount, nums2_right, k - s2LeftCount);
        }
    }
```

