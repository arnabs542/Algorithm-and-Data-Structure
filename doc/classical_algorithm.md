<!-- START doctoc generated TOC please keep comment here to allow auto update -->
<!-- DON'T EDIT THIS SECTION, INSTEAD RE-RUN doctoc TO UPDATE -->
**Table of Contents**  *generated with [DocToc](https://github.com/thlorenz/doctoc)*

- [Matrix Problem](#matrix-problem)
  - [Sub region or Path in Matrix](#sub-region-or-path-in-matrix)
    - [Example](#example)
  - [Pattern Along row/col Problem](#pattern-along-rowcol-problem)
  - [Largest square/rectangle inside](#largest-squarerectangle-inside)
- [Sort](#sort)
  - [Quick Sort](#quick-sort)
  - [Select Sort Common](#select-sort-common)
    - [Partial Selection: Find K-th smallest](#partial-selection-find-k-th-smallest)
  - [Bucket Sort:](#bucket-sort)
  - [Merge Sort](#merge-sort)
    - [Find kth element in two sorted arrays](#find-kth-element-in-two-sorted-arrays)
- [BackTracking/Recurisve](#backtrackingrecurisve)
  - [Common logic](#common-logic)
  - [Permutation](#permutation)
  - [SubSet](#subset)
  - [Combination](#combination)
  - [Application](#application)
    - [Letter Combinations of a Phone Number](#letter-combinations-of-a-phone-number)
    - [Generate parentheses](#generate-parentheses)
    - [Robot Room Cleaner](#robot-room-cleaner)
- [Others](#others)
  - [BFPRT](#bfprt)
  - [Half Majority](#half-majority)
  - [Search a 2D matrix](#search-a-2d-matrix)
  - [First missing positive](#first-missing-positive)
- [Random/Probablity](#randomprobablity)
  - [Random sampling: Generate random k numbers in range n](#random-sampling-generate-random-k-numbers-in-range-n)
  - [Reject sampling](#reject-sampling)
  - [Suffle](#suffle)
  - [Revisor sampling](#revisor-sampling)
- [LRU Cache](#lru-cache)
  - [LRU Cache](#lru-cache-1)
  - [First Unique Number](#first-unique-number)
  - [Insert Delete GetRandom O(1)](#insert-delete-getrandom-o1)
- [Greedy](#greedy)
- [Interval](#interval)
  - [Interval overlap](#interval-overlap)
    - [Merge intervals](#merge-intervals)
    - [Remove intervals so that no overlap happen](#remove-intervals-so-that-no-overlap-happen)
    - [Interval Overlap](#interval-overlap)
      - [Meeting room](#meeting-room)
      - [Meeting Scheduler](#meeting-scheduler)

<!-- END doctoc generated TOC please keep comment here to allow auto update -->



# Matrix Problem

## Sub region or Path in Matrix

> Use DFS or BFS to search

* For subregion problem, usually started with target pixel and traversal region, need some matrix to record visited flag or directly modify the original matrix

* For Path Problem, start with path starting or ending point.

* Stop Conditions:
  * visited conditions
  * updated cell value larger or smaller than new DFS/BFS ones

### Example

* https://leetcode.com/problems/number-of-islands/


Given a 2d grid map of '1's (land) and '0's (water), count the number of islands. An island is surrounded by water and is formed by connecting adjacent lands horizontally or vertically. You may assume all four edges of the grid are all surrounded by water.
Example 1:
```
11110
11010
11000
00000
Answer: 1
Example 2:
11000
11000
00100
00011
```


```CPP
//method 1: DFS
int numIslands(vector<vector<char>>& grid) {
    if (grid.size() == 0) return 0;
    int len = grid.size();
    int high = grid[0].size();
    int ret = 0;
    for(int i=0;i<len;i++){
        for(int j=0;j<high;j++){
            if(grid[i][j]=='1'){
                ret++;
                DFS_visit(grid,i,j,len,high);
            }
        }
    }
    return ret;
}

void DFS_visit(vector<vector<char>>& grid, int x, int y, int m, int n){
    grid[x][y] = 2;//marked all adjcent cells of (x,y) as one island and visited(2 instead of 1)
    if (x + 1 < m && grid[x + 1][y] == '1') {
        DFS_visit(grid, x + 1, y, m, n);
    }
    if (y + 1 < n && grid[x][y + 1] == '1') {
        DFS_visit(grid, x, y + 1, m, n);
    }
    if (x - 1 >= 0 && grid[x - 1][y] == '1') {
        DFS_visit(grid, x-1, y, m, n);
    }
    if (y - 1 >= 0 && grid[x][y - 1] == '1') {
        DFS_visit(grid, x, y-1, m, n);
    }
}

//method 2: BFS
class Solution {
public:
//use BFS
int numIslands(vector<vector<char>>& grid) {

  int m = grid.size();
  if(m==0)
      return 0;
  int n = grid[0].size();
  int ret = 0;
  vector<vector<bool>> visited(m, vector<bool>(n, false));
  queue<int> q_row;
  queue<int> q_col;

  for(int i=0;i<m;i++){
      for(int j=0;j<n;j++){
          if(grid[i][j]=='1' && visited[i][j]==false){
              visited[i][j]==true;
              q_row.push(i);
              q_col.push(j);
              ret++;
              while(!q_row.empty()){
                  int x = q_row.front();
                  int y = q_col.front();
                  q_row.pop();
                  q_col.pop();
                  if (x+1<m && grid[x+1][y]=='1' && !visited[x+1][y]){
                      q_row.push(x+1);
                      q_col.push(y);
                      visited[x+1][y] = true;
                  }
                  if (x-1 >=0 && grid[x-1][y]=='1' && !visited[x-1][y]){
                      q_row.push(x-1);
                      q_col.push(y);
                      visited[x-1][y] = true;
                  }
                  if (y+1<n && grid[x][y+1]=='1' && !visited[x][y+1]){
                      q_row.push(x);
                      q_col.push(y+1);
                      visited[x][y+1] = true;
                  }
                  if (y-1>=0 && grid[x][y-1]=='1' && !visited[x][y-1]){
                      q_row.push(x);
                      q_col.push(y-1);
                      visited[x][y-1]=true;
                  }
              }
          }
      }
  }
  return ret;
}
```

* https://leetcode.com/problems/longest-increasing-path-in-a-matrix/
Given an integer matrix, find the length of the longest increasing path.
From each cell, you can either move to four directions: left, right, up or down. You may NOT move diagonally or move outside of the boundary (i.e. wrap-around is not allowed).
```
Example 1:
nums = [
  [9,9,4],
  [6,6,8],
  [2,1,1]
]
Return 4
The longest increasing path is [1, 2, 6, 9].
```

```CPP
int longestIncreasingPath(vector<vector<int>>& matrix) {
    int ret = 0;
    row=matrix.size();
    if(!row) return ret;
    col=matrix[0].size();
    for(int i=0;i<row;i++){
        for(int j=0;j<col;j++){
            //Longest increase path starting from current node
            int cur = dfs(matrix,i,j,1);
            ret = ret>cur?ret:cur;
        }
    }

    return ret;
}

int dfs(vector<vector<int>>& matrix, int x, int y, int path){
    int left = path;
    int right = path;
    int up = path;
    int down = path;
    //search four directions
    if(x+1<row&&matrix[x+1][y]>matrix[x][y]){
        down = dfs(matrix,x+1,y,path+1);
    }
    if(x-1>=0&&matrix[x-1][y]>matrix[x][y]){
        up = dfs(matrix,x-1,y,path+1);
    }
    if(y+1<col&&matrix[x][y+1]>matrix[x][y]){
        right = dfs(matrix,x,y+1,path+1);
    }
    if(y-1>=0&&matrix[x][y-1]>matrix[x][y]){
        left = dfs(matrix,x,y-1,path+1);
    }
    return max(max(max(left,right),up),down);

}

//Use DP to cache
int longestIncreasingPath(vector<vector<int>>& matrix) {
    int ret = 0;
    row=matrix.size();
    if(!row) return ret;
    col=matrix[0].size();
    //dp: record longest increase starting from i,j, when some other node visit, it dose not need to calculate again
    vector<vector<int>> cache(row,vector<int>(col,0));
    for(int i=0;i<row;i++){
        for(int j=0;j<col;j++){
            //Longest increase path starting from current node, calcualte four direction
            ret = max(ret,dfs(matrix,i,j,cache)+1);
        }
    }

    return ret;
}

int dfs(vector<vector<int>>& matrix, int x, int y, vector<vector<int>>& cache){
    if(cache[x][y])
        return cache[x][y];
    int left = 0;
    int right = 0;
    int up = 0;
    int down = 0;
    //search four directions
    if(x+1<row&&matrix[x+1][y]>matrix[x][y]){
        down = dfs(matrix,x+1,y,cache)+1;
    }
    if(x-1>=0&&matrix[x-1][y]>matrix[x][y]){
        up = dfs(matrix,x-1,y,cache)+1;
    }
    if(y+1<col&&matrix[x][y+1]>matrix[x][y]){
        right = dfs(matrix,x,y+1,cache)+1;
    }
    if(y-1>=0&&matrix[x][y-1]>matrix[x][y]){
        left = dfs(matrix,x,y-1,cache)+1;
    }
    int maxval = max(max(max(left,right),up),down);
    cache[x][y] = maxval;
    return maxval;

}
```

* https://leetcode.com/problems/walls-and-gates/#/description
You are given a m x n 2D grid initialized with these three possible values.

-1 - A wall or an obstacle.

0 - A gate.

INF - Infinity means an empty room. We use the value 231 - 1 = 2147483647 to represent INF as you may assume that the distance to a gate is less than 2147483647.

Fill each empty room with the distance to its nearest gate. If it is impossible to reach a gate, it should be filled with INF.

```
For example, given the 2D grid:
INF  -1  0  INF
INF INF INF  -1
INF  -1 INF  -1
  0  -1 INF INF
After running your function, the 2D grid should be:
  3  -1   0   1
  2   2   1  -1
  1  -1   2  -1
  0  -1   3   4
```

```CPP
void wallsAndGates(vector<vector<int>>& rooms) {
        row=rooms.size();
        if(!row) return;
        col=rooms[0].size();
        if(!col) return;

        for(int i=0;i<row;i++){
            for(int j=0;j<col;j++){
                if(rooms[i][j]==0){
                    //starting from gate and traversal whole matrix
                    DFS(rooms,i,j,0);
                }
            }
        }

    }

    void DFS(vector<vector<int>>& rooms, int i, int j, int path){
        if (i<0 || i >= row || j<0 || j >= col || path>rooms[i][j]) {
			return;
		}
		else {
			rooms[i][j] = path;
			DFS(rooms, i - 1, j, path + 1);
			DFS(rooms, i + 1, j, path + 1);
			DFS(rooms, i, j - 1, path + 1);
			DFS(rooms, i, j + 1, path + 1);
		}

    }

```



## Pattern Along row/col Problem
search space goes from certain node along its same row and col index

> Common techniques:  Preprocess: Assist with two vector, row and col, and get some feature/sum of characters of same row/col

* Lonely Pixel

https://leetcode.com/problems/lonely-pixel-i/
Given a picture consisting of black and white pixels, find the number of black lonely pixels.
The picture is represented by a 2D char array consisting of 'B' and 'W', which means black and white pixels respectively.

A black lonely pixel is character 'B' that located at a specific position where the same row and same column don't have any other black pixels.

```
Example:
Input:
[['W', 'W', 'B'],
 ['W', 'B', 'W'],
 ['B', 'W', 'W']]

Output: 3
Explanation: All the three 'B's are black lonely pixels.
```

```CPP
int findLonelyPixel(vector<vector<char>>& picture) {
    int m=picture.size();
    if(m==0) return 0;
    int n=picture[0].size();

    int ret = 0;
    vector<int> row(m,0);
    vector<int> col(n,0);

    for(int i=0;i<m;i++){
        for(int j=0;j<n;j++){
            if(picture[i][j]=='B'){
                row[i]++;
                col[j]++;
            }
        }
    }

    for(int i=0;i<m;i++){
        for(int j=0;j<n;j++){
            if(picture[i][j]=='B' && row[i]==1 && col[j]==1){
                ret++;
            }
        }
    }
    return ret;
}

```

* Bomb Enemy

//https://leetcode.com/problems/bomb-enemy/

Given a 2D grid, each cell is either a wall 'W', an enemy 'E' or empty '0' (the number zero), return the maximum enemies you can kill using one bomb.
The bomb kills all the enemies in the same row and column from the planted point until it hits the wall since the wall is too strong to be destroyed.
Note that you can only put the bomb at an empty cell.

```
Example:
For the given grid

0 E 0 0
E 0 W E
0 E 0 0
return 3. (Placing a bomb at (1,1) kills 3 enemies)
```

```CPP
class Solution {
    int row = 0;
    int col = 0;
public:
    int maxKilledEnemies(vector<vector<char>>& grid) {
        //pre-process with row and col
        row = grid.size();
		if (!row) return 0;
		col = grid[0].size();
		int ret = 0;
		int row_enemy; //enemy killed for fixed row along col
		vector<int> col_enemy(col, 0); //enemy killed for fixed col along row

        for (int i = 0; i<row; i++) {
			for (int j = 0; j<col; j++) {
			    if(j==0 || grid[i][j-1]=='W'){
			        row_enemy = row_help(grid,i,j);
			    }
			    if(i==0 || grid[i-1][j]=='W'){
			        col_enemy[j] = col_help(grid,i,j);
			    }
			    if(grid[i][j]=='0')
			        ret = max(ret,row_enemy+col_enemy[j]);
			}
        }
        return ret;
    }

    int row_help(vector<vector<char>>& grid, int i, int j){
        int num = 0;
        for(int k=j;k<col;k++){

            if(grid[i][k]=='E')
                num++;
            else if(grid[i][k]=='W')
                break;
        }
        return num;
    }

    int col_help(vector<vector<char>>& grid, int i, int j){
        int num = 0;
        for(int k=i;k<row;k++){
            if(grid[k][j]=='E')
                num++;
            else if(grid[k][j]=='W')
                break;
        }
        return num;
    }
};

```

## Largest square/rectangle inside

> similar as array, usually divide this problem into row and col two array


* Largest Square with all 1 in the boundary
Given a matrix containing either 0 or 1 in each cell, find the square with the longest side containing all 1s in its boundary. Cells inside the square may contain either 0 or 1.

```
For example, given matrix

[
  [0, 1, 0, 1, 1]
  [0, 1, 1, 1, 0]
  [0, 1, 0, 1, 1]
  [1, 1, 1, 1, 1]
  [1, 1, 1, 1, 1]
]
The square with the maximum size containing all 1s in its boundary has top-left corner at (1,1) and bottom-right corner at (3, 3)
```


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

* Maximal-square
https://leetcode.com/problems/maximal-square/#/description
Given a 2D binary matrix filled with 0's and 1's, find the largest square containing only 1's and return its area.

```
For example, given the following matrix:

1 0 1 0 0
1 0 1 1 1
1 1 1 1 1
1 0 0 1 0
Return 4.
```

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

# Sort

## Quick Sort
```CPP
void qSort(int a[], int start, int end){
	if(start>=end)
		return;
	int i = start;
	int j = end-1;
	int pivot = a[start];

	while(i<j){
		do{
			i++;
		}while(i<end&&x[i]<pivot);

		do{
			j--;
		}while(j>=start&&x[j]>pivot);

		swap(a[i],a[j]);
	}
	swap(a,pivot,a[j]);
	qSort(x, start, j-1);
       qSort(x, j + 1, end);

}
```

## Select Sort Common 

The basic idea is to use Quick Select algorithm to partition the array with pivot:

```
Put numbers < pivot to pivot's left
Put numbers > pivot to pivot's right
Then

if indexOfPivot == k, return A[k]
else if indexOfPivot < k, keep checking left part to pivot
else if indexOfPivot > k, keep checking right part to pivot
```

### Partial Selection: Find K-th smallest
```CPP
int selectsort(vector<int> num, int k){
	int len = num.size();
	for(int i=0;i<k;i++){
		for(int j=i+1;j<len;j++){
			if(num[j]<num[i]){
				swap(num[j],num[i]);
			}
		}

	}
	return nums[k-1];
}

```

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

```CPP
int findKthLargest(vector<int>& nums, int k) {
        return quickSelect(nums, 0, nums.size()-1, k);
    }
    
    int quickSelect(vector<int>& nums, int low, int high, int k) {
      int pivot = low;

      // use quick sort's idea
      // put nums that are <= pivot to the left
      // put nums that are  > pivot to the right
      for (int j = low; j < high; j++) {
        if (nums[j] <= nums[high]) {
          swap(nums, pivot++, j);
        }
      }
      swap(nums, pivot, high);

      // count the nums that are > pivot from high
      int count = high - pivot + 1;
      // pivot is the one!
      if (count == k) 
          return nums[pivot];
      // pivot is too small, so it must be on the right
      if (count > k) {
          return quickSelect(nums, pivot + 1, high, k);
      }else {
          return quickSelect(nums, low, pivot - 1, k - count);
      }
          
      // pivot is too big, so it must be on the left
      
    }
```



## Bucket Sort:
Used heavily when values are bounded into certain range
```CPP
void bucketSort(vector<int> in) {
	vector<int> bucket(120, 0);
	for (int i = 0; i < in.size(); i++) {
		bucket[i]++;
	}
	int index = 0;
	for (int i = 0; i < 120;i++) {
		while (bucket[i] > 0) {
			in[index] = i;
			index++;
			bucket[i]--;
		}
	}
}

```

Example will be:
https://leetcode.com/problems/maximum-gap/

Given an unsorted array, find the maximum difference between the successive elements in its sorted form.
Try to solve it in linear time/space.
Return 0 if the array contains less than 2 elements.
You may assume all elements in the array are non-negative integers and fit in the 32-bit signed integer range

```CPP
int maximumGap(vector<int>& nums) {
		int max_g = INT_MIN;
		int min_g = INT_MAX;
		int len = nums.size();
		if (len <= 1)
			return 0;

		for (int i = 0; i<len; i++) {
			max_g = max(max_g, nums[i]);
			min_g = min(min_g, nums[i]);
		}
		int bucket_size = max(1, (max_g - min_g) / (len - 1));
		int bucket_num = (max_g - min_g) / bucket_size + 1;

		if (bucket_num <= 1)
			return (max_g - min_g);
		vector<int> bucket_max(bucket_num, INT_MIN);
		vector<int> bucket_min(bucket_num, INT_MAX);
		vector<int> bucket_count(bucket_num, 0);
		int index;
		//using bucket, we basic sort this array
		for (int i = 0; i<len; i++) {

			index = (nums[i] - min_g) / bucket_size;
			bucket_count[index]++;
			bucket_min[index] = min(bucket_min[index], nums[i]);
			bucket_max[index] = max(bucket_max[index], nums[i]);
		}

		int maxGap = INT_MIN;
		int last_max = min_g;//max number in last bucket
		for (int i = 0; i<bucket_num; i++) {
			if (bucket_count[i]>0) {
				maxGap = max(maxGap, bucket_min[i] - last_max);
				last_max = bucket_max[i];
			}
		}
		return maxGap;

	}

```

## Merge Sort

### Find kth element in two sorted arrays
General idea:

* If A[k/2] < B[k/2], kth element is within A[k/2...k]+B[1...k/2]
* If A[k/2] > B[k/2]，kth element is within A[1...k/2]+B[k/2...k]

https://leetcode.com/problems/median-of-two-sorted-arrays/

There are two sorted arrays nums1 and nums2 of size m and n respectively.
Find the median of the two sorted arrays. The overall run time complexity should be O(log (m+n)).
Example 1:
nums1 = [1, 3]
nums2 = [2]
The median is 2.0
Example 2:
nums1 = [1, 2]
nums2 = [3, 4]
The median is (2 + 3)/2 = 2.5

```CPP
double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
		int m = nums1.size(), n = nums2.size();
		int k = (m + n) / 2;
		int num1 = findKth(nums1, 0, m, nums2, 0, n, k + 1);
		if ((n + m) % 2 == 0)
		{
			int num2 = findKth(nums1, 0, m, nums2, 0, n, k);
			return (num1 + num2) / 2.0;
		}
		else return num1;
	}
	int findKth(vector<int> & nums1, int nums1_left, int nums1_right, vector<int>& nums2, int nums2_left, int nums2_right, int k)
	{
		int m = nums1_right - nums1_left;
		int n = nums2_right - nums2_left;
		if (m > n) return findKth(nums2, nums2_left, nums2_right, nums1, nums1_left, nums1_right, k);
		else if (m == 0)
			return nums2[nums2_left + k - 1];
		else if (k == 1)
			return min(nums1[nums1_left], nums2[nums2_left]);
		else {
			int s1LeftCount = min(k / 2, m);
			int s2LeftCount = k - s1LeftCount;
			if (nums1[nums1_left + s1LeftCount - 1] == nums2[nums2_left + s2LeftCount - 1])
				return nums1[nums1_left + s1LeftCount - 1];
			else if (nums1[nums1_left + s1LeftCount - 1] < nums2[nums2_left + s2LeftCount - 1])
				return findKth(nums1, nums1_left + s1LeftCount, nums1_right, nums2, nums2_left, nums2_right, k - s1LeftCount);
			else
				return findKth(nums1, nums1_left, nums1_right, nums2, nums2_left + s2LeftCount, nums2_right, k - s2LeftCount);
		}
	}

```

# BackTracking/Recurisve

## Common logic

> DFS+Recursive

1.	DFS/recursive logical key is call back and each level just do one thing and every level do the same thing repeat
2.	Interface definition. For most problem, use reference in C++(&) so some data structure needs to be in every level and modified. Otherwise each level should be in tact
3.	Push_back() and pop_back() is key thing to go over all items, they should be balance (push should be paired with pop), when thinking the problem, every level(in DFS or recursive) should consider its own level, do not go into recursive logic next level. Same for set item true/false (visited in two dimensional array. etc)
4.	If not push/pop. Use local variable
5.	Put core recursive logic tact, judgement/return/error case should be outside the recursive loop.

```CPP
//Core Logic Code
//Core Recursive logic can be seens as
void help(int &ret, int start, void * param) {
	if (certain condition) {
		// process ret logic
		return;
	}

	for (i = start; i < param;i++) {
		one_res.push_back();  //make a choice
    ret = f(); //some ret logic
		help(ret, i+1/i, param);
		one_res.pop_back(); //retrieve the choice
	}
}



```
## Permutation

Get all permutation of array

```CPP
vector<vector<int>> permuteUnique(vector<int>& nums) {
		vector<vector<int>> ret;
		vector<int> cur;
		vector<bool> visit(nums.size(), false);
		std::sort(nums.begin(), nums.end());
		permute_helper(ret, cur, nums, visit, nums.size());

		return ret;

	}

	void permute_helper(vector<vector<int>>& ret, vector<int>& cur, vector<int>& nums, vector<bool> visit, int len) {
		if (cur.size() == len) {
			ret.push_back(cur);
			return;
		}
		int prev = INT_MAX;
		for (int i = 0; i<len; i++) {
			if (visit[i] == false && nums[i] != prev) {
				cur.push_back(nums[i]);
				visit[i] = true;
				prev = nums[i];
				permute_helper(ret, cur, nums, visit, len);
				cur.pop_back();
				visit[i] = false;
			}
		}
	}

```

## SubSet

https://leetcode.com/problems/subsets/

Given a set of distinct integers, nums, return all possible subsets (the power set).

Note: The solution set must not contain duplicate subsets.

```
Example:

Input: nums = [1,2,3]
Output:
[
  [3],
  [1],
  [2],
  [1,2,3],
  [1,3],
  [2,3],
  [1,2],
  []
]
```

```CPP
class Solution {
public:
    vector<vector<int>> res;
    vector<vector<int>> subsets(vector<int>& nums) {
        vector<int> track;
        //record all path
        backtrack(nums, 0, track);
        return res;
    }
        
    void backtrack(vector<int>& nums, int start, vector<int>& track) {
        res.push_back(track);
        for (int i = start; i < nums.size(); i++) {
            // make choice
            track.push_back(nums[i]);
            // backtrack
            backtrack(nums, i + 1, track);
            // retreive choice
            track.pop_back();
        }
    }

};
```

## Combination

https://leetcode.com/problems/combinations/

Given two integers n and k, return all possible combinations of k numbers out of 1 ... n.

```
Example:

Input: n = 4, k = 2
Output:
[
  [2,4],
  [3,4],
  [2,3],
  [1,2],
  [1,3],
  [1,4],
]
```

```CPP
class Solution {
public:
    vector<vector<int>>res;
    vector<vector<int>> combine(int n, int k) {
        if (k <= 0 || n <= 0) 
            return res;
        vector<int> track;
        backtrack(n, k, 1, track);
        return res;
    }
    
    void backtrack(int n, int k, int start, vector<int>& track) {
        // to the bottom of tree(backtrack tree)
        if (k == track.size()) {
            res.push_back(track);
            return;
        }
        // i from current start
        for (int i = start; i <= n; i++) {
            // make choice
            track.push_back(i);
            backtrack(n, k, i + 1, track);
            // retreieve choice
            track.pop_back();
        }
    }
};
```

## Application

### Letter Combinations of a Phone Number

https://leetcode.com/problems/letter-combinations-of-a-phone-number/ 

Given a string containing digits from 2-9 inclusive, return all possible letter combinations that the number could represent.

A mapping of digit to letters (just like on the telephone buttons) is given below. Note that 1 does not map to any letters.


```
Example:

Input: "23"
Output: ["ad", "ae", "af", "bd", "be", "bf", "cd", "ce", "cf"].
```

```CPP
class Solution {
private:
    map<int,string> dic;
public:
    void init(){

        dic[2] = "abc";  
        dic[3] = "def";
        dic[4] = "ghi";
        dic[5] = "jkl";
        dic[6] = "mno";
        dic[7] = "pqrs";
        dic[8] = "tuv";
        dic[9] = "wxyz";
    }
    
    vector<string> letterCombinations(string digits) {
        vector<string> ret;
        /* for this question, we need to create a look-up dictionary */
       
        if(digits.empty())
            return ret;
        
        
        init();
        
        string one = "";
        help(ret,one,digits,0);
        return ret;        
    }
    
    void help(vector<string> &ret, string one, string& digits,int idx){
        if(idx==digits.size()){
            ret.push_back(one);
            return;
        }
        //DO not over counts.
        string letter = dic[digits[idx]-'0'];
        for(int i=0;i<letter.size();i++){
            
            help(ret,one+letter[i],digits,idx+1);
        }

    }
```



### Generate parentheses

https://leetcode.com/problems/generate-parentheses/

```
Given n pairs of parentheses, write a function to generate all combinations of well-formed parentheses.

For example, given n = 3, a solution set is:

[
  "((()))",
  "(()())",
  "(())()",
  "()(())",
  "()()()"
]
```

```CPP
class Solution {
public:
    vector<string> generateParenthesis(int n) {
        vector<string> ret;
        help(ret,"",n,n);
        
        return ret;
    }
    //left is number of "(", and right is number of ")"
    void help(vector<string> &ret,string str, int left, int right){
        if(left==0 && right==0){
            ret.push_back(str);
            return;
        }
        if(left>0)
            help(ret,str+"(",left-1,right);
        if(left<right) //valid Parentheses starts with "("
            help(ret,str+")",left,right-1);
    }
};
```

### Robot Room Cleaner

https://leetcode.com/problems/robot-room-cleaner/

Given a robot cleaner in a room modeled as a grid.Each cell in the grid can be empty or blocked.The robot cleaner with 4 given APIs can move forward, turn left or turn right. Each turn it made is 90 degrees.When it tries to move into a blocked cell, its bumper sensor detects the obstacle and it stays on the current cell.Design an algorithm to clean the entire room using only the 4 given APIs shown below.

```
interface Robot {
  // returns true if next cell is open and robot moves into the cell.
  // returns false if next cell is obstacle and robot stays on the current cell.
  boolean move();

  // Robot will stay on the same cell after calling turnLeft/turnRight.
  // Each turn will be 90 degrees.
  void turnLeft();
  void turnRight();

  // Clean the current cell.
  void clean();
}
```

```JAVA
class Solution {
// going clockwise : 0: 'up', 1: 'right', 2: 'down', 3: 'left'
  int[][] directions = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};
  Set<Pair<Integer, Integer>> visited = new HashSet();
  Robot robot;

  public void goBack() {
    robot.turnRight();
    robot.turnRight();
    robot.move();
    robot.turnRight();
    robot.turnRight();
  }

  public void backtrack(int row, int col, int d) {
    visited.add(new Pair(row, col));
    robot.clean();
    // going clockwise : 0: 'up', 1: 'right', 2: 'down', 3: 'left'
    for (int i = 0; i < 4; ++i) {
      int newD = (d + i) % 4;
      int newRow = row + directions[newD][0];
      int newCol = col + directions[newD][1];

      if (!visited.contains(new Pair(newRow, newCol)) && robot.move()) {
        backtrack(newRow, newCol, newD);
        goBack();
      }
      // turn the robot following chosen direction : clockwise
      robot.turnRight();
    }
  }

  public void cleanRoom(Robot robot) {
    this.robot = robot;
    backtrack(0, 0, 0);
  }
}
```


# Others

## BFPRT
In an unordered array, find the k'th smallest or largest value

first method is recursive:
1. select a pivot number
2. partition the collection into <,=,> 3 collections compared with pivot
3. check k's smallest location, then recursive

The issue is pivot choice could be random and worst case is O(N^2)

## Half Majority
https://leetcode.com/problems/majority-element/#/description
Given an array of size n, find the majority element. The majority element is the element that appears more than ⌊ n/2 ⌋ times.

```CPP
int majorityElement(vector<int>& nums) {
  int cand = 0;
  int times = 0;
  int len = nums.size();
  for (int i = 0; i < len; i++) {
    if (times == 0) {
      cand = nums[i];
      times = 1;
    } else if (nums[i] == cand) {
      times++;
    } else {
      times--;
    }
  }
  times = 0;
  for (int i = 0; i < len; i++) {
    if (nums[i] == cand) {
      times++;
    }
  }
  if (times > len / 2)
      return cand;
}

```

Extend. [K/N], then we just need to prepare K candidates


## Search a 2D matrix
https://leetcode.com/problems/search-a-2d-matrix-ii/#/description
Write an efficient algorithm that searches for a value in an m x n matrix. This matrix has the following properties:

Integers in each row are sorted in ascending from left to right.
Integers in each column are sorted in ascending from top to bottom.

```CPP
bool searchMatrix(vector<vector<int>>& matrix, int target) {
    int row = matrix.size();
    if(row==0) return false;
    int col = matrix[0].size();

    int x = 0;
    int y = col-1;
    while(x<row && y>=0){
        if(matrix[x][y]>target){
            y = y-1;
        }else if(matrix[x][y]<target){
            x = x + 1;
        }else{
            return true;
        }

    }
    return false;
}

```

## First missing positive
ideally we should have vector as 1,2,3,...n. so nums[i-1]=i

Just go through the array sequentially and for every index write the value at the index to the index specified by value, recursively placing any value at that location to its place and throwing away values > N. Then go again through the array looking for the spot where value doesn't match the index - that's the smallest value not in the array.

```CPP
int firstMissingPositive(vector<int>& nums) {
  int len = nums.size();
  int ret = 0;
  for(int i=0;i<len;i++){
      int target = nums[i];
      //recursively placing any value to location to its place, until find or no more place
      while(target>0 && target<=len && target!=nums[target-1]){
          swap(target,nums[target-1]);
      }
  }

  for(int i=0;i<len;i++){
      if(nums[i]!=i+1){
          ret = i+1;
          return ret;
      }
  }
  return len+1;
}
```

# Random/Probablity

To get random probablity p=1/N

```CPP
p = (rand()*N)%N
if(p==0) //this will give 1/N probability
  {...}
```

## Random sampling: Generate random k numbers in range n

Example to draw 3 random from 0-9:

* First draw (n1), a random number between 1 and 7
* Second draw (n2), a random number between 1 and 8, with 8 having TWO chances to be drawn:
  * if 8 is drawn
  * if n1 is drawn
* Third draw (n3), a random number between 1 and 9, with 9 having THREE chances to be drawn:
  * if 9 is drawn
  * if n1 is drawn
  * if n2 is drawn

* So, each number has 3(k) chances to be drawn:
  * The numbers at or below 7 have a chance to be drawn each of the 3 draws
  * The number 8 has two chances to be drawn on the second draw, and one draw thereafter
  * The number 9 has three chances to be drawn on the third draw,

```CPP
set<int> randomSample(int k, int n){
  set<int> ret;
  for(int i=n-k;i<n;i++){
    int t = rand()%i;
    if(ret.find(t)==ret.end()){
      ret.insert(t);
    }else{
      ret.insert(i);
    }
  }
  return ret;
}
```


## Reject sampling
Given a function which generates a random integer in the range 1 to 7, write a function which generates a random integer in the range 1 to 10 uniformly.
The main idea is when you generate a number in the desired range, output that number immediately. If the number is out of the desired range,
reject it and re-sample again. As each number in the desired range has the same probability of being chosen, a uniform distribution is produced.

```CPP
int rand10() {
  int row, col, idx;
  do {
    row = rand7();
    col = rand7();
    idx = col + (row-1) * 7;
  } while (idx > 40);
  return 1 + (idx-1)%10;
}


```

## Suffle
Shuffle a Deck

```CPP
void KnuthShuffle(int* pArr)
{
    int val;
    for(int i=51;i>=0;i--)
    {
        val=(rand() * 52)%i;
        swap(pArr[i], pArr[val]);
    }
}
```

https://leetcode.com/problems/shuffle-an-array/#/
```CPP
vector<int> shuffle(vector<int> nums) {
    vector<int> ret(nums);
    //shuffle each position with another one after that
    for (int i = 0;i < ret.size();i++) {
        int pos = rand()%(ret.size()-i);
        swap(ret[i+pos], ret[i]);
    }
    return ret;
}

```

## Revisor sampling
Reservoir sampling is a family of randomized algorithms for randomly choosing a sample of k items from a list S containing n items, where n is either a very large or unknown number. Typically n is large enough that the list doesn't fit into main memory.

* Keep the first item(or first k items) in memory.
* When i-th item comes
  * With 1/i probability, replace the first item with new item
  * With (1-1/i) probability, keep item


```CPP
// A function to randomly select k items from stream[0..n-1].
vector<int> selectKItems(vector<int> stream, int n, int k){
  vector<int> ret;
  int i;
  for(i=0;i<k;i++){
    ret[i] = stream[i];
  }
  for(;i<n;i++){
    int pos = rand()%(i+1);
    if(pos<k)
      ret[pos] = stream[i];
  }
  return ret;
}

```

Revisor sampling can also be used to some other random sample issues

> Given an array of integers with possible duplicates, randomly output the index of a given target number.

Example:
https://leetcode.com/problems/random-pick-index/#/description
int[] nums = new int[] {1,2,3,3,3};
Solution solution = new Solution(nums);

// pick(3) should return either index 2, 3, or 4 randomly. Each index should have equal probability of returning.
solution.pick(3);

// pick(1) should return 0. Since in the array only nums[0] is equal to 1.
solution.pick(1);

```CPP
int pick(int target,vector<int> n) {
    int ret = -1;
    int size = 0;
    for(int i=0;i<n.size();i++){
        if(n[i]==target){
            size++;
            if(size==1)
                ret = i; //init
            else{
                if(rand()%size==0)
                    ret = i;//revisor sampling with probability p=1/size
            }
        }
    }
    return ret;
}

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




# Greedy

# Interval

## Interval overlap

### Merge intervals
https://leetcode.com/problems/merge-intervals/#/description
Given a collection of intervals, merge all overlapping intervals.

For example,
Given [1,3],[2,6],[8,10],[15,18],
return [1,6],[8,10],[15,18].

```CPP
static bool mycompare(Interval s1, Interval s2){
    return s1.start<s2.start;
}

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
```

### Remove intervals so that no overlap happen

https://leetcode.com/problems/non-overlapping-intervals/#/description
Given a collection of intervals, find the minimum number of intervals you need to remove to make the rest of the intervals non-overlapping.

Note:
You may assume the interval's end point is always bigger than its start point.
Intervals like [1,2] and [2,3] have borders "touching" but they don't overlap each other.
Example 1:
Input: [ [1,2], [2,3], [3,4], [1,3] ]
Output: 1
Explanation: [1,3] can be removed and the rest of intervals are non-overlapping.

Example 2:
Input: [ [1,2], [1,2], [1,2] ]
Output: 2
Explanation: You need to remove two [1,2] to make the rest of intervals non-overlapping.

Example 3:
Input: [ [1,2], [2,3] ]
Output: 0
Explanation: You don't need to remove any of the intervals since they're already non-overlapping.

```CPP
static bool mycompare(Interval s1, Interval s2){
    return s1.start<s2.start;
}
int eraseOverlapIntervals(vector<Interval>& intervals) {

    if(intervals.size()==0)
        return 0;
    sort(intervals.begin(),intervals.end(),mycompare);
    int prev = 0;
    int ret = 0;
    for (int i = 1; i < intervals.size(); i++) {
        if (intervals[i].start < intervals[prev].end) {
            ret++; //need to remove
            if (intervals[i].end < intervals[prev].end) //remove one with largest area, max end coordinate
                prev = i;
        }
        else
            prev = i;

    }

    return ret;
}

```

### Interval Overlap

* usually these questions looks like get some min/max for interval list considering intervals could overlap

#### Meeting room

https://leetcode.com/problems/meeting-rooms-ii/#/description
Given an array of meeting time intervals consisting of start and end times [[s1,e1],[s2,e2],...] (si < ei), find the minimum number of conference rooms required.

For example,
Given [[0, 30],[5, 10],[15, 20]],
return 2.

```CPP
static bool sortcomp(Interval s1, Interval s2){
    return s1.start<s2.start;
}

struct pq_compare{
    bool operator()(Interval& a, Interval& b){
        return a.end>b.end;
    }
};

int minMeetingRooms(vector<Interval>& intervals) {
    if(intervals.size()==0)
        return 0;
    sort(intervals.begin(),intervals.end(),sortcomp);
    priority_queue<Interval, vector<Interval>, pq_compare> pq;//maintain the earliest ends time, min queue
    pq.push(intervals[0]);
    for(int i=1;i<intervals.size();i++){
        Interval tmp = pq.top();

        if(intervals[i].start>=tmp.end){
            pq.pop(); //extend current room
        }
        pq.push(intervals[i]);
    }
    return pq.size();
}

```

#### Meeting Scheduler

https://leetcode.com/problems/meeting-scheduler/

Given the availability time slots arrays slots1 and slots2 of two people and a meeting duration duration, return the earliest time slot that works for both of them and is of duration duration.If there is no common time slot that satisfies the requirements, return an empty array.

The format of a time slot is an array of two elements [start, end] representing an inclusive time range from start to end.  It is guaranteed that no two availability slots of the same person intersect with each other. That is, for any two time slots [start1, end1] and [start2, end2] of the same person, either start1 > end2 or start2 > end1.

 
```
Example 1:

Input: slots1 = [[10,50],[60,120],[140,210]], slots2 = [[0,15],[60,70]], duration = 8
Output: [60,68]
Example 2:

Input: slots1 = [[10,50],[60,120],[140,210]], slots2 = [[0,15],[60,70]], duration = 12
Output: []
```

* Solution 1: 2 pointers

```CPP
 vector<int> minAvailableDuration(vector<vector<int>>& slots1, vector<vector<int>>& slots2, int duration) {
        sort(slots1.begin(), slots1.end()); // sort  by start time 
        sort(slots2.begin(), slots2.end()); //
        
        int i = 0, j = 0;
        int n1 = slots1.size(), n2 = slots2.size();
        while(i<n1 && j<n2){
            
            int start = max(slots1[i][0],slots2[j][0]);
            int end = min(slots1[i][1],slots2[j][1]);
            
            if(start+duration<=end){
                return {start, start + duration};
            }else if(slots1[i][1]<slots2[j][1]){
                i++;
            }else{
                j++;
            }
            
        }
        
        return {};
    }
```

* Solution 2: Priority Queue

```CPP
vector<int> minAvailableDuration(vector<vector<int>>& slots1, vector<vector<int>>& slots2, int duration) {
    //min queue by start time
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> q;
    for (auto s : slots1) {
        if (s[1] - s[0] >= duration) q.push({ s[0], s[1] });
    }
    for (auto s : slots2) {
        if (s[1] - s[0] >= duration) q.push({ s[0], s[1] });
    }
    
    while (q.size()>1) {
        
        int end1 = q.top().second;
        q.pop();
        //since min queue by start time, so start1 is always < start2
        int start2 = q.top().first;
        if (end1 >= start2 + duration)
            return { start2, start2 + duration };
    }
    return {};
}
```



https://leetcode.com/problems/minimum-number-of-arrows-to-burst-balloons/#/description
There are a number of spherical balloons spread in two-dimensional space. For each balloon, provided input is the start and end coordinates of the horizontal diameter. Since it's horizontal, y-coordinates don't matter and hence the x-coordinates of start and end of the diameter suffice. Start is always smaller than end. There will be at most 104 balloons.

An arrow can be shot up exactly vertically from different points along the x-axis. A balloon with xstart and xend bursts by an arrow shot at x if xstart ≤ x ≤ xend. There is no limit to the number of arrows that can be shot. An arrow once shot keeps travelling up infinitely. The problem is to find the minimum number of arrows that must be shot to burst all balloons.

Example:

Input:
[[10,16], [2,8], [1,6], [7,12]]

Output:
2

Explanation:
One way is to shoot one arrow for example at x = 6 (bursting the balloons [2,8] and [1,6]) and another arrow at x = 11 (bursting the other two balloons).

```CPP
static bool mycompare(pair<int, int> s1, pair<int, int> s2){
    return s1.first<s2.first;
}

int findMinArrowShots(vector<pair<int, int>>& points) {
    if(points.size()==0)
        return 0;
    sort(points.begin(),points.end(),mycompare);
    //idea is to get overlap area among ballons
    vector<pair<int, int>> overlap;
    overlap.push_back(points[0]);
    for(int i=1;i<points.size();i++){
        if(points[i].first<=overlap.back().second){
            overlap.back().first = max(points[i].first,overlap.back().first);  //calculate possible overlap and update
            overlap.back().second = min(points[i].second,overlap.back().second);
        }else{
            overlap.push_back(points[i]);
        }

    }
    return overlap.size();
}
```