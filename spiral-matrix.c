//https://leetcode.com/problems/spiral-matrix/
/*
Given a matrix of m x n elements (m rows, n columns), return all elements of the matrix in spiral order.

For example,
Given the following matrix:
[
 [ 1, 2, 3 ],
 [ 4, 5, 6 ],
 [ 7, 8, 9 ]
]
You should return [1,2,3,6,9,8,7,4,5].
*/
class Solution {
public:
    vector<int> spiralOrder(vector<vector<int>>& matrix) {
        vector<int> ret;
        int row = matrix.size();
        if(!row)
            return ret;
        int col = matrix[0].size();
        int row_start = 0;
        int row_end = row-1;
        int col_start = 0;
        int col_end = col-1;
        
        while(row_start<row_end && col_start<col_end){
            for(int i=col_start;i<=col_end;i++){
                ret.push_back(matrix[row_start][i]);
            }
            row_start++;
            for(int i=row_start;i<=row_end;i++){
                ret.push_back(matrix[i][col_end]);
            }
            col_end--;
            for(int i=col_end;i>=col_start;i--){
                ret.push_back(matrix[row_end][i]);
            }
            row_end--;
            for(int i=row_end;i>=row_start;i--){
                ret.push_back(matrix[i][col_start]);
            }
            col_start++;
        }
        //when remaing only one row. 
        if(row_start==row_end){
            for(int i=col_start;i<=col_end;i++){
                ret.push_back(matrix[row_start][i]);
            }
            row_start++;
        }
        //when remaning only one col. noticing last row_start++ could prevent remaning one item to be printed twice
        if(col_start==col_end){
            for(int i=row_start;i<=row_end;i++){
                ret.push_back(matrix[i][col_start]);
            }
        }
        
        return ret;
        
    }
};
