//https://leetcode.com/problems/best-time-to-buy-and-sell-stock-with-cooldown/
/*
Say you have an array for which the ith element is the price of a given stock on day i.
Design an algorithm to find the maximum profit. You may complete as many transactions as you like (ie, buy one and sell one share of the stock multiple times) with the following restrictions:

You may not engage in multiple transactions at the same time (ie, you must sell the stock before you buy again).
After you sell your stock, you cannot buy stock on next day. (ie, cooldown 1 day)
Example:

prices = [1, 2, 3, 0, 2]
maxProfit = 3
transactions = [buy, sell, cooldown, buy, sell]
*/

class Solution {
public:
  int maxProfit(vector<int>& prices) {
      /*
      maintain multiple dp sequence
      buy[i] means before day i what is the maxProfit for any sequence end with buy.
      sell[i] means before day i what is the maxProfit for any sequence end with sell.
      rest[i] means before day i what is the maxProfit for any sequence end with rest.
      buy [i] = max(rest[i-1]-prices[i], buy[i-1])  //either you can buy right now after rest, or just bought last day
      sell[i] = max(buy[i-1]+prices[i],sell[i-1])   //either you can sell today or do not sell
      rest[i] = max(sell[i-1],buy[i-1],rest[i-1])   //either last day is buy, sell or rest
      */
      
      int len = prices.size();
      if(len==0)
          return 0;
      vector<int> buy(len,0);
      vector<int> sell(len,0);
      vector<int> rest(len,0);
      buy[0] = -prices[0];
      sell[0] = 0;
      rest[0] = 0;
      
      for(int i=1;i<len;i++){
          buy [i] = max(rest[i-1]-prices[i], buy[i-1]);  //either you can buy right now after rest, or just bought last day
          sell[i] = max(buy[i-1]+prices[i],sell[i-1]);   //either you can sell today or do not sell
          rest[i] = max(max(sell[i-1],buy[i-1]),rest[i-1]);   //either last day is buy, sell or rest            
      }
      
      return max(sell[len-1],rest[len-1]);
      
  }
};
