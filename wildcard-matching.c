//https://leetcode.com/problems/wildcard-matching/
/*
'?' Matches any single character.
'*' Matches any sequence of characters (including the empty sequence).

The matching should cover the entire input string (not partial).

The function prototype should be:
bool isMatch(const char *s, const char *p)

Some examples:
isMatch("aa","a") → false
isMatch("aa","aa") → true
isMatch("aaa","aa") → false
isMatch("aa", "*") → true
isMatch("aa", "a*") → true
isMatch("ab", "?*") → true
isMatch("aab", "c*a*b") → false
*/

/*
dp[i][j] indicates whether substring s(0:i-1) matches substring p(0:j-1) 

1, If p[j-1] == s[i-1] :  dp[i][j] = dp[i-1][j-1];
2, If p[j-1] == '?' : dp[i][j] = dp[i-1][j-1];
3, If p[j-1] == '*': 
    dp[i][j] = dp[i-1][j] to check sequence before *
    dp[i][j] = dp[i][j-1] to check sequence after *

*/

//Method 1: DP
class Solution {
public:
    bool isMatch(string s, string p) {

        int len_s = s.size();
        int len_p = p.size();
        

        vector<vector<bool>> dp(len_s+1,vector<bool>(len_p+1,false));
        dp[0][0] = true;
    	for(int j=1; j<=len_p; j++) {
    		if(p[j-1]=='*'){
    			dp[0][j] = true;
    		} else {
    			break;
    		}
    	}
        
        for(int i=1;i<=len_s;i++){
            for(int j=1;j<=len_p;j++){
                if(s[i-1]==p[j-1] || p[j-1]=='?'){
                    dp[i][j] = dp[i-1][j-1];
                }
                if(p[j-1]=='*'){
                    dp[i][j] = dp[i-1][j] || dp[i][j-1];    
                }
            }
        }
            
        return dp[len_s][len_p];
            
    }
};
