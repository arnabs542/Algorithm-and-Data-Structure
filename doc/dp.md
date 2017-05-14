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

## digit number to letter str(transition problem)

1:26 -> A:Z, for a vector, count how many ways to do the transition

```CPP
//Method 1: Recursive

int cnt(string s){
  if(s.size()==0 || s=="")
    return 0;
  vector<char> array = strtovec(s);
  return process(array,0);
}

int process(vector<char> v, int index){
  if(index==v.size()) //cross the boundary, recursive use index+1 as params
    return 1; //reach the end
  if(v[index]=='0')
    return 0;
    //if transition finished at index i, count how many transition ways starting from index+1;
  int ret = process(v,index+1);
  if(index+1<v.size() && (v[index]-'0')*10 + (v[index+1]-'0')<=26)
    ret += process(v,index+2);

  return ret;
}

//Method2: DP


```



## Number of island
