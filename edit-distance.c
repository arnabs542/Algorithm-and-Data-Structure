//https://leetcode.com/problems/edit-distance/
/*
Given two words word1 and word2, find the minimum number of steps required to convert word1 to word2. (each operation is counted as 1 step.)

You have the following 3 operations permitted on a word:

a) Insert a character
b) Delete a character
c) Replace a character
*/

class Solution {
public:
  int minDistance(string word1, string word2) {
      /*
      dp: dp[i][j] is min steps from word1[0:i] to word2 [0:j]
      dp[i][j] = min (dp[i-1][j]+1, dp[i][j-1]+1, dp[i-1][j-1]+1/0). 
      */
      int m=word1.size();
      int n=word2.size();
      
      if(m==0)
          return n;
      if(n==0)
          return m;
      
      vector<vector<int>> dp(m+1,vector<int>(n+1,0));
      
      for(int i=1;i<=m;i++)
          dp[i][0] = i;
          
      for(int j=1;j<=n;j++)
          dp[0][j] = j;
          
      for(int i=1;i<=m;i++){
          for(int j=1;j<=n;j++){
              if(word1[i-1]==word2[j-1])
                  dp[i][j] = min(min(dp[i-1][j]+1, dp[i][j-1]+1), dp[i-1][j-1]);
              else
                  dp[i][j] = min(min(dp[i-1][j]+1, dp[i][j-1]+1), dp[i-1][j-1]+1);
          }
      }
      
      return dp[m][n];
  }
};
