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
//method 2: made simple, use one d vector
class Solution {
public:
	int maxKilledEnemies(vector<vector<char>>& grid) {
		int row = grid.size();
		if (!row) return 0;
		int col = grid[0].size();
		int ret = 0;
		vector<int> row_enemy(row, 0); //enemy killed for fixed row along col
		vector<int> col_enemy(col, 0); //enemy killed for fixed col along row

		for (int i = 0; i<row; i++) {
			for (int j = 0; j<col; j++) {
				if (j == 0 || grid[i][j - 1] == 'W') {
					//starting from current, fix row to extend col
					row_enemy[i] = rowArea(grid, i, j);
				}
				if (i == 0 || grid[i - 1][j] == 'W') {
					//starting from current, fix col to extend row
					col_enemy[j] = colArea(grid, i, j);
				}
				if (grid[i][j] == '0') {
					ret = ret>(row_enemy[i] + col_enemy[j]) ? ret : (row_enemy[i] + col_enemy[j]);
				}
			}
		}

		return ret;
	}

	int rowArea(vector<vector<char>>& grid, int row, int col) {
		int ret = 0;
		while (col<grid[row].size() && grid[row][col] != 'W') {
			if (grid[row][col] == 'E')
				ret++;
			col++;
		}
		return ret;
	}
	int colArea(vector<vector<char>>& grid, int row, int col) {
		int ret = 0;
		while (row<grid.size() && grid[row][col] != 'W') {
			if (grid[row][col] == 'E')
				ret++;
			row++;
		}
		return ret;
	}
};
