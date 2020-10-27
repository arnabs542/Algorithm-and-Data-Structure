<!-- START doctoc generated TOC please keep comment here to allow auto update -->
<!-- DON'T EDIT THIS SECTION, INSTEAD RE-RUN doctoc TO UPDATE -->
**Table of Contents**  *generated with [DocToc](https://github.com/thlorenz/doctoc)*

- [Basic Array Operation](#basic-array-operation)
  - [Two pointer](#two-pointer)
        - [Fast/Slow pointer](#fastslow-pointer)
        - [From both sides](#from-both-sides)
    - [In Place Operation](#in-place-operation)
      - [Remove element(Delete in place)](#remove-elementdelete-in-place)
      - [Move zeros(Swap inplace)](#move-zerosswap-inplace)
      - [Remove Duplicate in sorted array](#remove-duplicate-in-sorted-array)
    - [Sort Array By Parity](#sort-array-by-parity)
    - [Squares of a Sorted Array](#squares-of-a-sorted-array)
    - [Merge array](#merge-array)
    - [Replace Elements with Greatest Element on Right Side](#replace-elements-with-greatest-element-on-right-side)
    - [Contains Duplicate](#contains-duplicate)
    - [Max consecutive Ones](#max-consecutive-ones)
    - [Maximum Points You Can Obtain from Cards](#maximum-points-you-can-obtain-from-cards)
    - [Sub Array with Product less than target](#sub-array-with-product-less-than-target)
    - [Read buffer from Read4](#read-buffer-from-read4)
    - [Sort Color(Dutch flag)](#sort-colordutch-flag)
    - [BackSpace String compare](#backspace-string-compare)
    - [Shortest Unsorted Continuous Subarray](#shortest-unsorted-continuous-subarray)
  - [Three pointers problems](#three-pointers-problems)
    - [3 Sum](#3-sum)
    - [3 Sum Cloest](#3-sum-cloest)
    - [Valid-triangle-number](#valid-triangle-number)
  - [Cyclic Sort](#cyclic-sort)
    - [Find missing numbers](#find-missing-numbers)
    - [Find the Corrupt Pair](#find-the-corrupt-pair)
    - [Smallest missing positive](#smallest-missing-positive)
- [Sub Array](#sub-array)
  - [Common Tchnqiues](#common-tchnqiues)
  - [Sub Array Sum](#sub-array-sum)
    - [Two sum](#two-sum)
    - [Subarray sum number that equals to certain target](#subarray-sum-number-that-equals-to-certain-target)
    - [Find Two Non-overlapping Sub-arrays Each With Target Sum](#find-two-non-overlapping-sub-arrays-each-with-target-sum)
    - [Maximum Size Subarray Sum Equals k](#maximum-size-subarray-sum-equals-k)
      - [Follow Up: Maximum Size Subarray Sum Equals k If subarray contains all positive](#follow-up-maximum-size-subarray-sum-equals-k-if-subarray-contains-all-positive)
      - [Follow up: subarray sum to multiple of k](#follow-up-subarray-sum-to-multiple-of-k)
      - [Follow up: Binary Subarrays With Sum](#follow-up-binary-subarrays-with-sum)
    - [Max subarray sum](#max-subarray-sum)
      - [Follow up: max sub matrix size](#follow-up-max-sub-matrix-size)
    - [Maximum Product Subarray](#maximum-product-subarray)
    - [Count of range sum](#count-of-range-sum)
  - [Subarray Reorder](#subarray-reorder)
    - [Common technqiue](#common-technqiue)
    - [Move array elements](#move-array-elements)
    - [Reorder array(Detect Duplicate)](#reorder-arraydetect-duplicate)
    - [Shortest sub-array length to make sure whole string is sorted](#shortest-sub-array-length-to-make-sure-whole-string-is-sorted)
  - [Subarray Pattern](#subarray-pattern)
    - [Contiguous subarray with equal number of 0 and 1](#contiguous-subarray-with-equal-number-of-0-and-1)
    - [Max Consecutive Ones(with flip most k zeros)](#max-consecutive-oneswith-flip-most-k-zeros)
  - [Array split/Cut/Partition Problem](#array-splitcutpartition-problem)
- [Sliding Windows](#sliding-windows)
  - [Maximum Average Subarray](#maximum-average-subarray)
    - [Maximum Average Subarray/fixed sliding window](#maximum-average-subarrayfixed-sliding-window)
    - [Maximum Average Subarray/dynamic sliding window](#maximum-average-subarraydynamic-sliding-window)
  - [Maximum value in sliding window](#maximum-value-in-sliding-window)
  - [Mini Sub string](#mini-sub-string)
  - [Longest Substring with At Most Two Distinct Characters](#longest-substring-with-at-most-two-distinct-characters)
    - [Fruit Into Baskets](#fruit-into-baskets)
  - [Longest Substring Without Repeating Characters](#longest-substring-without-repeating-characters)
  - [Longest Substring with Same Letters after K change](#longest-substring-with-same-letters-after-k-change)
    - [Max Consecutive Ones with K changes](#max-consecutive-ones-with-k-changes)
  - [Permutation in a String](#permutation-in-a-string)
  - [Find All Anagrams in a String](#find-all-anagrams-in-a-string)
  - [Smallest Window containing Substring](#smallest-window-containing-substring)
  - [Longest Substring Without Repeating Characters](#longest-substring-without-repeating-characters-1)
- [Histogram](#histogram)
  - [Water container problem](#water-container-problem)
    - [container with most water](#container-with-most-water)
    - [Trap Rain Water](#trap-rain-water)
  - [Array Change problem](#array-change-problem)
    - [Make nums inside array even](#make-nums-inside-array-even)

<!-- END doctoc generated TOC please keep comment here to allow auto update -->

# Basic Array Operation

## Two pointer

##### Fast/Slow pointer

##### From both sides

### In Place Operation

#### Remove element(Delete in place)

https://leetcode.com/problems/remove-element/

Given an array nums and a value val, remove all instances of that value in-place and return the new length.

Do not allocate extra space for another array, you must do this by modifying the input array in-place with O(1) extra memory.

The order of elements can be changed. It doesn't matter what you leave beyond the new length.

```
Example 1:

Given nums = [3,2,2,3], val = 3,
Your function should return length = 2, with the first two elements of nums being 2.
It doesn't matter what you leave beyond the returned length.

Example 2:

Given nums = [0,1,2,2,3,0,4,2], val = 2,
Your function should return length = 5, with the first five elements of nums containing 0, 1, 3, 0, and 4.
Note that the order of those five elements can be arbitrary.
It doesn't matter what values are set beyond the returned length.
```

> Solution 1: two pointers

```CPP
int removeElement(vector<int>& nums, int val) {
    int i =0;
    for(int j=0;j<nums.size();j++){
        if(nums[j]!=val){
            nums[i] = nums[j];
            i++;
        }
    }
    return i;
}
```

> Solution 2: swap with end item

```CPP
int removeElement(vector<int>& nums, int val) {
    int i =0;
    int n = nums.size();
    while(i<n){
        if(nums[i]==val){
            nums[i] = nums[n-1];
            n--;
        }else{
            i++;
        }
    }
    
    return n;
}
```

#### Move zeros(Swap inplace)

https://leetcode.com/problems/move-zeroes/

Given an array nums, write a function to move all 0's to the end of it while maintaining the relative order of the non-zero elements.

```
Example:

Input: [0,1,0,3,12]
Output: [1,3,12,0,0]
```

```CPP
    void moveZeroes(vector<int>& nums) {
        int i =0;
        
        for(int j=0; j< nums.size();j++){
            if(nums[j]!=0){
                nums[i] = nums[j];
                i++;
            }
            
        }
        //fill 0
        while(i<nums.size()) {
            nums[i] = 0;
            i++;
        }
        
    }
```

#### Remove Duplicate in sorted array

https://leetcode.com/problems/remove-duplicates-from-sorted-array/

Given a sorted array nums, remove the duplicates in-place such that each element appear only once and return the new length.Do not allocate extra space for another array, you must do this by modifying the input array in-place with O(1) extra memory.

```CPP
int removeDuplicates(vector<int>& nums) {
    int n = nums.size();
    int len = n;
    int j = 0;
    for(int i=1;i<n;i++){
        if(nums[j]==nums[i]){
            len--;
        }else{
            j++;
            nums[j] = nums[i];
        }
    }
    
    return len;
}
```

### Sort Array By Parity

https://leetcode.com/problems/sort-array-by-parity/

Given an array A of non-negative integers, return an array consisting of all the even elements of A, followed by all the odd elements of A.

You may return any answer array that satisfies this condition.

 
```
Example 1:

Input: [3,1,2,4]
Output: [2,4,3,1]
The outputs [4,2,3,1], [2,4,1,3], and [4,2,1,3] would also be accepted.
```

```CPP
vector<int> sortArrayByParity(vector<int>& A) {
    int i = 0;
    for (int j = 0; j < A.size(); j++)
        if (A[j] % 2 == 0) 
            swap(A[i++], A[j]);
    return A;
}
```

### Squares of a Sorted Array

https://leetcode.com/problems/squares-of-a-sorted-array/

Given an array of integers A sorted in non-decreasing order, return an array of the squares of each number, also in sorted non-decreasing order.

 
```
Example 1:

Input: [-4,-1,0,3,10]
Output: [0,1,9,16,100]
Example 2:

Input: [-7,-3,2,3,11]
Output: [4,9,9,49,121]
```

```CPP
vector<int> sortedSquares(vector<int>& A) {
    int i =0;
    int j=A.size()-1;
    //two pinter from each side 
    vector<int> ret(A.size(),0);
    for(int k=A.size()-1;k>=0;k--){
        if(abs(A[i])>abs(A[j])){
            ret[k]=A[i]*A[i];
            i++;
        }else{
            ret[k]=A[j]*A[j];
            j--;
        }
    }
    return ret;
}
```

### Merge array

https://leetcode.com/problems/merge-sorted-array/

Given two sorted integer arrays nums1 and nums2, merge nums2 into nums1 as one sorted array.

The number of elements initialized in nums1 and nums2 are m and n respectively.
You may assume that nums1 has enough space (size that is equal to m + n) to hold additional elements from nums2.

```
Example:

Input:
nums1 = [1,2,3,0,0,0], m = 3
nums2 = [2,5,6],       n = 3

Output: [1,2,2,3,5,6]
```

> Process from end is common

```CPP
void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
    int i=m-1;
    int j=n-1;
    int p = m+n-1;
    while(i>=0 && j>=0){
        if(nums1[i]>=nums2[j]){
            nums1[p]=nums1[i];
            i--;
        }else{
            nums1[p]=nums2[j];
            j--;
        }
        p--;
    }
    
    //process if there is remaining
    if(i<0){
       while(j>=0){
            nums1[j] = nums2[j];
            j--;
        } 
    }
}
```

### Replace Elements with Greatest Element on Right Side

https://leetcode.com/problems/replace-elements-with-greatest-element-on-right-side/

Given an array arr, replace every element in that array with the greatest element among the elements to its right, and replace the last element with -1.

After doing so, return the array.

 
```
Example 1:

Input: arr = [17,18,5,4,6,1]
Output: [18,6,6,6,1,-1]
```

```CPP
vector<int> replaceElements(vector<int>& arr) {
    //process from end
    int m=-1;
    for(int i=arr.size()-1;i>=0;i--) {
        int cur=arr[i];
        arr[i]=m;
        m=max(m, cur);
    }
    return arr;
}
```

### Contains Duplicate

https://leetcode.com/problems/contains-duplicate-iii/

Given an array of integers, find out whether there are two distinct indices i and j in the array such that the absolute difference between nums[i] and nums[j] is at most t and the absolute difference between i and j is at most k.

```

Example 1:

Input: nums = [1,2,3,1], k = 3, t = 0
Output: true
Example 2:

Input: nums = [1,0,1,1], k = 1, t = 2
Output: true
Example 3:

Input: nums = [1,5,9,1,5,9], k = 2, t = 3
Output: false
```

Method 1: check bound every time

```CPP
 bool containsNearbyAlmostDuplicate(vector<int>& nums, int k, int t) {
    set<int> s; // set is ordered automatically 
    for (int i = 0; i < nums.size(); i++) {
        if (i > k) 
          s.erase(nums[i-k-1]); // keep the set contains nums i j at most k
        // |x - nums[i]| <= t  ==> -t <= x - nums[i] <= t;
        auto pos = s.lower_bound(nums[i] - t); // x-nums[i] >= -t ==> x >= nums[i]-t 
        // x - nums[i] <= t ==> |x - nums[i]| <= t    
        if (pos != s.end() && *pos - nums[i] <= t) 
          return true;
        s.insert(nums[i]);
    }
    return false;
}
```

Method 2: 

We use the concept of sliding window and buckets together to achieve an optimal solution with O(N) time complexity.

Sliding window ensures only those indices are considered whose the absolute difference is at most k. We only consider k indices at a time. This fulfills the second condition.

Buckets are used to ensure that the absolute difference between two numbers is at most t. Let's take a deeper look at them.
We (floor) divide each number by t+1 and put it in a bucket with key as the quotient.

```CPP
    bool containsNearbyAlmostDuplicate(vector<int>& nums, int k, int t) {
      if (nums.size() < 2 || k < 1 || t < 0) return false;
      unordered_map<long long, long long> bucket;
      for (int i = 0; i < nums.size(); i++)
      {
        if (i > k) bucket.erase(((long long)nums[i - k - 1]  - INT_MIN) / ((long long)t + 1));
        long long num = (long long)nums[i] - INT_MIN;
        long long id = num / ((long long)t + 1);
        if (bucket.count(id)
          || (bucket.count(id - 1) && nums[i] - bucket[id - 1] <= t)
          || (bucket.count(id + 1) && bucket[id + 1] - nums[i] <= t))
          return true;
        bucket[id] = nums[i];
      }
      return false;       
    }
```


### Max consecutive Ones

https://leetcode.com/problems/max-consecutive-ones-ii/

Given a binary array, find the maximum number of consecutive 1s in this array if you can flip at most one 0.


```
Example 1:
Input: [1,0,1,1,0]
Output: 4
Explanation: Flip the first zero will get the the maximum number of consecutive 1s.
    After flipping, the maximum number of consecutive 1s is 4.

```

```CPP
int findMaxConsecutiveOnes(vector<int>& nums) {
    queue<int> q;
    int i=0;
    int ret =0;
    //keep a qeue with [i,j] that contains only 1 0(can be extended to k)
    for(int j=0;j<nums.size();j++){
        if(nums[j]==0){
            q.push(j);
        }
        if(q.size()>1){
            //last 0 position +1 will remove 0
            i = q.front()+1;
            q.pop();
        }
        ret = max(ret,j-i+1);
    }
    
    return ret;
}
```

### Maximum Points You Can Obtain from Cards

https://leetcode.com/problems/maximum-points-you-can-obtain-from-cards/

There are several cards arranged in a row, and each card has an associated number of points The points are given in the integer array cardPoints.

In one step, you can take one card from the beginning or from the end of the row. You have to take exactly k cards.

Your score is the sum of the points of the cards you have taken.

Given the integer array cardPoints and the integer k, return the maximum score you can obtain.

 
```
Example 1:

Input: cardPoints = [1,2,3,4,5,6,1], k = 3
Output: 12
Explanation: After the first step, your score will always be 1. However, choosing the rightmost card first will maximize your total score. The optimal strategy is to take the three cards on the right, giving a final score of 1 + 6 + 5 = 12.
Example 2:

Input: cardPoints = [2,2,2], k = 2
Output: 4
Explanation: Regardless of which two cards you take, your score will always be 4.
```

```CPP
int maxScore(vector<int>& cardPoints, int k) {
    //two pointer, with rotating sliding window
    int res=0, n=cardPoints.size(), sum=0;
    for(int i=n-k; i<n;i++) 
        res+=cardPoints[i]; // take k right
    sum = res;
    for(int i=0;i<k;i++) {
        sum-=cardPoints[n-k+i];
        sum+=cardPoints[i];
        res=max(res,sum);
    }
    return res;
}
```

### Sub Array with Product less than target

https://leetcode.com/problems/subarray-product-less-than-k/

https://www.educative.io/courses/grokking-the-coding-interview/RMV1GV1yPYz

Your are given an array of positive integers nums.

Count and print the number of (contiguous) subarrays where the product of all the elements in the subarray is less than k.

```
Example 1:
Input: nums = [10, 5, 2, 6], k = 100
Output: 8
Explanation: The 8 subarrays that have product less than 100 are: [10], [5], [2], [6], [10, 5], [5, 2], [2, 6], [5, 2, 6].
Note that [10, 5, 2] is not included as the product of 100 is not strictly less than k.
```

```CPP
    int numSubarrayProductLessThanK(vector<int>& nums, int k) {
            if (k == 0) 
                return 0;
            int cnt = 0;
            int product = 1;
            for (int i = 0, j = 0; j < nums.size(); j++) {
                product *= nums[j];
                while (i <= j && product >= k) {
                    //move left pointer
                    product /= nums[i++];
                }
                cnt += j - i + 1;
            }
            return cnt;
    }
```


### Read buffer from Read4

https://leetcode.com/problems/read-n-characters-given-read4-ii-call-multiple-times/

Given a file and assume that you can only read the file using a given method read4, implement a method read to read n characters. Your method read may be called multiple times.

 
```
Method read4:

The API read4 reads 4 consecutive characters from the file, then writes those characters into the buffer array buf.

The return value is the number of actual characters read.

Note that read4() has its own file pointer, much like FILE *fp in C.

Definition of read4:

    Parameter:  char[] buf4
    Returns:    int

Note: buf4[] is destination not source, the results from read4 will be copied to buf4[]
```

```CPP
class Solution {
public:
    /**
     * @param buf Destination buffer
     * @param n   Number of characters to read
     * @return    The number of actual characters read
     */
    //read from read4 first, if it is all consumed, then start a new read4 again
    char buf4[4];
    int prevSize = 0, prevIndex = 0;
    int read(char *buf, int n) {
        int counter = 0;
        
        while (counter < n) {
            if (prevIndex < prevSize) {
                buf[counter++] = buf4[prevIndex++];
            } else {
                prevSize = read4(buf4);
                prevIndex = 0;
                if (prevSize == 0) {
                    // no more data to consume from stream
                    break;
                }
            }
        }
        return counter;
    }
};
```

### Sort Color(Dutch flag)

https://leetcode.com/problems/sort-colors/

https://www.educative.io/courses/grokking-the-coding-interview/RMBxV6jz6Q0

```CPP
    void sortColors(vector<int>& arr) {
            int low = 0, high = arr.size() - 1;
            for (int i = 0; i <= high;) {
              if (arr[i] == 0) {
                swap(arr[i], arr[low]);
                i++;
                low++;
              } else if (arr[i] == 1) {
                i++;
              } else {  
                swap(arr[i], arr[high]);
                // decrement 'high' only
                high--;
              }
            }
    }
```

### BackSpace String compare

https://leetcode.com/problems/backspace-string-compare/

Given two strings S and T, return if they are equal when both are typed into empty text editors. # means a backspace character.

Note that after backspacing an empty text, the text will continue empty.

```
Example 1:

Input: S = "ab#c", T = "ad#c"
Output: true
Explanation: Both S and T become "ac".
Example 2:

Input: S = "ab##", T = "c#d#"
Output: true
Explanation: Both S and T become "".
Example 3:

Input: S = "a##c", T = "#a#c"
Output: true
Explanation: Both S and T become "c".
Example 4:

Input: S = "a#c", T = "b"
Output: false
Explanation: S becomes "c" while T becomes "b".
```


```CPP
    bool backspaceCompare(string S, string T) {
        //count from back
        int index1 = S.size()-1;
        int index2 = T.size()-1;
        while (index1 >= 0 || index2 >= 0) {
              int i1 = getNextValidCharIndex(S, index1);
              int i2 = getNextValidCharIndex(T, index2);

              if (i1 < 0 && i2 < 0) {  // reached the end of both the strings
                return true;
              }

              if (i1 < 0 || i2 < 0) {  // reached the end of one of the strings
                return false;
              }

              if (S[i1] != T[i2]) {  // check if the characters are equal
                return false;
              }

              index1 = i1 - 1;
              index2 = i2 - 1;
            }
        
        return true;
        
    }
    
    int getNextValidCharIndex(const string &str, int index) {
        int backspaceCount = 0;
        while (index >= 0) {
          if (str[index] == '#') {  // found a backspace character
            backspaceCount++;
          } else if (backspaceCount > 0) {  // a non-backspace character
            backspaceCount--;
          } else {
            break;
          }

          index--;  // skip a backspace or a valid character
        }
        return index;
  }
```

### Shortest Unsorted Continuous Subarray

https://leetcode.com/problems/shortest-unsorted-continuous-subarray/

Given an integer array nums, you need to find one continuous subarray that if you only sort this subarray in ascending order, then the whole array will be sorted in ascending order.

Return the shortest such subarray and output its length.

 
```
Example 1:

Input: nums = [2,6,4,8,10,9,15]
Output: 5
Explanation: You need to sort [6, 4, 8, 10, 9] in ascending order to make the whole array sorted in ascending order.


Example 2:

Input: nums = [1,2,3,4]
Output: 0
```

```CPP
int findUnsortedSubarray(vector<int>& nums) {
        int len = nums.size();
        if (len==0 || len == 1) {
            return 0;
        }
        //from right to left, record value not descending. find left most
        int min_v = nums[len-1];
        int l = -1;
        for (int i = len - 2; i >=0; i--) {
            if (nums[i] > min_v) {
              l = i;
            }else{
                min_v = nums[i];
            } 
        }
        if (l == -1) {
            return 0;
        }
        //from left to rightm record value not ascending, find right most
        int r = -1;
        int max_v = nums[0];
        for (int i = 1; i <len; i++) {
            if (nums[i] < max_v) {
              r = i;
            }else{
                max_v = nums[i];
            } 
        }
        return r - l + 1;        
    }
```


## Three pointers problems
> Common techniques
* Sort the array
* Fix the first pointer, and define left and right, search from beginning and end
* define the condition properly

### 3 Sum

https://leetcode.com/problems/3sum/#/description

Given an array nums of n integers, are there elements a, b, c in nums such that a + b + c = 0? Find all unique triplets in the array which gives the sum of zero.

Note:
The solution set must not contain duplicate triplets.

```
Example:

Given array nums = [-1, 0, 1, 2, -1, -4],

A solution set is:
[
  [-1, 0, 1],
  [-1, -1, 2]
]
```


```CPP
vector<vector<int>> threeSum(vector<int>& nums) {
    sort(nums.begin(),nums.end());
    vector<vector<int>> ret;
    for(int i=0;i<nums.size();i++){
        int target = -nums[i];
        int start = i+1;
        int end = nums.size()-1;
        while(start<end){
            if(nums[start]+nums[end]>target){
                end--;
            }else if(nums[start]+nums[end]<target){
                start++;
            }else{
                vector<int> one;
                one.push_back(nums[i]);
                one.push_back(nums[start]);
                one.push_back(nums[end]);
                ret.push_back(one);
                int begin = nums[start];
                int finish = nums[end];

                while(start<end && nums[start]==begin)
                    start++;
                while(start<end && nums[end]==finish)
                    end--;
            }
            if(start>=end)
                break;
        }
                // Processing duplicates of Number 1
        while (i + 1 < nums.size() && nums[i + 1] == nums[i])
            i++;
    }

    return ret;
}

```

### 3 Sum Cloest 

https://leetcode.com/problems/3sum-closest/

https://www.educative.io/courses/grokking-the-coding-interview/3YlQz7PE7OA

Given an array of unsorted numbers and a target number, find a triplet in the array whose sum is as close to the target number as possible, return the sum of the triplet. If there are more than one such triplet, return the sum of the triplet with the smallest sum.

```
Example 1:

Input: [-2, 0, 1, 2], target=2
Output: 1
Explanation: The triplet [-2, 1, 2] has the closest sum to the target.
```

```CPP
  static int searchTriplet(vector<int>& arr, int targetSum) {
    sort(arr.begin(), arr.end());
    int smallestDifference = numeric_limits<int>::max();
    for (int i = 0; i < arr.size() - 2; i++) {
      int left = i + 1, right = arr.size() - 1;
      while (left < right) {
        // comparing the sum of three numbers to the 'targetSum' can cause overflow
        // so, we will try to find a target difference
        int targetDiff = targetSum - arr[i] - arr[left] - arr[right];
        if (targetDiff == 0) {            //  we've found a triplet with an exact sum
          return targetSum - targetDiff;  // return sum of all the numbers
        }

        if (abs(targetDiff) < abs(smallestDifference)) {
          smallestDifference = targetDiff;  // save the closest difference
        }

        if (targetDiff > 0) {
          left++;  // we need a triplet with a bigger sum
        } else {
          right--;  // we need a triplet with a smaller sum
        }
      }
    }
    return targetSum - smallestDifference;
  }
```

### Valid-triangle-number

There are lots of problem can be soled by similar idea.

https://leetcode.com/problems/valid-triangle-number/#/description


Given an array consists of non-negative integers, your task is to count the number of triplets chosen from the array that can make triangles if we take them as side lengths of a triangle.
```
Example 1:
Input: [2,2,3,4]
Output: 3
Explanation:
Valid combinations are: 
2,3,4 (using the first 2)
2,3,4 (using the second 2)
2,2,3
```
Note:
* The length of the given array won't exceed 1000.
* The integers in the given array are in the range of [0, 1000].

```CPP
int triangleNumber(vector<int>& nums) {
    //3 sum problem
    int len = nums.size();
    sort(nums.begin(),nums.end());
    int ret = 0;
    for(int i=2;i<len;i++){
        int l=0;
        int r=i-1;
        while(l<r){
            if(nums[l]+nums[r]>nums[i]){
              //all l>current l can form triangle 
                ret+=r-l;
                r--;
            }else {
              l++;
            }
                
        }
    }

    return ret;
}
```

## Cyclic Sort

### Find missing numbers

https://www.educative.io/courses/grokking-the-coding-interview/Y52qNM0ljWK

We are given an unsorted array containing numbers taken from the range 1 to ‘n’. The array can have duplicates, which means some numbers will be missing. Find all those missing numbers.

```
Example 1:

Input: [2, 3, 1, 8, 2, 3, 5, 1]
Output: 4, 6, 7
Explanation: The array should have all numbers from 1 to 8, due to duplicates 4, 6, and 7 are missing.
Example 2:

Input: [2, 4, 1, 2]
Output: 3
Example 3:

Input: [2, 3, 2, 1]
Output: 4
```

```CPP
static vector<int> findNumbers(vector<int> &nums) {
      int i = 0;
      while (i < nums.size()) {
        if (nums[i] != nums[nums[i] - 1]) {
          swap(nums, i, nums[i] - 1);
        } else {
          i++;
        }
      }

      vector<int> missingNumbers;
      for (i = 0; i < nums.size(); i++) {
        if (nums[i] != i + 1) {
          missingNumbers.push_back(i + 1);
        }
      }

      return missingNumbers;
  }

private:
  static void swap(vector<int> &arr, int i, int j) {
    int temp = arr[i];
    arr[i] = arr[j];
    arr[j] = temp;
  }
```

###  Find the Corrupt Pair 

We are given an unsorted array containing ‘n’ numbers taken from the range 1 to ‘n’. The array originally contained all the numbers from 1 to ‘n’, but due to a data error, one of the numbers got duplicated which also resulted in one number going missing. Find both these numbers.

```
Example 1:

Input: [3, 1, 2, 5, 2]
Output: [2, 4]
Explanation: '2' is duplicated and '4' is missing.
Example 2:

Input: [3, 1, 2, 3, 6, 4]
Output: [3, 5]
Explanation: '3' is duplicated and '5' is missing.
```

```CPP
//Since only one number got corrupted, the number at the wrong index is the duplicated number and the index itself represents the missing number.

static vector<int> findNumbers(vector<int> &nums) {
    int i = 0;
    while (i < nums.size()) {
      if (nums[i] != nums[nums[i] - 1]) {
        swap(nums, i, nums[i] - 1);
      } else {
        i++;
      }
    }

    for (i = 0; i < nums.size(); i++) {
      if (nums[i] != i + 1) {
        return vector<int>{nums[i], i + 1};
      }
    }

    return vector<int>{-1, -1};
  }

 private:
  static void swap(vector<int> &arr, int i, int j) {
    int temp = arr[i];
    arr[i] = arr[j];
    arr[j] = temp;
  }
```

### Smallest missing positive

https://leetcode.com/problems/first-missing-positive/

https://www.educative.io/courses/grokking-the-coding-interview/R1GXQ071GQ0

```CPP
    int firstMissingPositive(vector<int>& nums) {
/*
ideally we should have vector as 1,2,3,...n. so nums[i-1]=i

Just go through the array sequentially and for every index write the value at the index to the index specified by value, recursively placing any value at that location to its place and throwing away values > N (<0). Then go again through the array looking for the spot where value doesn't match the index - that's the smallest value not in the array. 
*/

  int i = 0;
    while (i < nums.size()) {
      //for negative or >size num, not process, their position will be missing positive
      if (nums[i] > 0 && nums[i] <= nums.size() && nums[i] != nums[nums[i] - 1]) {
        swap(nums, i, nums[i] - 1);
      } else {
        i++;
      }
    }

    for (i = 0; i < nums.size(); i++) {
      if (nums[i] != i + 1) {
        return i + 1;
      }
    }

    return nums.size() + 1;
  }

 private:
  static void swap(vector<int> &arr, int i, int j) {
    int temp = arr[i];
    arr[i] = arr[j];
    arr[j] = temp;
  }
```



# Sub Array
> Common techniques
* solve the sub problem: the same problem mapping to subarray ending in current index i, so can get the results from i-1
* two pointer to get these longest/smallest problem
  * two pointers could start both from beginning: with different move forward conditions:
  * The idea is to use two pointers to transfer original problem into sub problem between [l,r]
* preprocess
  * Get the sum
  * from begin and end
* Hash table
  * Key could be array item itself, or some preprocessed one: like sum, or certain signature
  * value is number of total items, or index(used in longest subarray case)

> __*Tips*__:
  * whether to record value into hashmap/set before and after process.  
  * insert special case for hash set/map, like index -1, value 0. etc, so sum calculation including sum from beging to current or sum of current item


## Common Tchnqiues

1. preprocess: sum all
2. two pointers
3. DP
4. Hash Map to record index or occurence
5. Matrix problem: transfer to subarray problem


## Sub Array Sum

### Two sum
https://leetcode.com/problems/two-sum/#/description
Given an array of integers, return indices of the two numbers such that they add up to a specific target.

You may assume that each input would have exactly one solution, and you may not use the same element twice.

```CPP
vector<int> twoSum(vector<int>& nums, int target) {
    //O(nlog(n)) is easy, sort and use pointer head and tail
    //O(n)
    int len = nums.size();
    vector<int> ret;
    unordered_map<int,int> m; //key is val, val is index
    for(int i=0;i<len;i++){
        if(m.find(target-nums[i])!=m.end()){
            ret.push_back(i);
            ret.push_back(m[target-nums[i]]);
            return ret;
        }
        m[nums[i]] = i;    
    }
}
```


### Subarray sum number that equals to certain target
https://leetcode.com/problems/subarray-sum-equals-k/#/description
Given an array of integers and an integer k, you need to find the total number of continuous subarrays whose sum equals to k.

we know the key to solve this problem is ```SUM[i, j]```. So if we know ```SUM[0, i - 1]``` and ```SUM[0, j]```, then we can easily get ```SUM[i, j]```. To achieve this, we just need to go through the array, calculate the current sum and save number of all seen PreSum to a HashMap. Time complexity O(n), Space complexity O(n).

```CPP

// Hash Map: K is sum value from 0->K, value is occurence times

int subarraySum(vector<int>& nums, int k) {
    int len = nums.size();
    int sum = 0;
    int ret = 0;
    map<int,int> m; //key is sum value, val is how many times it appears
    //if sum-k==0, then it means it has sum value from begining to current ==k, need to count
    m[0] = 1;  
    for(int i=0;i<len;i++){
        sum+=nums[i];
        if(m.find(sum-k)!=m.end())
            ret+=m[sum-k];
        m[sum]++;
    }
    return ret;    
}

//if we do not insert init value, it would be
int subarraySum(vector<int>& nums, int k) {
    int len = nums.size();
    long long sum = 0;
    int ret = 0;
    unordered_map<int,int> m; //key is sum value, val is how many times it appears
    //m[0] = 0;  //if sum-k==0, then it means it has sum value from begining to current ==k, need to count
    for(int i=0;i<len;i++){
        sum+=nums[i];
        if(sum==k)
            ret++;
        if(m.find(sum-k)!=m.end())
            ret+=m[sum-k];
        m[sum]++;
    }

    return ret;    
}

```

### Find Two Non-overlapping Sub-arrays Each With Target Sum

https://leetcode.com/problems/find-two-non-overlapping-sub-arrays-each-with-target-sum/

Given an array of integers arr and an integer target.

You have to find two non-overlapping sub-arrays of arr each with sum equal target. There can be multiple answers so you have to find an answer where the sum of the lengths of the two sub-arrays is minimum.

Return the minimum sum of the lengths of the two required sub-arrays, or return -1 if you cannot find such two sub-arrays.

 
```
Example 1:

Input: arr = [3,2,2,4,3], target = 3
Output: 2
Explanation: Only two sub-arrays have sum = 3 ([3] and [3]). The sum of their lengths is 2.
Example 2:

Input: arr = [7,3,4,7], target = 7
Output: 2
Explanation: Although we have three non-overlapping sub-arrays of sum = 7 ([7], [3,4] and [7]), but we will choose the first and third sub-arrays as the sum of their lengths is 2.
Example 3:

Input: arr = [4,3,2,6,2,3,4], target = 6
Output: -1
Explanation: We have only one sub-array of sum = 6.
```

```CPP
class Solution {
public:
    int minSumOfLengths(vector<int>& arr, int target) {
        
        int sum=0; //sum: index
        int l = INT_MAX;
        int ret = INT_MAX;
        unordered_map<int,int> m;
        m[0]=-1;
        for(int i=0;i<arr.size();i++){
            sum += arr[i];
            m[sum] =i;  
        }
        sum=0;
        //check for both left and right subarry to ensure no overlap
        for(int i=0;i<arr.size();i++){
            sum += arr[i];

            //check min len sub array added to target from left to i
            if(m.find(sum-target)!=m.end() ){
                l = min(l,i-m[sum-target]);
            }
            
            //if left subarray is found, check  sub array from i+1 -> right
            if(m.find(sum+target)!=m.end() && l<INT_MAX){
                ret = min(ret, l+m[sum+target]-i);
            }
        }

        return ret==INT_MAX?-1:ret;
    }
};
```


### Maximum Size Subarray Sum Equals k

https://leetcode.com/problems/maximum-size-subarray-sum-equals-k/

Given an array nums and a target value k, find the maximum length of a subarray that sums to k. If there isn't one, return 0 instead.

Note:
The sum of the entire nums array is guaranteed to fit within the 32-bit signed integer range.

```
Example 1:

Input: nums = [1, -1, 5, -2, 3], k = 3
Output: 4 
Explanation: The subarray [1, -1, 5, -2] sums to 3 and is the longest.
Example 2:

Input: nums = [-2, -1, 2, 1], k = 1
Output: 2 
Explanation: The subarray [-1, 2] sums to 1 and is the longest.
```

Follow Up:
Can you do it in O(n) time?

```CPP

//K is current sum from begining of array, value is left most index that has the K

int Longestsubarray(vector<int> nums, int k){
    unordered_map<int, int> sums;
    int cur_sum = 0;
    int max_len = 0;
    for (int i = 0; i < nums.size(); i++) {
        cur_sum += nums[i];
        if (cur_sum == k) {
            max_len = i + 1;
        } else if (sums.find(cur_sum - k) != sums.end()) {
            max_len = max(max_len, i - sums[cur_sum - k]);
        }
        //do not update if already exist,
        if (sums.find(cur_sum) == sums.end()) {
            sums[cur_sum] = i;
        }            
    }
    return max_len;
}

```

#### Follow Up: Maximum Size Subarray Sum Equals k If subarray contains all positive

```CPP
//use two pointers
int Longestsubarray(vector<int> arr, int k){
  if (arr.size()==0 || k==0) {
    return 0;
  }
  int left = 0;
  int right = 0;
  int sum = arr[0];
  int len = 0;
  while (right < arr.size()) {
    if (sum == k) {
      len = max(len, right - left + 1);
      sum -= arr[left++];
    } else if (sum < k) {
      right++;
      if (right == arr.size()) {
        break;
      }
      sum += arr[right];
    } else {
      sum -= arr[left++];
    }
  }
  return len;
}
```

#### Follow up: subarray sum to multiple of k
https://leetcode.com/problems/continuous-subarray-sum/#/description

Given a list of non-negative numbers and a target integer k, write a function to check if the array has a continuous subarray of size at least 2 that sums up to the multiple of k, that is, sums up to n*k where n is also an integer.

```CPP
bool checkSubarraySum(vector<int>& nums, int k) {
    //easy way is O(N^2)
    //proprocess. first get a sum array, then use hash map to
    int len = nums.size();
    int sum = 0;
    unordered_map<int,int> m; //key is sum, val is index
    m[0] = -1;
    for(int i=0;i<len;i++){
        sum += nums[i];
        if(k!=0)
            sum = sum%k;
        if(m.find(sum)!=m.end()){
            if(i-m[sum]>1)
                return true;
        }else{
            m[sum]=i;
        }
    }
    return false;
}

```

#### Follow up: Binary Subarrays With Sum

https://leetcode.com/problems/binary-subarrays-with-sum/

In an array A of 0s and 1s, how many non-empty subarrays have sum S?

```
Example 1:

Input: A = [1,0,1,0,1], S = 2
Output: 4
Explanation: 
The 4 subarrays are bolded below:
[1,0,1,0,1]
[1,0,1,0,1]
[1,0,1,0,1]
[1,0,1,0,1]
```

```CPP
int numSubarraysWithSum(vector<int>& A, int S) {
    //sum: count as map
    unordered_map<int,int> m;
    m[0] = 1; //so if subarray from start, we can still count
    int ret =0;
    int sum=0;
    for(int i=0;i<A.size();i++){
        sum+=A[i];
        ret+=m[sum-S];
        m[sum]++;
    }
    return ret;
}
```


### Max subarray sum
https://leetcode.com/problems/maximum-subarray/
Find the contiguous subarray within an array (containing at least one number) which has the largest sum.
```
For example, given the array [-2,1,-3,4,-1,2,1,-5,4],
the contiguous subarray [4,-1,2,1] has the largest sum = 6.
```

```CPP
int maxSubArray(vector<int>& nums) {
    int len = nums.size();
    int ret = INT_MIN;
    int sum = 0;
    for(int i=0;i<len;i++){
        sum+=nums[i];
        ret = max(ret,sum);
        //if sum<0. subarray should start from next item
        if(sum<0)
            sum = 0;
    }
    return ret;
}
```

> Most Matrix problem will be transmitted to sub array problem

#### Follow up: max sub matrix size

Sub matrix num: O(n^4). algorithm search from row 1->row n, then from row 2->row n

```CPP
int maxSubarea(vector<vector<int>> m){
  int ret = INT_MIN;
  int cur = 0;
  int row = m.size();
  int col = m[0].size();
  for (int i = 0; i < row; i++) {
    vector<int> s(col,0);
    for (int j = i; j < row; j++) {
      cur = 0;
      for (int k = 0; k < col; k++) {
        s[k] += m[j][k];
        cur += s[k];
        ret = max(max, cur);
        cur = cur < 0 ? 0 : cur;
      }
    }
  }
  return ret;
}
```

### Maximum Product Subarray
https://leetcode.com/problems/maximum-product-subarray/#/description

Find the contiguous subarray within an array (containing at least one number) which has the largest product.
```
For example, given the array [2,3,-2,4],
the contiguous subarray [2,3] has the largest product = 6.
```


```CPP
int maxProduct(vector<int>& nums) {
    int prod = 1;
    int ret = INT_MIN;
    int begin = 1;
    int end = 1;
    int len = nums.size();
    for(int i=0;i<nums.size();i++){
        begin*=nums[i];
        end*=nums[len-1-i];
        ret = max(ret,max(begin,end));
        begin = begin==0?1:begin;
        end = end==0?1:end;
    }
    return ret;
}

//method 2:
int maxProduct(vector<int>& nums) {
    int max_cur = nums[0]; //max until current index
    int min_cur = nums[0]; //min until current index
    int ret = nums[0];
    for(int i=1;i<nums.size();i++){
        if(nums[i]<0)
            swap(max_cur,min_cur);

        max_cur = max(nums[i],max_cur*nums[i]);
        min_cur = min(nums[i],min_cur*nums[i]);
        ret = max(ret,max_cur);
    }
    return ret;
}
```

* Product of array except itself
https://leetcode.com/problems/product-of-array-except-self/
Given an array of n integers where n > 1, nums, return an array output such that output[i] is equal to the product of all the elements of nums except nums[i].
Solve it without division and in O(n).

For example, given [1,2,3,4], return [24,12,8,6].


```CPP
vector<int> productExceptSelf(vector<int>& nums) {
    int len=nums.size();
    vector<int> begin(len,0);  //product value vector from begin until index i(exclusive)
    vector<int> end(len,0);    //product value vector from end until index i(exclusive)
    vector<int> ret(len,0);
    begin[0]=1;
    end[len-1]=1;
    for(int i=1;i<len;i++){
        begin[i] = begin[i-1] * nums[i-1];
    }
    for(int i=len-2;i>=0;i--){
        end[i]=end[i+1] * nums[i+1];
    }
    for(int i=0;i<len;i++){
        ret[i]=begin[i]* end[i];
    }
    return ret;
}

//method 2: it can be optimized to O(1) memory
vector<int> productExceptSelf(vector<int>& nums) {
    int len=nums.size();
    int begin = 1;
    int end = 1;
    vector<int> ret(len,1);
    for(int i=0;i<len;i++){
        ret[i]* =begin;
        begin * =nums[i];
        ret[len-1-i]* =end;
        end * =nums[len-1-i];
    }
    return ret;
}

```

### Count of range sum
https://leetcode.com/problems/count-of-range-sum/#/description
Given an integer array nums, return the number of range sums that lie in [lower, upper] inclusive.

Range sum S(i, j) is defined as the sum of the elements in nums between indices i and j (i ≤ j), inclusive.

```CPP
int countRangeSum(vector<int>& nums, int lower, int upper) {
    int len = nums.size();
    int ret = 0;
    long long sum = 0;
    // lower<=sum[i]-sum[j]<=upper
    //j (0=< j< i) satisfy sum[i]-upper=< sum[j]<=-sum[i]-lower.
    multiset<long long> s; //multi set allow same item
    s.insert(0); //since one number itself can be see as range, insert 0 to collect one number case
    for(int i=0;i<len;i++){
        sum+=nums[i];
        //count how many in that range
        ret+=std::distance(s.lower_bound(sum-upper),s.upper_bound(sum-lower));
        s.insert(sum);
    }
    return ret;
}
```

## Subarray Reorder

### Common technqiue

> Two pointer problem
> one for loop for main array, and the other pointer moving if condition meet

### Move array elements

https://leetcode.com/problems/move-zeroes/#/description

Given an array nums, write a function to move all 0's to the end of it while maintaining the relative order of the non-zero elements.
For example, given nums = [0, 1, 0, 3, 12], after calling your function, nums should be [1, 3, 12, 0, 0].

```CPP
void moveZeroes(vector<int>& nums) {
    int next = 0;
    // move all the nonzero elements advance
    for (int i=0; i<nums.size(); i++) {
        if (nums[i] != 0) {
            nums[next] = nums[i];
            next++;
        }
    }
    while(next<nums.size()) {
        nums[next] = 0;
        next++;
    }
}
```

### Reorder array(Detect Duplicate)

https://leetcode.com/problems/set-mismatch/description/

The set S originally contains numbers from 1 to n. But unfortunately, due to the data error, one of the numbers in the set got duplicated to another number in the set, which results in repetition of one number and loss of another number.

Given an array nums representing the data status of this set after the error. Your task is to firstly find the number occurs twice and then find the number that is missing. Return them in the form of an array.

```
Example 1:

Input: nums = [1,2,2,4]

Output: [2,3]
```

The idea is using array indexing, that is putting each nums[i] into the position with index nums[i] - 1. Then, the array becomes [1,2,3,4,5...,n]. So we can find the duplicate number when nums[i] != i+1.

```CPP
vector<int> findErrorNums(vector<int>& nums) {
    vector<int> ret;
    for (int i = 0; i < nums.size(); i++) {
        while (nums[nums[i]-1] != nums[i]) {
            swap(nums[nums[i]-1], nums[i]);
        }
    }
    for (int i = 0; i < nums.size(); i++) {
        if (nums[i] != i+1){
            ret.push_back(nums[i]);
            ret.push_back(i+1);
            return ret;
        }

    }
    return ret;        
}
```

### Shortest sub-array length to make sure whole string is sorted
https://leetcode.com/problems/shortest-unsorted-continuous-subarray/#/description

[1,2,3,6,4,5,7], need to sort[6,4,5] to ensure sorted



```CPP
//O(n) in time, O(1) extra memory
//from left->right, record max. from right->left, record min
/*
[1,5,3,4,2,6,7]
left->right: [1,5,R,R,R,6,7], right value which is smaller than max is 2
right->left:[1,L,L,L,L,2,6,7], left value which is larger than min is 5

re sort L->R
*/

int findUnsortedSubarray(vector<int>& nums) {
    int len = nums.size();
    if (len==0 || len == 1) {
        return 0;
    }
    //from right to left, record value not descending. find left most
    int min_v = nums[len - 1];
    int l = -1;
    for (int i = len - 2; i >=0; i--) {
        if (nums[i] > min_v) {
          l = i;
        } else {
          min_v = nums[i];
        }
    }
    if (l == -1) {
        return 0;
    }
    //from left to right record value not ascending, find right most
    int max_v = nums[0];
    int r = -1;
    for (int i = 1; i <len; i++) {
        if (nums[i] < max_v) {
          r = i;
        } else {
          max_v = nums[i];
        }
    }
    return r - l + 1;        
}

```

## Subarray Pattern

### Contiguous subarray with equal number of 0 and 1
https://leetcode.com/problems/contiguous-array
Given a binary array, find the maximum length of a contiguous subarray with equal number of 0 and 1.

```CPP
int findMaxLength(vector<int>& nums) {
    int len=nums.size();
    int ret = 0;
    int shift = 0; //shift: num of 0 - num of 1
    map<int,int> m; //key is shift, val is index. find two index that has same shift, len in between has same 0 and 1
    m[0]=-1;
    for(int i=0;i<len;i++){
        if(nums[i]==1){
            shift++;
        }else{
            shift--;
        }
        if(m.find(shift)!=m.end()){
            ret = max(ret,i-m[shift]);
        }else{
            m[shift]=i;
        }  
    }
    return ret;
}

```

### Max Consecutive Ones(with flip most k zeros)
https://leetcode.com/problems/max-consecutive-ones-ii/
Given a binary array, find the maximum number of consecutive 1s in this array if you can flip at most k 0.
```
Example 1:
Input: [1,0,1,1,0], k =1
Output: 4
Explanation: Flip the first zero will get the the maximum number of consecutive 1s.
    After flipping, the maximum number of consecutive 1s is 4.
```


```CPP
int findMaxConsecutiveOnes(vector<int>& nums) {
    int len = nums.size();
    //The idea is to keep a window [l, h] that contains at most k zero
    int ret=0;
    queue<int> q;
    int k=1;
    for(int l=0,h=0;h<len;h++){
        if(nums[h]==0){
            q.push(h);
        }
        if(q.size()>k){
            l=q.front()+1;
            q.pop();
        }
        ret = max(ret,h-l+1);
    }
    return ret;
}
```


* Longest subarray that can be integrated

Longest subarray that can be integrated so that items in subarray is ascending order and step is 1.

```CPP
int LongestIntegratedLength(vector<int> nums){
  int len = 0;
  int max_v = 0;
  int min_v = 0;
  set<int> s;
  for (int i = 0; i < nums.size(); i++) {
    max_v = INT_MIN;
    min_v = INT_MAX;
    for (int j = i; j < nums.size(); j++) {
      if (s.find(nums[j])!=s.end()) {
        break;
      }
      set.insert(nums[j]);
      max_v = max(max_v, nums[j]);
      min_v = min(min_v, nums[j]);
      if (max_v - min_v == j - i) {
        len = max(len, j - i + 1);
      }
    }
    s.clear();
  }
  return len;
}

```

## Array split/Cut/Partition Problem

Same idea as before, need to Preprocess the array, most split will need some sum preprocess. and then try different split

```CPP
//https://leetcode.com/problems/split-array-with-equal-sum/
/*
Given an array with n integers, you need to find if there are triplets (i, j, k) which satisfies following conditions:
0 < i, i + 1 < j, j + 1 < k < n - 1
Sum of subarrays (0, i - 1), (i + 1, j - 1), (j + 1, k - 1) and (k + 1, n - 1) should be equal.
where we define that subarray (L, R) represents a slice of the original array starting from the element indexed L to the element indexed R.
Example:
Input: [1,2,1,2,1,2,1]
Output: True
Explanation:
i = 1, j = 3, k = 5.
sum(0, i - 1) = sum(0, 0) = 1
sum(i + 1, j - 1) = sum(2, 2) = 1
sum(j + 1, k - 1) = sum(4, 4) = 1
sum(k + 1, n - 1) = sum(6, 6) = 1
*/

bool splitArray(vector<int>& nums) {
        //get a middle cut, and then calculate left and right cur respectively see find whether there is equal
        int len = nums.size();
        if(len<7)
            return false;

        vector<int> sum(len,0);
        sum[0] = nums[0];
        for(int i=1;i<len;i++){
            sum[i]=sum[i-1]+nums[i];
        }
        //i is left cut, j is middle cut, k is right cut
        for(int j=3;j<len-3;j++){
            unordered_set<int> s; //record sum in for subarray, for each different middle cut we have new set for split
            for(int i=0;i<j-1;i++){
                if(sum[i-1]==sum[j-1]-sum[i])
                    s.insert(sum[i-1]); //one subarray in left cut candidate
            }

            for(int k=j+2;k<len-1;k++){
                if(sum[len-1]-sum[k]==sum[k-1]-sum[j] && s.find(sum[len-1]-sum[k])!=s.end()) //find right cut and equals to left
                    return true;
            }
        }
        return false;

    }

```




# Sliding Windows

```CPP
int left = 0, right = 0;

while (right < s.size()) {
  //Increase the window size 
    window.add(s[right]);
    right++;

    while (window_can_be_shrink) {
        //reduce the window
        window.remove(s[left]);
        left++;
    }
}
```

## Maximum Average Subarray 

### Maximum Average Subarray/fixed sliding window

https://leetcode.com/problems/maximum-average-subarray-i/

Given an array consisting of n integers, find the contiguous subarray of given length k that has the maximum average value. And you need to output the maximum average value.

```CPP
double findMaxAverage(vector<int>& nums, int k) {
    double sum=0;
    for(int i=0;i<k;i++)
        sum+=nums[i];
    double res=sum;
    for(int i=k;i<nums.size();i++){
        sum+=nums[i]-nums[i-k];
        res=max(res,sum);
    }
    return res/k;
}
```

### Maximum Average Subarray/dynamic sliding window

https://leetcode.com/problems/maximum-average-subarray-ii/

Given an array consisting of n integers, find the contiguous subarray whose length is greater than or equal to k that has the maximum average value. And you need to output the maximum average value.

```
Example 1:
Input: [1,12,-5,-6,50,3], k = 4
Output: 12.75
Explanation:
when length is 5, maximum average value is 10.8,
when length is 6, maximum average value is 9.16667.
Thus return 12.75.
```

## Maximum value in sliding window

https://leetcode.com/problems/sliding-window-maximum/

You are given an array of integers nums, there is a sliding window of size k which is moving from the very left of the array to the very right. You can only see the k numbers in the window. Each time the sliding window moves right by one position.

Return the max sliding window.

 
```
Example 1:

Input: nums = [1,3,-1,-3,5,3,6,7], k = 3
Output: [3,3,5,5,6,7]
Explanation: 
Window position                Max
---------------               -----
[1  3  -1] -3  5  3  6  7       3
 1 [3  -1  -3] 5  3  6  7       3
 1  3 [-1  -3  5] 3  6  7       5
 1  3  -1 [-3  5  3] 6  7       5
 1  3  -1  -3 [5  3  6] 7       6
 1  3  -1  -3  5 [3  6  7]      7
```

```CPP
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        //use deque, make sure the queue is always in sorted order with front the largest item's index
        vector<int> ret;
        deque<int> dq; //store index, with num[index] monotonic decreasing from front
        for(int i=0;i<nums.size();i++){
            if(!dq.empty() && (dq.front()==i-k)){
                //the max value's index in deque reach the window size, need to pop out.
                    dq.pop_front();
            }
            while(!dq.empty() && nums[dq.back()]<nums[i]){
                dq.pop_back();
            }
            dq.push_back(i);
            if (i>=k-1)
                ret.push_back(nums[dq.front()]);
        }
        return ret;
    }
```



## Mini Sub string

Given a string S and a string T, find the minimum window in S which will contain all the characters in T in complexity O(n).

```
Example:

Input: S = "ADOBECODEBANC", T = "ABC"
Output: "BANC"
Note:

If there is no such window in S that covers all characters in T, return the empty string "".
If there is such window, you are guaranteed that there will always be only one unique minimum window in S.
```

We use the pattern and code will be 

```CPP

class Solution {
public:
    string minWindow(string s, string t) {
        string s, t;

        int left = 0, right = 0;
        string res = s;

        // two counters
        unordered_map<char, int> window;
        unordered_map<char, int> needs;
        for (char c : t) 
          needs[c]++;

        // record how many char in windows match condition
        int match = 0; 

        while (right < s.size()) {
            char c1 = s[right];
            if (needs.count(c1)) {
                window[c1]++; // 
                if (window[c1] == needs[c1])
                    //  c1 has same occurance in needs and window
                    match++;
            }
            right++;

            // all chars match
            while (match == needs.size()) {
                if (right - left < minLen) {
                    // update min sgtring
                    start = left;
                    minLen = right - left;
                  }
                char c2 = s[left];
                if (needs.count(c2)) {
                    window[c2]--; // remove from window
                    if (window[c2] < needs[c2])
                        // c2 dose not meet requirements
                        match--;
                }
                left++;
            }
        }
        return minLen == INT_MAX ?"" : s.substr(start, minLen);
    }
};


```

## Longest Substring with At Most Two Distinct Characters

https://leetcode.com/explore/interview/card/google/59/array-and-strings/3054/

Given a string s , find the length of the longest substring t  that contains at most 2 distinct characters.

```
Example 1:

Input: "eceba"
Output: 3
Explanation: t is "ece" which its length is 3.
Example 2:

Input: "ccaabbb"
Output: 5
Explanation: t is "aabbb" which its length is 5.
```

```CPP
    int lengthOfLongestSubstringTwoDistinct(string s) {
        int start = 0;
        unordered_map<char,int> m;
        int ret = 0;
        for(int i=0;i<str.size();i++){
            m[str[i]]++;
            while(m.size()>k){
                if(--m[str[start]]==0){ //move this start char position will eliminate one char in map, so reduce size
                    m.erase(str[start]);
                }
                start++;
            }
            ret = max(ret,i-start+1);
        }
        return ret;         
    }
```

### Fruit Into Baskets

In a row of trees, the i-th tree produces fruit with type tree[i].

You start at any tree of your choice, then repeatedly perform the following steps:

Add one piece of fruit from this tree to your baskets.  If you cannot, stop.
Move to the next tree to the right of the current tree.  If there is no tree to the right, stop.
Note that you do not have any choice after the initial choice of starting tree: you must perform step 1, then step 2, then back to step 1, then step 2, and so on until you stop.

You have two baskets, and each basket can carry any quantity of fruit, but you want each basket to only carry one type of fruit each.

What is the total amount of fruit you can collect with this procedure?

```CPP
    int totalFruit(vector<int>& tree) {
                //Find out the longest length of subarrays with at most 2 different numbers
        unordered_map<int, int> count;
        int i, j;
        int ret = 0;
        for (i = 0, j = 0; j < tree.size(); ++j) {
            count[tree[j]]++;
            while (count.size() > 2) {
                count[tree[i]]--;
                if (count[tree[i]] == 0)
                    count.erase(tree[i]);
                i++;
            }
            ret = max(ret,j-i+1);
        }
        return ret;
    }
```

## Longest Substring Without Repeating Characters

https://leetcode.com/problems/longest-substring-without-repeating-characters/

```CPP
  static int findLength(const string& str) {

      int start = 0, end = 0;
      unordered_map<char, int> m;
      int res = 0; // record longest length

      for(end=0;end<str.size();end++) {
          m[str[end]]++;
          //repeating char appear, so move left
          while (m[str[end]] > 1) {
              m[str[start]]--;
              start++;
          }
          res = max(res, end - start+1);
      }
      return res;

  }
```

## Longest Substring with Same Letters after K change

https://www.educative.io/courses/grokking-the-coding-interview/R8DVgjq78yR

https://leetcode.com/problems/longest-repeating-character-replacement/

Given a string s that consists of only uppercase English letters, you can perform at most k operations on that string.
In one operation, you can choose any character of the string and change it to any other uppercase English character.
Find the length of the longest sub-string containing all repeating letters you can get after performing the above operations.


```
Example 1:

Input:
s = "ABAB", k = 2

Output:
4

Explanation:
Replace the two 'A's with two 'B's or vice versa.
 

Example 2:

Input:
s = "AABABBA", k = 1

Output:
4

Explanation:
Replace the one 'A' in the middle with 'B' and form "AABBBBA".
The substring "BBBB" has the longest repeating letters, which is 4.
```

```CPP
    int characterReplacement(string s, int k) {
          int start = 0, end = 0;
          unordered_map<char,int> m;
          int maxRepeat = 0;  //at any given window, max 
          int res = 0; // record longest length

          for(end=0;end<s.size();end++) {
              m[s[end]]++;
              maxRepeat = max(maxRepeat, m[s[end]]);
              //we can change at most K
              if (end - start + 1 - maxRepeat > k) {
                m[s[start]]--;
                start++;
              }
              res = max(res, end - start+1);
          }
          return res;  
    }
```

### Max Consecutive Ones with K changes

https://leetcode.com/problems/max-consecutive-ones-iii/

https://www.educative.io/courses/grokking-the-coding-interview/B6VypRxPolJ

Given an array containing 0s and 1s, if you are allowed to replace no more than ‘k’ 0s with 1s, find the length of the longest contiguous subarray having all 1s.

```
Example 1:

Input: Array=[0, 1, 1, 0, 0, 0, 1, 1, 0, 1, 1], k=2
Output: 6
Explanation: Replace the '0' at index 5 and 8 to have the longest contiguous subarray of 1s having length 6.
Example 2:

Input: Array=[0, 1, 0, 0, 1, 1, 0, 1, 1, 0, 0, 1, 1], k=3
Output: 9
Explanation: Replace the '0' at index 6, 9, and 10 to have the longest contiguous subarray of 1s having length 9.
```



```CPP
int longestOnes(vector<int>& arr, int K) {
      int start = 0, end = 0;
      int maxOnes = 0;  //at any given window, max 
      int res = 0; // record longest length

      for(end=0;end<arr.size();end++) {
          if(arr[end]==1)
            maxOnes++;
          //we can change at most K
          if (end - start + 1 - maxOnes > K) {
            if(arr[start]==1)
              maxOnes--;
            start++;
          }
          res = max(res, end - start+1);
      }
      return res;       
}
```

## Permutation in a String

https://www.educative.io/courses/grokking-the-coding-interview/N8vB7OVYo2D

https://leetcode.com/problems/permutation-in-string/

Given two strings s1 and s2, write a function to return true if s2 contains the permutation of s1. In other words, one of the first string's permutations is the substring of the second string.

 
```
Example 1:

Input: s1 = "ab" s2 = "eidbaooo"
Output: True
Explanation: s2 contains one permutation of s1 ("ba").
Example 2:

Input:s1= "ab" s2 = "eidboaoo"
Output: False
```

```CPP
static bool findPermutation(const string &str, const string &pattern) {
        if(pattern.size()==0)
            return true;
        unordered_map<char,int> m;
        int l = 0;
        int r = 0;
        int cnt = 0;
        for(int i=0;i<pattern.size();i++){
            m[pattern[i]]++;  
            cnt++;
        }
        for(int l=0,r=0;r<str.size();r++){
            if(m.find(str[r])!=m.end() && m[str[r]]-->0){
                //m[s2[r]] could be smaller than 0, so s2[r] pays off and have more, leaving for l to move
                cnt--;
                while(cnt==0){//include all in pattern
                    if(r-l+1==pattern.size())  {
                        return true;
                    }
                    //if size > pattern, move left pointer
                    if(m.find(str[l])!=m.end() && m[str[l]]++==0){
                        cnt++;
                    }
                    l++;
                }
            }
        }
        return false;
  }
```

A more descriptive solution is

1. Create a HashMap to calculate the frequencies of all characters in the pattern.

2. Iterate through the string, adding one character at a time in the sliding window.

3. If the character being added matches a character in the HashMap, decrement its frequency in the map. If the character frequency becomes zero, we got a complete match.

4. If at any time, the number of characters matched is equal to the number of distinct characters in the pattern (i.e., total characters in the HashMap), we have gotten our required permutation.

5. If the window size is greater than the length of the pattern, shrink the window to make it equal to the size of the pattern. At the same time, if the character going out was part of the pattern, put it back in the frequency HashMap.

```CPP
bool checkInclusion(string pattern, string str) {
    if(pattern.size()==0)
        return true;
    unordered_map<char,int> m;
    int l = 0;
    int r = 0;
    int cnt = 0;
    for(int i=0;i<pattern.size();i++){
        m[pattern[i]]++;  
    }
    for(r=0;r<str.size();r++){
        if(m.find(str[r])!=m.end()){
            m[str[r]]--;  
            //find all occurence for this letter
            if(m[str[r]]==0){
                cnt++;
            }
        }
        
        if(cnt == m.size() && (r-l+1)==pattern.size()){
            return true;
        }
        if(r>=pattern.size()-1){
            if(m.find(str[l])!=m.end()){
                if(m[str[l]]==0)
                    cnt--;
                m[str[l]]++;

            }
            l++;
        }


    }
    return false;
}
```


## Find All Anagrams in a String

https://leetcode.com/problems/find-all-anagrams-in-a-string/

Given a string s and a non-empty string p, find all the start indices of p's anagrams in s.

Strings consists of lowercase English letters only and the length of both strings s and p will not be larger than 20,100.

The order of output does not matter.

```
Example 1:

Input:
s: "cbaebabacd" p: "abc"

Output:
[0, 6]

Explanation:
The substring with start index = 0 is "cba", which is an anagram of "abc".
The substring with start index = 6 is "bac", which is an anagram of "abc".
Example 2:

Input:
s: "abab" p: "ab"

Output:
[0, 1, 2]

Explanation:
The substring with start index = 0 is "ab", which is an anagram of "ab".
The substring with start index = 1 is "ba", which is an anagram of "ab".
The substring with start index = 2 is "ab", which is an anagram of "ab".
```


The same solution as before:

```CPP
class Solution {
public:
    vector<int> findAnagrams(string s, string t) {
        vector<int> res;
        int left = 0, right = 0;
        unordered_map<char, int> needs;
        unordered_map<char, int> window;
        for (char c : t) needs[c]++;
        int match = 0;

        while (right < s.size()) {
            char c1 = s[right];
            if (needs.count(c1)) {
                window[c1]++;
                if (window[c1] == needs[c1])
                    match++;
            }
            right++;

            while (match == needs.size()) {
                //match anagrams
                if (right - left == t.size()) {
                    res.push_back(left);
                }
                char c2 = s[left];
                if (needs.count(c2)) {
                    window[c2]--;
                    if (window[c2] < needs[c2])
                        match--;
                }
                left++;
            }
        }
        return res;
    }
};
```

## Smallest Window containing Substring

https://leetcode.com/problems/minimum-window-substring/

Given a string S and a string T, find the minimum window in S which will contain all the characters in T in complexity O(n).

```
Example:

Input: S = "ADOBECODEBANC", T = "ABC"
Output: "BANC"
```


##  Longest Substring Without Repeating Characters

https://leetcode.com/problems/longest-substring-without-repeating-characters/

```
Example 1:

Input: "abcabcbb"
Output: 3 
Explanation: The answer is "abc", with the length of 3. 
Example 2:

Input: "bbbbb"
Output: 1
Explanation: The answer is "b", with the length of 1.
Example 3:

Input: "pwwkew"
Output: 3
Explanation: The answer is "wke", with the length of 3. 
             Note that the answer must be a substring, "pwke" is a subsequence and not a substring.
```

* For substring, slide window is no brainer

```CPP
class Solution {
public:
    int lengthOfLongestSubstring(string s) {
            int left = 0, right = 0;
            unordered_map<char, int> window;
            int res = 0; // record longest length

            while (right < s.size()) {
                char c1 = s[right];
                window[c1]++;
                right++;
                //repeating char appear, so move left
                while (window[c1] > 1) {
                    char c2 = s[left];
                    window[c2]--;
                    left++;
                }
                res = max(res, right - left);
            }
            return res;
    }
};
```

# Histogram
Histogram problem includes like water container, max rectangle. etc.

## Water container problem

### container with most water

https://leetcode.com/problems/container-with-most-water/

Given n non-negative integers a1, a2, ..., an , where each represents a point at coordinate (i, ai). n vertical lines are drawn such that the two endpoints of line i is at (i, ai) and (i, 0). Find two lines, which together with x-axis forms a container, such that the container contains the most water.

```CPP
    int maxArea(vector<int>& height) {
        int l = 0;
        int r = height.size()-1;
        int ret = 0;
        
        while(l<r){
            int min_h = min(height[l],height[r]);
            int area = min_h*(r-l);
            ret = max(ret,area);

            //check from both side, skip if lower than current bar
            while(height[l]<=min_h && l<r)
                l++;
            while(height[r]<=min_h && l<r)
                r--;
            
        }
        
        return ret;
    }
```

### Trap Rain Water

https://leetcode.com/problems/trapping-rain-water/

Given n non-negative integers representing an elevation map where the width of each bar is 1, compute how much water it is able to trap after raining.

```CPP
//two pointer approach
int trap(vector<int>& height) {
    int l = 0, r = height.size()-1, level = 0, water = 0;
    while (l < r) {
        int lower = height[height[l] < height[r] ? l++ : r--];
        level = max(level, lower);
        water += level - lower;
    }
    return water;
}
```

Another solution is to use monotonic stack, We add the index of the bar to the stack if bar is smaller than or equal to the bar at top of stack, which means that the current bar is bounded by the previous bar in the stack(monotonic increasing stack). If we found a bar longer than that at the top, we are sure that the bar at the top of the stack is bounded by the current bar and a previous bar in the stack, hence, we can pop it and add resulting trapped water to \text{ans}ans.

```CPP
int trap(vector<int>& height) {
        int ret = 0;

        stack<int> s;   //record current highest bar index, highest bar in bottom
        s.push(0);
        
        
        for(int i=1;i<height.size();i++){
            //current height is higher than stack top, so we get a potential container
            while(!s.empty() && height[i]>height[s.top()]){
                int top = s.top();
                s.pop();
                if(s.empty())
                    break;
                int dis = i-s.top()-1; //this top is higher than pop out top
                int h = min(height[i],height[s.top()]) - height[top];
                ret += dis*h;
            }
            s.push(i);
        }
        
        return ret;
    }
```



## Array Change problem

> Commonly problem such as change items in array so that certain condition meet

### Make nums inside array even


https://leetcode.com/problems/super-washing-machines/#/description

we have n super washing machines on a line. Initially, each washing machine has some dresses or is empty.
For each move, you could choose any m (1 ≤ m ≤ n) washing machines, and pass one dress of each washing machine to one of its adjacent washing machines at the same time .
Given an integer array representing the number of dresses in each washing machine from left to right on the line, you should find the minimum number of moves to make all the washing machines have the same number of dresses. If it is not possible to do it, return -1.

Example1
Input: [1,0,5]
Output: 3
Explanation:
1st move:    1     0 <-- 5    =>    1     1     4
2nd move:    1 <-- 1 <-- 4    =>    2     1     3
3rd move:    2     1 <-- 3    =>    2     2     2

Example2
Input: [0,3,0]
Output: 2
Explanation:
1st move:    0 <-- 3     0    =>    1     2     0
2nd move:    1     2 --> 0    =>    1     1     1

Example3
Input: [0,2,0]
Output: -1
Explanation:
It's impossible to make all the three washing machines have the same number of dresses.

```CPP
int findMinMoves(vector<int>& machines) {
        int ret = -1;
        int len = machines.size();
        vector<int> sum(len+1,0);
        for(int i=0;i<machines.size();i++){
            sum[i+1]= sum[i] + machines[i];
        }
        if(sum[len]%machines.size()!=0)
            return ret; //not able to evenly distribute

        int average = sum[len]/len;

        /* For a single machine, necessary operations is to transfer dresses from one side to another until sum of both sides and itself reaches the average number. We can calculate (required dresses) - (contained dresses) of each side as L and
        L > 0 && R > 0: both sides lacks dresses, and we can only export one dress from current machines at a time, so result is abs(L) + abs(R)
        L < 0 && R < 0: both sides contains too many dresses, and we can import dresses from both sides at the same time, so result is max(abs(L), abs(R))
        L < 0 && R > 0 or L >0 && R < 0: the side with a larger absolute value will import/export its extra dresses from/to current machine or other side, so result is max(abs(L), abs(R))
        */

        int l = 0;  //all dress left of current
        int r = 0;  //all dress right of current
        for(int i=0;i<len;i++){
            l = i*average-sum[i]; //0 until i-1;
            r = (len-i-1)* average - (sum[len]-sum[i+1]);  //i+1 until end
            if(l>0 && r>0)
                ret = max(ret, abs(l)+abs(r));
            else
                ret = max(ret,max(abs(l),abs(r)));
        }
        return ret;

}
```
