//https://leetcode.com/problems/number-of-islands/
//https://leetcode.com/problems/number-of-islands/
/*
Given a 2d grid map of '1's (land) and '0's (water), count the number of islands. An island is surrounded by water and is formed by connecting adjacent lands horizontally or vertically. You may assume all four edges of the grid are all surrounded by water.

Example 1:

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
*/
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

};
