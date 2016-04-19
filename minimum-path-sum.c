/*
http://www.lintcode.com/en/problem/minimum-path-sum/
Given a m x n grid filled with non-negative numbers, 
find a path from top left to bottom right which minimizes the sum of all numbers along its path.
*/

#include <algorithm> 
class Solution {
public:
    /**
     * @param grid: a list of lists of integers.
     * @return: An integer, minimizes the sum of all numbers along its path
     */
    int minPathSum(vector<vector<int> > &grid) {
        int row = grid.size();
        int col = grid[0].size();
        
        int cur_min[row][col];
        cur_min[0][0] = grid[0][0];
        //int min_global = 0;
        int i,j;
        
        for(i=1;i<row;i++){
            cur_min[i][0] = cur_min[i-1][0] + grid[i][0];
        }
        
        for(j=1;j<col;j++){
            cur_min[0][j] = cur_min[0][j-1] + grid[0][j];
        }
        
        for(i=1;i<row;i++){
            for(j=1;j<col;j++){
                cur_min[i][j] = std::min(cur_min[i][j-1],cur_min[i-1][j])+grid[i][j];
                //min_global = std::min(cur_min[i][j],min_global);
            }
        }
        
        return cur_min[row-1][col-1];
    }
};
