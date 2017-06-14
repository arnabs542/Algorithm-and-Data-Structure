/*
https://leetcode.com/problems/longest-palindromic-substring/#/description
Given a string s, find the longest palindromic substring in s. You may assume that the maximum length of s is 1000.

Example:
Input: "babad"
Output: "bab"
Note: "aba" is also a valid answer.
*/
string longestPalindrome(string s) {
    //dp[i][j] is whether there is palindrome string from i->j inclusive
    //dp[i][j] = dp[i+1][j-1] if s[i]==s[j] and i+1>=j-1
    int len = s.size();
    vector<vector<bool>> dp(len,vector<bool>(len,false));
    string ret="";
    for(int i=0;i<len;i++){
        dp[i][i] = true;
        ret = s[i];
    }
    for(int i=len-1;i>=0;i--){
        for(int j=i+1;j<len;j++){
            if((s[i]==s[j]) && ((i+1>=j-1) || dp[i+1][j-1]))
                dp[i][j] = true;
            if (dp[i][j] && (ret == "" || j-i+1 > ret.length()))
                ret = s.substr(i, j-i+1);
        }
    }
    return ret;
}
