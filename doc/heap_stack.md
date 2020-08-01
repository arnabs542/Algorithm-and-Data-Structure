<!-- START doctoc generated TOC please keep comment here to allow auto update -->
<!-- DON'T EDIT THIS SECTION, INSTEAD RE-RUN doctoc TO UPDATE -->
**Table of Contents**  *generated with [DocToc](https://github.com/thlorenz/doctoc)*

- [Heap](#heap)
  - [K-th Largest/Smallest problem](#k-th-largestsmallest-problem)
    - [In array](#in-array)
    - [In stream](#in-stream)
    - [In Matrix](#in-matrix)
  - [Search in sorted list of vectors](#search-in-sorted-list-of-vectors)
  - [Two Heaps](#two-heaps)
    - [Find the median value in data stream on the fly:](#find-the-median-value-in-data-stream-on-the-fly)
    - [Max value with constraint](#max-value-with-constraint)
  - [Interval sort](#interval-sort)
  - [Rearrange:Hash Map with Priority queue](#rearrangehash-map-with-priority-queue)
    - [Rearrange String k Distance Apart](#rearrange-string-k-distance-apart)
    - [Task schedule](#task-schedule)
  - [Auto completion system](#auto-completion-system)
  - [Max Tree](#max-tree)
- [Stack/Queue](#stackqueue)
  - [Min Stack](#min-stack)
  - [Stack To minic function call](#stack-to-minic-function-call)
  - [Other Stack Problem](#other-stack-problem)
    - [132 pattern](#132-pattern)
- [Max/Min in Sub array: Monotonic stack or Deque](#maxmin-in-sub-array-monotonic-stack-or-deque)
  - [Dequeue: Update Largest/Smallest value in sliding window](#dequeue-update-largestsmallest-value-in-sliding-window)
    - [Example: Longest Continuous Subarray With Absolute Diff Less Than or Equal to Limit](#example-longest-continuous-subarray-with-absolute-diff-less-than-or-equal-to-limit)
  - [Monotonic stack](#monotonic-stack)
    - [Previous Larger and Next Larger](#previous-larger-and-next-larger)
    - [Previous less or Next Less](#previous-less-or-next-less)
    - [Max tree](#max-tree)
    - [Monotonic stack applications: (min/Max in sub array problem)](#monotonic-stack-applications-minmax-in-sub-array-problem)
      - [Next Greater element](#next-greater-element)
      - [Max Rectangle](#max-rectangle)

<!-- END doctoc generated TOC please keep comment here to allow auto update -->

# Heap

Heap is implemented as tree structure in logic view and array in physical view. Here is the basic operation

```
// parent
int parent(int root) {
    return root / 2;
}
// left child
int left(int root) {
    return root * 2;
}
// right child
int right(int root) {
    return root * 2 + 1;
}
```

Time complexity for construct the heap is:

```shell
O(N): 1*log(1)+2*log(2)...+n*log(n) = O(N)
```
## K-th Largest/Smallest problem

* Method 1: Sort and get the K-th, the drawback is complexity is ```Nlog(N)```

* Method 2: since we only interested in K-th, just use heap and complexity is ```Nlog(K)```, Use heap will be best. Also it can deal with the streaming case

### In array

https://leetcode.com/problems/kth-largest-element-in-an-array/

Find the kth largest element in an unsorted array. Note that it is the kth largest element in the sorted order, not the kth distinct element.

```
Example 1:

Input: [3,2,1,5,6,4] and k = 2
Output: 5
Example 2:

Input: [3,2,3,1,2,4,5,5,6] and k = 4
Output: 4
```

Note:
You may assume k is always valid, 1 ≤ k ≤ array's length.

```CPP
class Solution {
public:
    //for min heap, we need compare function which is not default less, but larger
    struct mycompare{
        bool operator()(int a, int b){
            return a>b;
        }
    };

    int findKthLargest(vector<int>& nums, int k) {
        //should have a min heap size k, where top is the minimum of max k values.
        priority_queue<int,vector<int>,mycompare> pq;
        for(int i=0;i<nums.size();i++){
            pq.push(nums[i]);
            if(pq.size()>k)
                pq.pop();
        }
        
        return pq.top();
    }
};
```

### In stream
we can expand this problem, let's see 

https://leetcode.com/problems/kth-largest-element-in-a-stream/

Design a class to find the kth largest element in a stream. Note that it is the kth largest element in the sorted order, not the kth distinct element.

Your KthLargest class will have a constructor which accepts an integer k and an integer array nums, which contains initial elements from the stream. For each call to the method KthLargest.add, return the element representing the kth largest element in the stream.

```
Example:

int k = 3;
int[] arr = [4,5,8,2];
KthLargest kthLargest = new KthLargest(3, arr);
kthLargest.add(3);   // returns 4
kthLargest.add(5);   // returns 5
kthLargest.add(10);  // returns 5
kthLargest.add(9);   // returns 8
kthLargest.add(4);   // returns 8
```

Note:
You may assume that nums' length ≥ k-1 and k ≥ 1.


```CPP
class KthLargest {
public:
    struct mycompare{
        bool operator()(int a, int b){
            return a>b;
        }
    };
    priority_queue<int,vector<int>,mycompare> pq;
    int len = 0;
    
    KthLargest(int k, vector<int>& nums) {
        len = k;
        //min heap, top is minimum of largest K
        for(int i=0;i<nums.size();i++){
            pq.push(nums[i]);
            if(pq.size()>k)
                pq.pop();
        }
    }
    
    int add(int val) {
        pq.push(val);
        if(pq.size()>len) 
            pq.pop();
        return pq.top();

    }
};
```

```CPP
class KthLargest {
public:
    KthLargest(int k, vector<int>& nums) {
        
    }
    
    int add(int val) {
        
    }
};

/**
 * Your KthLargest object will be instantiated and called as such:
 * KthLargest* obj = new KthLargest(k, nums);
 * int param_1 = obj->add(val);
 */
```


### In Matrix

https://leetcode.com/problems/kth-smallest-element-in-a-sorted-matrix/

Given a n x n matrix where each of the rows and columns are sorted in ascending order, find the kth smallest element in the matrix.

Note that it is the kth smallest element in the sorted order, not the kth distinct element.

```
Example:

matrix = [
   [ 1,  5,  9],
   [10, 11, 13],
   [12, 13, 15]
],
k = 8,

return 13.
```

Note:
You may assume k is always valid, 1 ≤ k ≤ n2.


```CPP
class Solution {
public:
    struct mycompare{
        bool operator()(pair<int,pair<int,int>> a, pair<int,pair<int,int>> b){
            return a.first>b.first;
        }
    };
    int kthSmallest(vector<vector<int>>& matrix, int k) {
        int n = matrix.size(); //n*n matrix
        //construct minheap, so top is min value.  item is int(val), and pair<> matrix index
        priority_queue <pair<int,pair<int,int>>, vector<pair<int,pair<int,int>>>, mycompare> pq;
        //insert all first col, 
        for(int i=0;i<n;i++){
            pq.push(make_pair(matrix[i][0],make_pair(i,0)));
        }
        //pick any value [row,col+1] where [row,col] is location of top of heap, so it is definitely larger than top of heap.
        //insert to heap, and pop top(min value)
        int ret;
        while(k--){
            int val=pq.top().first;
            int x=pq.top().second.first;
            int y=pq.top().second.second;
            ret = val;
            pq.pop();
            if(y<n-1){
                pq.push(make_pair(matrix[x][y+1],make_pair(x,y+1)));
            }
        }
        
        return ret;
    }
};

/* complexity will be K*log(Row) */
```

## Search in sorted list of vectors

Some problem exhibts like there are vectors with items are sorted vector, and need to do some stuffs

https://leetcode.com/articles/smallest-range/

You have k lists of sorted integers in ascending order. Find the smallest range that includes at least one number from each of the k lists.

We define the range [a,b] is smaller than range [c,d] if b-a < d-c or a < c if b-a == d-c.

```
Example 1:
Input:[[4,10,15,24,26], [0,9,12,20], [5,18,22,30]]
Output: [20,24]
Explanation:
List 1: [4, 10, 15, 24,26], 24 is in range [20,24].
List 2: [0, 9, 12, 20], 20 is in range [20,24].
List 3: [5, 18, 22, 30], 22 is in range [20,24].
```

```CPP
vector<int> smallestRange(vector<vector<int>>& nums) {
    typedef vector<int>::iterator vi;
    struct comp {
        bool operator()(pair<vi, vi> p1, pair<vi, vi> p2) {
            return * p1.first > * p2.first;
        }
    };

    int l = INT_MAX, h = INT_MIN;
    priority_queue<pair<vi, vi>, vector<pair<vi, vi>>, comp> pq;
    for(int i=0;i<nums.size();i++){
        l = min(l, nums[i][0]);
        h = max(h, nums[i][0]);
        pq.push(make_pair(nums[i].begin(), nums[i].end())); //min heap

    }
    vector<int> ret = {l,h};

    while(true){
        auto cur =pq.top();
        pq.pop();
        ++cur.first;
        if (cur.first == cur.second)   //reach one list's end
            break;
        pq.push(cur);  //push cur min's next item in vector
        l = * pq.top().first;
        h = max(h, * cur.first);
        if (h - l < ret[1] - ret[0])
            ret = {l, h};
    }
    return ret;
}

```

## Two Heaps

### Find the median value in data stream on the fly:

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

### Max value with constraint

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

## Interval sort


https://leetcode.com/problems/merge-intervals/

Given a collection of intervals, merge all overlapping intervals.

Example 1:

Input: [[1,3],[2,6],[8,10],[15,18]]
Output: [[1,6],[8,10],[15,18]]
Explanation: Since intervals [1,3] and [2,6] overlaps, merge them into [1,6].
Example 2:

Input: [[1,4],[4,5]]
Output: [[1,5]]
Explanation: Intervals [1,4] and [4,5] are considered overlapping.


```CPP
class Solution {
private:
    static bool mycompare(Interval s1, Interval s2){
        return s1.start<s2.start;
    }
public:
    vector<Interval> merge(vector<Interval>& intervals) {
        vector<Interval> ret;
        if(intervals.size()==0)
            return ret;
        sort(intervals.begin(),intervals.end(),mycompare);
        //direct compare with current one in vector, and push/modify the end
        ret.push_back(intervals[0]);
        for (int i = 1; i < intervals.size(); i++) {
            if(intervals[i].start>ret.back().end)
                ret.push_back(intervals[i]);
            else
                ret.back().end = max(ret.back().end,intervals[i].end);
        }

        return ret;
    }
};
```


https://leetcode.com/problems/meeting-rooms-ii/

Given an array of meeting time intervals consisting of start and end times [[s1,e1],[s2,e2],...] (si < ei), find the minimum number of conference rooms required.

For example,
Given [[0, 30],[5, 10],[15, 20]],
return 2.

```CPP
class Solution {
private:
  static bool mycompare(Interval s1, Interval s2){
      return s1.start<s2.start;
  }

  struct pq_compare{
      bool operator()(Interval& a, Interval& b){
          return a.end>b.end;
      }
  };
public:
  int minMeetingRooms(vector<Interval>& intervals) {
      if(intervals.size()==0)
          return 0;
      sort(intervals.begin(),intervals.end(),mycompare);
      priority_queue<Interval, vector<Interval>, pq_compare> pq;//maintain the earliest ends time, min queue
      int len = intervals.size();
      pq.push(intervals[0]);
      for(int i=1;i<len;i++){
          int cur_end = pq.top().end;
          if(intervals[i].start<cur_end){
              pq.push(intervals[i]); //if start time eariler, need a new room.
          }else{
              pq.pop();           //if start later than cur earilest end time, extend current room end time
              pq.push(intervals[i]);
          }
      }

      return pq.size();
  }
};
```

https://leetcode.com/problems/employee-free-time/

We are given a list schedule of employees, which represents the working time for each employee. Each employee has a list of non-overlapping Intervals, and these intervals are in sorted order. Return the list of finite intervals representing common, positive-length free time for all employees, also in sorted order.

Example 1:
Input: schedule = [[[1,2],[5,6]],[[1,3]],[[4,10]]]
Output: [[3,4]]
Explanation:
There are a total of three employees, and all common
free time intervals would be [-inf, 1], [3, 4], [10, inf].
We discard any intervals that contain inf as they aren't finite.
Example 2:
Input: schedule = [[[1,3],[6,7]],[[2,4]],[[2,5],[9,12]]]
Output: [[5,6],[7,9]]

```CPP
class Solution {
private:
  static bool mycompare(Interval s1, Interval s2){
      return s1.start<s2.start;
  };
public:
    vector<Interval> employeeFreeTime(vector<vector<Interval>>& schedule) {
        vector<Interval> res, v;
        for (auto a : schedule) {
            v.insert(v.end(), a.begin(), a.end());
        }
        sort(v.begin(), v.end(), mycompare);
        Interval t = v[0];
        for (Interval i : v) {
            if (t.end < i.start) {
                res.push_back(Interval(t.end, i.start));
                t = i;
            } else {
                t = (t.end < i.end) ? i : t;
            }
        }
        return res;
    }
};
```



## Rearrange:Hash Map with Priority queue


* we need to record both hash map with val representing count, and have another priority queue based on hash map val

* every round pop from priority queue, decrease count,

* re push back to priority_queue

### Rearrange String k Distance Apart

* Key idea is to use hash map and priority queue. hash map's key is char and val is how many times it appears, pq is to record via map's val

* Every time just to process map and pq. pop pq with counter decrease and re push to pq

https://leetcode.com/problems/rearrange-string-k-distance-apart/#/description

Given a non-empty string s and an integer k, rearrange the string such that the same characters are at least distance k from each other.
All input strings are given in lowercase letters. If it is not possible to rearrange the string, return an empty string "".

Example 1:
s = "aabbcc", k = 3
Result: "abcabc"

The same letters are at least distance 3 from each other.
Example 2:
s = "aaabc", k = 3
Answer: ""

It is not possible to rearrange the string.
Example 3:
s = "aaadbbcc", k = 2
Answer: "abacabcd"
Another possible answer is: "abcabcda"
The same letters are at least distance 2 from each other.

```CPP
string rearrangeString(string s, int k) {
    int len = s.size();
    if(k==0)
        return s;

    map<char,int> m;
    for(int i=0;i<s.size();i++){
        m[s[i]]++;
    }
    string ret = "";

    priority_queue<pair<int,char>> pq;  //count and char
    for(auto i:m){
        pq.push(make_pair(i.second,i.first)); //heap via char's occurence count
    }

    while(!pq.empty()){
        vector<pair<int,char>> tmp;
        int cnt = min(len,k);
        for(int i=0;i<cnt;i++){
            if(!pq.empty()){
                pair<int,char> cur = pq.top();
                if(--cur.first>0)
                    tmp.push_back(cur);
                ret+=cur.second;
                pq.pop();
                len--;
            }else{
                return "";
            }
        }
        for(int i=0;i<tmp.size();i++){
            pq.push(tmp[i]);
        }
    }

    return ret;
}
```

Another method
```CPP
string rearrangeString(string s, int k) {
    int len = s.size();
    if(k==0)
        return s;

    vector<int> cnt(26,0);
    for(int i=0;i<len;i++)
        cnt[s[i]-'a']++;
    string ret = "";
    //keep track of the most left position that one character can appear.
    vector<int> valid(26,0);

    for(int i=0;i<len;i++){
        int pos = findMaxleft(cnt, valid, i);
        if(pos==-1)
            return "";
        cnt[pos]--;
        valid[pos] = i+k;
        ret += char('a'+pos);

    }
    return ret;
}

int findMaxleft(vector<int> &cnt, vector<int> &valid, int index){
    int pos = -1;
    int v = INT_MIN;
    for(int i=0;i<cnt.size();i++){
       if(cnt[i]>0 && cnt[i]>v && index>=valid[i]){
           v = cnt[i];
           pos = i;
       }
   }
   return pos;
}
```

### Task schedule
https://leetcode.com/problems/task-scheduler/#/description
Given a char array representing tasks CPU need to do. It contains capital letters A to Z where different letters represent different tasks.Tasks could be done without original order. Each task could be done in one interval. For each interval, CPU could finish one task or just be idle.

However, there is a non-negative cooling interval n that means between two same tasks, there must be at least n intervals that CPU are doing different tasks or just be idle.

You need to return the least number of intervals the CPU will take to finish all the given tasks.

Example 1:
Input: tasks = ['A','A','A','B','B','B'], n = 2
Output: 8
Explanation: A -> B -> idle -> A -> B -> idle -> A -> B.

```CPP
int leastInterval(vector<char>& tasks, int n) {
    map<char,int> m;
    for(int i=0;i<tasks.size();i++){
        m[tasks[i]]++;
    }
    priority_queue<int> pq; //heap for task's count
    for(auto i:m){
        pq.push(i.second);
    }
    int ret = 0;
    int cycle = n+1;
    while(!pq.empty()){
        int t = 0;
        vector<int> tmp;
        for(int i=0;i<cycle;i++){
            if(!pq.empty()){
                tmp.push_back(pq.top());
                pq.pop();
                t++;
            }
        }
        for (int i=0;i<tmp.size();i++) {
            if (--tmp[i]>0) {
                pq.push(tmp[i]);
            }
        }
        ret += !pq.empty() ? cycle : t;
    }

    return ret;
}
```

## Auto completion system

https://leetcode.com/problems/design-search-autocomplete-system/description/

```CPP
struct mycompare{
  bool operator()(const pair<string, int> &a, const pair<string, int> &b){
    return a.second > b.second || a.second == b.second && a.first < b.first;
  }
};

AutocompleteSystem(vector<string> sentences, vector<int> times) {
    for (int i = 0; i < times.size(); i++)
        dict[sentences[i]] += times[i];
    data.clear();
}

vector<string> input(char c) {
    if (c == '#') {
        dict[data]++;
        data.clear();
        return {};
    }else{
        data+=c;
        priority_queue<pair<string, int>, vector<pair<string, int>>, mycompare> pq;
        for (auto &p : dict) {
            bool match = true;
            for (int i = 0; i < data.size(); i++) {
                if (data[i] != p.first[i]) {
                    match = false;
                    break;
                }
            }
            if (match) {
                pq.push(p);
                if (pq.size() > 3)
                    pq.pop();
            }
        }

        vector<string> res(pq.size());
        for (int i = pq.size() - 1; i >= 0; i--) {
            res[i] = pq.top().first;
            pq.pop();
        }
        return res;
    }
}
```

## Max Tree

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

# Max/Min in Sub array: Monotonic stack or Deque


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


### Max tree 


We can use this monotonic stack way to create the max-tree:

1. For any value, check left and right cloest larger/smaller value.
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

#### Max Rectangle

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