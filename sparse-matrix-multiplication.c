//https://leetcode.com/problems/sparse-matrix-multiplication/
/*
Given two sparse matrices A and B, return the result of AB.
You may assume that A's column number is equal to B's row number.

Example:
A = [
  [ 1, 0, 0],
  [-1, 0, 3]
]

B = [
  [ 7, 0, 0 ],
  [ 0, 0, 0 ],
  [ 0, 0, 1 ]
]
     |  1 0 0 |   | 7 0 0 |   |  7 0 0 |
AB = | -1 0 3 | x | 0 0 0 | = | -7 0 3 |
                  | 0 0 1 |

*/
class Solution {
public:
    vector<vector<int>> multiply(vector<vector<int>>& A, vector<vector<int>>& B) {
        
        int a_row = A.size();
        int b_row = B.size();
        //if(a_row==0 || b_row==0)
        //    return ret;
        int a_col = A[0].size();
        int b_col = B[0].size();
        //if(a_col==0 || b_col==0)
        //    return ret;
        //a col==b_row, a_row*b_col
        vector<vector<int>> ret(a_row,vector<int>(b_col,0));
        for(int i=0;i<a_row;i++){
            for(int j=0;j<a_col;j++){
                if(A[i][j]!=0){  //sparse matrix, try to avoid unnecessary cal
                    for(int k=0;k<b_col;k++){
                        if(B[j][k]!=0)
                            ret[i][k] += A[i][j]*B[j][k];
                    }
                }
            }
        }
        
        return ret;
    }
};
