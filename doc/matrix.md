<!-- START doctoc generated TOC please keep comment here to allow auto update -->
<!-- DON'T EDIT THIS SECTION, INSTEAD RE-RUN doctoc TO UPDATE -->
**Table of Contents**  *generated with [DocToc](https://github.com/thlorenz/doctoc)*

- [Matrix Problem](#matrix-problem)
  - [General Techniques](#general-techniques)
    - [Use DFS or BFS to search](#use-dfs-or-bfs-to-search)
      - [DFS usually for sub region](#dfs-usually-for-sub-region)
      - [BFS For Path Problem](#bfs-for-path-problem)
    - [Stop Conditions:](#stop-conditions)
  - [Sub region](#sub-region)
    - [Number of Islands](#number-of-islands)
      - [Number of Closed Islands](#number-of-closed-islands)
  - [Shorest/Longest Path in Matrix](#shorestlongest-path-in-matrix)
    - [Longest Increase Path](#longest-increase-path)
    - [Walls and gates](#walls-and-gates)
    - [Shortest Path in Binary Matrix](#shortest-path-in-binary-matrix)
    - [As Far from Land as Possible](#as-far-from-land-as-possible)
  - [Pattern Along row/col Problem](#pattern-along-rowcol-problem)
    - [Lonely Pixel](#lonely-pixel)
    - [Bomb Enemy](#bomb-enemy)
  - [Largest square/rectangle inside](#largest-squarerectangle-inside)
    - [Maximal-square](#maximal-square)
- [Sparse Matrix](#sparse-matrix)
  - [Sparse Matrix Representation](#sparse-matrix-representation)
  - [Add/Transpose/Multiply Operations](#addtransposemultiply-operations)

<!-- END doctoc generated TOC please keep comment here to allow auto update -->

# Matrix Problem

## General Techniques

### Use DFS or BFS to search

#### DFS usually for sub region

For subregion problem, usually started with target pixel and traversal region, need some matrix to record visited flag or directly modify the original matrix.

pros of using DFS from one pixel can cover all that sub region

#### BFS For Path Problem

start with path starting or ending point. usually for longest/shortest , largest/smallest path problem. pros of BFS is you can start from several points(insert all of them first into queue), and search level by level, once you reach some condition, you can stop without other path to further search

### Stop Conditions:

  * visited conditions
  * updated cell value larger or smaller than new DFS/BFS ones


## Sub region

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

#### Number of Closed Islands

https://leetcode.com/problems/number-of-closed-islands/

Given a 2D grid consists of 0s (land) and 1s (water).  An island is a maximal 4-directionally connected group of 0s and a closed island is an island totally (all left, top, right, bottom) surrounded by 1s.

Return the number of closed islands.


```CPP
int row = 0;
    int col = 0;
    int closedIsland(vector<vector<int>>& grid) {
        row = grid.size();
        if(row==0)
            return false;
        col = grid[0].size();
        
        int ret = 0;
        
        for(int i=0;i<row;i++){
            for(int j=0;j<col;j++){
                if(grid[i][j]==0){
                    if(DFS(grid, i, j)==true){
                        ret++;
                    }
                }
            }
        }
        
        return ret;
    }
    
    bool DFS(vector<vector<int>>& grid, int x, int y){

        //out boundary, not closed
        if ( x<0 || x>=row || y<0 || y>=col){
            return false;
        }
        
        //to water bouundary
        if(grid[x][y]==1){
            return true;
        }
        
        grid[x][y]=1; //mark 1 so we do not need to revisit
        
        bool up = DFS(grid, x, y+1);
        bool down = DFS(grid, x, y-1);
        bool left = DFS(grid, x-1, y);
        bool right = DFS(grid, x+1, y);
        
        return up && down && left && right;
        
    }
```

## Shorest/Longest Path in Matrix

* DFS
* BFS

Usually BFS is better since we can go level by level, also allow us to search from multiple different points
otherwise DFS needs to travel to end from one point which could be very deep.

For BFS, need to check stop condition

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

https://leetcode.com/problems/walls-and-gates/#/description
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

```CPP
//BFS Solution

void wallsAndGates(vector<vector<int>>& rooms) {
        int row = rooms.size();
        if(row==0)
            return;
        
        int col = rooms[0].size();
        
        
        
        queue<pair<int,int>> q;
        
        for(int i=0;i<row;i++){
            for(int j=0;j<col;j++){
                if(rooms[i][j]==0){
                    q.push(make_pair(i,j));
                }
            }
        }
        
        vector<vector<int>> dirs = {{1,0},{0,1},{-1,0},{0, -1}};
        
        while(!q.empty()){
            
            pair<int,int> pos = q.front();
            q.pop();
            for(auto dir: dirs){
                int x = pos.first + dir[0];
                int y = pos.second + dir[1];
                
                if(x<0 || x>=row || y<0 || y>=col || rooms[x][y] ==-1)
                    continue;
                //not visited, or visited but has a closer path to gate, insert to queue
                if(rooms[x][y] > rooms[pos.first][pos.second]+1){
                    rooms[x][y] = rooms[pos.first][pos.second]+1;
                    q.push(make_pair(x,y));
                }
                
            }
        }
```

### Shortest Path in Binary Matrix

https://leetcode.com/problems/shortest-path-in-binary-matrix/

In an N by N square grid, each cell is either empty (0) or blocked (1).

A clear path from top-left to bottom-right has length k if and only if it is composed of cells C_1, C_2, ..., C_k such that:

```
Adjacent cells C_i and C_{i+1} are connected 8-directionally (ie., they are different and share an edge or corner)
C_1 is at location (0, 0) (ie. has value grid[0][0])
C_k is at location (N-1, N-1) (ie. has value grid[N-1][N-1])
If C_i is located at (r, c), then grid[r][c] is empty (ie. grid[r][c] == 0).
Return the length of the shortest such clear path from top-left to bottom-right.  If such a path does not exist, return -1.
```

Thos shortest path problem can usually solved by BFS, so we can exit immediately if shortest path has been found

```CPP
int shortestPathBinaryMatrix(vector<vector<int>>& grid) {
        int row = grid.size();
        int col = grid[0].size();
        if (grid[0][0]==1 || grid[row-1][col-1]==1)
            return -1;
        //possible to visit all 8 directions
        vector<vector<int>> directions = {{1,1}, {0,1},{1,0},{0,-1},{-1,0},{-1, -1},{1, -1},{-1, 1}};
        queue<pair<int,int>> q;
        //start count
        grid[0][0] =1;
        q.push(make_pair(0,0));
        
        while(!q.empty()){
            auto cur = q.front();
            int x = cur.first, y = cur.second;
            //finish to end, exist
            if( x == row -1 && y == col -1) 
                return grid[x][y];

            for(auto direction : directions){
                int nx = x + direction[0];
                int ny = y + direction[1];
                if(nx >= 0 && nx < row && ny >= 0 && ny < col && grid[nx][ny] == 0){
                    q.push(make_pair(nx,ny));
                    grid[nx][ny] = grid[x][y] + 1;
                }
            }
            q.pop();
        }
        
        return -1;
        
    }
```


### As Far from Land as Possible

https://leetcode.com/problems/as-far-from-land-as-possible/

Given an n x n grid containing only values 0 and 1, where 0 represents water and 1 represents land, find a water cell such that its distance to the nearest land cell is maximized, and return the distance. If no land or water exists in the grid, return -1.

The distance used in this problem is the Manhattan distance: the distance between two cells (x0, y0) and (x1, y1) is |x0 - x1| + |y0 - y1|.

 
```
Example 1:


Input: grid = [[1,0,1],[0,0,0],[1,0,1]]
Output: 2
Explanation: The cell (1, 1) is as far as possible from all the land with distance 2.
Example 2:


Input: grid = [[1,0,0],[0,0,0],[0,0,0]]
Output: 4
Explanation: The cell (2, 2) is as far as possible from all the land with distance 4.
```
* DFS Solution

```CPP
int row = 0;
    int col = 0;
    int maxDistance(vector<vector<int>>& grid) {
        row = grid.size();
        col = grid[0].size();
        
        int ret = 0;
        for(int i=0;i<row;i++){
            for(int j=0;j<col;j++){
                if(grid[i][j]==1){
                    grid[i][j] = 0; //critical to set, otherwise won't start
                    //use >1 to represent the distance
                    DFS(grid, i, j, 1);
                }
            }
        }
        
        //above iteration ensure all distance is to nearest land
       for(int i=0;i<row;i++){
            for(int j=0;j<col;j++){
               if (grid[i][j] > 1) 
                   ret = max(ret, grid[i][j] - 1);
            }
        }
        
        
        return ret==0?-1:ret;
    }
    
    void DFS(vector<vector<int>>& grid, int i, int j, int dist){
        //reach boudary or land, or already found shorter path to a land
        if(i<0 || i >= row || j<0 || j >= col || (grid[i][j] != 0 && grid[i][j] <= dist))
            return;
        
        grid[i][j] = dist;
        DFS(grid, i - 1, j, dist + 1);
        DFS(grid, i + 1, j, dist + 1);
        DFS(grid, i, j - 1, dist + 1);
        DFS(grid, i, j + 1, dist + 1);
    }
```

* BFS way

```CPP
int maxDistance(vector<vector<int>>& grid) {
        int row = grid.size();
        int col = grid[0].size();
        
        queue<pair<int, int>> q;
        
        vector<vector<int>> gridValues(row, vector<int>(col, INT_MAX));
        
        int ret = -1;
        for(int i=0;i<row;i++){
            for(int j=0;j<col;j++){
                if(grid[i][j]==1){
                    q.push(make_pair(i,j));
                    gridValues[i][j] = 0;
                }
            }
        }
        
        if(q.empty())
            return -1;
        
        //four direction
        vector<int> dx({0, 1, 0, -1});
        vector<int> dy({1, 0, -1, 0});
        
        //using BFS, we start level by level, first level is cloest to 1, then next level, 
        //this ensure we do not go too deep from one level

        while (!q.empty())
        {
            auto pos = q.front();
            q.pop();
            
            for (int i = 0; i < 4; ++i)
            {
                int x = pos.first + dx[i];
                int y = pos.second + dy[i];
                
                if (x >= 0 && x < row && y >= 0 && y < col)
                {
                    if (gridValues[x][y] == INT_MAX)
                    {   //not visited before
                        q.push(make_pair(x, y));
                    }
          //  updated to the distance to nearest land cell. 
                    gridValues[x][y] = 
                        min(gridValues[x][y], gridValues[pos.first][pos.second] + 1);
                }
            }
        }
        
    // Step 3: find the maximum values in gridValues.
        for (int i = 0; i < row; ++i)
        {
            for (int j = 0; j < col; ++j)
            {
                if (grid[i][j] == 0)
                {
                    ret = max(ret, gridValues[i][j]);
                }
            }
        }
        
        return ret;

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

# Sparse Matrix

## Sparse Matrix Representation

A sparse matrix can be represented by using TWO representations, those are as follows...

* Triplet Representation (Array Representation)
* Linked Representation

```CPP
int main()
{
    // sparse matrix of class 5x6 with 6 non-zero values
    int sparseMatrix[5][6] =
    {
        {0 , 0 , 0 , 0 , 9, 0 },
        {0 , 8 , 0 , 0 , 0, 0 },
        {4 , 0 , 0 , 2 , 0, 0 },
        {0 , 0 , 0 , 0 , 0, 5 },
        {0 , 0 , 2 , 0 , 0, 0 }
    };

    int width = sparseMatrix.size();
    int height = sparseMatrix[0].size();

    // Finding total non-zero values in the sparse matrix
    int size = 0;
    for (int row = 0; row < width; row++)
        for (int column = 0; column < height; column++)
            if (sparseMatrix[row][column] != 0)
                size++;

    // Defining result Matrix
    int resultMatrix[3][size];

    // Generating result matrix
    int k = 0;
    for (int row = 0; row < height; row++)
        for (int column = 0; column < height; column++)
            if (sparseMatrix[row][column] != 0)
            {
                resultMatrix[0][k] = row;
                resultMatrix[1][k] = column;
                resultMatrix[2][k] = sparseMatrix[row][column];
                k++;
            }

    // Displaying result matrix
    cout<<"Triplet Representation : "<<endl;
    for (int row=0; row<3; row++)
    {
        for (int column = 0; column<size; column++)
            cout<<resultMatrix[row][column]<<" ";

        cout<<endl;
    }
    return 0;
}
```

## Add/Transpose/Multiply Operations

Design a Sparse Matrix Class, Implement Add, Transpose, Multiply 

https://www.geeksforgeeks.org/operations-sparse-matrices/

```CPP
class sparse_matrix 
{ 
    const MAX = 10000;  //should be less than row x col
    // Double-pointer initialized by  
    // the constructor to store  
    // the triple-represented form 
    int **data; 
  
    // dimensions of matrix 
    int row, col; 
  
    // total number of elements in matrix 
    int len; 

public: 
    //contructor
    sparse_matrix(int r, int c) 
    { 
  
        // initialize row 
        row = r; 
  
        // initialize col 
        col = c; 
  
        // initialize length to 0 
        len = 0; 
  
        //Array of Pointer to make a matrix 
        data = new int *[MAX]; 
  
        // Array representation 
        // of sparse matrix 
        //[,0] represents row 
        //[,1] represents col 
        //[,2] represents value 
        for (int i = 0; i < MAX; i++) 
            data[i] = new int[3]; 
    } 

    void insert(int r, int c, int val){
      // invalid entry 
        if (r > row || c > col) 
        { 
            return; 
        } 
        else
        { 
            data[len][0] = r; 
            data[len][1] = c; 
            data[len][2] = val; 
            len++; 
        } 
    }

    void add(sparse_matrix b) 
    { 
        // if matrices don't have same dimensions 
        if (row != b.row || col != b.col) 
        {
            cout << "Matrices can't be added"; 
            return;
        }

        int apos = 0, bpos = 0; 
        sparse_matrix result(row, col); 

        while(apos < len && bpos < b.len){
          //b's row or col is smaller, 
          if(data[apos][0] > b.data[bpos][0] || 
            (data[apos][0] == b.data[bpos][0] && data[apos][1] > b.data[bpos][1])){

            result.insert(b.data[bpos][0], b.data[bpos][1], b.data[bpos][2]); 
            bpos++; 
          }// a's row or col is smaller
          else if(data[apos][0] < b.data[bpos][0] || 
            (data[apos][0] == b.data[bpos][0] && data[apos][1] < b.data[bpos][1])){

            result.insert(data[bpos][0], data[bpos][1], data[bpos][2]); 
            apos++; 
          }else{
            int newVal = data[apos][2] +  b.data[bpos][2]; 
            if(addedval !=0){
              //sparse, so do not record 0
              result.insert(data[apos][0], data[apos][1], newVal); 

            }
            apos++; 
            bpos++; 
          }

        }

        // insert remaining elements 
        while (apos < len) 
          result.insert(data[apos][0], data[apos][1], data[apos++][2]); 
  
        while (bpos < b.len) 
          result.insert(b.data[bpos][0], b.data[bpos][1], b.data[bpos++][2]); 

    }

    void multiply(sparse_matrix b) 
    { 
        if (col != b.row) 
        { 
  
            // Invalid multiplication 
            cout << "Can't multiply, Invalid dimensions"; 
            return; 
        } 
  
        // transpose b to compare row 
        // and col values and to add them at the end 
        b = b.transpose(); 
        int apos, bpos; 
  
        // result matrix of dimension row X b.col 
        // however b has been transposed, 
        // hence row X b.row 
        sparse_matrix result(row, b.row); 
  
        // iterate over all elements of A 
        for (apos = 0; apos < len;) 
        { 
  
            // current row of result matrix 
            int r = data[apos][0]; 
  
            // iterate over all elements of B 
            for (bpos = 0; bpos < b.len;) 
            { 
  
                // current column of result matrix 
                // data[,0] used as b is transposed 
                int c = b.data[bpos][0]; 
  
                // temporary pointers created to add all 
                // multiplied values to obtain current 
                // element of result matrix 
                int tempa = apos; 
                int tempb = bpos; 
  
                int sum = 0; 
  
                // iterate over all elements with 
                // same row and col value 
                // to calculate result[r] 
                while (tempa < len && data[tempa][0] == r && 
                       tempb < b.len && b.data[tempb][0] == c) 
                { 
                    if (data[tempa][1] < b.data[tempb][1]) 
  
                        // skip a 
                        tempa++; 
  
                    else if (data[tempa][1] > b.data[tempb][1]) 
  
                        // skip b 
                        tempb++; 
                    else
  
                        // same col, so multiply and increment 
                        sum += data[tempa++][2] *  
                             b.data[tempb++][2]; 
                } 
  
                // insert sum obtained in result[r] 
                // if its not equal to 0 
                if (sum != 0) 
                    result.insert(r, c, sum); 
  
                while (bpos < b.len &&  
                       b.data[bpos][0] == c) 
  
                    // jump to next column 
                    bpos++; 
            } 
            while (apos < len && data[apos][0] == r) 
  
                // jump to next row 
                apos++; 
        } 
        result.print(); 
    } 
}
```
