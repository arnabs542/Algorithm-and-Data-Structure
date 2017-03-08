//https://leetcode.com/problems/pacific-atlantic-water-flow/
/*
Given an m x n matrix of non-negative integers representing the height of each unit cell in a continent, the "Pacific ocean" touches the left and top edges of the matrix and the "Atlantic ocean" touches the right and bottom edges.

Water can only flow in four directions (up, down, left, or right) from a cell to another one with height equal or lower.

Find the list of grid coordinates where water can flow to both the Pacific and Atlantic ocean.

Note:
The order of returned grid coordinates does not matter.
Both m and n are less than 150.
Example:

Given the following 5x5 matrix:

  Pacific ~   ~   ~   ~   ~ 
       ~  1   2   2   3  (5) *
       ~  3   2   3  (4) (4) *
       ~  2   4  (5)  3   1  *
       ~ (6) (7)  1   4   5  *
       ~ (5)  1   1   2   4  *
          *   *   *   *   * Atlantic

Return:

[[0, 4], [1, 3], [1, 4], [2, 2], [3, 0], [3, 1], [4, 0]] (positions with parentheses in above matrix).
*/

class Solution {
public:
    vector<pair<int, int>> pacificAtlantic(vector<vector<int>>& matrix) {
        vector<pair<int, int>> ret;
        int row = matrix.size();
        if(!row)
            return ret;
        int col = matrix[0].size();
        //grid ==1 means can flow to sea(p or a)
        vector<vector<int>> p(row,vector<int>(col,0));
        vector<vector<int>> a(row,vector<int>(col,0));
        //check grids 
        for(int i=0;i<row;i++){
            DFS(matrix,p,-1,i,0);
            DFS(matrix,a,-1,i,col-1);
            
        }
        for(int j=0;j<col;j++){
            DFS(matrix,p,-1,0,j);
            DFS(matrix,a,-1,row-1,j);
        }
        
        //adding both
        for(int i=0;i<row;i++){
            for(int j=0;j<col;j++){
                if(p[i][j] && a[i][j]){
                    ret.push_back(make_pair(i,j));
                }
            }
        }
        
        return ret;
        
    }
    
    void DFS(vector<vector<int>>& matrix, vector<vector<int>> &sea, int height, int x, int y){
        int row = matrix.size();
        int col = matrix[0].size();
        //checked out of boudary 
        if( x>=row ||x<0 || y>=col || y<0)
            return;
        //current grid is visited or lower than adjcent, water can not flow to adjcent
        if(sea[x][y] || height>matrix[x][y])
            return;
        sea[x][y] = 1;
        //check water can flow from next grid to current grid, which leads to sea
        
        DFS(matrix,sea,matrix[x][y],x+1,y);
        DFS(matrix,sea,matrix[x][y],x-1,y);
        DFS(matrix,sea,matrix[x][y],x,y+1);
        DFS(matrix,sea,matrix[x][y],x,y-1);
        
    }
   
};
