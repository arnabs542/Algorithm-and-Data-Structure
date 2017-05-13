https://leetcode.com/problems/interleaving-string/#/description

Given s1, s2, s3, find whether s3 is formed by the interleaving of s1 and s2.

For example,
Given:
s1 = "aabcc",
s2 = "dbbca",

When s3 = "aadbbcbcac", return true.
When s3 = "aadbbbaccc", return false.

bool isInterleave(string s1, string s2, string s3) {
    int len1 = s1.size();
    int len2 = s2.size();
    int len3 = s3.size();
    if(len3!=len1+len2)
        return false;
    //dp[i+1][j+1] means whether s1(0:i) and s2(0:j) can interleave s3(0:i+j+1)
    vector<vector<bool>> dp(len1+1,vector<bool>(len2,false));
    dp[0][0] = true;

    for(int i=1;i<=len1;i++){
        //whether s1(0:i-1) can interleave s3 without s2
        dp[i][0] = dp[i-1][0] && (s1[i-1]==s3[i-1]);
    }
    for(int j=1;j<=len2;j++){
        //whether s2(0:j-1) can interleave s3 without s1
        dp[0][j] = dp[0][j-1] && (s2[j-1]==s3[j-1]);
    }

    for(int i=1;i<=len1;i++){
        for(int j=1;j<=len2;j++){
            dp[i][j] = dp[i-1][j] &&(s1[i-1]==s3[i+j-1]) || dp[i][j-1] && (s2[j-1]==s3[i+j-1]);
        }
    }
    return dp[len1][len2];
}
