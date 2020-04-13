<!-- START doctoc generated TOC please keep comment here to allow auto update -->
<!-- DON'T EDIT THIS SECTION, INSTEAD RE-RUN doctoc TO UPDATE -->
**Table of Contents**  *generated with [DocToc](https://github.com/thlorenz/doctoc)*

- [Array](#array)
  - [Array re-order](#array-re-order)
    - [Detect duplicate](#detect-duplicate)
  - [Sub Array](#sub-array)
    - [Classical Sub-Array Problem](#classical-sub-array-problem)
      - [Common Tchnqiues](#common-tchnqiues)
      - [Two sum](#two-sum)
      - [Sub Array Sum, longest/shortest](#sub-array-sum-longestshortest)
      - [Subarray Pattern](#subarray-pattern)
    - [Array split/Cut/Partition Problem](#array-splitcutpartition-problem)
  - [Three pointers problems](#three-pointers-problems)
    - [3 Sum](#3-sum)
    - [Valid-triangle-number](#valid-triangle-number)
  - [Histogram](#histogram)
    - [Water container problem](#water-container-problem)
    - [Array Change problem](#array-change-problem)
      - [Make nums inside array even](#make-nums-inside-array-even)

<!-- END doctoc generated TOC please keep comment here to allow auto update -->


# Array

## Array re-order

* one for loop for main array, and the other pointer moving if condition meet

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

### Detect duplicate

https://leetcode.com/problems/set-mismatch/description/

The set S originally contains numbers from 1 to n. But unfortunately, due to the data error, one of the numbers in the set got duplicated to another number in the set, which results in repetition of one number and loss of another number.

Given an array nums representing the data status of this set after the error. Your task is to firstly find the number occurs twice and then find the number that is missing. Return them in the form of an array.

Example 1:

Input: nums = [1,2,2,4]

Output: [2,3]

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

## Sub Array
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


### Classical Sub-Array Problem

#### Common Tchnqiues

1. preprocess: sum all
2. two pointers
3. DP
4. Hash Map to record index or occurence
5. Matrix problem: transfer to subarray problem

#### Two sum
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

#### Sub Array Sum, longest/shortest

* Shortest substring length to make sure whole string is sorted
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


* Subarray sum number that equals to certain target
https://leetcode.com/problems/subarray-sum-equals-k/#/description
Given an array of integers and an integer k, you need to find the total number of continuous subarrays whose sum equals to k.

```CPP
int subarraySum(vector<int>& nums, int k) {
    //notice if the array is all positive, it is different
    //easy way is to do O(N^2), calculate all subarry starting from 0->len-1, to end
    //if we want to do O(N), need a map to record
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
m[0]=0;
for(int i=0;i<len;i++){
    sum+=nums[i];
    if(sum==k)  //count how many times sum from begining
        ret++;
    if(m.find(sum-k)!=m.end())
        ret+=m[sum-k];
    m[sum]++;
}

```

* Follow up: Longest Subarray with sum to k

```CPP
int Longestsubarray(vector<int> nums, int k){
  int ret = 0;
  int sum = 0;
  map<int,int> m;//key is sum val, val is index
  m[0] = 0;  //so if sum-k = 0, means sum==k, we can have len
  for(int i=0;i<nums.size();i++){
    sum+=nums[i];
    if(m.find(sum-k)!=m.end()){
      ret = max(ret, i-m[sum-k]+1); //get the length
    }
    //if sum is already there, we do not record index since we need left most index to get longest
    if(m.find(sum)==m.end())  
      m[sum] = i;
  }

}

```

* Follow Up: If subarray contains all positive

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

* Follow up: subarray sum to multiple of k
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

* Max subarray sum
https://leetcode.com/problems/maximum-subarray/
Find the contiguous subarray within an array (containing at least one number) which has the largest sum.
For example, given the array [-2,1,-3,4,-1,2,1,-5,4],
the contiguous subarray [4,-1,2,1] has the largest sum = 6.
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

* Follow up: max sub matrix size

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

Most Matrix problem will be transmitted to sub array problem

* Maximum Product Subarray
https://leetcode.com/problems/maximum-product-subarray/#/description

Find the contiguous subarray within an array (containing at least one number) which has the largest product.

For example, given the array [2,3,-2,4],
the contiguous subarray [2,3] has the largest product = 6.

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

* Count of range sum
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

#### Subarray Pattern

* Contiguous subarray with equal number of 0 and 1
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

* Max Consecutive Ones(with flip most k zeros)
https://leetcode.com/problems/max-consecutive-ones-ii/
Given a binary array, find the maximum number of consecutive 1s in this array if you can flip at most k 0.

Example 1:
Input: [1,0,1,1,0], k =1
Output: 4
Explanation: Flip the first zero will get the the maximum number of consecutive 1s.
    After flipping, the maximum number of consecutive 1s is 4.
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

### Array split/Cut/Partition Problem

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

## Three pointers problems
> Common techniques
* Sort the array
* Fix the first pointer, and define left and right, search from beginning and end
* define the condition properly

### 3 Sum

https://leetcode.com/problems/3sum/#/description
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

### Valid-triangle-number

There are lots of problem can be soled by similar idea.

https://leetcode.com/problems/valid-triangle-number/#/description
Given an unsorted array of positive integers. Find the number of triangles that can be formed with three different array elements as three sides of triangles.

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
            }else
                l++;
        }
    }

    return ret;
}
```

## Histogram
Histogram problem includes like water container, max rectangle. etc.

### Water container problem

### Array Change problem

> Commonly problem such as change items in array so that certain condition meet

#### Make nums inside array even


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
