<!-- START doctoc generated TOC please keep comment here to allow auto update -->
<!-- DON'T EDIT THIS SECTION, INSTEAD RE-RUN doctoc TO UPDATE -->
**Table of Contents**  *generated with [DocToc](https://github.com/thlorenz/doctoc)*

- [Stack/Queue](#stackqueue)
  - [Validate Stack sequence](#validate-stack-sequence)
  - [Min Stack](#min-stack)
  - [Stack To minic function call](#stack-to-minic-function-call)
  - [Other Stack Problem](#other-stack-problem)
    - [132 pattern](#132-pattern)
- [Monotonic stack/Deque](#monotonic-stackdeque)
  - [Dequeue: Update Largest/Smallest value in sliding window](#dequeue-update-largestsmallest-value-in-sliding-window)
    - [Example: Longest Continuous Subarray With Absolute Diff Less Than or Equal to Limit](#example-longest-continuous-subarray-with-absolute-diff-less-than-or-equal-to-limit)
  - [Monotonic stack](#monotonic-stack)
    - [Previous Larger and Next Larger](#previous-larger-and-next-larger)
    - [Previous less or Next Less](#previous-less-or-next-less)
    - [Monotonic stack applications: (min/Max in sub array problem)](#monotonic-stack-applications-minmax-in-sub-array-problem)
      - [Next Greater element](#next-greater-element)
      - [Next Greater with length calculation](#next-greater-with-length-calculation)
        - [Stock Span](#stock-span)
        - [Daily Temperature](#daily-temperature)
      - [Minimum Cost Tree From Leaf Values](#minimum-cost-tree-from-leaf-values)
    - [Remove K digits](#remove-k-digits)
    - [Max tree](#max-tree)
  - [Largest Area](#largest-area)
    - [Largest Rectangle in Histogram](#largest-rectangle-in-histogram)
    - [Max Rectangle(histogram approach)](#max-rectanglehistogram-approach)
    - [Trap Rain water](#trap-rain-water)

<!-- END doctoc generated TOC please keep comment here to allow auto update -->

# Stack/Queue

## Validate Stack sequence

https://leetcode.com/problems/validate-stack-sequences/

Given two sequences pushed and popped with distinct values, return true if and only if this could have been the result of a sequence of push and pop operations on an initially empty stack.

 
```
Example 1:

Input: pushed = [1,2,3,4,5], popped = [4,5,3,2,1]
Output: true
Explanation: We might do the following sequence:
push(1), push(2), push(3), push(4), pop() -> 4,
push(5), pop() -> 5, pop() -> 3, pop() -> 2, pop() -> 1
Example 2:

Input: pushed = [1,2,3,4,5], popped = [4,3,5,1,2]
Output: false
Explanation: 1 cannot be popped before 2.
```

```CPP
bool validateStackSequences(vector<int>& pushed, vector<int>& popped) {
    stack<int> stack;
    int i = 0;
    for (int x : pushed) {
        stack.push(x);
        //Each time, we'll try to pop the elements from as many as possibile popped.
        while (stack.size() && stack.top() == popped[i]) {
            stack.pop();
            i++;
        }
    }
    return stack.size() == 0;
}
```

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

## Stack To minic function call

https://leetcode.com/problems/exclusive-time-of-functions/#/description


Given the running logs of n functions that are executed in a nonpreemptive single threaded CPU, find the exclusive time of these functions.
Each function has a unique id, start from 0 to n-1. A function may be called recursively or by another function.
A log is a string has this format : function_id:start_or_end:timestamp. For example, "0:start:0" means function 0 starts from the very beginning of time 0. "0:end:0" means function 0 ends to the very end of time 0.
Exclusive time of a function is defined as the time spent within this function, the time spent by calling other functions should not be considered as this function's exclusive time. You should return the exclusive time of each function sorted by their function id.

Example 1:
Input:
n = 2
logs =
["0:start:0",
 "1:start:2",
 "1:end:5",
 "0:end:6"]
Output:[3, 4]
Explanation:
Function 0 starts at time 0, then it executes 2 units of time and reaches the end of time 1.
Now function 0 calls function 1, function 1 starts at time 2, executes 4 units of time and end at time 5.
Function 0 is running again at time 6, and also end at the time 6, thus executes 1 unit of time.
So function 0 totally execute 2 + 1 = 3 units of time, and function 1 totally execute 4 units of time.

```CPP
vector<int> exclusiveTime(int n, vector<string>& logs) {
    vector<int> ret(n,0); //func id as index, time is value
    stack<pair<int,int>> s; //func id, current execution time, when start, push, when end, pop

    for(int i=0;i<logs.size();i++){
        int index = 0;
        int id = checkid(logs[i],index);
        int label = checklabel(logs[i],index);
        int t = checktime(logs[i],index);
        if(label==0){
            s.push(make_pair(id,t));
        }else{
            pair<int,int> cur = s.top();
            int last = t-cur.second+1;
            ret[cur.first]+=last;
            s.pop();
            if (!s.empty()) {
              //to remove over count, not time for s.top().first id
                ret[s.top().first] -= last;
            }
        }
    }


    return ret;
}

int checkid(string s, int &index){
    int ret = 0;
    while(index<s.size()){
        if(s[index]==':'){
            index++;
            break;
        }
        ret = ret*10+s[index]-'0';
        index++;
    }
    return ret;
}

int checklabel(string s,int &index){
    int ret = 0;

    if(s[index]=='s'){
        index = index + 6;
        ret = 0;
    }else{
        index = index + 4;
        ret = 1;
    }
    return ret;
}

int checktime(string s, int &index){
    int ret = 0;
    while(index<s.size()){
        ret = ret*10+s[index]-'0';
        index++;
    }
    return ret;
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

### 132 pattern

https://leetcode.com/problems/132-pattern/

Given a sequence of n integers a1, a2, ..., an, a 132 pattern is a subsequence ai, aj, ak such that i < j < k and ai < ak < aj. Design an algorithm that takes a list of n numbers as input and checks whether there is a 132 pattern in the list.

Note: n will be less than 15,000.
Example 1:

Input: [1, 2, 3, 4]
Output: False
Explanation: There is no 132 pattern in the sequence.

Example 2:
Input: [3, 1, 4, 2]
Output: True

Explanation: There is a 132 pattern in the sequence: [1, 4, 2].

Example 3:
Input: [-1, 3, 2, 0]
Output: True
Explanation: There are three 132 patterns in the sequence: [-1, 3, 2], [-1, 3, 0] and [-1, 2, 0].

```CPP
bool find132pattern(vector<int>& nums) {
  /*
  Have a stack, each time we store a new number, we first pop out all numbers that are smaller than that number. The numbers that are popped out becomes candidate for s3.
  We keep track of the maximum of such s3. Once we encounter any number smaller than s3, we know we found a valid sequence since s1 < s3 implies s1 < s2.
  */

    int s3=INT_MIN;
    stack<int> s; //for s3, top will be max s3 value;
    for(int i=nums.size()-1;i>=0;i--){
        if(nums[i]<s3)
            return true;
        else{
            while(!s.empty() && nums[i]>s.top()){
                s3 = max(s3,s.top());
                s.pop();
            }
        }
        s.push(nums[i]);
    }

    return false;
}

```

# Monotonic stack/Deque


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

### Example: Longest Continuous Subarray With Absolute Diff Less Than or Equal to Limit

https://leetcode.com/problems/longest-continuous-subarray-with-absolute-diff-less-than-or-equal-to-limit/

Given an array of integers nums and an integer limit, return the size of the longest non-empty subarray such that the absolute difference between any two elements of this subarray is less than or equal to limit.

 
```
Example 1:

Input: nums = [8,2,4,7], limit = 4
Output: 2 
Explanation: All subarrays are: 
[8] with maximum absolute diff |8-8| = 0 <= 4.
[8,2] with maximum absolute diff |8-2| = 6 > 4. 
[8,2,4] with maximum absolute diff |8-2| = 6 > 4.
[8,2,4,7] with maximum absolute diff |8-2| = 6 > 4.
[2] with maximum absolute diff |2-2| = 0 <= 4.
[2,4] with maximum absolute diff |2-4| = 2 <= 4.
[2,4,7] with maximum absolute diff |2-7| = 5 > 4.
[4] with maximum absolute diff |4-4| = 0 <= 4.
[4,7] with maximum absolute diff |4-7| = 3 <= 4.
[7] with maximum absolute diff |7-7| = 0 <= 4. 
Therefore, the size of the longest subarray is 2.
Example 2:

Input: nums = [10,1,2,4,7,2], limit = 5
Output: 4 
Explanation: The subarray [2,4,7,2] is the longest since the maximum absolute diff is |2-7| = 5 <= 5.
```


```CPP
int longestSubarray(vector<int>& nums, int limit) {
        //record high and low in each subarray
      deque<int> maxq;
      deque<int> minq;
      int i=0, j;
      int ret =1;
      for (j=0;j<nums.size();j++){
          //maxq monotonically decrease from front
          while(!maxq.empty() && nums[j]>maxq.back())
              maxq.pop_back();
          //minq monotonically increase from front
          while(!minq.empty() && nums[j]<minq.back())
              minq.pop_back();
          
          maxq.push_back(nums[j]);
          minq.push_back(nums[j]);
          
          //reduce the window size
          while(maxq.front()-minq.front()>limit){
              
              if(maxq.front()==nums[i])
                  maxq.pop_front();
              if(minq.front()==nums[i])
                  minq.pop_front();
              
              i++;
          }
          ret = max(ret, j - i + 1);
          
      }
      return ret;
}
```

## Monotonic stack 

### Previous Larger and Next Larger


> For a input size N array, return size N pairs of values (left, right), in which left is the cloest larger value from left side of current item, and right is the cloest larger value from right side of current item

* monotonic stack, values are increasing from top to bottom

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

### Previous less or Next Less

* Key idea is to maintain a monotonic decreasing stack, values are decreasing from top to bottom

> find the previous less element of each element in a vector with O(n) time:


What is the previous less element of an element?

```
For example:
[3, 7, 8, 4]
The previous less element of 7 is 3.
The previous less element of 8 is 7.
The previous less element of 4 is 3.
There is no previous less element for 3.
```

```CPP
// previous_less[i] = j means A[j] is the previous less element of A[i].
// previous_less[i] = -1 means there is no previous less element of A[i].
vector<int> previous_less(A.size(), -1);
for(int i = 0; i < A.size(); i++){
  while(!s.empty() && A[s.top()] > A[i]){
    s.pop();
  }
  previous_less[i] = s.empty()? -1: s.top();
  s.push(i);
}
```

> find the next less element of each element in a vector with O(n) time:


What is the next less element of an element?

```
For example:
[3, 7, 8, 4]
The next less element of 8 is 4.
The next less element of 7 is 4.
There is no next less element for 3 and 4.
```

```CPP
// next_less[i] = j means A[j] is the next less element of A[i].
// next_less[i] = -1 means there is no next less element of A[i].
vector<int> next_less(A.size(), -1);
for(int i = 0; i < A.size(); i++){
  while(!s.empty() && A[s.top()] > A[i]){
    auto x = s.top(); 
    s.pop();
    next_less[x] = i;
  }
  s.push(i);
}
```


### Monotonic stack applications: (min/Max in sub array problem)

#### Next Greater element

https://leetcode.com/problems/next-greater-element-i/

You are given two arrays (without duplicates) nums1 and nums2 where nums1’s elements are subset of nums2. Find all the next greater numbers for nums1's elements in the corresponding places of nums2.

The Next Greater Number of a number x in nums1 is the first greater number to its right in nums2. If it does not exist, output -1 for this number.

```

Example 1:
Input: nums1 = [4,1,2], nums2 = [1,3,4,2].
Output: [-1,3,-1]
Explanation:
    For number 4 in the first array, you cannot find the next greater number for it in the second array, so output -1.
    For number 1 in the first array, the next greater number for it in the second array is 3.
    For number 2 in the first array, there is no next greater number for it in the second array, so output -1.
Example 2:
Input: nums1 = [2,4], nums2 = [1,2,3,4].
Output: [3,-1]
Explanation:
    For number 2 in the first array, the next greater number for it in the second array is 3.
    For number 4 in the first array, there is no next greater number for it in the second array, so output -1.

```

```CPP
vector<int> nextGreaterElement(vector<int>& nums1, vector<int>& nums2) {
        //We use a stack to keep a decreasing whenever we see a number x greater than stack.top() we pop all elements less than x and for all the popped ones, their next greater element is x
        
        int len = nums1.size();
        
        stack<int> s;
        //use a map to record num->next greater
        unordered_map<int,int> m;
        vector<int> ret(len,-1);
        
        for(int i=0;i<nums2.size();i++){
            while(!s.empty() && nums2[i]>s.top()){
                m[s.top()]=nums2[i];
                s.pop();
            }
            s.push(nums2[i]);
        }
        
        for(int i=0;i<nums1.size();i++){
            if(m.find(nums1[i])==m.end()){
                ret[i] = -1;
            }else{
                ret[i] = m[nums1[i]];
            }
        }
        
        return ret;
    }
```

https://leetcode.com/problems/next-greater-element-ii/

Given a circular array (the next element of the last element is the first element of the array), print the Next Greater Number for every element. The Next Greater Number of a number x is the first greater number to its traversing-order next in the array, which means you could search circularly to find its next greater number. If it doesn't exist, output -1 for this number.

```
Example 1:
Input: [1,2,1]
Output: [2,-1,2]
Explanation: The first 1's next greater number is 2; 
The number 2 can't find next greater number; 
The second 1's next greater number needs to search circularly, which is also 2.
```

Similar idea as before, but we can just store index here

```CPP
vector<int> nextGreaterElements(vector<int>& nums) {
    //stack is decreaseing
    int len = nums.size();
    vector<int> ret(len,-1);
    //store index here
    stack<int> s;
    
    //loop 2Xlen as it is circular
    for(int i=0;i<2*len;i++){
        while(!s.empty() && nums[s.top()]<nums[i%len]){
            ret[s.top()]=nums[i%len];
            s.pop();
        }
        if(i<len)
            s.push(i);
    }
    
    return ret;
}
```

#### Next Greater with length calculation

> Same as most array problem, we can use other count to record like up to  count or index

##### Stock Span 


https://leetcode.com/problems/online-stock-span/

Write a class StockSpanner which collects daily price quotes for some stock, and returns the span of that stock's price for the current day.

The span of the stock's price today is defined as the maximum number of consecutive days (starting from today and going backwards) for which the price of the stock was less than or equal to today's price.

For example, if the price of a stock over the next 7 days were [100, 80, 60, 70, 60, 75, 85], then the stock spans would be [1, 1, 1, 2, 1, 4, 6].

 
```
Example 1:

Input: ["StockSpanner","next","next","next","next","next","next","next"], [[],[100],[80],[60],[70],[60],[75],[85]]
Output: [null,1,1,1,2,1,4,6]
Explanation: 
First, S = StockSpanner() is initialized.  Then:
S.next(100) is called and returns 1,
S.next(80) is called and returns 1,
S.next(60) is called and returns 1,
S.next(70) is called and returns 2,
S.next(60) is called and returns 1,
S.next(75) is called and returns 4,
S.next(85) is called and returns 6.

Note that (for example) S.next(75) returned 4, because the last 4 prices
(including today's price of 75) were less than or equal to today's price.
```

```CPP
//Push every pair of <price, cnt> to a stack.
//cnt counts how many items in stack is smaller than current price
//monotonic decreasing stack
stack<pair<int,int>> s;
StockSpanner() {
    
}

int next(int price) {
    
    int cnt = 1;
    //default cnt is 1 including current itself
    
    while(!s.empty() && s.top().first<=price){
        cnt += s.top().second;
        s.pop();
    }
    s.push(make_pair(price, cnt));
    
    return cnt;
    
}
```

##### Daily Temperature

https://leetcode.com/problems/daily-temperatures/

Given a list of daily temperatures T, return a list such that, for each day in the input, tells you how many days you would have to wait until a warmer temperature. If there is no future day for which this is possible, put 0 instead.
```
For example, given the list of temperatures T = [73, 74, 75, 71, 69, 72, 76, 73], your output should be [1, 1, 4, 2, 1, 1, 0, 0].
```


```CPP
vector<int> dailyTemperatures(vector<int>& T) {

        //stack, <temp, index>, 
        //whne pop up, calculate current index to top index distance, which is how many days
        stack<pair<int,int>> s;
        int len = T.size();
        vector<int> ret(len,0);
        int cnt = 0;
        for (int i=0; i<len;i++){
            
            while(!s.empty() && s.top().first<T[i]){
                ret[s.top().second] = i-s.top().second;
                s.pop();
            }
            s.push(make_pair(T[i],i));
            
        }
        ret[len-1] =0; //always 0 for last
        
        return ret;
    }
```

#### Minimum Cost Tree From Leaf Values

https://leetcode.com/problems/minimum-cost-tree-from-leaf-values/

Given an array arr of positive integers, consider all binary trees such that:

Each node has either 0 or 2 children;
The values of arr correspond to the values of each leaf in an in-order traversal of the tree.  (Recall that a node is a leaf if and only if it has 0 children.)
The value of each non-leaf node is equal to the product of the largest leaf value in its left and right subtree respectively.
Among all possible binary trees considered, return the smallest possible sum of the values of each non-leaf node.  It is guaranteed this sum fits into a 32-bit integer.

 
```
Example 1:

Input: arr = [6,2,4]
Output: 32
Explanation:
There are two possible trees.  The first has non-leaf node sum 36, and the second has non-leaf node sum 32.

    24            24
   /  \          /  \
  12   4        6    8
 /  \               / \
6    2             2   4
```

```CPP
int mctFromLeafValues(vector<int>& arr) {
        //need to put larger node as close to root as possible, so they won't be used many times
        //search from smallest and next greater to construct, then we can remove them
        
        int res = 0;
        stack<int> s;
        s.push(INT_MAX); //since need to compare top and next top in stack, insert MAX to ensure stack has value
        for (int a : arr) {
            while (s.top() <= a) {
                int mid = s.top();
                s.pop();
                res += mid * min(s.top(), a);
            }
            s.push(a);
        }
        while(s.size()>2) {
            int tmp = s.top();
            s.pop();
            res += tmp*s.top();
        }
        return res;
        
    }
```

### Remove K digits

https://leetcode.com/problems/remove-k-digits/

Given a non-negative integer num represented as a string, remove k digits from the number so that the new number is the smallest possible.

Note:
The length of num is less than 10002 and will be ≥ k.
The given num does not contain any leading zero.

```
Example 1:

Input: num = "1432219", k = 3
Output: "1219"
Explanation: Remove the three digits 4, 3, and 2 to form the new number 1219 which is the smallest.
```

```CPP
 string removeKdigits(string num, int k) {
        //the is equivilent to pick up len-k digit to get the minimum
        string ret;
        int len = num.size();
        if( len == k) return string("0");
        //while the last number is larger than the new one, 
        // keep poping out the last number until a smaller one appears
        for(int i=0;i<num.size();i++){
            while(!ret.empty() && k>0 && ret.back()>num[i]){
                ret.pop_back();
                k--;
            }
            ret.push_back(num[i]);
        }
        //remianing is monotonitically increase
        // discard the last k digits
        // e.g. 123456 k=3
        while (k != 0){
            k--;
            ret.pop_back();
        }
        
       // for sol with leading zeros
        // e.g. 10200 k=1
        while(ret[0] == '0') ret.erase(0,1);
        
        return ret.length() == 0 ? "0" : ret;
    }
```


### Max tree 


https://leetcode.com/problems/maximum-binary-tree/

Given an integer array with no duplicates. A maximum tree building on this array is defined as follow:

The root is the maximum number in the array.
The left subtree is the maximum tree constructed from left part subarray divided by the maximum number.
The right subtree is the maximum tree constructed from right part subarray divided by the maximum number.
Construct the maximum tree by the given array and output the root node of this tree.

```

Example 1:
Input: [3,2,1,6,0,5]
Output: return the tree root node representing the following tree:

      6
    /   \
   3     5
    \    / 
     2  0   
       \
        1
```

We can use this monotonic stack way to create the max-tree:

1. For any value, check left and right cloest larger/smaller value.
2. compare these two, put itself as child of smaller between left and right.

It will be a binary tree, not necessary full balanced binary tree

```CPP
TreeNode* constructMaximumBinaryTree(vector<int>& nums) {
        //decreasing stack,  

        //For each number, we keep pop the stack until empty or a bigger number; 
        stack<TreeNode*> s;
        for(int i=0;i<nums.size();i++){
            TreeNode* node = new TreeNode(nums[i]);
            while(!s.empty() && s.top()->val<nums[i]){
                node->left = s.top();
                s.pop();
            }
            //only largest number in s, build right
            if (!s.empty()){
                s.top()->right = node;
            }
            s.push(node);
            
        }
        //Get bottom of stack, which is root
        TreeNode* ret;
        while(!s.empty()){
            ret = s.top();
            s.pop();
        }
        return ret;
    }
```




## Largest Area

### Largest Rectangle in Histogram

https://leetcode.com/problems/largest-rectangle-in-histogram/

Given n non-negative integers representing the histogram's bar height where the width of each bar is 1, find the area of largest rectangle in the histogram.

```CPP
int largestRectangleArea(vector<int>& heights) {
    //use a stack to track the index
    // push index if height[index] > height[top],
    //stack only has increasing height's index
    
    int ret = 0;
    heights.push_back(0); //no run time error.
    stack<int> index;
    for(int i=0;i<heights.size();i++){
        //we are not in continous height increase anymore, need to cal back all area until bar<current one 
        while(index.size()>0 && heights[index.top()] >= heights[i]){
            int h = heights[index.top()];
            index.pop();
            int left = index.size() > 0 ? index.top() : -1;
            int area = (i-1-left)*h;
            ret = ret>area?ret:area;
        }
        index.push(i);
    }
    return ret;
}
```

### Max Rectangle(histogram approach)

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
    //for each current bar in histogram, get all bars in stack> current bar
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

### Trap Rain water

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