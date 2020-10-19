<!-- START doctoc generated TOC please keep comment here to allow auto update -->
<!-- DON'T EDIT THIS SECTION, INSTEAD RE-RUN doctoc TO UPDATE -->
**Table of Contents**  *generated with [DocToc](https://github.com/thlorenz/doctoc)*

- [Heap](#heap)
  - [K way Merge](#k-way-merge)
    - [Merge K sorted List](#merge-k-sorted-list)
    - [K-th Largest/Smallest problem](#k-th-largestsmallest-problem)
      - [K-th Largest in Array](#k-th-largest-in-array)
      - [K-th Smallest In stream](#k-th-smallest-in-stream)
      - [K smallest In M Sorted Lists](#k-smallest-in-m-sorted-lists)
      - [K smallest In Matrix](#k-smallest-in-matrix)
      - [K pairs of smallest Sum](#k-pairs-of-smallest-sum)
      - [smallest range in K lists](#smallest-range-in-k-lists)
  - [Top K Problem](#top-k-problem)
    - [K-th Smallest/Largest](#k-th-smallestlargest)
      - [K-th Cloest points](#k-th-cloest-points)
    - [Minimum Cost to Connect Sticks](#minimum-cost-to-connect-sticks)
    - [Top K frequent numbers](#top-k-frequent-numbers)
  - [Two Heaps](#two-heaps)
    - [Find the median value in data stream on the fly:](#find-the-median-value-in-data-stream-on-the-fly)
    - [Sliding Window Median(Find Median in stream)](#sliding-window-medianfind-median-in-stream)
    - [Maximize Capital/IPO](#maximize-capitalipo)
    - [Find Next Interval](#find-next-interval)
  - [Interval sort](#interval-sort)
    - [Merge Interval](#merge-interval)
    - [Meeting room needed](#meeting-room-needed)
    - [Common Free time](#common-free-time)
  - [Rearrange:Hash Map with Priority queue](#rearrangehash-map-with-priority-queue)
    - [Rearrange String k Distance Apart](#rearrange-string-k-distance-apart)
    - [Task schedule](#task-schedule)
  - [Auto completion system](#auto-completion-system)
  - [Other Heap Problem](#other-heap-problem)
    - [Define own compare func:Top K Frequent Words](#define-own-compare-functop-k-frequent-words)

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

## K way Merge

Whenever we are given ‘K’ sorted arrays, we can use a Heap to efficiently perform a sorted traversal of all the elements of all arrays. 

### Merge K sorted List

https://leetcode.com/problems/merge-k-sorted-lists/

You are given an array of k linked-lists lists, each linked-list is sorted in ascending order.

Merge all the linked-lists into one sorted linked-list and return it.

 
```
Example 1:

Input: lists = [[1,4,5],[1,3,4],[2,6]]
Output: [1,1,2,3,4,4,5,6]
Explanation: The linked-lists are:
[
  1->4->5,
  1->3->4,
  2->6
]
merging them into one sorted list:
1->1->2->3->4->4->5->6
```

```CPP
class Solution {
public:
    struct mycompare{
        bool operator()(ListNode* a, ListNode* b){
            return a->val>b->val;
        }
    };

    ListNode* mergeKLists(vector<ListNode*>& lists) {
        ListNode* ret = NULL;

        //construct min heap
        priority_queue<ListNode*, vector<ListNode*>, mycompare> pq; 
        ListNode* dummy = new ListNode(0);
        ListNode* head = dummy;
        for(int i=0; i<lists.size(); i++){ 
            if(lists[i]){ 
                pq.push(lists[i]);
            }
        }

        while(!pq.empty()){
            head->next = pq.top();
            head = head->next;
            if(head->next)
                pq.push(head->next);
            pq.pop();
        }
        
        return dummy->next;
        
    }
};
```

### K-th Largest/Smallest problem

since we only interested in K-th, just use heap and complexity is ```Nlog(K)```


#### K-th Largest in Array

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

* __min-heap__ heap top is minimum of K maximum numbers, which is K-th largest

```CPP
class Solution {
public:
    int findKthLargest(vector<int>& nums, int k) {
        priority_queue<int, vector<int>, greater<int>> pq;
        for (int num : nums) {
            pq.push(num);
            if (pq.size() > k) {
                pq.pop();
            }
        }
        return pq.top();
    }
};
```


* __max-heap__ heap top is max, so if we pop K-1 numbers, we pop K-1 larger number , and remaining is K-th largest

```CPP
class Solution {
public:
    int findKthLargest(vector<int>& nums, int k) {
        priority_queue<int> pq(nums.begin(), nums.end());
        for (int i = 0; i < k - 1; i++) {
            pq.pop();
        }
        return pq.top();
    }
};
```

#### K-th Smallest In stream
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

#### K smallest In M Sorted Lists

https://www.educative.io/courses/grokking-the-coding-interview/myAqDMyRXn3

Given ‘M’ sorted arrays, find the K’th smallest number among all the arrays.

```
Example 1:

Input: L1=[2, 6, 8], L2=[3, 6, 7], L3=[1, 3, 4], K=5
Output: 4
Explanation: The 5th smallest number among all the arrays is 4, this can be verified from the merged 
list of all the arrays: [1, 2, 3, 3, 4, 6, 6, 7, 8]
Example 2:

Input: L1=[5, 8, 9], L2=[1, 7], K=3
Output: 7
Explanation: The 3rd smallest number among all the arrays is 7.
```

```CPP

// the input is a list of arrays compared to LinkedLists. This means that when we want to push the next number in the heap we need to know what the index of the current number in the current array was.

struct valueCompare {
    bool operator()(const pair<int, pair<int, int>> &x, const pair<int, pair<int, int>> &y) {
      return x.first > y.first;
    }
  };

  static int findKthSmallest(const vector<vector<int>> &lists, int k) {
    priority_queue<pair<int, pair<int, int>>, vector<pair<int, pair<int, int>>>, valueCompare>
        minHeap;

    // put the 1st element of each array in the min heap, along with indexes in 2 d vector
    for (int i = 0; i < lists.size(); i++) {
      if (!lists[i].empty()) {
        pq.push(make_pair(lists[i][0], make_pair(i, 0)));
      }
    }

    // take the smallest (top) element form the min heap, if the running count is equal to k 
    // we have taken k minimum already, return 

    int numberCount = 0, result;
    while (!minHeap.empty()) {
      auto cur = minHeap.top();
      minHeap.pop();
      result = cur.first;
      if (++numberCount == k) {
        break;
      }
      cur.second.second++; //go to next col in current row
      //if within boudary
      if (lists[cur.second.first].size() > cur.second.second) {
        cur.first = lists[cur.second.first][cur.second.second];
        minHeap.push(cur);
      }
    }

    return result;
  }
```

* We can also use Max Heap to solve this problem, insert all into heap, and limit Heap size to K, so finally top is max of K minimum items, which is K-th smallest


```CPP
 public:
  struct valueCompare {
    bool operator()(const pair<int, pair<int, int>> &x, const pair<int, pair<int, int>> &y) {
      return x.first > y.first;
    }
  };

  static int findKthSmallest(const vector<vector<int>> &lists, int k) {
    priority_queue<pair<int, pair<int, int>>, vector<pair<int, pair<int, int>>>, valueCompare>
        maxHeap;

    // put the 1st element of each array in the min heap
    for (int i = 0; i < lists.size(); i++) {
      for (int j = 0; j < lists[i].size(); j++) {
        maxHeap.push(make_pair(lists[i][0], make_pair(i, 0)));
        if (maxHeap.size() > k) {
          maxHeap.pop();
      }
      }
    }


    return maxHeap.top().first;
  }
```


#### K smallest In Matrix

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
        //after pop K-1 times(K-1 smaller value, next is K-th smallest)
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



#### K pairs of smallest Sum

https://leetcode.com/problems/find-k-pairs-with-smallest-sums/

https://www.educative.io/courses/grokking-the-coding-interview/B1JKxRB8EDJ

You are given two integer arrays nums1 and nums2 sorted in ascending order and an integer k.
Define a pair (u,v) which consists of one element from the first array and one element from the second array.
Find the k pairs (u1,v1),(u2,v2) ...(uk,vk) with the smallest sums.

```CPP
private:
    struct mycompare{
        bool operator()(pair<int, int>& p1, pair<int, int>& p2){
            return p1.first + p1.second < p2.first + p2.second;
        }
    };
public:
    vector<pair<int,int>> kSmallestPairs(vector<int>& nums1, vector<int>& nums2, int k) {
        vector<pair<int,int>> ret;
        //Max heap, keep K smalleset values, top is max of K items in heap

        priority_queue<pair<int, int>, vector<pair<int, int>>, mycompare> pq;
        for(int i=0;i<nums1.size();i++){
            for(int j=0;j<nums2.size();j++){
                if(pq.size()<k){
                    pq.push(make_pair(nums1[i],nums2[j]));
                }else{
                    pair<int,int> cur_max = pq.top();
                    pair<int,int> newone = make_pair(nums1[i],nums2[j]);
                    //upcomming < top, 
                    if(cur_max.first+cur_max.second>nums1[i] + nums2[j]){
                        pq.push(newone);
                        pq.pop();
                    }else{
                      //since it is increasing array, from then on, we can not fin any pairs which is smaller 
                      break;
                    }
                        
                }
            }
        }
        
        while(!pq.empty()){
            ret.push_front(pq.top());
            pq.pop();
        }
        return ret;
    }
```

#### smallest range in K lists

https://leetcode.com/problems/smallest-range-covering-elements-from-k-lists/

https://www.educative.io/courses/grokking-the-coding-interview/JPGWDNRx3w2

Given ‘M’ sorted arrays, find the smallest range that includes at least one number from each of the ‘M’ lists.

```
Example 1:

Input: L1=[1, 5, 8], L2=[4, 12], L3=[7, 8, 10]
Output: [4, 7]
Explanation: The range [4, 7] includes 5 from L1, 4 from L2 and 7 from L3.
Example 2:

Input: L1=[1, 9], L2=[4, 12], L3=[7, 10, 16]
Output: [9, 12]
Explanation: The range [9, 12] includes 9 from L1, 12 from L2 and 10 from L3.
```

We can start by inserting the first number from all the arrays in a min-heap. We will keep track of the largest number that we have inserted in the heap (let’s call it currentMaxNumber).

In a loop, we’ll take the smallest (top) element from the min-heap andcurrentMaxNumber has the largest element that we inserted in the heap. If these two numbers give us a smaller range, we’ll update our range.

```CPP
vector<int> smallestRange(vector<vector<int>>& nums) {
        typedef vector<int>::iterator vi;
        struct comp {
            bool operator()(pair<vi, vi> p1, pair<vi, vi> p2) {
                return *p1.first > *p2.first;
            }
        }; 
        
        int l = INT_MAX, h = INT_MIN;
        priority_queue<pair<vi, vi>, vector<pair<vi, vi>>, comp> pq;
        for(int i=0;i<nums.size();i++){
            l = min(l, nums[i][0]);
            h = max(h, nums[i][0]);
            //min heap based on low bound, what stored is iterator, which we can use ++ to go to next in vector.
            pq.push(make_pair(nums[i].begin(), nums[i].end())); 
            
        }
        vector<int> ret = {l,h};
        
        while(true){
            auto cur =pq.top();
            pq.pop();
            ++cur.first; //go to next in current min's vector
            if (cur.first == cur.second)   //reach one list's end
                break;
            pq.push(cur);  //push cur min's next item in vector
            //update both low and high
            l = *pq.top().first;
            h = max(h, *cur.first);
            if (h - l < ret[1] - ret[0])
                ret = {l, h};
            
            
        }
        
        return ret;
        
    }
```

## Top K Problem

### K-th Smallest/Largest

```CPP
static int findKthSmallestNumber(const vector<int> &nums, int k) {
    priority_queue<int> maxHeap; //top is max out of K nums, so it is K- smallest

    // put first k numbers in the max heap
    for (int i = 0; i < k; i++) {
      maxHeap.push(nums[i]);
    }

    // go through the remaining numbers of the array, if the number from the array is smaller than
    // the top (biggest) number of the heap, remove the top number from heap and add the number from
    // array
    for (int i = k; i < nums.size(); i++) {
      if (nums[i] < maxHeap.top()) {
        maxHeap.pop();
        maxHeap.push(nums[i]);
      }
    }

    // the root of the heap has the Kth smallest number
    return maxHeap.top();
  }
```

#### K-th Cloest points

https://leetcode.com/problems/k-closest-points-to-origin/

We have a list of points on the plane.  Find the K closest points to the origin (0, 0).

(Here, the distance between two points on a plane is the Euclidean distance.)

You may return the answer in any order.  The answer is guaranteed to be unique (except for the order that it is in.)

 
```
Example 1:

Input: points = [[1,3],[-2,2]], K = 1
Output: [[-2,2]]
Explanation: 
The distance between (1, 3) and the origin is sqrt(10).
The distance between (-2, 2) and the origin is sqrt(8).
Since sqrt(8) < sqrt(10), (-2, 2) is closer to the origin.
We only want the closest K = 1 points from the origin, so the answer is just [[-2,2]].
```

```CPP
struct compare {
    bool operator()(vector<int>& p, vector<int>& q) {
        return p[0] * p[0] + p[1] * p[1] < q[0] * q[0] + q[1] * q[1];
    }
};

int dist(vector<int> p) {
    return (p[0] * p[0]) + (p[1] * p[1]);
}

vector<vector<int>> kClosest(vector<vector<int>>& points, int K) {
     vector<vector<int>> ret;
    //max heap, K cloest value, top is farest out of all smallest K 
    
    priority_queue<vector<int>, vector<vector<int>>, compare> maxHeap;
    for (int i=0;i<K;i++) {
        maxHeap.push(points[i]);
    }
    
    for (int i=K;i<points.size();i++){
        vector<int> cur = maxHeap.top();
        if(dist(points[i])<dist(cur)){
            maxHeap.pop();
            maxHeap.push(points[i]);
        }
    }
    
    while(!maxHeap.empty()){
        ret.push_back(maxHeap.top());
        maxHeap.pop();
    }
    return ret;
    
}
```

### Minimum Cost to Connect Sticks
https://leetcode.com/problems/minimum-cost-to-connect-sticks/

You have some sticks with positive integer lengths.

You can connect any two sticks of lengths X and Y into one stick by paying a cost of X + Y.  You perform this action until there is one stick remaining.

Return the minimum cost of connecting all the given sticks into one stick in this way.

```

Example 1:

Input: sticks = [2,4,3]
Output: 14
Example 2:

Input: sticks = [1,8,3,5]
Output: 30
```

```CPP
    int connectSticks(vector<int>& sticks) {
        //min pq, so each time just add up top 2
        priority_queue<int, vector<int>, greater<int>> pq(sticks.begin(), sticks.end());
        int ret = 0;
        while (pq.size() > 1) {
            int a = pq.top(); 
            pq.pop();
            int b = pq.top(); 
            pq.pop();
            ret += a + b;
            //combine to 1 stick
            pq.push(a + b);
        }
        return ret;
    }
```

### Top K frequent numbers

https://leetcode.com/problems/top-k-frequent-elements/



```CPP
struct comparePair {
    bool operator()(pair<int, int> p, pair<int, int> q) {
        return p.second>q.second;
    }
};

class Solution {
public:
    vector<int> topKFrequent(vector<int>& nums, int k) {
        //use heap sort to achieven o(log(n)) time complexity 
        unordered_map<int,int> m;
        
        vector<int> ret;
        for(int i=0;i<nums.size();i++){
            m[nums[i]] ++;
        }
        
        priority_queue<pair<int, int>, vector<pair<int, int>>, comparePair> minHeap;
        
        for(auto it: m){
            
            if(minHeap.size()<k){
                minHeap.push(it);
            }else{
                if(minHeap.top().second<it.second){
                    minHeap.pop();
                    minHeap.push(it);
                }
            }
        }
        
        for(int i=0;i<k;i++){
            ret.push_back(minHeap.top().first);
            minHeap.pop();
        }
        reverse(ret.begin(), ret.end());
        
        return ret;
    }
};
```

## Two Heaps

In many problems, where we are given a set of elements such that we can divide them into two parts. To solve the problem, we are interested in knowing the smallest element in one part and the biggest element in the other part. This pattern is an efficient approach to solve such problems.

This pattern uses two Heaps to solve these problems; A Min Heap to find the smallest element and a Max Heap to find the biggest element.

### Find the median value in data stream on the fly:

Design a median holder function: use two heaps: maxheap to hold the smaller half of data stream, and minheap to hold the larger half of data stream. Need to balance both heaps to same size(or one can only hold 1 more item )
https://leetcode.com/problems/find-median-from-data-stream/

```CPP
 //two heaps: max_half has max half nums, min_half has small half nums
 priority_queue<int> maxHeap;  //max heap: top of min_half heap is max value in min heap
 priority_queue<int, vector<int>, mycompare> minHeap; //min heap: top of max_half heap is min value of max heap

 struct mycompare{
    bool operator()(int a, int b){
        return a>b;
    }
};


 // Adds a number into the data structure.
 void addNum(int num) {

    if (maxHeap.empty() || maxHeap.top() >= num) {
      maxHeap.push(num);
    } else {
      minHeap.push(num);
    }

    // either both the heaps will have equal number of elements or max-heap will have one
    // more element than the min-heap
    if (maxHeap.size() > minHeap.size() + 1) {
      minHeap.push(maxHeap.top());
      maxHeap.pop();
    } else if (maxHeap.size() < minHeap.size()) {
      maxHeap.push(minHeap.top());
      minHeap.pop();
    }

 }

 // Returns the median of current data stream
 double findMedian() {
    if (maxHeap.size() == minHeap.size()) {
      // we have even number of elements, take the average of middle two elements
      return maxHeap.top() / 2.0 + minHeap.top() / 2.0;
    }
    // because max-heap will have one more element than the min-heap
    return maxHeap.top();
 }
```

### Sliding Window Median(Find Median in stream)

https://www.educative.io/courses/grokking-the-coding-interview/3Y9jm7XRrXO

https://leetcode.com/problems/sliding-window-median/

Given an array of numbers and a number ‘k’, find the median of all the ‘k’ sized sub-arrays (or windows) of the array.
```
Example 1:

Input: nums=[1, 2, -1, 3, 5], k = 2
Output: [1.5, 0.5, 1.0, 4.0]
Explanation: Lets consider all windows of size ‘2’:

[1, 2, -1, 3, 5] -> median is 1.5
[1, 2, -1, 3, 5] -> median is 0.5
[1, 2, -1, 3, 5] -> median is 1.0
[1, 2, -1, 3, 5] -> median is 4.0
```



### Maximize Capital/IPO

https://www.educative.io/courses/grokking-the-coding-interview/B6x69OLX4jY

https://leetcode.com/problems/ipo/

 You are given several projects. For each project i, it has a pure profit Pi and a minimum capital of Ci is needed to start the corresponding project. Initially, you have W capital. When you finish a project, you will obtain its pure profit and the profit will be added to your total capital.


```
Example 1:

Input: Project Capitals=[0,1,2], Project Profits=[1,2,3], Initial Capital=1, Number of Projects=2
Output: 6
Explanation:

With initial capital of ‘1’, we will start the second project which will give us profit of ‘2’. Once we selected our first project, our total capital will become 3 (profit + initial capital).
With ‘3’ capital, we will select the third project, which will give us ‘3’ profit.
After the completion of the two projects, our total capital will be 6 (1+2+3).
```


```CPP

//Find all the projects that we can choose with the available capital.
//From the list of projects in the 1st step, choose the project that gives us a maximum profit.

  struct cost_compare{
      bool operator()(pair<int,int> a, pair<int,int> b){
          return a.first>b.first;
      }
    };

    struct profit_compare{
      bool operator()(pair<int,int> a, pair<int,int> b){
          return a.first<b.first;
      }
    };
    
    
    int findMaximizedCapital(int numberOfProjects, int initialCapital, vector<int> &profits,  vector<int> &capital) {
        int n = profits.size();
        priority_queue<pair<int, int>, vector<pair<int, int>>, cost_compare> minCapitalHeap;
        priority_queue<pair<int, int>, vector<pair<int, int>>, profit_compare> maxProfitHeap;

        // insert all project capitals to a min-heap
        for (int i = 0; i < n; i++) {
          minCapitalHeap.push(make_pair(capital[i], i));
        }

        // let's try to find a total of 'numberOfProjects' best projects
        int availableCapital = initialCapital;
        for (int i = 0; i < numberOfProjects; i++) {
          // find all projects that can be selected within the available capital
          //check which one can be max profit
          while (!minCapitalHeap.empty() && minCapitalHeap.top().first <= availableCapital) {
            auto capitalIndex = minCapitalHeap.top().second;
            minCapitalHeap.pop();
            maxProfitHeap.push(make_pair(profits[capitalIndex], capitalIndex));
          }

          // terminate if we are not able to find any project that can be completed within the available
          // capital
          if (maxProfitHeap.empty()) {
            break;
          }

          // select the project with the maximum profit
          availableCapital += maxProfitHeap.top().first;
          maxProfitHeap.pop();
        }

        return availableCapital;
      
    }
```

### Find Next Interval

https://leetcode.com/problems/find-right-interval/

https://www.educative.io/courses/grokking-the-coding-interview/gkkmqXO6zrY


You are given an array of intervals, where intervals[i] = [starti, endi] and each starti is unique.

The right interval for an interval i is an interval j such that startj >= endi and startj is minimized.

Return an array of right interval indices for each interval i. If no right interval exists for interval i, then put -1 at index i.

 
```
Example 1:

Input: intervals = [[1,2]]
Output: [-1]
Explanation: There is only one interval in the collection, so it outputs -1.
Example 2:

Input: intervals = [[3,4],[2,3],[1,2]]
Output: [-1,0,1]
Explanation: There is no right interval for [3,4].
The right interval for [2,3] is [3,4] since start0 = 3 is the smallest start that is >= end1 = 3.
The right interval for [1,2] is [2,3] since start1 = 2 is the smallest start that is >= end2 = 2.
Example 3:

Input: intervals = [[1,4],[2,3],[3,4]]
Output: [-1,2,-1]
Explanation: There is no right interval for [1,4] and [3,4].
The right interval for [2,3] is [3,4] since start2 = 3 is the smallest start that is >= end1 = 3.
```

```CPP
vector<int> findRightInterval(vector<vector<int>>& intervals) {
    map<int, int> hash; //K is interval start , v is index
    vector<int> res;
    int n = intervals.size();
    for (int i = 0; i < n; ++i)
        hash[intervals[i][0]] = i;
    for (auto in : intervals) {
        auto itr = hash.lower_bound(in[1]);
        if (itr == hash.end()) 
            res.push_back(-1);
        else 
            res.push_back(itr->second);
    }
    return res;
}
```

## Interval sort

### Merge Interval

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

### Meeting room needed

https://leetcode.com/problems/meeting-rooms-ii/

Given an array of meeting time intervals consisting of start and end times [[s1,e1],[s2,e2],...] (si < ei), find the minimum number of conference rooms required.

For example,
Given [[0, 30],[5, 10],[15, 20]],
return 2.

```CPP

/*
 * Definition for an interval.
 * struct Interval {
 *     int start;
 *     int end;
 *     Interval() : start(0), end(0) {}
 *     Interval(int s, int e) : start(s), end(e) {}
 * };
 */

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

### Common Free time

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

## Other Heap Problem

### Define own compare func:Top K Frequent Words

https://leetcode.com/problems/top-k-frequent-words/

Given a non-empty list of words, return the k most frequent elements.

Your answer should be sorted by frequency from highest to lowest. If two words have the same frequency, then the word with the lower alphabetical order comes first.

```
Example 1:
Input: ["i", "love", "leetcode", "i", "love", "coding"], k = 2
Output: ["i", "love"]
Explanation: "i" and "love" are the two most frequent words.
    Note that "i" comes before "love" due to a lower alphabetical order.
Example 2:
Input: ["the", "day", "is", "sunny", "the", "the", "the", "sunny", "is", "is"], k = 4
Output: ["the", "is", "sunny", "day"]
Explanation: "the", "is", "sunny" and "day" are the four most frequent words,
    with the number of occurrence being 4, 3, 2 and 1 respectively.

```

```CPP
struct Comp {
    bool operator()(const pair<string, int>& l, const pair<string, int>& r) const {
        return l.second>r.second || ( l.second==r.second && l.first<r.first);
    }
};

vector<string> topKFrequent(vector<string>& words, int k) {
    //
    
    unordered_map<string, int> m;
    for(auto w : words){
        m[w]++;
    }
    //min heap to store K max, if count is same, pop lower alphabetical orde
    priority_queue<pair<string,int>, vector<pair<string,int>>, Comp> pq;
    
    for (auto it : m){
        pq.push(make_pair(it.first, it.second));
        if(pq.size()>k) 
            pq.pop();
    }
        
    
    vector<string> res;
    while (!pq.empty()) {
        res.insert(res.begin(),pq.top().first);
        pq.pop();
    }
    
    return res;
}
```




