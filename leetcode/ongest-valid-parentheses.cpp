//https://leetcode.com/problems/longest-valid-parentheses/#/description

int longestValidParentheses(string s) {
      //dp[i] is longest valid parentheses ending at index i;
    /*notice that define dp[i] is critical, if we define dp[i] as longest valid parentheses
    from 0->i, it is different*/
    int len = s.size();
    vector<int> dp(len,0);
    int ret = 0;
    for(int i=1;i<len;i++){
      if(s[i]==')'){
        //j is left position that where j->i is Validparentheses, need to accumulate dp[j-1] for
        //longestValidparentheses ending at j-1
        int j = i-dp[i-1]-1;
        if(j>=0 && s[j]=='('){
          dp[i] = dp[i-1]+2; //at least j->i is Validparentheses
          dp[i] += (j>0?dp[j-1]:0); //accumualte longestValidparentheses ending at j-1
        }
      }
      ret = max(ret,dp[i]);
    }
    return ret;
}
