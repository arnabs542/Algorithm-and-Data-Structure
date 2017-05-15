https://leetcode.com/problems/decode-ways/#/description
A message containing letters from A-Z is being encoded to numbers using the following mapping:

'A' -> 1
'B' -> 2
...
'Z' -> 26
Given an encoded message containing digits, determine the total number of ways to decode it.

```CPP
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
//since we only need to count p(i+1) and possible p(i+2)
int numDecodings(string s) {
    if(s.size()==0 || s==" ")
        return 0;
    int len = s.size();
    int cur = s[len-1]=='0'?0:1;
    int next = 1;
    int tmp = 0;
    for(int i=len-2;i>=0;i--){
        if (s[i] == '0') {
            next = cur;
            cur = 0;
        } else {
          tmp = cur;
          if ((s[i] - '0') * 10 + s[i + 1] - '0' <= 26) {
            cur += next;
          }
          next = tmp;
        }
    }

    return cur;
}
