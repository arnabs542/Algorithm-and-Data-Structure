
//https://leetcode.com/problems/longest-palindromic-subsequence/#/

//recursive,O(2^n)
int longestPalindromeSubseq(string s) {
    return help(s, 0,s.size()-1);
}

int help(string &s, int l, int r){
    if(l==r)
        return 1;
    if(l>r)
        return 0;
    if(s[l]==s[r])
        return 2+help(s,l+1,r-1);
    else
        return max(help(s,l,r-1),help(s,l+1,r));
}

//two dimensional DP,
//recursive to DP, memorize, O(n^2)
int longestPalindromeSubseq(string s) {
    int len = s.size();
    //dp[l][r] is longestPalindromeSubseq from l to r
    vector<vector<int>> dp(len,vector<int>(len,0));
    return help(s, 0,s.size()-1, dp);
}

int help(string &s, int l, int r, vector<vector<int>> &dp){
    if(l==r)
        return 1;
    if(l>r)
        return 0;
    if(s[l]==s[r]){
        dp[l][r]==0?dp[l][r]=2+help(s,l+1,r-1,dp):dp[l][r];
    }
    else{
        dp[l][r]==0?dp[l][r]=max(help(s,l+1,r,dp),help(s,l,r-1,dp)):dp[l][r];
    }
    return dp[l][r];
}


//DP
int longestPalindromeSubseq(string s) {
    int len = s.size();
    ////dp[l][r] is longestPalindromeSubseq from l to r
    vector<vector<int>> dp(len,vector<int>(len,0));
    for(int j=0;j<len;j++){
        for(int i=j;i>=0;i--){
            if(i==j){
                dp[i][j] = 1;
            }else{
                if(s[i]==s[j]){
                    dp[i][j] = dp[i+1][j-1] + 2;
                }else{
                    dp[i][j] = max(dp[i+1][j], dp[i][j-1]);
                }

            }
        }
    }
    return dp[0][len-1];
}
