//https://leetcode.com/problems/search-a-2d-matrix/
/*
Write an efficient algorithm that searches for a value in an m x n matrix. This matrix has the following properties:

    Integers in each row are sorted from left to right.
    The first integer of each row is greater than the last integer of the previous row.

For example,

Consider the following matrix:

[
  [1,   3,  5,  7],
  [10, 11, 16, 20],
  [23, 30, 34, 50]
]

Given target = 3, return true.
*/
class Solution {
public:
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        //transfer into a 1d list
         if(matrix.empty() || matrix[0].empty())
        {
            return false;
        }
        int row = matrix.size();
        int col = matrix[0].size();
        int start = 0;
        int end = row*col-1;
        
        while(start<=end){
            int mid = start + (end-start)/2;
            int x = mid/col;
            int y = mid%col;
            if(matrix[x][y]>target){
                end = mid-1;
            }else if(matrix[x][y]<target){
                start = mid+1;
            }else if(matrix[x][y]==target){
                return true;
            }
        }
        return false;
    }
};
