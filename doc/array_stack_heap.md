<!-- START doctoc generated TOC please keep comment here to allow auto update -->
<!-- DON'T EDIT THIS SECTION, INSTEAD RE-RUN doctoc TO UPDATE -->
**Table of Contents**  *generated with [DocToc](https://github.com/thlorenz/doctoc)*

- [Array](#array)
  - [Sub Array](#sub-array)
    - [Classical Sub-Array Problem](#classical-sub-array-problem)
    - [Array split Problem](#array-split-problem)
  - [Typical three pointers problems](#typical-three-pointers-problems)
  - [Histogram](#histogram)
    - [Water container problem](#water-container-problem)
    - [Array Change problem](#array-change-problem)
      - [Make nums inside array even](#make-nums-inside-array-even)
- [Heap](#heap)
  - [Top K problem](#top-k-problem)
  - [Other Stack Problem](#other-stack-problem)
  - [Dequeue: Update Largest/Smallest value in sliding window](#dequeue-update-largestsmallest-value-in-sliding-window)
  - [Max-tree](#max-tree)
  - [Monotonic stack](#monotonic-stack)

<!-- END doctoc generated TOC please keep comment here to allow auto update -->



# Array

## Sub Array
> Common techniques
* solve the sub problem: the same problem mapping to subarry ending in current index i, so can get the results from i-1
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

* Two sum
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

* Longest substring length to make sure whole string is sorted
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
          min_v = min(min_v, nums[i]);
        }
    }
    if (l == -1) {
        return 0;
    }
    //from left to rightm record value not ascending, find right most
    int max_v = nums[0];
    int r = -1;
    for (int i = 1; i <len; i++) {
        if (nums[i] < max_v) {
          r = i;
        } else {
          max_v = max(max_v, nums[i]);
        }
    }
    return r - l + 1;        
}

```


* Longest Sum SubArray Length: Subarray sum equal to target

```CPP
int LongestSumSubArrayLength(vector<int> nums, int k){
  int len = nums.size();
  int l = 0; //left index
  int r = 0;//right index
  int sum=0;
  int ret = 0;
  while(r<len){
    sum+=nums[r];
    if(sum==k){
      ret = max(r-l+1,ret);
      sum -=nums[l++];
    }else if(sum<k){
      r++;
    }else{
      sum-=nums[l++];
    }
  }

  return ret;

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

* Maximum Product Subarray
//https://leetcode.com/problems/maximum-product-subarray/#/description

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

* Local minimum

Find array if there is local min(left and right is larger) and return index

```CPP
//Binary search

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

### Array split Problem

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

## Typical three pointers problems
> Common techniques
* Sort the array
* Fix the first pointer, and define left and right, search from beginning and end
* define the condition properly

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

* Valid-triangle-number

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
        * /

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



# Heap

Heap is implemented as tree structure in logic view and array in physical view:

```shell
For node in index i:
Children: left: 2*i+1; right: 2*i+2
Parent: (i-1)/2
```

Time complexity for construct the heap is:

```shell
O(N): 1*log(1)+2*log(2)...+n*log(n) = O(N)
```
## Top K problem

Use heap will be best. See example:

Q: Suppose we have matrix with each row sorted in increasing order, print largest top K values
```CPP
struct compare{
  bool operator()(pair<int,int> a, pair<int,int> b){
    return a.second > b.second;
  }
};

vector<int> topKinMatrix(vector<vector<int> matrix, int k){
  //pq is max heap, where <int, int> represents item's row index and value respectively
  Priority_queue(pair<int,int>, vector<pair<int,int>>, compare) pq;
  vector<int> ret;
  int row = matrix.size();
  //init the heap to hold row number largest (from head of each row array)
  for(int i=0;i<row;i++){
    pq.push(make_pair(i, matrix[i].back()));
  }
  //keep get the back of each row, and pop back heap value its position in row
  while(true){
    int cur_row_index = pq.top().first;
    ret.push_back(pq.top());
    pq.pop();
    matrix[cur_row_index].pop_back();
    if(![cur_row_index].empty())
      pq.push(matrix[cur_row_index].back());

    if(ret.size()==K)
      break;
  }

  return ret;
}

/* complexity will be K*log(Row) */
```

* Find the median value in data stream on the fly:



Design a median holder function: use two heaps: maxheap to hold the smaller half of data stream, and minheap to hold the larger half of data stream. Need to balance both heaps to same size(or one can only hold 1 more item )
https://leetcode.com/problems/find-median-from-data-stream/

 ```CPP
 struct mycompare{
    bool operator()(int a, int b){
        return a>b;
    }
};
 //two heaps: max_half has max half nums, min_half has small half nums
 priority_queue<int> min_half;  //max heap: top of min_half heap is max value in min heap
 priority_queue<int, vector<int>, mycompare> max_half; //min heap: top of max_half heap is min value of max heap

 // Adds a number into the data structure.
 void addNum(int num) {
     //need to make sure push into both heap, otherwise if two heaps are equal and one new item //input, this new item could be mistakely choosen as median since later balance function //is not called
     max_half.push(num);
     min_half.push(max_half.top());
     max_half.pop();

     //balance both heap, make sure max_half is either equal size of min_half or has one more item
     while(min_half.size()>max_half.size()+1){
         max_half.push(min_half.top());
         min_half.pop();
     }

 }

 // Returns the median of current data stream
 double findMedian() {
     if(max_half.size()==min_half.size()){
         return (min_half.top()+max_half.top())/2.0;
     }else{
         return (double) min_half.top();
     }
 }
 ```

* Max profit:

 You are given several projects. For each project i, it has a pure profit Pi and a minimum capital of Ci is needed to start the corresponding project. Initially, you have W capital. When you finish a project, you will obtain its pure profit and the profit will be added to your total capital.https://leetcode.com/contest/leetcode-weekly-contest-18a/problems/ipo/

 ```CPP
 struct cost_compare{
     bool operator()(pair<int,int> a, pair<int,int> b){
         return a.first>b.first;
     }
 };

 struct profit_compare{
     bool operator()(pair<int,int> a, pair<int,int> b){
         return a.second<b.second;
     }
 };

 int findMaximizedCapital(int k, int W, vector<int>& Profits, vector<int>& Capital) {
    priority_queue<pair<int,int>,vector<pair<int,int>>,cost_compare> cost; //min heap for cost
    priority_queue<pair<int,int>,vector<pair<int,int>>,profit_compare> profit; //max heap for profit


    int len = Capital.size();
    pair<int,int> cur;
    for(int i=0;i<len;i++){
      cur = make_pair(Capital[i],Profits[i]);
      cost.push(cur);
    }
    int picks = 0;
    while(k>0){

      while(!cost.empty() && W>=cost.top().first){
         //only pick possible project, do not trade yet
         profit.push(cost.top());
         cost.pop();
      }
      if(profit.empty())
         break;
     //deal the real transaction here
       cur = profit.top();
       W = W + cur.second;
       profit.pop();
       k--;
    }
    return W;    
 }
 ```

# Stack/Queue

## Min Stack

maintain a min stack that query  minimum value in stack is O(1). idea is to maintain two stacks, regular one and the other one whose peek/top records the min value
push(x) -- Push element x onto stack.
pop() -- Removes the element on top of the stack.
top() -- Get the top element.
getMin() -- Retrieve the minimum element in the stack.

```CPP
//Basic idea is to maintain two stacks, regular one and the other one whose peek/top records the min value

stack<int> data_s; //regular stack
stack<int> min_s; //stack that records min val of current stack  

void push(int x) {
    if(min_s.empty() || x<=min_s.top()){
        min_s.push(x);
    }
    data_s.push(x);
}

void pop() {
    if(getMin()==data_s.top())
        min_s.pop();
    data_s.pop();
}

int top() {
    return data_s.top();
}

int getMin() {
    return min_s.top();
}
```

## Other Stack Problem
* Convert a stack to Queue:

The idea is to Use two stacks, one for push, one for pop to mimic the queue tail and head
```CPP
// Use two stacks, one for push, one for pop to mimic the queue tail and head

stack<int> stack_push;
stack<int> stack_pop;

void Push(int input){
  stack_push.push(input);
}

int pop(){
  if(stack_push.empty()&&stack_pop.empty())
    return;
  //put all push stack items into pop stack,
  //Ensure that pop stack is empty before transfer
  if(stack_pop.empty()){
    while(!stack_push.empty()){
      stack_pop.push(stack_push.top());
      stack_push.pop();
    }
  }
  int ret = stack_pop.top();
  stack_pop.pop();
  return ret;
}
```

* Revert stack recursively without extra new stack:

The idea is to use function recursively because recursive uses stack
```CPP
stack<int> s;
void reverse(stack<int> &s){
  if(s.empty())
    return;
  int ret = getAndRemoveLastElement(s);
  reverse(s);
  s.push(ret);
}
//this function will delete last/bottom of current stack. return top of current stack
int getAndRemoveLastElement(stack<int> &s){
  int cur = s.top();
  s.pop();
  if(s.empty())
    return cur;
  int last = getAndRemoveLastElement(s);
  s.push(cur);
  return last;
}

```

## Dequeue: Update Largest/Smallest value in sliding window

1. use dequeue(double linked list), new item will be inserted into tail.
2. store the index instead of the value in dequeue.
3. when updating, remove tail of dequeue until new value is the index of Smallest in dequeue. ensure the head of dequeue is index of Largest
4. ensure the dequeue is in decreasing order from head to tail


```CPP
## With fix size window
std::deque<int> dq;
for(int i=0;i<array.size();i++){

  //update dequeue structure to ensure decreasing order from head to tail.
  while(!dq.empty() && array[dq.end()]<array[i]){
    dq.pop_back()
  }
  dq.push_back(i); //store index

  if(dq.front()>=i-w) //head index expires. w is window size
    dq.pop_front();
}
```

> An example problem could be:

* In Array, if a max of subarray minus min of subarray <= Num, calculate how many such Array

Requirements: Max{arr[i..j]} – Min{arr[i..j]} <= num.

Where Max{arr[i..j]} is max value in subarray i->j.
Min{arr[i..j]} is min value in subarray i->j

1. if a subarray dose not match condition, extend it can not match
2. if a subarray match condition, reduce subarray still can match
3. assume start from position i, and extend to j position that matches, but extend to j+1 dose not match, so we can know the num of subarray that starting from index i will be j-1+1.
4. like sliding window, need to move left i to i+1, since i->j matches, so i+1->j matches.
and then can move forward j to j+1 and try  again.

```CPP
int AllLessNumSubArray(vector<int> array, int num){
  int i = 0; //left index
  int j = 0; //right index
  int len = array.size();
  int ret = 0;
  deque<int> max_dq;  //record max value's index in subarray
  deque<int> min_dq;  //record min value's index in subarray
  while(i < len){
    //j is right index, extends the subarray as sliding right
    while(j < len){
      int input = array[j];
      //update max value index
      while(!max_dq.empty() && input>=max_dq.back()){
        max_dq.pop_back();
      }
      max_dq.push_back(j);
      //update min value index
      while(!min_dq.empty() && input<=min_dq.back()){
        min_dq.pop_back();
      }
      min_dq.push_back(j);
      //reach the right boundary
      if(array[j]-array[i]>num)
        break;
      j++;
    }
    if(min_dq.front()==i)
      min_dq.pop_front();
    if(max_dq.front()==i)
      max_dq.pop_front();

    ret+= j-i+1;
    i++;
  }

  return ret;
}
```




## Max-tree

We can use max heap and heap insert.
```CPP
struct TreeNode{
  int val;
  TreeNode* left;
  TreeNode* right;
};

TreeNode * getMaxtree_method1(vector<int> array){
  int len = array.size();
  std::vector<TreeNode> node;
  //init heap tree
  for(int i=0;i<array.size();i++){
    node[i] = new TreeNode(array[i]);
  }
  //heap sort array
  for(int i=0;i<len;i++){
    heapSort(array,i);
  }
  //Build up the max tree
  for(int i=0;i<array.size();i++){
    int left_child = 2*i+1;
    int right_child = 2*i+2;
    if(left_child<array.size())
      node[i]->left = node[left_child];
    if(right_child<array.size())
      node[i]->right = node[right_child]
  }
  return node[0];
}

void heapSort(vector<int> &array, int index){
  while(index!=0){
    int parent = (index-1)/2;
    if(array[parent]<array[index]){
      swap(array[parent],array[index]);
      index = parent;
    }else{
      break;
    }
  }
}
```


## Monotonic stack

> for a given item in array, find its values from its left and right which are larger than it and are cloest to current item.

> For a input size N array, return size N pairs of values (left, right), in which left is the cloest larger value from left side of current item, and right is the cloest larger value from right side of current item

Algorithm:
```CPP
stack<int> s; //monotonic stack, values are increasing from top to bottom
vector<pair<int,int>> ret;
int left,right,input;
for(int i=0;i<array.size();i++){
  input = array[i];

  while(!s.empty() && input>s.top()){
    s.pop(); //will get the left and right for this popped value;
    left = stack.empty()?NULL:s.top(); //since monotonic, current top after pop should be larger
    right = input; //input is larger than popped
    ret.push_back(make_pair(left,right));
  }
  s.push(input);
}
//if there are still values in stack, it is monotonic, so right larger is NULL
while(!s.empty()){
  right = NULL;
  s.pop();
  left = stack.empty()?NULL:s.top();
  ret.push_back(make_pair(left,right));
}

return ret;
```

We can use this monotonic stack way to create the max-tree:

1. For any value, check left and right cloest larger value.
2. compare these two, put itself as child of smaller between left and right.

It will be a binary tree, not necessary full balanced binary tree
```CPP
struct TreeNode{
  int val;
  TreeNode* left;
  TreeNode* right;
};

TreeNode * getMaxtree_method2(vector<int> array){
  stack<TreeNode> s; //monotonic stack for TreeNode value
  map<TreeNode,TreeNode> Parents; //key is node, val is its parents
  std::vector<TreeNode*> node;
  //init TreeNode array
  for(int i=0;i<array.size();i++){
    node[i] = new TreeNode(array[i]);
  }
  //for each node in array, find its left cloest larger and right cloest larger, put into map
  for(int i=0;i<array.size();i++){
    int input = array[i];
    int left,right;
    while(!s.empty() && s.top()->val<input){
      TreeNode cur = s.top();
      s.pop();
      left = stack.empty()? NULL: s.top();
      right = new TreeNode(input);
      parents[cur] = left==NULL || left->val<right->val?left:right;
    }
    s.push(node[i]);
  }
  //go through all array, and stack still have value
  while(!s.empty()){
    //Right is always null since we are to the end of the array
    TreeNode cur = s.top();
    s.pop();
    left = stack.empty()?NULL:s.top();
    parents[cur] = left;
  }
  //Build up the tree
  TreeNode* head;
  TreeNode* Parent;
  for(int i=0;i<array.size();i++){
    parent = parents[node[i]];
    if(parent==NULL){
      head = node[i]; //found tree root
    }else if(parent->left == NULL){
      parent->left = node[i];
    }else{
      parent->right = node[i];
    }
  }

  return head;
}
```

* Use this data structure for other Problem:

* [Max rectangle in matrix](https://leetcode.com/problems/maximal-rectangle)

1. step 1 is to calculate row by row, for each item in matrix, what is max rectangle/histogram size when this item is the bottom of histogram


2. use monotonic stack, check each histogram left and right cloest smaller, then its histogram can only extend to left+1 and right-1, can calculate area

```CPP
int maximalRectangle(vector<vector<char>>& matrix){
  int row = matrix.size();
  if(row==0)
    return 0;
  int col = matrix[0].size();
  vector<int> histogram(col,0); //histogram size extending current item via col
  int max_area = 0;
  for(int i =0; i<row; i++){
    for(int j =0; j<col; j++){
        if(matrix[i][j]=='1')
            histogram[j]++;
        else
            histogram[j] =0;
      }
    //for each row, begin to check max area based on histogram of current row
    max_area = max(max_area, getRectanglesize(histogram));
  }


  return max_area;

}

int getRectanglesize(vector<int>& histogram){
    stack<int> s; //need to have monotonic decreasing stack, record index
    int max_size = 0;
    int left, right, height, cur_size;
    for(int i=0;i<histogram.size();i++){
      while(!s.empty() && histogram[i]<= histogram[s.top()]){
        height = histogram[s.top()];
        s.pop();
        //left and right boundary
        left = s.empty()? -1:s.top();
        right = i;
        cur_size = (right-left-1) * height;
        max_size = max(max_size , cur_size);
      }
      s.push(i);
    }
    //if there are still values in stack, it must has top as right most, otherwise will be popped out
    while(!s.empty()){
      height = histogram[s.top()];
      s.pop();
      left = s.empty()?-1:s.top();
      cur_size = (histogram.size()-left-1) * height;
      max_size = max(max_size , cur_size);
    }
    return max_size;
}

```
