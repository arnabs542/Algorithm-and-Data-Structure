//https://leetcode.com/problems/burst-balloons/
/*
Given n balloons, indexed from 0 to n-1. Each balloon is painted with a number on it represented by array nums. You are asked to burst all the balloons. If the you burst balloon i you will get nums[left] * nums[i] * nums[right] coins. 
Here left and right are adjacent indices of i. After the burst, the left and right then becomes adjacent.
Find the maximum coins you can collect by bursting the balloons wisely.

Note: 
(1) You may imagine nums[-1] = nums[n] = 1. They are not real therefore you can not burst them.
(2) 0 ≤ n ≤ 500, 0 ≤ nums[i] ≤ 100

Example:
Given [3, 1, 5, 8]
Return 167
    nums = [3,1,5,8] --> [3,5,8] -->   [3,8]   -->  [8]  --> []
   coins =  3*1*5      +  3*5*8    +  1*3*8      + 1*8*1   = 167
*/

class Solution {
public:
  int maxCoins(vector<int>& nums) {
      /*
      DP, 
      supposing DP[i,j] is max value when bursting ballon from i->j(i and j will stay)
      //first to extend the array with 1 for begining and end: 1),3,1,5,8,(1
      ex: one state(assuming we first select 1) =  1*3*5 + max(1,3)+ max(5,1)
      idea is to calculate all max(i,j) from i to j. (i<j)
      if choose i ballon
      dp(start,end) = max(dp(start,end),dp(start,i)+dp(i,end)+i*nums[start]*nums[end]
      */
     
      nums.push_back(1);
      nums.insert(nums.begin(),1);
      int len = nums.size();
      vector<vector<int>> dp(len,vector<int>(len,0));
      
      for(int k=1;k<=len;k++){
          for(int start=0;start+k<len;start++){
              int end = start+k;
              for(int i=start+1;i<end;i++){
                  dp[start][end] = max(dp[start][end],nums[start]*nums[i]*nums[end]+dp[start][i]+dp[i][end]);
              }
          }
      }
      
      
      return dp[0][len-1];
  }
};
