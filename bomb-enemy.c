//https://leetcode.com/problems/bomb-enemy/
/*
Given a 2D grid, each cell is either a wall 'W', an enemy 'E' or empty '0' (the number zero), return the maximum enemies you can kill using one bomb.
The bomb kills all the enemies in the same row and column from the planted point until it hits the wall since the wall is too strong to be destroyed.
Note that you can only put the bomb at an empty cell.

Example:
For the given grid

0 E 0 0
E 0 W E
0 E 0 0
return 3. (Placing a bomb at (1,1) kills 3 enemies)
*/
#include <stdlib.h>
class Solution {
public:
    int maxKilledEnemies(vector<vector<char>>& grid) {
        int m = grid.size(), n = m ? grid[0].size() : 0;
        /*
        dp_row represents how many enemy killed in different row same col
        dp_col represents how many enemy killed in different col same row
        */
        int result = 0;
        int num = 0;
        vector<vector<int>> dp_row(m,vector<int>(n,0));
        vector<vector<int>> dp_col(m,vector<int>(n,0));
        for (int i=0; i<m; i++) {
            for (int j=0; j<n; j++) {
                if (!j || grid[i][j-1] == 'W') {
                    num = 0;
                    for (int k=j; k<n && grid[i][k] != 'W'; k++)
                        num += grid[i][k] == 'E';
                    for (int k=j; k<n && grid[i][k] != 'W'; k++)
                        dp_col[i][k] = num;
                }
                if (!i || grid[i-1][j] == 'W') {
                    num = 0;
                    for (int k=i; k<m && grid[k][j] != 'W'; k++)
                        num += grid[k][j] == 'E';
                    for (int k=i; k<m && grid[k][j] != 'W'; k++)
                        dp_row[k][j] = num;
                }
                if (grid[i][j] == '0')
                    result = max(result, dp_row[i][j]+dp_col[i][j]);
            }
        }
        return result;
    }

};
