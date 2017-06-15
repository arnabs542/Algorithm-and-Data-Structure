<!-- START doctoc generated TOC please keep comment here to allow auto update -->
<!-- DON'T EDIT THIS SECTION, INSTEAD RE-RUN doctoc TO UPDATE -->
**Table of Contents**  *generated with [DocToc](https://github.com/thlorenz/doctoc)*

- [Matrix Problem](#matrix-problem)
  - [Sub region or Path in Matrix](#sub-region-or-path-in-matrix)
  - [Pattern Along row/col Problem](#pattern-along-rowcol-problem)
  - [Largest square/rectangle inside](#largest-squarerectangle-inside)
- [BackTracking](#backtracking)
  - [Common logic](#common-logic)
- [Others](#others)
  - [BFPRT](#bfprt)
  - [Half Majority](#half-majority)
  - [Search a 2D matrix](#search-a-2d-matrix)
  - [First missing positive](#first-missing-positive)

<!-- END doctoc generated TOC please keep comment here to allow auto update -->

# Matrix Problem

## Sub region or Path in Matrix

> Use DFS or BFS to search

* For subregion problem, usually started with target pixel and traversal region, need some matrix to record visited flag or directly modify the original matrix

* For Path Problem, start with path starting or ending point.  


## Pattern Along row/col Problem
search space goes from certain node along its same row and col index

> Common techniques:  Preprocess: Assist with two vector, row and col, and get some feature/sum of characters of same row/col

* Lonely Pixel

https://leetcode.com/problems/lonely-pixel-i/
Given a picture consisting of black and white pixels, find the number of black lonely pixels.
The picture is represented by a 2D char array consisting of 'B' and 'W', which means black and white pixels respectively.

A black lonely pixel is character 'B' that located at a specific position where the same row and same column don't have any other black pixels.

Example:
Input:
[['W', 'W', 'B'],
 ['W', 'B', 'W'],
 ['B', 'W', 'W']]

Output: 3
Explanation: All the three 'B's are black lonely pixels.

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

Example:
For the given grid

0 E 0 0
E 0 W E
0 E 0 0
return 3. (Placing a bomb at (1,1) kills 3 enemies)
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

> * similar as array, usually divide this problem into row and col two array


* Largest Square with all 1 in the boundary
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

* Maximal-square
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

# BackTracking

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
