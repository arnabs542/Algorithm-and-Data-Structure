//https://leetcode.com/problems/regular-expression-matching/
/*
'.' Matches any single character.
'*' Matches zero or more of the preceding element.

The matching should cover the entire input string (not partial).

The function prototype should be:
bool isMatch(const char *s, const char *p)

Some examples:
isMatch("aa","a") → false
isMatch("aa","aa") → true
isMatch("aaa","aa") → false
isMatch("aa", "a*") → true
isMatch("aa", ".*") → true
isMatch("ab", ".*") → true
isMatch("aab", "c*a*b") → true
*/

/*
dp[i][j] indicates whether substring s(0:i-1) matches substring p(0:j-1) 

1, If p[j-1] == s[i-1] :  dp[i][j] = dp[i-1][j-1];
2, If p[j-1] == '.' : dp[i][j] = dp[i-1][j-1];
3, If p[j-1] == '*': we need to check p[j-2] as it is precedening char
   here are two sub conditions:
     1   if p[j-2] != s[i-1] : dp[i][j] = dp[i][j-2]  //in this case, a* only counts as empty
     2   if p[j-2] == s[i-1] or p[j-2] == '.':
                    dp[i][j] = dp[i-1][j]    //in this case, a* counts as multiple a 
                 or dp[i][j] = dp[i][j-1]   // in this case, a* counts as single a
                 or dp[i][j] = dp[i][j-2]   // in this case, a* counts as empty

*/

//Method 1: DP
class Solution {
public:
  bool isMatch(string s, string p) {

      int len_s = s.size();
      int len_p = p.size();
      

      vector<vector<bool>> dp(len_s+1,vector<bool>(len_p+1,false));
      dp[0][0] = true;
      
      
      for (int j= 2; j<=len_p; j++){
          if(p[j-1]=='*' && dp[0][j-2])
              dp[0][j] = true;
      }
      
      for(int i=1;i<=len_s;i++){
          for(int j=1;j<=len_p;j++){
              if(s[i-1]==p[j-1] || p[j-1]=='.'){
                  dp[i][j] = dp[i-1][j-1];
              }
              if(p[j-1]=='*'){
                  //need to check precedent char: p[j-2]
                  if(p[j-2]==s[i-1]||p[j-2] == '.')
                      dp[i][j] = dp[i-1][j] || dp[i][j-1] ||dp[i][j-2];
                  else if(p[j-2]!=s[i-1])
                      dp[i][j] = dp[i][j-2];
                      
              }
          }
      }
          
      return dp[len_s][len_p];
  }
};

//method 2: recursive
class Solution {
public:
    bool isMatch(string s, string p) {

        if (p.empty())    
            return s.empty();
        
        if(p[1]=='*'){
            
            //check p.substr(2) if matches zero precedenct char
            //check s.substr(1) if matches multiple precendecnt char
            return (isMatch(s,p.substr(2)) || 
            !s.empty() && (s[0]==p[0] || p[0]=='.')&&isMatch(s.substr(1),p));
        }else if(p[0]=='.' || s[0]==p[0]){
            return !s.empty() && isMatch(s.substr(1),p.substr(1));
        }else{
            return false;
        }

    }
};
