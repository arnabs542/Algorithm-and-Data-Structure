//https://leetcode.com/problems/best-time-to-buy-and-sell-stock-iii/
/*
you have an array for which the ith element is the price of a given stock on day i.
Design an algorithm to find the maximum profit. You may complete at most two transactions.
*/

class Solution {
public:
  int maxProfit(vector<int>& prices) {
      /*
      DP:
      max1[i] is max profit from 0 to i
      max2[i] is max profit from i to len-1
      */
      if (prices.size() <= 1) return 0;
      
      int len=prices.size();
      int minfirst=prices[0];
      int maxsecond=prices[len-1];
      vector<int> max1(len,0);
      vector<int> max2(len,0);
      for(int i=1;i<len-1;i++){
          max1[i] = max(max1[i-1],prices[i]-minfirst);
          minfirst = min(prices[i],minfirst);

      }
      for(int j=len-2;j>=0;j--){
          max2[j] = max(max2[j+1],maxsecond-prices[j]);
          maxsecond = max(maxsecond,prices[j]);            
      }

      int final_max = 0;
      
      for(int i=0;i<len;i++){
          final_max = max(final_max,(max1[i]+max2[i]));
      }
      
      return final_max;
  }
};
