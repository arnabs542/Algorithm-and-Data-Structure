//https://leetcode.com/problems/ugly-number-ii/
/*
Write a program to find the n-th ugly number.
Ugly numbers are positive numbers whose prime factors only include 2, 3, 5. For example, 1, 2, 3, 4, 5, 6, 8, 9, 10, 12 is the sequence of the first 10 ugly numbers.
Note that 1 is typically treated as an ugly number.
*/

class Solution {
public:
  int nthUglyNumber(int n) {
      /*
      dp[i] is the ith ugly numbers,  it could be multiplied by either 2, 3, or 5 from a smaller ugly number.
      like to merge 3 sorted list L2,l3,l5, recording position of smaller ugly number base
      */
      vector<int> dp(n,0);
      int l2=0;
      int l3=0;
      int l5=0;
      dp[0] = 1;
      for(int i=1;i<n;i++){
          dp[i] = min(min(dp[l2]*2,dp[l3]*3),dp[l5]*5);
          if(dp[i]==dp[l2]*2)
              l2++;
          if(dp[i]==dp[l3]*3)
              l3++;
          if(dp[i]==dp[l5]*5)
              l5++;
      }
      return dp[n-1];
  }
};
