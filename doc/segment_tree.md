<!-- START doctoc generated TOC please keep comment here to allow auto update -->
<!-- DON'T EDIT THIS SECTION, INSTEAD RE-RUN doctoc TO UPDATE -->
**Table of Contents**  *generated with [DocToc](https://github.com/thlorenz/doctoc)*

- [Problem Statement (Range sum use case)](#problem-statement-range-sum-use-case)
- [Segment Tree](#segment-tree)
  - [Segment Tree Structure](#segment-tree-structure)
    - [Logical representation](#logical-representation)
    - [In Memory representation](#in-memory-representation)
- [Binary Index Tree](#binary-index-tree)
  - [Basic Idea](#basic-idea)
  - [Operation](#operation)
  - [Implementation](#implementation)
- [Practical problem](#practical-problem)
  - [count of range query](#count-of-range-query)
  - [Range Query mutable](#range-query-mutable)
  - [Range Sum Query 2D-immutable](#range-sum-query-2d-immutable)
  - [Range Sum Query 2D - Mutable](#range-sum-query-2d---mutable)

<!-- END doctoc generated TOC please keep comment here to allow auto update -->

# Problem Statement (Range sum use case)

Let us consider the following problem to understand Segment Trees.

We have an array arr[0 . . . n-1]. We should be able to


- Find the sum of elements from index l to r where 0 <= l <= r <= n-1, or find minimum/maximum in that range

- Change value of a specified element of the array to a new value x. We need to do arr[i] = x where 0 <= i <= n-1.


1. Solution 

run a loop from l to r and calculate the sum of elements in the given range. To update a value, simply do arr[i] = x. The first operation takes O(n) time and the second operation takes O(1) time.


2. Solution

create another array and store sum from start to i at the ith index in this array. The sum of a given range can now be calculated in O(1) time, but update operation takes O(n) time now. This works well if the number of query operations is large and very few updates.

# Segment Tree



## Segment Tree Structure

### Logical representation 

perform __both the operations in O(log n) time__ once given the array

Representation of Segment trees

1. length n is power of 2. choose close value of power of 2.
2. Leaf Nodes are the elements of the input array.
3. Each internal node represents some merging of the leaf nodes. The merging may be different for different problems. For this problem, merging is sum of leaves under a node.

![segment-tree1](https://github.com/zhangruiskyline/Algorithm-and-Data-Structure/blob/master/img/segment-tree1.png)


![segment-tree2](https://github.com/zhangruiskyline/Algorithm-and-Data-Structure/blob/master/img/segment-tree2.png)

### In Memory representation

```
we can easily construct a segment tree for this array using a 2*N sized array where N is number of elements in original array. The leaf nodes will start from index N in this array and will go upto index (2*N – 1)

element at index i in original array will be at index (i + N) in the segment tree array

For an index i , its left child will be at (2 * i) and right child will be at (2*i + 1) index. So the values at nodes at (2 * i) and (2*i + 1) is combined at ith node to construct the tree.

```

The dummy values are never accessed and have no use. This is some wastage of space due to simple array representation. We may optimize this wastage using some clever implementations, but code for sum and update becomes more complex.

# Binary Index Tree

## Basic Idea

https://www.hackerearth.com/practice/data-structures/advanced-data-structures/fenwick-binary-indexed-trees/tutorial/

We know the fact that each integer can be represented as the sum of powers of two. Similarly, for a given array of size , we can maintain an array  such that, at any index we can store the sum of some numbers of the given array. This can also be called a partial sum tree.

Let’s use an example to understand how  stores partial sums.
```
//for ease, we make sure our given array is 1-based indexed
int a[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16};
```

![BIT](https://github.com/zhangruiskyline/Algorithm-and-Data-Structure/blob/master/img/BIT.jpg)


```
               {           a[x],                  if x is odd
BIT[x] =                    a[1] + ... + a[x],     if x is power of 2
               }
```

To generalize this every index  in the  array stores the cumulative sum from the index  to  (both inclusive), where  represents the last set bit in the index .

Sum of first 12 numbers in array ```BIT[12]+BIT[8]```

Similarly, sum of first 6 elements ```BIT[6]+BIT[4]```

Sum of first 8 elements ```BIT[8]```




## Operation


* Update

1. cal 2's complement (-i)
2. AND with original value i * -i
3. ADD from original value i+= i* -i

```
void update(int x, int val)       //add "val" at index "x"
{
    for(; x <= n; x += x&-x)
          BIT[x] += val;
}
```

Suppose we call update(13, 2).

Here we see from the above figure that indices 13, 14, 16 cover index 13 and thus we need to add 2 to them also.

Initially  is 13,  then we need to update 14, which we get from 13(1101) last SET bit, and AND  13+1 =14, then we have 
14 (1110), get last SET bit and add 14+2 = 16.

* Query Sum

1. cal 2's complement (-i)
2. AND with original value i * -i
3. SUB from original value i-= i* -i

```
int query(int x)      //returns the sum of first x elements in given array a[]
{
     int sum = 0;
     for(; x > 0; x -= x&-x)
         sum += BIT[x];
     return sum;
}
```

suppose we want to query first 14 elements. 

We get ```sum = BIT[14] = (a[14]+a[13])```, then we isolate last SET bit 14(1110) and sub = 12. we then have
```sum = BIT[14]+BIT[12] = (a[14]+a[13])+ (a[12]+...a[9])```, then last SET bit of 12(1100) and sub = 8, we have
```sum = BIT[14]+BIT[12]+BIT[8] = (a[14]+a[13])+ (a[12]+...a[9])+(a[8]+..a[1])```, and last SET of 8(1000) an sub =0. loop end.


## Implementation

```CPP
/*         n --> No. of elements present in input array.  
    BITree[0..n] --> Array that represents Binary Indexed Tree. 
    arr[0..n-1] --> Input array for which prefix sum is evaluated. */
  
// Returns sum of arr[0..index]. This function assumes 
// that the array is preprocessed and partial sums of 
// array elements are stored in BITree[]. 
int getSum(int BITree[], int index) 
{ 
    int sum = 0; // Iniialize result 
  
    // index in BITree[] is 1 more than the index in arr[] 
    index = index + 1; 
  
    // Traverse ancestors of BITree[index] 
    while (index>0) 
    { 
        // Add current element of BITree to sum 
        sum += BITree[index]; 
  
        // Move index to parent node in getSum View 
        index -= index & (-index); 
    } 
    return sum; 
} 
  
// Updates a node in Binary Index Tree (BITree) at given index 
// in BITree. The given value 'val' is added to BITree[i] and  
// all of its ancestors in tree. 
void updateBIT(int BITree[], int n, int index, int val) 
{ 
    // index in BITree[] is 1 more than the index in arr[] 
    index = index + 1; 
  
    // Traverse all ancestors and add 'val' 
    while (index <= n) 
    { 
      // Add 'val' to current node of BI Tree 
      BITree[index] += val; 
    
      // Update index to that of parent in update View 
      index += index & (-index); 
    } 
} 
  
// Constructs and returns a Binary Indexed Tree for given 
// array of size n. 
int *constructBITree(int arr[], int n) 
{ 
    // Create and initialize BITree[] as 0 
    int *BITree = new int[n+1]; 
    for (int i=1; i<=n; i++) 
        BITree[i] = 0; 
  
    // Store the actual values in BITree[] using update() 
    for (int i=0; i<n; i++) 
        updateBIT(BITree, n, i, arr[i]); 
  
    // Uncomment below lines to see contents of BITree[] 
    //for (int i=1; i<=n; i++) 
    //     cout << BITree[i] << " "; 
  
    return BITree; 
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


## Range Query mutable


https://leetcode.com/problems/range-sum-query-mutable/

Given an integer array nums, find the sum of the elements between indices i and j (i ≤ j), inclusive.

The update(i, val) function modifies nums by updating the element at index i to val.

```
Example:

Given nums = [1, 3, 5]

sumRange(0, 2) -> 9
update(1, 2)
sumRange(0, 2) -> 8
```

```CPP
class NumArray {
private:
    vector<int> tree;
    int len = 0;
public:
    NumArray(vector<int> &nums) {
        len = nums.size();
        tree.resize(2*len,0);
        for(int i=len,j=0;i<2*len;i++,j++){
            tree[i] = nums[j];
        }
        for(int i=len-1;i>=0;i--){
            tree[i] = tree[2*i]+tree[2*i+1];
        }
    }

    void update(int i, int val) {
        int shift = tree[len+i] - val;
        int index = len+i;
        while(index>=1) {
            tree[index] = tree[index] - shift;
            index = index/2;
        }
    }

    int sumRange(int i, int j) {
        // get leaf with value 'i'
        i += len;
        // get leaf with value 'j'
        j += len;
        int sum = 0;

    /*
The idea behind the query function is that whether we should include an element in the sum or we should include its parent.  

Consider that L is the left border of an interval and R is the right border of the interval. if L is odd then it means that it is the right child of it’s parent and our interval includes only L and not it’s parent. 

So we will simply include this node to sum and move to the parent of it’s next node by doing L = (L+1)/2. Now, if L is even then it is the left child of it’s parent and interval includes it’s parent also unless the right borders interferes. 

    */

        while (i <= j) {
          //left
            if ((i % 2) == 1) {
               sum += tree[i];
               i++;
            }
            if ((j % 2) == 0) {
               sum += tree[j];
               j--;
            }
            i /= 2;
            j /= 2;
        }
        return sum;
    }
};
```

Another solution is build the Segment Tree in recursive 


```CPP
struct SegmentTreeNode {
    int start, end, sum;
    SegmentTreeNode* left;
    SegmentTreeNode* right;
    SegmentTreeNode(int a, int b):start(a),end(b),sum(0),left(nullptr),right(nullptr){}
};
class NumArray {
    SegmentTreeNode* root;
public:
    NumArray(vector<int> &nums) {
        int n = nums.size();
        root = buildTree(nums,0,n-1);
    }
   
    void update(int i, int val) {
        modifyTree(i,val,root);
    }

    int sumRange(int i, int j) {
        return queryTree(i, j, root);
    }
    SegmentTreeNode* buildTree(vector<int> &nums, int start, int end) {
        if(start > end) return nullptr;
        SegmentTreeNode* root = new SegmentTreeNode(start,end);
        if(start == end) {
            root->sum = nums[start];
            return root;
        }
        int mid = start + (end - start) / 2;
        root->left = buildTree(nums,start,mid);
        root->right = buildTree(nums,mid+1,end);
        root->sum = root->left->sum + root->right->sum;
        return root;
    }
    int modifyTree(int i, int val, SegmentTreeNode* root) {
        if(root == nullptr) return 0;
        int diff;
        if(root->start == i && root->end == i) {
            diff = val - root->sum;
            root->sum = val;
            return diff;
        }
        int mid = (root->start + root->end) / 2;
        if(i > mid) {
            diff = modifyTree(i,val,root->right);
        } else {
            diff = modifyTree(i,val,root->left);
        }
        root->sum = root->sum + diff;
        return diff;
    }
    int queryTree(int i, int j, SegmentTreeNode* root) {
        if(root == nullptr) return 0;
        if(root->start == i && root->end == j) return root->sum;
        int mid = (root->start + root->end) / 2;
        if(i > mid) return queryTree(i,j,root->right);
        if(j <= mid) return queryTree(i,j,root->left);
        return queryTree(i,mid,root->left) + queryTree(mid+1,j,root->right);
    }
};
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

## Range Sum Query 2D - Mutable

https://leetcode.com/problems/range-sum-query-2d-mutable/

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
update(3, 2, 2)
sumRegion(2, 1, 4, 3) -> 10
```

```CPP
class NumMatrix {
private:
    
    vector<vector<int>> tree;
    vector<vector<int>> num;
    int _row;
    int _col;
    
public:
    NumMatrix(vector<vector<int>>& matrix) {
        _row = matrix.size();
        if (0 == _row) 
            return;
        _col = matrix[0].size();
        num = vector<vector<int>>(matrix);
        tree = vector<vector<int>>(_row + 1, vector<int>(_col + 1, 0));
        for (int i = 0; i < _row; i++) 
         for (int j = 0; j < _col; j++) {
            updateTree(i, j, num[i][j]);
        }
        
    }
    
    void update(int row, int col, int val) {
            updateTree(row, col, val - num[row][col]);
            num[row][col] = val;
    }
    
    int sumRegion(int row1, int col1, int row2, int col2) {
        return read(row2+1, col2+1) - read(row1, col2+1) - read(row2+1, col1) + read(row1, col1);
    }
    
    void updateTree(int row, int col, int val) {
    for (int i = row + 1; i <= _row; i += i & (-i)) 
      for (int j = col + 1; j <= _col; j += j & (-j)) 
            tree[i][j] += val;
    
    }

    int read(int row, int col) {
        int sum = 0;
        for (int i = row; i > 0; i -= i & (-i))
         for (int j = col; j > 0; j -= j & (-j)) {
                sum += tree[i][j];
        }
        return sum;
    }
};
```