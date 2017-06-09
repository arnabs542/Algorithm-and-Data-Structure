# Array

## Sub Array problem
> Common techniques
* solve the sub problem: the same problem mapping to subarry ending in current index i, so can get the results from i-1
* two pointer problem to get these longest/smallest problem
  * two pointers could start both from beginning: with different move forward conditions: likely in sum issue
  * from begin and end: product issue
* preprocess
  * Get the sum
  * get product from begin and end of array
* Hash table to record value, index/occur number

> __*Tips*__:
  * whether to record value into hashmap/set before and after process.  
  * insert special case for hash set/map, like index -1, value 0. etc, so sum calculation including sum from beging to current or sum of current item




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

### Longest substring length to make sure whole string is sorted
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


### Longest Sum SubArray Length: Subarray sum equal to target

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

### Follow up: subarray sum to multiple of k
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

### Subarray sum number that equals to certain target
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

### Max subarray sum
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

### Maximum Product Subarray
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

### Product of array except itself
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

### Local minimum

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

## 3Sum problems: Typical three pointers problems
> Common techniques
* Sort the array
* Fix the first pointer, and move the second and third
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

### Follow up: Number of triangles
There are lots of problem can be soled by similar idea

http://www.geeksforgeeks.org/find-number-of-triangles-possible/
Given an unsorted array of positive integers. Find the number of triangles that can be formed with three different array elements as three sides of triangles.

```CPP
int NumOfTriangles(vector<int> arr)
{
    int len = arr.size();
    sort(arr.begin(),arr.end());
    int ret = 0;

    for (int i = 0; i < len-2; i++)
    {
        //right most index
        int k = i+2;

        // Fix the second element
        for (int j = i+1; j < len; j++)
        {
            while (k < len && arr[i] + arr[j] > arr[k])
               ++k;

            ret += k - j - 1;
        }
    }

    return ret;
}

```

## Matrix(Rectangle) Problem

> * similar as array, usually divide this problem into row and col two array

### Largest Square with all 1 in the boundary
Given a matrix containing either 0 or 1 in each cell, find the square with the longest side containing all 1s in its boundary. Cells inside the square may contain either 0 or 1.

For example, given matrix

[
  [0, 1, 0, 1, 1]
  [0, 1, 1, 1, 0]
  [0, 1, 0, 1, 1]
  [1, 1, 1, 1, 1]
  [1, 1, 1, 1, 1]
]
The square with the maximum size containing all 1s in its boundary has top-left corner at (1,1) and bottom-right corner at (3, 3)


```CPP
//two help matrix:
//help1: starting from current position, how many consecutive 1 in right
//help2: starting from current position, how many consecutive 1 down

int getLargestSquareSide(vector<vector<int>> matrix){

  int row = matrix.size();
  int col = matrix[0].size();
  //starting from current position, how many consecutive 1 in right
  vector<vector<int>> right(row,vector<int>(col,0));
  //starting from current position, how many consecutive 1 down
  vector<vector<int>> down(row,vector<int>(col,0));
  int ret = 0;
  for(int i=0;i<row;i++){
    right[i][col-1]=matrix[i][col-1];
  }
  for(int j=0;j<col;j++){
    down[row-1][j-1]=matrix[row-1][j];
  }

  for(int i=row-2;i>=0;i--){
    for(int j=col-2;j>=0;j--){
      right[i][j] = matrix[i][j]==0?0:right[i+1][j]+1;
      down[i][j]=matrix[i][j]==0?0:down[i][j+1];
    }
  }
  //starting from largest size
  for(int size=min(row,col);size>0;size--){
    if(hasALloneBorder(size,right,down,row,col)){
      return size;
    }
  }
  return 0;

}

bool hasALloneBorder(int size, vector<vector<int>> &right, vector<vector<int>> &down,int row, int col){
  for(int i=0;i<=row-size;i++){
    for(int j=0;i<=col-size;j++){
      if(right[i][j]>=size && down[i][j]>=size && right[i+size-1][j]>=size && down[i][j+size-1]>=size)
        return true;
    }
  }
  return false;
}

```

### Maximal-square
https://leetcode.com/problems/maximal-square/#/description
Given a 2D binary matrix filled with 0's and 1's, find the largest square containing only 1's and return its area.

For example, given the following matrix:

1 0 1 0 0
1 0 1 1 1
1 1 1 1 1
1 0 0 1 0
Return 4.

```CPP
//similar as subarray, use dp to consider max square's edge len ending i,j
int maximalSquare(vector<vector<char>>& matrix) {
    int row = matrix.size();
    if(row==0)
        return 0;
    int col = matrix[0].size();


    //dp[i][j] is the max edge len for point ending (i,j)
    vector<vector<int>> dp(row,vector<int>(col,0));
    //first row and col
    int maxlen = 0;
    for(int i=0;i<row;i++){
        if(matrix[i][0]=='1'){
            dp[i][0] = 1;
            maxlen = 1;
        }
    }
    for(int j=0;j<col;j++){
        if(matrix[0][j]=='1'){
            dp[0][j] = 1;
            maxlen = 1;
        }
    }

    for(int i=1;i<row;i++){
        for(int j=1;j<col;j++){
            if(matrix[i][j]=='1'){
                //check from up left i-1,j-1, and current row [i][j-1], current col [i-1][j]
                dp[i][j] = min(min(dp[i-1][j],dp[i][j-1]),dp[i-1][j-1]) + 1;
                maxlen = maxlen>dp[i][j]?maxlen:dp[i][j];
            }else{
                dp[i][j] = 0;
            }
        }
    }

    return maxlen*maxlen;
}

```

## Histogram

Histogram problem includes like water container, max rectangle. etc.

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

# Stack/Queue

## Min Stack:

maintain a min stack that query  minimum value in stack is O(1). idea is to maintain two stacks, regular one and the other one whose peek/top records the min value

```CPP
//Basic idea is to maintain two stacks, regular one and the other one whose peek/top records the min value

stack<int> data_s; //regular stack
stack<int> min_s; //stack that records min val of current stack

void push(int input){
  if(min_s.empty() || min_s.top()>input){
    min_s.push(input);
  }else{
    min_s.push(min_s.top());
  }
  data_s.push(input);
}

void pop(){
  if(!min_s.empty())
     min_s.pop();
  if(!data_s.empty())
    data_s.pop();
}

int getMin(){
  if(!min_s.empty())
    return ERROR;
  return min_s.top();
}
```

## Convert a stack to Queue:

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

## Revert stack recursively without extra new stack:

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



## max-tree(Assume no duplicate values.)

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


## __monotonic stack__

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

[Max rectangle in matrix](https://leetcode.com/problems/maximal-rectangle)

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

 * Find the median value in data stream on the fly: https://leetcode.com/problems/find-median-from-data-stream/

 Design a median holder function: use two heaps: maxheap to hold the smaller half of data stream, and minheap to hold the larger half of data stream. Need to balance both heaps to same size(or one can only hold 1 more item )

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
