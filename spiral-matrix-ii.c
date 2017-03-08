//https://leetcode.com/problems/spiral-matrix-ii
/*
Given an integer n, generate a square matrix filled with elements from 1 to n2 in spiral order.
For example,
Given n = 3,

You should return the following matrix:
[
 [ 1, 2, 3 ],
 [ 8, 9, 4 ],
 [ 7, 6, 5 ]
]
*/
class Solution {
public:
    vector<vector<int>> generateMatrix(int n) {
        int row_start = 0;
        int row_end = n-1;
        int col_start = 0;
        int col_end = n-1;
        vector<vector<int>> ret(n,vector<int>(n,0));
        int num = 1;
        while(row_start<row_end && col_start<col_end){
            for(int i=col_start;i<=col_end;i++){
                ret[row_start][i]=num;
                num++;
            }
            row_start++;
            for(int i=row_start;i<=row_end;i++){
                ret[i][col_end]=num;
                num++;
            }
            col_end--;
            for(int i=col_end;i>=col_start;i--){
                ret[row_end][i] = num;
                num++;
            }
            row_end--;
            for(int i=row_end;i>=row_start;i--){
                ret[i][col_start]=num;
                num++;
            }
            col_start++;
        }
        if(row_start==row_end && col_start==col_end)
            ret[row_start][col_start]=num;
        return ret;
    }
};
