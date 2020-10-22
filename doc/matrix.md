<!-- START doctoc generated TOC please keep comment here to allow auto update -->
<!-- DON'T EDIT THIS SECTION, INSTEAD RE-RUN doctoc TO UPDATE -->
**Table of Contents**  *generated with [DocToc](https://github.com/thlorenz/doctoc)*

- [Matrix Problem](#matrix-problem)
  - [Sub region or Path in Matrix](#sub-region-or-path-in-matrix)
    - [Number of Islands](#number-of-islands)
    - [Longest Increase Path](#longest-increase-path)
    - [Walls and gates](#walls-and-gates)
  - [Pattern Along row/col Problem](#pattern-along-rowcol-problem)
    - [Lonely Pixel](#lonely-pixel)
    - [Bomb Enemy](#bomb-enemy)
  - [Largest square/rectangle inside](#largest-squarerectangle-inside)
    - [Maximal-square](#maximal-square)

<!-- END doctoc generated TOC please keep comment here to allow auto update -->

# Matrix Problem

## Sub region or Path in Matrix

> Use DFS or BFS to search

* For subregion problem, usually started with target pixel and traversal region, need some matrix to record visited flag or directly modify the original matrix

* For Path Problem, start with path starting or ending point.

* Stop Conditions:
  * visited conditions
  * updated cell value larger or smaller than new DFS/BFS ones

### Number of Islands

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

### Longest Increase Path

https://leetcode.com/problems/longest-increasing-path-in-a-matrix/

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

### Walls and gates

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

### Lonely Pixel

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

### Bomb Enemy

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

### Maximal-square
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

