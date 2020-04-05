<!-- START doctoc generated TOC please keep comment here to allow auto update -->
<!-- DON'T EDIT THIS SECTION, INSTEAD RE-RUN doctoc TO UPDATE -->
**Table of Contents**  *generated with [DocToc](https://github.com/thlorenz/doctoc)*

- [Binary search](#binary-search)
  - [Binary Search Framework](#binary-search-framework)
    - [Binary search for Target](#binary-search-for-target)
      - [Key points](#key-points)
    - [Boundary in Binary Search](#boundary-in-binary-search)
      - [Key points](#key-points-1)
  - [Local Minimum](#local-minimum)
  - [Numerical(Square) Calculation](#numericalsquare-calculation)
- [Matrix Problem](#matrix-problem)
  - [Sub region or Path in Matrix](#sub-region-or-path-in-matrix)
    - [Example](#example)
  - [Pattern Along row/col Problem](#pattern-along-rowcol-problem)
  - [Largest square/rectangle inside](#largest-squarerectangle-inside)
- [Sort](#sort)
  - [Quick Sort](#quick-sort)
  - [Select Sort](#select-sort)
    - [Partial Selection: Find K-th smallest](#partial-selection-find-k-th-smallest)
  - [Bucket Sort:](#bucket-sort)
  - [Merge Sort](#merge-sort)
    - [Find kth element in two sorted arrays](#find-kth-element-in-two-sorted-arrays)
- [BackTracking/Recurisve](#backtrackingrecurisve)
  - [Common logic](#common-logic)
  - [Permutation](#permutation)
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
- [Greedy](#greedy)
- [Interval](#interval)
  - [Interval overlap](#interval-overlap)
    - [Merge intervals](#merge-intervals)
    - [Interval Overlap](#interval-overlap)
- [Trie](#trie)
  - [Example: Detect Words](#example-detect-words)

<!-- END doctoc generated TOC please keep comment here to allow auto update -->

# Binary search

Anything that can split the Search space can use Binary search

## Binary Search Framework 

```CPP
int binarySearch(int[] nums, int target) {
    int left = 0, right = nums.size() - 1;

    while(left <= right) {
        int mid = left + (right - left) / 2;
        if (nums[mid] == target) {
            ...
        } else if (nums[mid] < target) {
            left = ...
        } else if (nums[mid] > target) {
            right = ...
        }
    }
    return ...;
}
```

### Binary search for Target

```CPP
int binarySearch(int[] nums, int target) {
    int left = 0; 
    int right = nums.length - 1; // length

    while(left <= right) {
        int mid = left + (right - left) / 2;
        if(nums[mid] == target)
            return mid; 
        else if (nums[mid] < target)
            left = mid + 1; // 
        else if (nums[mid] > target)
            right = mid - 1; // 
    }
    return -1;
}
```

#### Key points

1. use ```<=``` or not ```<```:

The end condition for ```while(left <= right)``` is ```left = right + 1```, so the ```[left, right]``` will becomes ```[right+1, right]```, which is not possible, so it is correct ending condition, since we have searched into impossible state.


but for end condition for ```while(left < right)``` is ```left = right```, so the ```[left, right]``` will becomes ```[right, right]```, which is possible, and we will not visit ```right``` value.


2. use ```left=mid-1 / right = mid+1``` or not ```left =mid/ right = mid```

Also we need to consider whether we need to move mid index. since our search range is ```[left, right]```, so if mid is not target, then we should search ```[left, mid-1]```, or ```[mid+1, right]```

3. Limitation of former algorithm: Hard to return the boundary

find mid value left and right boudary of ```nums = [1,2,2,2,3]``` 

### Boundary in Binary Search

1. Find Left Boundary

```CPP
int left_bound(int[] nums, int target) {
    if (nums.length == 0) return -1;
    int left = 0;
    int right = nums.length; //why right is 1 above boundary?

    while (left < right) { // why <? not <=?
        int mid = (left + right) / 2;
        if (nums[mid] == target) {
            right = mid;
        } else if (nums[mid] < target) {
            left = mid + 1;
        } else if (nums[mid] > target) {
            right = mid; // 
        }
    }
    return left;
}
```

#### Key points

1. why use ```<```, not ```<=```

search range here is ```[left, right)```, which dose not include right, since we just need to find left boundary. so for ```while (left < right)```, the ending condition is ```left==right```, and our search range ```[left, right)``` will be exmpty in this case, so condition is good.

2. why no ```return -1```

since the boudary here means "how many items are less(for left) or more(for right) than target value". 

for ```nums = [2,3,5,7], target = 1``` will return 0. means 0 item is less than 1. for ```nums = [2,3,5,7], target = 8```, will return 4, means 4 items are smaller than 8.

so our func return will be in range of ```[0, size+1]```.

3. why use ```left=mid+1```, not ```left=mid``` as before

since our search range is ```[left, right)```, so after ```num[mid]``` has been checked, our next search should be dividied into ```[left, mid)``` and ```[mid+1, right)```

4. why we return ```left```, not ```mid``` or ```right```

actually it is same since our ending condition is ```left == right```

* we can also use former approach to do

```CPP
int left_bound(int[] nums, int target) {
    int left = 0, right = nums.length - 1;
    // search range is [left, right]
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (nums[mid] < target) {
            // range becomes [mid+1, right]
            left = mid + 1;
        } else if (nums[mid] > target) {
            // range becomes [left, mid-1]
            right = mid - 1;
        } else if (nums[mid] == target) {
            right = mid - 1;
        }
    }
    // since our ending condition is left == right + 1, so if target > all items
    // we end up left be more than max item. so need to check
    if (left >= nums.length || nums[left] != target)
        return -1;
    return left;
}
```



## Local Minimum

Local minimum
Find array if there is local min(left and right is larger) and return index

//Binary search
```CPP
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


## Numerical(Square) Calculation
https://leetcode.com/problems/sum-of-square-numbers/#/description

Given a non-negative integer c, your task is to decide whether there're two integers a and b such that a2 + b2 = c.

Example 1:
Input: 5
Output: True
Explanation: 1 * 1 + 2 * 2 = 5
Example 2:
Input: 3
Output: False

```CPP
bool judgeSquareSum(int c) {
    if (c < 0) {
        return false;
    }
    int left = 0, right = sqrt(c);
    while (left <= right) {
        int cur = left * left + right * right;
        if (cur < c) {
            left++;
        } else if (cur > c) {
            right--;
        } else {
            return true;
        }
    }
    return false;
}
```



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

## Select Sort
```CPP
void selectsort(vector<int> num){
	int len = num.size();
	for(int i=0;i<len-1;i++){
		for(int j=i+1;j<len;j++){
			if(num[j]<num[j]){
				swap(num[i],num[j]);
			}
		}
	}
}
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
		one_res.push_back();  //used mostly in vector
    ret = f(); //some ret logic
		help(ret, i+1/i, param);
		one_res.pop_back(); //pop what pushed, for string case since we use local variable, no need to pop, noticing
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

* Remove intervals so that no overlap happen

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

# Trie

In computer science, a trie, also called digital tree and sometimes radix tree or prefix tree (as they can be searched by prefixes), is a kind of search tree—an ordered tree data structure that is used to store a dynamic set or associative array where the keys are usually strings.

## Example: Detect Words

Design a data structure that supports the following two operations:

void addWord(word)

bool search(word)

search(word) can search a literal word or a regular expression string containing only letters a-z or .. A . means it can represent any one letter.

For example:

addWord("bad")

addWord("dad")

addWord("mad")

search("pad") -> false

search("bad") -> true

search(".ad") -> true

search("b..") -> true


```CPP
class WordDictionary {
public:
    struct TrieNode{
        bool end = false;
        struct TrieNode * child[26];
    };

    TrieNode * root = new TrieNode();
    // Adds a word into the data structure.
    void addWord(string word) {
        TrieNode * p = root;
        int len= word.size();
        for(int i=0;i<len;i++){
            int pos = word[i]-'a';
            if(p->child[pos] == NULL){
                p->child[pos] = new TrieNode();
            }

            p = p->child[pos];
        }
        p->end = true;//mark the end of tree

    }

    // Returns if the word is in the data structure. A word could
    // contain the dot character '.' to represent any one letter.
    bool search(string word) {
        return searchvalid(word,root);
    }

    bool searchvalid(string word, TrieNode * p){

        if(p==NULL)
            return false;
        int len = word.size();
        if(len == 0)
            return p->end;

        for(int i=0;i<len;i++){
            if(word[i]=='.'){
                //check all possible solution

                for(int j=0;j<26;j++){
                    if(p->child[j]!=NULL){
                         //check all possible solutions
                         if(searchvalid(word.substr(i+1,len-i),p->child[j]))
                            return true;
                    }
                }
                return false;

            }else{
                int pos=word[i]-'a';
                if(p->child[pos] == NULL)
                    return false;

                p=p->child[pos];
            }
        }

        return p->end;
    }
};

```
