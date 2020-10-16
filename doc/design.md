<!-- START doctoc generated TOC please keep comment here to allow auto update -->
<!-- DON'T EDIT THIS SECTION, INSTEAD RE-RUN doctoc TO UPDATE -->
**Table of Contents**  *generated with [DocToc](https://github.com/thlorenz/doctoc)*

- [Twitter](#twitter)
- [LRU Cache](#lru-cache)
  - [LRU Cache](#lru-cache-1)
  - [First Unique Number](#first-unique-number)
  - [Insert Delete GetRandom O(1)](#insert-delete-getrandom-o1)
- [rate Limiter](#rate-limiter)
- [Min Stack](#min-stack)
- [Circular Buffer](#circular-buffer)
- [Sparse Vector](#sparse-vector)
  - [Dot Product of Two Sparse Vectors](#dot-product-of-two-sparse-vectors)

<!-- END doctoc generated TOC please keep comment here to allow auto update -->

# Twitter

https://leetcode.com/problems/design-twitter/

Design a simplified version of Twitter where users can post tweets, follow/unfollow another user and is able to see the 10 most recent tweets in the user's news feed. Your design should support the following methods:

```
postTweet(userId, tweetId): Compose a new tweet.

getNewsFeed(userId): Retrieve the 10 most recent tweet ids in the user's news feed. Each item in the news feed must be posted by users who the user followed or by the user herself. Tweets must be ordered from most recent to least recent.

follow(followerId, followeeId): Follower follows a followee.

unfollow(followerId, followeeId): Follower unfollows a followee.
```

```CPP
struct tweet_format{
    int user_id;
    int time_id;
    int tweet_id;
};
bool tweet_compare (tweet_format i,tweet_format j) { return (i.time_id>j.time_id); }

class Twitter {
    //tweet_format tweet;
    int time_global;

    map<int,set<int>> following; //user and all its following
    map<int, vector<tweet_format>> user_tweets; 
public:
    /** Initialize your data structure here. */
    Twitter() {
        time_global = 0;
    }
    
    /** Compose a new tweet. */
    void postTweet(int userId, int tweetId) {
        //insert to itself tweet list
        tweet_format tweet;
        tweet.user_id = userId;
        tweet.time_id = ++ time_global;
        tweet.tweet_id = tweetId;
        user_tweets[userId].push_back(tweet);
    }
    
    /** Retrieve the 10 most recent tweet ids in the user's news feed. Each item in the news feed must be posted by users who the user followed or by the user herself. Tweets must be ordered from most recent to least recent. */
    vector<int> getNewsFeed(int userId) {
        vector<tweet_format> tweet_all;
        vector<int> ret;

        for (auto user: following[userId]){
            
            //push all current userId's following's tweet into vector
            for(int i=0;i<user_tweets[user].size();i++){
                tweet_all.push_back(user_tweets[user][i]);
            }
        }
        
        //add all of its own tweets
        for(int i=0;i<user_tweets[userId].size();i++){
            tweet_all.push_back(user_tweets[userId][i]);
        }

        std::sort(tweet_all.begin(),tweet_all.end(),tweet_compare);
        int len = tweet_all.size();
        if(len<10){
             for(int i=0;i<len;i++)
                ret.push_back(tweet_all[i].tweet_id);
        }else{
            for(int i=0;i<10;i++)
                ret.push_back(tweet_all[i].tweet_id);
        }
        return ret;
    }
    
    /** Follower follows a followee. If the operation is invalid, it should be a no-op. */
    void follow(int followerId, int followeeId) {
        if(followerId!=followeeId)
            following[followerId].insert(followeeId);

    }
    
    /** Follower unfollows a followee. If the operation is invalid, it should be a no-op. */
    void unfollow(int followerId, int followeeId) {
        following[followerId].erase(followeeId);
     }
};

/**
 * Your Twitter object will be instantiated and called as such:
 * Twitter obj = new Twitter();
 * obj.postTweet(userId,tweetId);
 * vector<int> param_2 = obj.getNewsFeed(userId);
 * obj.follow(followerId,followeeId);
 * obj.unfollow(followerId,followeeId);
 */
```

# LRU Cache
Design and implement a data structure for Least Recently Used (LRU) cache. It should support the following operations: get and put.

* get(key) - Get the value (will always be positive) of the key if the key exists in the cache, otherwise return -1.
* put(key, value) - Set or insert the value if the key is not already present. When the cache reached its capacity, it should invalidate the least recently used item before inserting a new item.

```CPP
int len = 0;
typedef list<pair<int,int>> pList; //pair is key value
pList l;
unordered_map<int,pList::iterator> m;  //val is iterator in list
//update function to update the list,
void update(pList::iterator it){
    int key = it->first;
    int val = it->second;
    l.erase(it);
    l.push_front(make_pair(key,val));
    m[key] = l.begin();
}

LRUCache(int capacity) {
    len = capacity;
}

int get(int key) {
    if(m.find(key)==m.end())
        return -1;
    update(m[key]);
    return m[key]->second;
}

void set(int key, int value) {
    if(m.find(key)!=m.end()){
        update(m[key]);
        m[key]->second = value;
    }else{
        l.push_front(make_pair(key,value));
        m[key] = l.begin();
        if(m.size()>len){
            m.erase(l.back().first);
            l.pop_back();
        }
    }
}
```
## LRU Cache

https://leetcode.com/problems/lru-cache/

Design and implement a data structure for Least Recently Used (LRU) cache. It should support the following operations: get and put.

get(key) - Get the value (will always be positive) of the key if the key exists in the cache, otherwise return -1.
put(key, value) - Set or insert the value if the key is not already present. When the cache reached its capacity, it should invalidate the least recently used item before inserting a new item.

The cache is initialized with a positive capacity.

Follow up:
Could you do both operations in O(1) time complexity?

```
Example:

LRUCache cache = new LRUCache( 2 /* capacity */ );

cache.put(1, 1);
cache.put(2, 2);
cache.get(1);       // returns 1
cache.put(3, 3);    // evicts key 2
cache.get(2);       // returns -1 (not found)
cache.put(4, 4);    // evicts key 1
cache.get(1);       // returns -1 (not found)
cache.get(3);       // returns 3
cache.get(4);       // returns 4
```

```CPP
class LRUCache {
public:
    int size;
    list<int> lru;                              //  LRU: back is least visit
    unordered_map<int, list<int>::iterator> m; // key -> iterator
    unordered_map<int, int> cache;                 // key -> value
    
    LRUCache(int capacity) {
        size = capacity;
    }
    
    int get(int key) {
        if (cache.find(key) != cache.end()) {
            update(key);
            return cache[key];
        }
        return -1;
    }
    
    void put(int key, int value) {
        cache[key] = value;
        update(key);
        
    }
    
    //LRU update, remove back, push front
    void update(int key){
        if (m.find(key) != m.end()) {
            lru.erase(m[key]);
        } else if (lru.size() >= size) {
            int old = lru.back();
            lru.pop_back();
            cache.erase(old);
            m.erase(old);
        }
        lru.push_front(key);
        m[key] = lru.begin();
    }
};
```

## First Unique Number

https://leetcode.com/problems/first-unique-number/

You have a queue of integers, you need to retrieve the first unique integer in the queue.

Implement the FirstUnique class:

FirstUnique(int[] nums) Initializes the object with the numbers in the queue.
int showFirstUnique() returns the value of the first unique integer of the queue, and returns -1 if there is no such integer.
void add(int value) insert value to the queue.
 
```
Example 1:

Input: 
["FirstUnique","showFirstUnique","add","showFirstUnique","add","showFirstUnique","add","showFirstUnique"]
[[[2,3,5]],[],[5],[],[2],[],[3],[]]
Output: 
[null,2,null,2,null,3,null,-1]
Explanation: 
FirstUnique firstUnique = new FirstUnique([2,3,5]);
firstUnique.showFirstUnique(); // return 2
firstUnique.add(5);            // the queue is now [2,3,5,5]
firstUnique.showFirstUnique(); // return 2
firstUnique.add(2);            // the queue is now [2,3,5,5,2]
firstUnique.showFirstUnique(); // return 3
firstUnique.add(3);            // the queue is now [2,3,5,5,2,3]
firstUnique.showFirstUnique(); // return -1
```

```CPP

//Write O(1), read O(n)

queue<int> q;                     // To keep the order of elements maintained
unordered_map<int, int> m;      // To keep the frequency of each element

FirstUnique(vector<int>& nums) {
    for(int i=0;i<nums.size();i++){
        m[nums[i]]++;
        q.push(nums[i]);
    }
}

//amortized time of O(1)O(1)

int showFirstUnique() {
    while(!q.empty() && m[q.front()] > 1){
        q.pop();
    }
    if(q.empty())
        return -1;
    else
        return q.front();
}

//O(1)

void add(int value) {
    m[value]++;
    q.push(value);
}
```

We can use LRU way to do so, remove when we add

```CPP
class FirstUnique {
public:
    
    list<int> l;                     // l is to maintain list of none duplicate
    unordered_map<int, list<int>::iterator> m;
    
    FirstUnique(vector<int>& nums) {
        for(int i=0;i<nums.size();i++){
            add(nums[i]);
        }
    }
    
    int showFirstUnique() {
        return l.size()>0? l.front():-1;
    }
    
    void add(int value) {
        auto it = m.find(value);
        if (it == m.end()) {
            l.push_back(value);
            m[value] = --l.end();
        }
        //remove none unique
        else if (it->second != l.end()) {
            l.erase(it->second);
            m[value] = l.end();
        }
    }
};
```

## Insert Delete GetRandom O(1)

https://leetcode.com/problems/insert-delete-getrandom-o1/

Design a data structure that supports all following operations in average O(1) time.

insert(val): Inserts an item val to the set if not already present.
remove(val): Removes an item val from the set if present.
getRandom: Returns a random element from current set of elements (it's guaranteed that at least one element exists when this method is called). Each element must have the same probability of being returned.

```CPP
class RandomizedSet {
public:
    /** Initialize your data structure here. */
    
    vector<int> v;

    unordered_map<int, int> m; //val, index
    RandomizedSet() {
        
    }
    
    /** Inserts a value to the set. Returns true if the set did not already contain the specified element. */
    bool insert(int val) {
        if(m.find(val)==m.end()){
            v.push_back(val);
            m[val] = v.size()-1;
            
            return true;
        }else{
            return false;
        }
    }
    
    /** Removes a value from the set. Returns true if the set contained the specified element. */
    bool remove(int val) {
        if(m.find(val)==m.end()){
            return false;
        }else {
            int index = m[val];
            int last = v.back();
            //swap to end
            v[index] = last;
            m[last] = m[val];
            v.pop_back();
            m.erase(val);
            return true;
        }
    }
    
    /** Get a random element from the set. */
    int getRandom() {
        int rand = random()%v.size();
        return v[rand];
    }
};
```

# rate Limiter

Logger Rate Limiter

Design a logger system that receive stream of messages along with its timestamps, each message should be printed if and only if it is not printed in the last 10 seconds.

Given a message and a timestamp (in seconds granularity), return true if the message should be printed in the given timestamp, otherwise returns false.

It is possible that several messages arrive roughly at the same time.

```CPP
class Logger {
public:
    /** Initialize your data structure here. */
    Logger() {
        
    }
    
    unordered_map<string, int> m;
    
    /** Returns true if the message should be printed in the given timestamp, otherwise returns false.
        If this method returns false, the message will not be printed.
        The timestamp is in seconds granularity. */
    bool shouldPrintMessage(int timestamp, string message) {
        bool ret;
        if(m.find(message)==m.end()){
            m[message] = timestamp;
            ret = true;
        }else{
            if(timestamp - m[message]>=10){
                m[message] = timestamp;
                ret = true;
            }else{
                ret = false;
            }
            
        }
        
        return ret;
    }
};
```

# Min Stack


https://leetcode.com/problems/min-stack/

Design a stack that supports push, pop, top, and retrieving the minimum element in constant time.

push(x) -- Push element x onto stack.
pop() -- Removes the element on top of the stack.
top() -- Get the top element.
getMin() -- Retrieve the minimum element in the stack.
 

Example 1:
```
Input
["MinStack","push","push","push","getMin","pop","top","getMin"]
[[],[-2],[0],[-3],[],[],[],[]]

Output
[null,null,null,null,-3,null,0,-2]

Explanation
MinStack minStack = new MinStack();
minStack.push(-2);
minStack.push(0);
minStack.push(-3);
minStack.getMin(); // return -3
minStack.pop();
minStack.top();    // return 0
minStack.getMin(); // return -2
```

```CPP
 /** initialize your data structure here. */
    stack<int> data_s; //regular stack
    stack<int> min_s; //stack that records min val of current stack  
    MinStack() {

    }
    
    void push(int x) {
        if(min_s.empty() || x<=min_s.top()){
            min_s.push(x);
        }
        data_s.push(x);
    }
    
    void pop() {
        if(min_s.top()==data_s.top())
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

# Circular Buffer

https://leetcode.com/problems/design-circular-queue/

```CPP
class MyCircularQueue {
private:
    vector<int> data;
    int head;
    int tail;
    int size;
public:
    /** Initialize your data structure here. Set the size of the queue to be k. */
    MyCircularQueue(int k) {
        data.resize(k);
        head = -1;
        tail = -1;
        size = k;
    }
    
    /** Insert an element into the circular queue. Return true if the operation is successful. */
    bool enQueue(int value) {
        if (isFull()) {
            return false;
        }
        if (isEmpty()) {
            head = 0;
        }
        tail = (tail + 1) % size;
        data[tail] = value;
        return true;
    }
    
    /** Delete an element from the circular queue. Return true if the operation is successful. */
    bool deQueue() {
        if (isEmpty()) {
            return false;
        }
        if (head == tail) {
            head = -1;
            tail = -1;
            return true;
        }
        head = (head + 1) % size;
        return true;
    }
    
    /** Get the front item from the queue. */
    int Front() {
        if (isEmpty()) {
            return -1;
        }
        return data[head];
    }
    
    /** Get the last item from the queue. */
    int Rear() {
        if (isEmpty()) {
            return -1;
        }
        return data[tail];
    }
    
    /** Checks whether the circular queue is empty or not. */
    bool isEmpty() {
        return head == -1;
    }
    
    /** Checks whether the circular queue is full or not. */
    bool isFull() {
        return ((tail + 1) % size) == head;
    }
};
```

# Sparse Vector

## Dot Product of Two Sparse Vectors

https://leetcode.com/problems/dot-product-of-two-sparse-vectors/

Given two sparse vectors, compute their dot product.

Implement class SparseVector:

SparseVector(nums) Initializes the object with the vector nums
dotProduct(vec) Compute the dot product between the instance of SparseVector and vec
A sparse vector is a vector that has mostly zero values, you should store the sparse vector efficiently and compute the dot product between two SparseVector.

Follow up: What if only one of the vectors is sparse?

 
```
Example 1:

Input: nums1 = [1,0,0,2,3], nums2 = [0,3,0,4,0]
Output: 8
Explanation: v1 = SparseVector(nums1) , v2 = SparseVector(nums2)
v1.dotProduct(v2) = 1*0 + 0*3 + 0*0 + 2*4 + 3*0 = 8
Example 2:

Input: nums1 = [0,1,0,0,0], nums2 = [0,0,0,0,2]
Output: 0
Explanation: v1 = SparseVector(nums1) , v2 = SparseVector(nums2)
v1.dotProduct(v2) = 0*0 + 1*0 + 0*0 + 0*0 + 0*2 = 0
Example 3:

Input: nums1 = [0,1,0,0,2,0,0], nums2 = [1,0,0,0,3,0,4]
Output: 6
```

```CPP
    
    vector<pair<int, int>> v;
    SparseVector(vector<int> &nums) {
        for (int i = 0; i < nums.size(); ++i)
            if (nums[i])
                v.push_back({i, nums[i]});
    }
    int dotProduct(SparseVector& vec) {
        int res = 0;
        int i =0;
        int j =0;
        while (i < v.size() && j < vec.v.size())
            if (v[i].first < vec.v[j].first)
                i++;
            else if (v[i].first > vec.v[j].first)
                ++j;
            else{
                res += v[i].second * vec.v[j].second;
                i++;
                j++;
            }
                
        return res;
    }
```
