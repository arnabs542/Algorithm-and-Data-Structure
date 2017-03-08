//https://leetcode.com/problems/coin-change/

/*
You are given coins of different denominations and a total amount of money amount. Write a function to compute the fewest number of coins that you need to make up that amount. If that amount of money cannot be made up by any combination of the coins, return -1.

Example 1:
coins = [1, 2, 5], amount = 11
return 3 (11 = 5 + 5 + 1)

Example 2:
coins = [2], amount = 3
return -1.
*/

class Solution {
public:
    int coinChange(vector<int>& coins, int amount) {
        //DP: dp[i] indicates fewest number of coins for amount i
        //DP[i] = min(DP[i],DP[i-coin[j]+1)
        if(amount==0)
            return 0;
        
        vector<int> DP(amount+1,amount+1);
        DP[0] = 0;
        
        for(int i=1;i<=amount;i++){
            for(int j=0;j<coins.size();j++){
                if(i>=coins[j])
                    DP[i]=min(DP[i],DP[i-coins[j]]+1);
            }
        }
        
        return DP[amount]==amount+1?-1:DP[amount];
    }
};
