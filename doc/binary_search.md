<!-- START doctoc generated TOC please keep comment here to allow auto update -->
<!-- DON'T EDIT THIS SECTION, INSTEAD RE-RUN doctoc TO UPDATE -->
**Table of Contents**  *generated with [DocToc](https://github.com/thlorenz/doctoc)*

- [Binary search](#binary-search)
  - [Binary Search Framework](#binary-search-framework)
    - [Binary search for Target](#binary-search-for-target)
      - [Key points](#key-points)
    - [Boundary in Binary Search](#boundary-in-binary-search)
      - [Find Left Boundary](#find-left-boundary)
        - [Key points](#key-points-1)
      - [Find Right Boundary](#find-right-boundary)
        - [Key Points](#key-points)
      - [All three together](#all-three-together)
    - [Example: first bad version](#example-first-bad-version)
  - [Search Range/Cloest problem](#search-rangecloest-problem)
    - [Find K Closest Elements](#find-k-closest-elements)
  - [Local Minimum](#local-minimum)
    - [Example](#example)
  - [Numerical(Square) Calculation](#numericalsquare-calculation)

<!-- END doctoc generated TOC please keep comment here to allow auto update -->

# Binary search

Anything that can split the Search space can use Binary search

## Binary Search Framework 

```CPP
int binarySearch(int[] nums, int target) {
    int left = 0, right = nums.size() - 1;

    while(left <= right) {
        int mid = left + (right - left) / 2;
        if (nums[mid] == target) {
            ...
        } else if (nums[mid] < target) {
            left = ...
        } else if (nums[mid] > target) {
            right = ...
        }
    }
    return ...;
}
```

### Binary search for Target

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

#### Key points

1. why use ```<=``` or not ```<```:

The end condition for ```while(left <= right)``` is ```left = right + 1```, so the ```[left, right]``` will becomes ```[right+1, right]```, which is not possible, so it is correct ending condition, since we have searched into impossible state.


but for end condition for ```while(left < right)``` is ```left = right```, so the ```[left, right]``` will becomes ```[right, right]```, which is possible, and we will not visit ```right``` value.


2. why use ```left=mid-1 / right = mid+1``` , not ```left =mid/ right = mid```

Also we need to consider whether we need to move mid index. since our search range is ```[left, right]```, so if mid is not target, then we should search ```[left, mid-1]```, or ```[mid+1, right]```

3. Limitation of former algorithm: Hard to return the boundary



### Boundary in Binary Search

> Q: find mid value left and right boudary of ```nums = [1,2,2,2,3]``` 

#### Find Left Boundary

```CPP
int left_bound(int[] nums, int target) {
    if (nums.length == 0) return -1;
    int left = 0;
    int right = nums.length; //why right is 1 above boundary?

    while (left < right) { // why <? not <=?
        int mid = (left + right) / 2;
        if (nums[mid] == target) {
            right = mid;
        } else if (nums[mid] < target) {
            left = mid + 1;
        } else if (nums[mid] > target) {
            right = mid; // 
        }
    }
    return left;
}
```

##### Key points

1. why use ```<```, not ```<=```

search range here is ```[left, right)```, which dose not include right, since we just need to find left boundary. so for ```while (left < right)```, the ending condition is ```left==right```, and our search range ```[left, right)``` will be exmpty in this case, so condition is good.

2. How to process if number dose not exist

since the boudary here means "how many items are less(for left) or more(for right) than target value". 

for ```nums = [2,3,5,7], target = 1``` will return 0. means 0 item is less than 1. for ```nums = [2,3,5,7], target = 8```, will return 4, means 4 items are smaller than 8.

so our func return will be in range of ```[0, size+1]```.

3. why use ```left=mid+1```, not ```left=mid``` as before

since our search range is ```[left, right)```, so after ```num[mid]``` has been checked, our next search should be dividied into ```[left, mid)``` and ```[mid+1, right)```

4. why we return ```left```, not ```mid``` or ```right```

actually it is same since our ending condition is ```left == right```

* we can also use former approach to do

```CPP
int left_bound(int[] nums, int target) {
    int left = 0, right = nums.length - 1;
    // search range is [left, right]
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (nums[mid] < target) {
            // range becomes [mid+1, right]
            left = mid + 1;
        } else if (nums[mid] > target) {
            // range becomes [left, mid-1]
            right = mid - 1;
        } else if (nums[mid] == target) {
            right = mid - 1;
        }
    }
    // since our ending condition is left == right + 1, so if target > all items
    // we end up left be more than max item. so need to check
    if (left >= nums.length || nums[left] != target)
        return -1;
    return left;
}
```
#### Find Right Boundary

```CPP
int right_bound(int[] nums, int target) {
    if (nums.length == 0) return -1;
    int left = 0, right = nums.length;

    while (left < right) {
        int mid = (left + right) / 2;
        if (nums[mid] == target) {
            left = mid + 1; 
        } else if (nums[mid] < target) {
            left = mid + 1;
        } else if (nums[mid] > target) {
            right = mid;
        }
    }
    return left - 1; // why this?
}
```

##### Key Points

1. boundary search

Key point is continue explore the boudary even if we find equal

```CPP
if (nums[mid] == target) {
    left = mid + 1; 
```

2. why return ```left-1```, not ```right```, do we search right boundary?

because its ending condition is ```left==right```, so return left is same as return right. but since we have 
```CPP
if (nums[mid] == target) {
    left = mid + 1; 
```

so ending time, ```num[left]``` will not be equal to ```target```.


#### All three together

```CPP
int binary_search(int[] nums, int target) {
    int left = 0, right = nums.length - 1; 
    while(left <= right) {
        int mid = left + (right - left) / 2;
        if (nums[mid] < target) {
            left = mid + 1;
        } else if (nums[mid] > target) {
            right = mid - 1; 
        } else if(nums[mid] == target) {
            // 
            return mid;
        }
    }
    // 
    return -1;
}

int left_bound(int[] nums, int target) {
    int left = 0, right = nums.length - 1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (nums[mid] < target) {
            left = mid + 1;
        } else if (nums[mid] > target) {
            right = mid - 1;
        } else if (nums[mid] == target) {
            // continue search and lock left 
            right = mid - 1;
        }
    }
    // check over boundary
    if (left >= nums.length || nums[left] != target)
        return -1;
    return left;
}


int right_bound(int[] nums, int target) {
    int left = 0, right = nums.length - 1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (nums[mid] < target) {
            left = mid + 1;
        } else if (nums[mid] > target) {
            right = mid - 1;
        } else if (nums[mid] == target) {
            // continue search and lock right 
            left = mid + 1;
        }
    }
    // check over boundary
    if (right < 0 || nums[right] != target)
        return -1;
    return right;
}
```

### Example: first bad version

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
    
    //this is a search left boundary problem 
    //search for [l,r)
    //ending condition is l==r (==mid) for while
    //check condition for l==r in the begining
    while(l<r){
        int mid = l+(r-l)/2;
        if (isBadVersion(mid)) {
            r = mid;
        }else {
            l = mid+1;
            ret = l;
        }
    }
    return ret;
}
```

## Search Range/Cloest problem

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


## Local Minimum

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

### Example

https://leetcode.com/problems/find-peak-element/

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

Explanation: Your function can return either index number 1 where the peak element is 2, 
             or index number 5 where the peak element is 6.
Follow up: Your solution should be in logarithmic complexity.


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


## Numerical(Square) Calculation
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