//https://leetcode.com/problems/triangle/
/*
Given a triangle, find the minimum path sum from top to bottom. Each step you may move to adjacent numbers on the row below.
For example, given the following triangle
[
     [2],
    [3,4],
   [6,5,7],
  [4,1,8,3]
]
The minimum path sum from top to bottom is 11 (i.e., 2 + 3 + 5 + 1 = 11).
Note:
Bonus point if you are able to do this using only O(n) extra space, where n is the total number of rows in the triangle.
*/
class Solution {
public:
    int minimumTotal(vector<vector<int>>& triangle) {
        /*
        dp[i][j] is the min total value when adding triangle[i][j],i is row and j is level. 
        dp[i][j] = min(dp[i][j-1]+triangle[i][j],dp[i][j]+triangle[i+1][j]);
        */
        int height = triangle.size();
        if(height==0)
            return 0;
        vector<vector<int>> dp(height,vector<int>(height,0));
        dp[0][0] = triangle[0][0];
        for(int i=1;i<height;i++){// j is level height
            dp[i][0] = triangle[i][0] + dp[i-1][0]; //for left most, only one path.
            int j;
            for(j=1;j<triangle[i].size()-1;j++){
                
                dp[i][j]=triangle[i][j]+min(dp[i-1][j-1],dp[i-1][j]);
            }
            dp[i][j] = triangle[i][j] + dp[i-1][j-1]; //for right most, only one path.
        }
        int ret = dp[height-1][0];
        for(int x=1;x<triangle[height-1].size();x++){
            ret = ret>dp[height-1][x]?dp[height-1][x]:ret;
        }
        return ret;
    }
};
