//https://leetcode.com/problems/longest-increasing-path-in-a-matrix/
/*
Given an integer matrix, find the length of the longest increasing path.
From each cell, you can either move to four directions: left, right, up or down. You may NOT move diagonally or move outside of the boundary (i.e. wrap-around is not allowed).

Example 1:
nums = [
  [9,9,4],
  [6,6,8],
  [2,1,1]
]
Return 4
The longest increasing path is [1, 2, 6, 9].

Example 2:
nums = [
  [3,4,5],
  [3,2,6],
  [2,2,1]
]
Return 4
The longest increasing path is [3, 4, 5, 6]. Moving diagonally is not allowed.
*/
//Method 1: DFS, O(n^4)
class Solution {
    int row = 0;
    int col = 0;
public:
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
};


//DP, based on former method, if we already know certain grid's LIP, we do not need to calculate again
class Solution {
    int row = 0;
    int col = 0;
public:
    //idea same as Longest increase substring, just in 2D
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
};
