https://leetcode.com/problems/decode-ways/#/description
A message containing letters from A-Z is being encoded to numbers using the following mapping:

'A' -> 1
'B' -> 2
...
'Z' -> 26
Given an encoded message containing digits, determine the total number of ways to decode it.

//Method 1: Recursive
int numDecodings(string s) {
    if(s.size()==0 || s==" ")
        return 0;
    return process(s,0);

}
//count how many ways to process from index i in string
int process(string s,int i){
    if(i==s.size())
        return 1;
    if(s[i]=='0')
        return 0;
    //if transition finished at index i, count how many transition ways starting from index+1;
    int ret = process(s,i+1);
    if(i+1<s.size() && (s[i]-'0') * 10 + (s[i+1])-'0'<=26)
        ret+=process(s,i+2);
    return ret;
}

//Method2: DP
int numDecodings(string s) {
    if(s.size()==0 || s==" ")
        return 0;
    int len = s.size();
    vector<int>dp(len,0);
    //dp[i] means how many decode ways from index 0->i
    //dp[i] = dp[i-1] + dp[i-2]

    dp[0] = s[0]=='0'?0:1;

    for(int i=1;i<len;i++){
        if(s[i]!='0')
            dp[i] += dp[i-1];
        if(s[i-1]!='0' && ((s[i-1]-'0') * 10 + (s[i]-'0')<=26))
            if(i>=2)
                dp[i] += dp[i-2];
            else
                dp[i]+=1;  //only special case, when i==1
    }
    return dp[len-1];
}

//Method 3: optimize the memory
