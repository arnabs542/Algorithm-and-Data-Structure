//https://leetcode.com/problems/longest-line-of-consecutive-one-in-matrix

/*
Given a 01 matrix M, find the longest line of consecutive one in the matrix. The line could be horizontal, vertical, diagonal or anti-diagonal.

Example:
Input:
[[0,1,1,0],
 [0,1,1,0],
 [0,0,0,1]]
Output: 3
*/


int longestLine(vector<vector<int>>& M) {
    //easy solution, go through hori, vertical, diagonal or anti-diagonal using dp way
    int m=M.size();
    if(m==0)
        return 0;
    int n=M[0].size();
    int ret = 0;

    vector<vector<vector<int>>> dp(m,vector<vector<int>>(n,vector<int>(4,0))); //m x n x 4
    for(int i=0;i<m;i++){
        for(int j=0;j<n;j++){
            if(M[i][j]==1){
                for(int k=0;k<4;k++){
                    dp[i][j][k] = 1;
                    ret = max(ret,1);
                }
                //for horizontal
                if(j>0){
                    dp[i][j][0] += dp[i][j-1][0];
                    ret = max(ret,dp[i][j][0]);
                }
                //vertical
                if(i>0){
                    dp[i][j][1] += dp[i-1][j][1];
                    ret = max(ret, dp[i][j][1]);
                }
                //diagnol
                if(i>0 && j>0){
                    dp[i][j][2] += dp[i-1][j-1][2];
                    ret = max(ret,dp[i][j][2]);
                }
                //anti_diagnol
                if(i>0 && j<n-1){
                    dp[i][j][3] += dp[i-1][j+1][3];
                    ret = max(ret,dp[i][j][3]);
                }
            }
        }
    }
    return ret;
}
