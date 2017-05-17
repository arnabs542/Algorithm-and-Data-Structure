# Recursive to DP

## Recursive in Log(n), Use Matrix Format

## Min Matrix Path Sum

```CPP
//DP transition
DP[i][j] = m[i][j]+Min(DP[i-1][j], DP[i][j-1])

int minPathsum(vector<vector<int>> m){
  int row = m.size();
  int col = m[0].size();
  vector<vector<int>> dp(row, vector<int>(col,0));

  for (int i = 1; i < row; i++) {
    dp[i][0] = dp[i - 1][0] + m[i][0];
  }
  for (int j = 1; j < col; j++) {
    dp[0][j] = dp[0][j - 1] + m[0][j];
  }
  for (int i = 1; i < row; i++) {
    for (int j = 1; j < col; j++) {
      dp[i][j] = Math.min(dp[i - 1][j], dp[i][j - 1]) + m[i][j];
    }
  }
  return dp[row - 1][col - 1];
}
```

> Method 2: Space compression

* position [i][j]  depends on position left on row i and up on col j
```CPP
	int uniquePaths(int m, int n) {
		vector<int> dp(n, 0);

		for (int j = 0; j<n; j++)
			dp[j] = 1;
		for (int i = 1; i<m; i++) {
			for (int j = 1; j<n; j++) {

        //here we can use only one vector: dp[j] will add dp[j] from last row and dp[j-1] from //just updated current row but left column


				dp[j] += dp[j - 1];
			}
		}
		return dp[n - 1];
	}


```

## Coin Exchange

```CPP
	int coinChange(vector<int>& coins, int amount) {
		//DP: dp[i] indicates fewest number of coins for amount i
		//DP[i] = min(DP[i],DP[i-coin[j]+1)
		if (amount == 0)
			return 0;

		vector<int> DP(amount + 1, amount + 1);
		DP[0] = 0;

		for (int i = 1; i <= amount; i++) {
			for (int j = 0; j<coins.size(); j++) {
				if (i >= coins[j])
					DP[i] = min(DP[i], DP[i - coins[j]] + 1);
			}
		}

		return DP[amount] == amount + 1 ? -1 : DP[amount];
	}

```

## Longest increase subsequence




## Longest common subsequence

http://www.lintcode.com/en/problem/longest-common-subsequence/ Given two strings, find the longest comment subsequence (LCS). Your code should return the length of LCS. Example For "ABCD" and "EDCA", the LCS is "A" (or D or C), return 1 For "ABCD" and "EACB", the LCS is "AC", return

```CPP
//considering DP matrix, str1's len is row, str2's len is col

int LCS(string s1, string s2){
  //dp[i][j] = LCS(str1(0->i),str2(0->j))
  //dp[i][j] = max(dp[i-1][j],dp[i][j-1])+ 1

  int len1 = s1.size();
  int len2 = s2.size();

  vector<vector<int>> dp(len1,vector<int>(len2,0));
  //pre process to set none dependent values.

  dp[0][0] = s1[0]==s2[0]?1:0;

  for(int i=1;i<len1;i++){
    dp[i][0] = max(dp[i - 1][0], s1[i] == s2[0] ? 1 : 0);
  }

  for(int j=1;j<len2;j++){
    dp[0][j] = max(dp[0][j - 1], s1[0] == s2[j] ? 1 : 0);
  }

  for (int i = 1; i < len1; i++) {
    for (int j = 1; j < len2; j++) {
      dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
      if (s1[i] == s2[j]) {
        dp[i][j] = max(dp[i][j], dp[i - 1][j - 1] + 1);
      }
    }
  }
  return dp[len1-1][len2-1];
}

```

## Longest common substring
http://lintcode.com/zh-cn/problem/longest-common-substring/
Longest common substring problem is to find the longest string (or strings) that is a substring (or are substrings) of two or more strings.

```CPP
//dp[i][j] is LCS when s1 ending i, s2 ending j
//dp[i][j] = dp[i-1][j-1]+1 if s1[i]==s2[j]

int LCS(string s1, string s2){

    int m = s1.size();
    int n = s2.size();
    int res = 0;
    vector<vector<int>> dp(m,vector<int>(n,0));

    for (int i=0; i<=m; i++){
        for (int j=0; j<=n; j++)
        {
            if (i == 0 || j == 0)
                dp[i][j] = 0;
            else if (s1[i-1] == s2[j-1]){
                dp[i][j] = dp[i-1][j-1] + 1;
                res = max(result, dp[i][j]);
            }
            else
              dp[i][j] = 0;
        }
    }
    return result;
}

```

## Lowest cost to convert one string to another
https://leetcode.com/problems/edit-distance/#/description
dp[i][j] is lowest cost for str1[0->i-1] change to str2[0->j-1]

if str1[i-1]==str2[j-1]
  dp[i][j] = dp[i-1][j-1]

if str1[i-1]!=str2[j-1]
  dp[i][j] = dp[i-1][j-1]+cost(replace) or
  dp[i][j] = dp[i][j-1]+cost(add) or
  dp[i][j] = dp[i-1][j]+cost(delete)

```CPP
  int minDistance(string word1, string word2) {
    // dp[i][j] to be the minimum number of operations to convert
    // word1[0..i - 1] to word2[0..j - 1].
      int m = word1.length(), n = word2.length();
      vector<vector<int> > dp(m + 1, vector<int> (n + 1, 0));
      for (int i = 1; i <= m; i++)
          dp[i][0] = i;
      for (int j = 1; j <= n; j++)
          dp[0][j] = j;  
      for (int i = 1; i <= m; i++) {
          for (int j = 1; j <= n; j++) {
              if (word1[i - 1] == word2[j - 1])
                dp[i][j] = dp[i - 1][j - 1];
              else
                dp[i][j] = min(dp[i - 1][j - 1] + 1, min(dp[i][j - 1] + 1, dp[i - 1][j] + 1));
          }
      }
      return dp[m][n];
  }

  //Solution 2:
  int minDistance(string word1, string word2) {
    int m = word1.length(), n = word2.length();
    vector<int> cur(m + 1, 0);
    for (int i = 1; i <= m; i++)
        cur[i] = i;
    for (int j = 1; j <= n; j++) {
        int pre = cur[0];
        cur[0] = j;
        for (int i = 1; i <= m; i++) {
            int temp = cur[i];
            if (word1[i - 1] == word2[j - 1])
                cur[i] = pre;
            else cur[i] = min(pre + 1, min(cur[i] + 1, cur[i - 1] + 1));
            pre = temp;
        }
    }
    return cur[m];
}
```

## Interleaving String
Given s1, s2, s3, find whether s3 is formed by the interleaving of s1 and s2.
https://leetcode.com/problems/interleaving-string/#/description

```CPP
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
```




## Poker Game/Cards in line

A array with value, two persons play each other, one can only pick up cards from two sides. get winner's accumulated value.

> F = max((V_left+s[i+1,j]),V_right+s[i,j-1]),    //first person to pick

> S = min(F(i+1,j),F(i,j-1))   //second person to pick

```CPP
//Recursive way
int win1(vector<int> cards){
  int len = cards.size();

  if (len == 0)
    return 0;
  //F is first player action. S is second player action
  return max(f(cards,0,len-1),s(cards,0,len-1))
}
//f is value first person can pick from cards ranging left to right
int f(vector<int> cards, int left, int right){
  if(left==right)
    return cards[left];
  //f can pick either left or right side
  return max(cards[left]+s(cards,left+1,right),cards[right]+s(cards,left,right-1));
}
//s is value second person can pick from cards ranging left to right
int s(vector<int> cards, int left, int right){
  if(left==right)
    return 0;

  //s can pick only what f left, and f should do optimal choice
  return min(f(cards,left+1,right),f(cards,left,right-1));
}

```

> we can convert the Recursive to DP

```CPP
//record the calculated values
//since we have two process function, we have two DP matrixs

int win2(vector<int> cards){
  int len = cards.size();
  vector<vector<int>> f(len,vector<int>(len,0));
  vector<vector<int>> s(len,vector<int>(len,0));

  //first to check which position dose not have depends, diagonal line
  //since right is always larger or equal to left, so we do not need to calculate left-bottom
  //start from disgonal line, until right upper conner
  for(int i=0;i<len;i++){
    f[i][j] = cards[i][j];
    s[i][j] = 0;
    for(int j=i-1;j<=0;j--){
      f[i][j] = max(cards[i]+s[i+1][j],cards[j]+s[i][j-1]);
      s[i][j] = min(f[i+1][j],f[i][j-1]);
    }
  }

  return max((f[0][len-1]),s[0][len-1]);

}

```

## digit number to letter str(decode-ways problem)


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
}
```

## sum of logic calculation to certain target, express ways

Given a array with 1 and 0 and logic symbol(&,|,^), calculate how many ways to get the desired value

```CPP
//Recursive
int expressways(String express, boolean desired) {
  if (express.size()==0 || express=="") {
    return 0;
  }

  if (!isValid(exp)) {
    return 0;
  }
  return p(exp, desired, 0, exp.size() - 1);
}

static int p(string exp, bool desired, int l, int r) {
  //l and r are only 1 or 0, not logic symbol
  if (l == r) {
    if (exp[l] == '1') {
      return desired ? 1 : 0;
    } else {
      return desired ? 0 : 1;
    }
  }
  int res = 0;
  if (desired) {
    for (int i = l + 1; i < r; i += 2) {
      switch (exp[i]) {
      case '&':
        res += p(exp, true, l, i - 1) * p(exp, true, i + 1, r);
        break;
      case '|':
        res += p(exp, true, l, i - 1) * p(exp, false, i + 1, r);
        res += p(exp, false, l, i - 1) * p(exp, true, i + 1, r);
        res += p(exp, true, l, i - 1) * p(exp, true, i + 1, r);
        break;
      case '^':
        res += p(exp, true, l, i - 1) * p(exp, false, i + 1, r);
        res += p(exp, false, l, i - 1) * p(exp, true, i + 1, r);
        break;
      }
    }
  } else {
    for (int i = l + 1; i < r; i += 2) {
      switch (exp[i]) {
      case '&':
        res += p(exp, false, l, i - 1) * p(exp, true, i + 1, r);
        res += p(exp, true, l, i - 1) * p(exp, false, i + 1, r);
        res += p(exp, false, l, i - 1) * p(exp, false, i + 1, r);
        break;
      case '|':
        res += p(exp, false, l, i - 1) * p(exp, false, i + 1, r);
        break;
      case '^':
        res += p(exp, true, l, i - 1) * p(exp, true, i + 1, r);
        res += p(exp, false, l, i - 1) * p(exp, false, i + 1, r);
        break;
      }
    }
  }
  return res;
}

//dp way
//two dp:
//t[i][j]: how many ways strings from i to j get true
//f[i][j]: how many ways strings from i to j get false
//need to start with smallest length


int expressways(String express, bool desired) {
  if (express.size()==0 || express=="") {
    return 0;
  }

  if (!isValid(exp)) {
    return 0;
  }
  int len = express.size();
  vector<vector<int>> t = (len,vector<int>(len,0)); //dp for true desired value
  vector<vector<int>> f = (len,vector<int>(len,0)); //dp for false desired value
  t[0][0] = exp[0] == '0' ? 0 : 1;
  f[0][0] = exp[0] == '1' ? 0 : 1;
  //step is two because we need to avoid symbol
  for (int i = 2; i < len; i += 2) {
    t[i][i] = exp[i] == '0' ? 0 : 1;
    f[i][i] = exp[i] == '1' ? 0 : 1;
    //starting from shortest length

    for (int j = i - 2; j >= 0; j -= 2) {
      for (int k = j; k < i; k += 2) {
        if (exp[k + 1] == '&') {
          t[j][i] += t[j][k] * t[k + 2][i];
          f[j][i] += (f[j][k] + t[j][k]) * f[k + 2][i] + f[j][k] * t[k + 2][i];
        } else if (exp[k + 1] == '|') {
          t[j][i] += (f[j][k] + t[j][k]) * t[k + 2][i] + t[j][k] * f[k + 2][i];
          f[j][i] += f[j][k] * f[k + 2][i];
        } else {
          t[j][i] += f[j][k] * t[k + 2][i] + t[j][k] * f[k + 2][i];
          f[j][i] += f[j][k] * f[k + 2][i] + t[j][k] * t[k + 2][i];
        }
      }
    }
  }
  return desired ? t[0][t.length - 1] : f[0][f.length - 1];
}
```

## Longest Palindromic Subsequence
https://leetcode.com/problems/longest-palindromic-subsequence/#/
### Exhaustive
search each position as center of Palindromic.

### Recursive to DP
```CPP
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
```

### Manacher

1. start from left to right, check right Boudary of Palindromic
2. check the diameter of Palindromic
3. current Palindromic center for right Boudary

## Add min char so that whole string is Palindromic


```CPP
int addMin(string s){
  int len = s.size();
  //dp[i][j] is minimum char added so that i->j is Palindromic
  vector<vector<int>> dp(len,vector<len,INT_MAX>);
  for(int j=0;j<len;j++){
    for(int i=j;i>=0;i--){
      if(i==j)
        dp[i][j] = 0; //no need to add since one char is Palindromic
      else if(i==j+1){ //for two char cases
        if(s[i]==s[j]){
          dp[i][j] = 0;
        }else{
          dp[i][j] = 1;
        }
      }else{ //for general case
        if(s[i]==s[j]){
          dp[i][j] = dp[i+1][j-1];
        }else{
          dp[i][j] = min(dp[i+1,j],dp[i,j-1])+1;
        }
      }
    }
  }

  return dp[0][len-1];
}
```

## Valid parentheses and longest valid parentheses
https://leetcode.com/problems/longest-valid-parentheses/#/description
```CPP
//isValid
bool isValid(string p){
  int a = 0;
  for(int i=0;i<p.size();i++){
    if(p[i]=='(')
      a++;
    else
      a--;
    if(a<0)
      return false;
  }

  return a==0?true:false;
}

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

```


## Minimum cuts needed for a palindrome partitioning
https://leetcode.com/problems/palindrome-partitioning-ii/#/description
Given a string s, partition s such that every substring of the partition is a palindrome.
Return the minimum cuts needed for a palindrome partitioning of s.



```CPP
//method 1:
//get all subsequence whether it is palindrome
//cut[i] is min cut needed to partition substring ending index i;
int minCut(string s) {
    /* cut[i] is minimum cut at char i,
    cut[i] = min{1 + cut[j], cut[i]}, where j < i and substring [j, i] is palindrome*/

    int len = s.size();
    vector<int>cut;
    for(int i=0;i<=len;i++)
        cut.push_back(i-1);


    vector<vector<bool>>isPal (len,vector<bool>(len, false));
    //isPal[i,j] indicate whether s[i->j] is pal

    for(int i=len-1;i>=0;i--){
        for(int j=i; j<len; j++) {
            if((i+1>j-1 || isPal[i+1][j-1]) && s[i]==s[j])
                isPal[i][j] = true;
        }
    }

    for(int i=1;i<=len;i++){
        for(int j=0;j<i;j++){
            if(isPal[j][i-1]) // check if substring [j, i-1] is palindrome
                cut[i] = min(cut[i], 1 + cut[j]);
        }
    }

    return cut[len];
}

//optimize
int minCut(string s) {
    /*isPal[i][j] , which is whether s[i..j] forms a pal
    cut[i], which is the minCut for s[i..n-1]*/

    int len = s.size();
    vector<int>cut(len,0);
    vector<vector<bool>>isPal (len,vector<bool>(len, false)); //isPal[i,j] indicate whether s[i->j] is pal

    for(int i=len-1;i>=0;i--){
        cut[i] = len-1-i;
        for(int j=i; j<len; j++) {
            if(s[i]==s[j] && (j-i<2 || isPal[i+1][j-1])){
                isPal[i][j] = true;
                if(j==len-1)
                    cut[i]=0;
                else
                    cut[i]=min(cut[i],cut[j+1]+1);
            }
        }
    }
    return cut[0];
}
```

## Number of island
