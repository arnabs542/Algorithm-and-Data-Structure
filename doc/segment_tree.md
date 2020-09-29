<!-- START doctoc generated TOC please keep comment here to allow auto update -->
<!-- DON'T EDIT THIS SECTION, INSTEAD RE-RUN doctoc TO UPDATE -->
**Table of Contents**  *generated with [DocToc](https://github.com/thlorenz/doctoc)*

- [Segment Tree Introduction](#segment-tree-introduction)
  - [Problem Statement (Range sum use case)](#problem-statement-range-sum-use-case)
  - [Segment Tree Structure](#segment-tree-structure)
    - [Logical representation](#logical-representation)
    - [In Memory representation](#in-memory-representation)
  - [Implementation](#implementation)
- [Practical problem](#practical-problem)
  - [count of range query](#count-of-range-query)
  - [Range Sum Query 2D-immutable](#range-sum-query-2d-immutable)

<!-- END doctoc generated TOC please keep comment here to allow auto update -->

# Segment Tree Introduction

## Problem Statement (Range sum use case)

Let us consider the following problem to understand Segment Trees.

We have an array arr[0 . . . n-1]. We should be able to


- Find the sum of elements from index l to r where 0 <= l <= r <= n-1, or find minimum/maximum in that range

- Change value of a specified element of the array to a new value x. We need to do arr[i] = x where 0 <= i <= n-1.


1. Solution 

run a loop from l to r and calculate the sum of elements in the given range. To update a value, simply do arr[i] = x. The first operation takes O(n) time and the second operation takes O(1) time.


2. Solution

create another array and store sum from start to i at the ith index in this array. The sum of a given range can now be calculated in O(1) time, but update operation takes O(n) time now. This works well if the number of query operations is large and very few updates.

## Segment Tree Structure

### Logical representation 

perform __both the operations in O(log n) time__ once given the array

Representation of Segment trees

1. Leaf Nodes are the elements of the input array.
2. Each internal node represents some merging of the leaf nodes. The merging may be different for different problems. For this problem, merging is sum of leaves under a node.

![segment-tree1](https://github.com/zhangruiskyline/DeepLearning/blob/master/img/segment-tree1.png)

### In Memory representation

```
we can easily construct a segment tree for this array using a 2*N sized array where N is number of elements in original array. The leaf nodes will start from index N in this array and will go upto index (2*N – 1)

element at index i in original array will be at index (i + N) in the segment tree array

For an index i , its left child will be at (2 * i) and right child will be at (2*i + 1) index. So the values at nodes at (2 * i) and (2*i + 1) is combined at ith node to construct the tree.

```

The dummy values are never accessed and have no use. This is some wastage of space due to simple array representation. We may optimize this wastage using some clever implementations, but code for sum and update becomes more complex.


## Implementation


```CPP
using namespace std; 
  
// limit for array size 
const int N = 100000;  
// Max size of tree 
vector<int> tree(2*N, 0); 
  
// function to build the tree 
void build( vector<int> arr)  
{  
    // insert leaf nodes in tree 
    int n = arr.size()
    for (int i=0; i<n; i++)     
        tree[n+i] = arr[i]; 
      
    // build the tree by calculating parents 
    for (int i = n - 1; i > 0; --i)      
        tree[i] = tree[i*2] + tree[i*2+1];     
} 

//
void update(int index, int value)  
{  
    // set value at position p 
    tree[index+n] = value; 
    index = index+n; 
      
    // move upward and update parents, noticing i could be odd or even, so it could be i+1 or i-1, XOR is best here
    for (int i=index; i > 1; i >>= 1) 
        tree[i>>1] = tree[i] + tree[i^1]; 
} 

// function to get sum on interval [l, r) 
int rangequery(int l, int r)  
{  
    int res = 0; 
      
    // loop to find the sum in the range 
    for (l += n, r += n; l < r; l >>= 1, r >>= 1) 
    { 
        if (l&1)  
            res += tree[l++]; 
      
        if (r&1)  
            res += tree[--r]; 
    } 
      
    return res; 
} 
```

# Practical problem

## count of range query

https://leetcode.com/problems/count-of-range-sum/

Given an integer array nums, return the number of range sums that lie in [lower, upper] inclusive.
Range sum S(i, j) is defined as the sum of the elements in nums between indices i and j (i ≤ j), inclusive.

Note:
A naive algorithm of O(n2) is trivial. You MUST do better than that.

```
Input: nums = [-2,5,-1], lower = -2, upper = 2,
Output: 3 
Explanation: The three ranges are : [0,0], [2,2], [0,2] and their respective sums are: -2, -1, 2.
```


## Range Sum Query 2D-immutable

https://leetcode.com/problems/range-sum-query-2d-immutable/

Given a 2D matrix matrix, find the sum of the elements inside the rectangle defined by its upper left corner (row1, col1) and lower right corner (row2, col2).

Range Sum Query 2D
The above rectangle (with the red border) is defined by (row1, col1) = (2, 1) and (row2, col2) = (4, 3), which contains sum = 8.

```
Example:
Given matrix = [
  [3, 0, 1, 4, 2],
  [5, 6, 3, 2, 1],
  [1, 2, 0, 1, 5],
  [4, 1, 0, 1, 7],
  [1, 0, 3, 0, 5]
]

sumRegion(2, 1, 4, 3) -> 8
sumRegion(1, 1, 2, 2) -> 11
sumRegion(1, 2, 2, 4) -> 12
```

```CPP
class NumMatrix {
public:
    NumMatrix(vector<vector<int>> &matrix) {
        if (matrix.size() == 0) return;
        sum = vector<vector<int>>(matrix.size()+1, vector<int>(matrix[0].size()+1, 0));
        for (int i = 0; i < matrix.size(); ++i) {
            for (int j = 0; j < matrix[0].size(); ++j) {
                sum[i+1][j+1] = matrix[i][j] + sum[i][j+1] + sum[i+1][j] -sum[i][j];
            }
        }
    }
    int sumRegion(int row1, int col1, int row2, int col2) {
        return sum[row2+1][col2+1] - sum[row2+1][col1] -sum[row1][col2+1] +sum[row1][col1];
    }
private:
    vector<vector<int>> sum;

};
```
