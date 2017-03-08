//https://leetcode.com/problems/unique-paths/
/*
A robot is located at the top-left corner of a m x n grid (marked 'Start' in the diagram below).
The robot can only move either down or right at any point in time. The robot is trying to reach the bottom-right corner of the grid (marked 'Finish' in the diagram below).
How many possible unique paths are there?
*/
//method 2:
class Solution {
public:
    int uniquePaths(int m, int n) {
        vector<int> dp(n,0);

        for(int j=0;j<n;j++)
            dp[j] = 1;        
        for(int i=1;i<m;i++){
            for(int j =1;j<n;j++){
                //here we can use only one vector: dp[j] will add dp[j] from last row and dp[j-1] from just updated current row
                dp[j] +=dp[j-1];
            }
        }
        return dp[n-1];
    }
};
