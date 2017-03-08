//https://leetcode.com/problems/guess-number-higher-or-lower-ii/
/*
We are playing the Guess Game. The game is as follows:
I pick a number from 1 to n. You have to guess which number I picked.
Every time you guess wrong, I'll tell you whether the number I picked is higher or lower.
However, when you guess a particular number x, and you guess wrong, you pay $x. You win the game when you guess the number I picked.

Example:

n = 10, I pick 8.

First round:  You guess 5, I tell you that it's higher. You pay $5.
Second round: You guess 7, I tell you that it's higher. You pay $7.
Third round:  You guess 9, I tell you that it's lower. You pay $9.

Game over. 8 is the number I picked.

You end up paying $5 + $7 + $9 = $21.
Given a particular n ≥ 1, find out how much money you need to have to guarantee a win.
*/

class Solution {
public:
    int getMoneyAmount(int n) {
        /*
        dp[i,j] is min needs to be paid to guarantee to win in range i->j
        dp[i,i] is 0; only single number, always guess right win.
        we can choose k (i<=k<=j) as our guess, and pay price k. After our guess, the problem is divided into two subproblems. Notice we do not need to pay the money for both subproblems
        dp[i,j] = min{max(dp[i,k-1],dp[k+1,j])+k}. i<k<j
        
        */
        if(n==1 || n==0)
            return 0;
        
        vector<vector<int>>dp(n+1,vector<int>(n+1));

        int local_max;
        /*
        why 
        
        for(int i=1; i<=n; i++){
            for(int j=i+1; j<=n; j++){
        dose not work?
        
        because to get any dp[i][j], we need to first have dp[i][k-1] and dp[k+1][j], so we need to have dp[i][j] for small interval then calculate large interval, 
        */
        for(int i=n-1; i>=1; i--){
            for(int j=i+1; j<=n; j++){

                int global_min = INT_MAX;
                for(int k=i;k<=j;k++){
                    //boundary case process
                    local_max = k + max(k-1>=i?dp[i][k-1]:0, k+1<=j?dp[k+1][j]:0); //max(dp[i,k-1],dp[k+1,j])+k
                    global_min = min(global_min, local_max); //min{max(dp[i,k-1],dp[k+1,j])+k}
                }
                //if they are adjecent, problem transfer into one choice from two, only pay less
                dp[i][j] = global_min; 
            }
        }
        
        return dp[1][n];
    }
};
