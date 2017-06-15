<!-- START doctoc generated TOC please keep comment here to allow auto update -->
<!-- DON'T EDIT THIS SECTION, INSTEAD RE-RUN doctoc TO UPDATE -->
**Table of Contents**  *generated with [DocToc](https://github.com/thlorenz/doctoc)*

- [String](#string)
  - [Substring problem](#substring-problem)
    - [Longest/shortest substring with conditions](#longestshortest-substring-with-conditions)
      - [Longest Substring Without Repeating Characters](#longest-substring-without-repeating-characters)
      - [Longest Substring with At Most K Distinct Characters](#longest-substring-with-at-most-k-distinct-characters)
      - [Minimum windows substring](#minimum-windows-substring)
    - [Substring Problem from 2 or more strings](#substring-problem-from-2-or-more-strings)
      - [Longest Word in Dictionary through Deleting](#longest-word-in-dictionary-through-deleting)
    - [KMP](#kmp)
  - [Subsequence Problem](#subsequence-problem)
  - [String Stream representation Problem](#string-stream-representation-problem)
    - [Combination](#combination)
    - [Expression(string as calculator expression)](#expressionstring-as-calculator-expression)
  - [Check if one string is Rotation of another string](#check-if-one-string-is-rotation-of-another-string)
  - [Implement a basic calculator to evaluate a simple expression string.](#implement-a-basic-calculator-to-evaluate-a-simple-expression-string)
- [Matrix Problem](#matrix-problem)
  - [Sub region or Path in Matrix](#sub-region-or-path-in-matrix)
  - [Pattern Along row/col Problem](#pattern-along-rowcol-problem)
  - [Largest square/rectangle inside](#largest-squarerectangle-inside)
- [BackTracking](#backtracking)
  - [Common logic](#common-logic)
- [Others](#others)
  - [BFPRT](#bfprt)
  - [Half Majority](#half-majority)
  - [Search a 2D matrix](#search-a-2d-matrix)
  - [First missing positive](#first-missing-positive)

<!-- END doctoc generated TOC please keep comment here to allow auto update -->

# String

## Substring problem

### Longest/shortest substring with conditions

> Common solutions

* use two pointers to mark left and right,
* use a map<char,int> to record how many times a char occur.
* may need to use some reference cnt to check condition satisfy

#### Longest Substring Without Repeating Characters
https://leetcode.com/problems/longest-substring-without-repeating-characters/#/description

> substring problems: (if ending at certain position. sub problem:)

In this problem, it is longest substring without duplicate ending at i

```CPP
//method 1: use a map to record position
int lengthOfLongestSubstring(string s) {
    int ret = 0;
    int len = s.size();
    map<char,int> m;//key is char, val is counts  
    int l=0;
    int r=0;
    int cnt = 0;
    while(r<s.size()){
      m[s[r]]++;
        if(m[s[r]]>1){//repeat happen
            cnt++;
        }
        r++;
        while(cnt>0){
            if(--m[s[l]]==1){ //back to unique
                cnt--;
            }
            l++;
        }
        ret = max(ret,r-l);
    }
    return ret;
}

//Method 2: DP
//dp[i] = longest substring ending at position i
//pos[i] is i'th char last occur position

int lengthOfLongestSubstring(string s) {
    int ret = 0;
    int len = s.size();
    map<char,int>pos; //each char's last occur position
    vector<int> dp(len,1); //lengthOfLongestSubstring at position i;

    for(int i=0;i<len;i++){
        int last;
        if(pos.find(s[i])!=pos.end())
            last= pos[s[i]]; //last occur position of s[i]
        else
            last = -1;//never occur
        if(i>0){
            dp[i] = i-dp[i-1]>last?dp[i-1]+1:i-last;  
        }
        //update position
        pos[s[i]] = i;
        ret = max(ret,dp[i]);
    }

    return ret;
}

```

#### Longest Substring with At Most K Distinct Characters

https://leetcode.com/problems/longest-substring-with-at-most-k-distinct-characters/

Given a string, find the length of the longest substring T that contains at most k distinct characters.
For example, Given s = “eceba” and k = 2,
T is "ece" which its length is 3.

```CPP
int lengthOfLongestSubstringKDistinct(string s, int k) {
    int ret = 0;
    int l=0;
    int r=0;
    map<char,int> m;

    while(r<s.size()){
        m[s[r]]++;
        r++;
        while(m.size()>k){//more than k distint char
            m[s[l]]--;  //move left to reduce char
            if(m[s[l]]==0){  //check remove left char could solve it
                m.erase(s[l]);
            }
            l++;
        }
        ret = max(ret,r-l);
    }
    return ret;
}

```

#### Minimum windows substring
https://leetcode.com/problems/minimum-window-substring/#/description
Given a string S and a string T, find the minimum window in S which will contain all the characters in T in complexity O(n).

For example,
S = "ADOBECODEBANC"
T = "ABC"
Minimum window is "BANC".

```CPP
string minWindow(string s, string t) {
        map<char,int> m; //char and its occurence
        for(int i=0;i<t.size();i++){
            m[t[i]]++;
        }
        int l=0;
        int r = 0;
        string ret = "";
        int len = INT_MAX;
        int cnt = t.size();
        while(r<s.size()){
            if(m.find(s[r])!=m.end()){
                if(m[s[r]]>0){
                    cnt--;
                }
                m[s[r]]--;  //this could be negative, means s has more s[r] than t has s[r]
            }
            r++;

            while(cnt==0){
                if(r-l<len){
                    len = r-l;
                    ret = s.substr(l,r-l);
                }
                if(m.find(s[l])!=m.end()){
                    if(m[s[l]]==0){ //move out s[l] substring will not include whole t
                        cnt++;
                    }
                    m[s[l]]++;
                }
                l++;
            }
        }
        return ret;
}
```

### Substring Problem from 2 or more strings

> Common problem description:

  * whether one string is substring of another
  * Further more: substring through some modification

> Common solution

  * two pointers for original string and target string.
  * original pointer keeps on moving, target pointer only moves when certain condition meet

#### Longest Word in Dictionary through Deleting

https://leetcode.com/problems/longest-word-in-dictionary-through-deleting/#/description

Given a string and a string dictionary, find the longest string in the dictionary that can be formed by deleting some characters of the given string. If there are more than one possible results, return the longest word with the smallest lexicographical order. If there is no possible result, return the empty string.

Example 1:
Input:
s = "abpcplea", d = ["ale","apple","monkey","plea"]

Output:
"apple"

```CPP
string findLongestWord(string s, vector<string>& d) {
    string ret;
    for(int i=0;i<d.size();i++){
        int j = 0; //index for s.
        int k = 0; //index for d[i]
        for(j=0;j<s.size() && k<d[i].size();j++){
            if(s[j]==d[i][k])  //matches, we can move k, otherwise only move j
                k++;
        }
        if(k==d[i].size()){//whole string in d[i] matches
            if(k>ret.size() || k==ret.size() && ret>d[i])
            //either new one is longer or equal size but lexicographical smaller
                ret = d[i];
        }
    }
    return ret;
}

```

### KMP

Used to check whether str2 is a substring of str1

Idea is to get the next array, next array is largest number i in substring m, where prefix(0->i-1) and postfix(m-i,m) is same


```CPP
//get start index of string m inside string s, if not found, return -1
int getIndexOf(String s, String m) {
  if (s == null || m == null || m.size() < 1 || s.size() < m.size()) {
    return -1;
  }
  int si = 0;
  int mi = 0;
  vector<int> next = getNextArray(ms);
  while (si < s.size() && mi < m.size()) {
    if (s[si] == m[mi]) {
      si++;
      mi++;
    } else if (next[mi] == -1) {
      si++;
    } else {
      mi = next[mi];
    }
  }
  return mi == ms.size() ? si - mi : -1;
}

vector<int> getNextArray(vector<int> ms) {
  vector<int> next;
  if (ms.size() == 1) {
    next.push_back(-1);
    return next;
  }
  next[0] = -1;
  next[1] = 0;
  int pos = 2;
  int cn = 0;
  while (pos < next.size()) {
    if (ms[pos - 1] == ms[cn]) {
      next[pos++] = ++cn;
    } else if (cn > 0) {
      cn = next[cn];
    } else {
      next[pos++] = 0;
    }
  }
  return next;
}
```

* KMP application

https://leetcode.com/problems/shortest-palindrome/#/description

Given a string S, you are allowed to convert it to a palindrome by adding characters in front of it. Find and return the shortest palindrome you can find by performing this transformation.

For example:
Given "aacecaaa", return "aaacecaaa".
Given "abcd", return "dcbabcd".

```CPP
//simple Solution
string shortestPalindrome(string s) {
    string s2=s;
    reverse(s2.begin(),s2.end());
    int n=s.size(),l;
    for(l=n;l>=0;l--)
    {
        if(s.substr(0,l)==s2.substr(n-l))
            break;
    }
    return s2.substr(0,n-l)+s;
}

/*
We can construct the following string and run KMP algorithm on it:
(s) + (some symbol not present in s) + (reversed string)

After running KMP on that string as result we get a vector p with values of a prefix function for each character (for definition of a prefix function see KMP algorithm description). We are only interested in the last value because it shows us the largest suffix of the reversed string that matches the prefix of the original string. So basically all we left to do is to add the first k characters of the reversed string to the original string, where k is a difference between original string size and the prefix function for the last character of a constructed string.
*/
string shortestPalindrome(string s) {
    string rev_s = s;
    reverse(rev_s.begin(), rev_s.end());
    string l = s + "#" + rev_s;

    vector<int> p(l.size(), 0);
    for (int i = 1; i < l.size(); i++) {
        int j = p[i - 1];
        while (j > 0 && l[i] != l[j])
            j = p[j - 1];
        p[i] = (j += l[i] == l[j]);
    }

    return rev_s.substr(0, s.size() - p[l.size() - 1]) + s;
}
```

## Subsequence Problem
https://leetcode.com/problems/is-subsequence/#/description
A subsequence of a string is a new string which is formed from the original string by deleting some (can be none) of the characters without disturbing the relative positions of the remaining characters. (ie, "ace" is a subsequence of "abcde" while "aec" is not).

Example 1:
s = "abc", t = "ahbgdc"
Return true.

Example 2:
s = "axc", t = "ahbgdc"
Return false.
```CPP
bool isSubsequence(string s, string t) {
    int index = 0;
    if(s.size()==0)
        return true;
    //two pointer solution
    for(int i=0;i<t.size();i++){
        if(s[index]==t[i]){
            index++;
            if(index==s.size())
                return true;
        }
    }
    return false;
}
```

## String Stream representation Problem

Typically this problem will have incoming string stream, with each char represent certain meaning(could be char, number, or encoding way), and need to process this stream to get some results

### Combination

* Reverse count and say

https://leetcode.com/problems/count-and-say/#/description
we need to reverse count and say to original string, for example, if encoded count and say is "2345", original could be "335555" and "<234:5>"

```CPP
vector<string> reverse_count_say(string in){
  vector<string> ret;
  string one = "";
  help(in,0,0,one,ret);
  return ret;
}

void help(string &in, int i, int cnt, string &one, vector<string> ret){
  if(cnt==0 && i==in.size()-1){
    //only one char left without cnt, invalid
    return;
  }
  if(i==in.size()){
    //successfully reverse
    ret.push_back(one);
  }
  //decode current one as number, can not decode
  help(in,i+1,cnt*10+in[i]-'0',one,ret);
  if(i>0){// can not decode first as char
    //decode current one as char, so we add to current solution
    char cur = in[i];
    for(int i=0;i<cnt,i++){
      one+=cur;
    }
    help(in,i+1,0,one,ret); //cnt reset to 0
  }
}

```

### Expression(string as calculator expression)

* String as calculator

https://leetcode.com/problems/basic-calculator-ii/#/description
Implement a basic calculator to evaluate a simple expression string.
The expression string contains only non-negative integers, '+, -, * ,/' operators and empty spaces . The integer division should truncate toward zero.
You may assume that the given expression is always valid.

Some examples:
"3+2*2" = 7
" 3/2 " = 1
" 3+5 / 2 " = 5

```CPP
int calculate(string s) {
    //key is to have a value in stack and operator saved
    int len = s.size();
    stack<int> saved;
    int cur = 0;
    char sign = '+';
    for(int i=0;i<len;i++){
        if(isdigit(s[i])){
            cur = cur*10+s[i]-'0';
        }
        if(!isdigit(s[i]) && !isspace(s[i]) || i == s.size()-1){
            if(sign=='+') saved.push(cur);
            if(sign=='-') saved.push(-cur);
            if(sign=='* '){
                int tmp = saved.top();
                saved.pop();
                saved.push(tmp*cur);
            }
            if(sign=='/'){
                int tmp = saved.top();
                saved.pop();
                saved.push(tmp/cur);
            }
            cur = 0;
            sign = s[i];
        }
    }

    int ret = 0;
    while(!saved.empty()){
        ret+=saved.top();
        saved.pop();
    }
    return ret;
}
```

The problem can be extended to case string may contain open ( and closing parentheses ), the plus + or minus sign -, non-negative integers and empty spaces .
"1 + 1" = 2
" 2-1 + 2 " = 3
"(1+(4+5+2)-3)+(6+8)" = 23

```CPP
int calculate(string s) {
  int len = s.size();
  int sign = 1;
  int ret = 0;
  int num = 0;
  stack<int> nums,ops;
  for(int i=0;i<len;i++){
      if(isdigit(s[i])){
        num = num*10+(s[i]-'0');
      }else{
        //not number anymore, so we would need to get the current calculation num and accumulated ret
        ret+=sign*num;
        num = 0;
        if(s[i]=='+') sign = 1;
        if(s[i]=='-') sign = -1;
        if(s[i]=='('){
            nums.push(ret);  //cache the results before bracket
            ops.push(sign);  //cache the sign before bracket
            ret = 0;
            sign = 1;
        }
        if (s[i] == ')' && ops.size()) {
            ret = ops.top() * ret + nums.top(); //finish the calculation of current bracket, so get cached
            ops.pop();
            nums.pop();
        }
    }
}
ret += sign * num;
return ret;
}

```


* Expression operators

https://leetcode.com/problems/expression-add-operators/#/description
Given a string that contains only digits 0-9 and a target value, return all possibilities to add binary operators (not unary) +, -, or * between the digits so they evaluate to the target value.

Examples:
"123", 6 -> ["1+2+3", "1*2*3"]
"232", 8 -> ["2*3+2", "2+3*2"]
"105", 5 -> ["1*0+5","10-5"]
"00", 0 -> ["0+0", "0-0", "0*0"]
"3456237490", 9191 -> []

```CPP
vector<string> addOperators(string num, int target) {
    vector<string> ret;
    string one = "";
    if(num.size()==0)
        return ret;

    help(num,0,one,0,0,ret,target);
    return ret;

}

void help(string num, int i, string one, long val, long save, vector<string> &ret, int target){

    if(i==num.size()){
        if(val==target)
            ret.push_back(one);
        return;
    }
    for(int j=i;j<num.size();j++){
        string t = num.substr(i, j-i+1);
        long cur = stol(t);
        if (to_string(cur).size() != t.size()) continue;  //remove some 0
        if(i==0){//first one, no operator
            help(num,j+1,one+to_string(cur),cur,cur,ret,target);
        }else{
            //add '+' before current num
            help(num,j+1,one+"+"+to_string(cur),val+cur,cur,ret,target);
            //add '-' before current num
            help(num,j+1,one+"-"+to_string(cur),val-cur,-cur,ret,target);
            //add '*' before current num, for mutiple, like 2+3*5, need to save 3 otherwise it will be 2+3=5*5
            help(num,j+1,one+"*"+to_string(cur), val-save + save*cur,save*cur ,ret,target);
        }
    }
}

```

## Check if one string is Rotation of another string

the easy way is to append the s1+s1, and check whether s2 is substring of s1.

How do we achieve O(N). s1+s1 exhaustive list all substring

## Implement a basic calculator to evaluate a simple expression string.
https://leetcode.com/problems/basic-calculator/#/description
Implement a basic calculator to evaluate a simple expression string.

The expression string may contain open ( and closing parentheses ), the plus + or minus sign -, non-negative integers and empty


```CPP
int calculate(string s) {
  int len = s.size();
  int sign = 1;
  int ret = 0;
  int num = 0;
  stack<int> nums,ops;
  for(int i=0;i<len;i++){
      if(isdigit(s[i])){
        num = num*10+(s[i]-'0');
      }else{
        //not number anymore, so we would need to get the current calculation num and accumulated ret
        ret+=sign*num;
        num = 0;
        if(s[i]=='+') sign = 1;
        if(s[i]=='-') sign = -1;
        if(s[i]=='('){
            nums.push(ret);  //cache the results before bracket
            ops.push(sign);  //cache the sign before bracket
            ret = 0;
            sign = 1;
        }
        if (s[i] == ')' && ops.size()) {
            ret = ops.top() * ret + nums.top(); //finish the calculation of current bracket, so get cached
            ops.pop();
            nums.pop();
        }
      }
  }
  ret += sign * num;
  return ret;
}

```

# Matrix Problem

## Sub region or Path in Matrix

> Use DFS or BFS to search

* For subregion problem, usually started with target pixel and traversal region, need some matrix to record visited flag or directly modify the original matrix

* For Path Problem, start with path starting or ending point.  


## Pattern Along row/col Problem
search space goes from certain node along its same row and col index

> Common techniques:  Preprocess: Assist with two vector, row and col, and get some feature/sum of characters of same row/col

* Lonely Pixel

https://leetcode.com/problems/lonely-pixel-i/
Given a picture consisting of black and white pixels, find the number of black lonely pixels.
The picture is represented by a 2D char array consisting of 'B' and 'W', which means black and white pixels respectively.

A black lonely pixel is character 'B' that located at a specific position where the same row and same column don't have any other black pixels.

Example:
Input:
[['W', 'W', 'B'],
 ['W', 'B', 'W'],
 ['B', 'W', 'W']]

Output: 3
Explanation: All the three 'B's are black lonely pixels.

```CPP
int findLonelyPixel(vector<vector<char>>& picture) {
    int m=picture.size();
    if(m==0) return 0;
    int n=picture[0].size();

    int ret = 0;
    vector<int> row(m,0);
    vector<int> col(n,0);

    for(int i=0;i<m;i++){
        for(int j=0;j<n;j++){
            if(picture[i][j]=='B'){
                row[i]++;
                col[j]++;
            }
        }
    }

    for(int i=0;i<m;i++){
        for(int j=0;j<n;j++){
            if(picture[i][j]=='B' && row[i]==1 && col[j]==1){
                ret++;
            }
        }
    }
    return ret;
}

```

* Bomb Enemy

//https://leetcode.com/problems/bomb-enemy/

Given a 2D grid, each cell is either a wall 'W', an enemy 'E' or empty '0' (the number zero), return the maximum enemies you can kill using one bomb.
The bomb kills all the enemies in the same row and column from the planted point until it hits the wall since the wall is too strong to be destroyed.
Note that you can only put the bomb at an empty cell.

Example:
For the given grid

0 E 0 0
E 0 W E
0 E 0 0
return 3. (Placing a bomb at (1,1) kills 3 enemies)
```CPP
class Solution {
    int row = 0;
    int col = 0;
public:
    int maxKilledEnemies(vector<vector<char>>& grid) {
        //pre-process with row and col
        row = grid.size();
		if (!row) return 0;
		col = grid[0].size();
		int ret = 0;
		int row_enemy; //enemy killed for fixed row along col
		vector<int> col_enemy(col, 0); //enemy killed for fixed col along row

        for (int i = 0; i<row; i++) {
			for (int j = 0; j<col; j++) {
			    if(j==0 || grid[i][j-1]=='W'){
			        row_enemy = row_help(grid,i,j);
			    }
			    if(i==0 || grid[i-1][j]=='W'){
			        col_enemy[j] = col_help(grid,i,j);
			    }
			    if(grid[i][j]=='0')
			        ret = max(ret,row_enemy+col_enemy[j]);
			}
        }
        return ret;
    }

    int row_help(vector<vector<char>>& grid, int i, int j){
        int num = 0;
        for(int k=j;k<col;k++){

            if(grid[i][k]=='E')
                num++;
            else if(grid[i][k]=='W')
                break;
        }
        return num;
    }

    int col_help(vector<vector<char>>& grid, int i, int j){
        int num = 0;
        for(int k=i;k<row;k++){
            if(grid[k][j]=='E')
                num++;
            else if(grid[k][j]=='W')
                break;
        }
        return num;
    }
};

```

## Largest square/rectangle inside

> * similar as array, usually divide this problem into row and col two array


* Largest Square with all 1 in the boundary
Given a matrix containing either 0 or 1 in each cell, find the square with the longest side containing all 1s in its boundary. Cells inside the square may contain either 0 or 1.

For example, given matrix

[
  [0, 1, 0, 1, 1]
  [0, 1, 1, 1, 0]
  [0, 1, 0, 1, 1]
  [1, 1, 1, 1, 1]
  [1, 1, 1, 1, 1]
]
The square with the maximum size containing all 1s in its boundary has top-left corner at (1,1) and bottom-right corner at (3, 3)


```CPP
//two help matrix:
//help1: starting from current position, how many consecutive 1 in right
//help2: starting from current position, how many consecutive 1 down

int getLargestSquareSide(vector<vector<int>> matrix){

  int row = matrix.size();
  int col = matrix[0].size();
  //starting from current position, how many consecutive 1 in right
  vector<vector<int>> right(row,vector<int>(col,0));
  //starting from current position, how many consecutive 1 down
  vector<vector<int>> down(row,vector<int>(col,0));
  int ret = 0;
  for(int i=0;i<row;i++){
    right[i][col-1]=matrix[i][col-1];
  }
  for(int j=0;j<col;j++){
    down[row-1][j-1]=matrix[row-1][j];
  }

  for(int i=row-2;i>=0;i--){
    for(int j=col-2;j>=0;j--){
      right[i][j] = matrix[i][j]==0?0:right[i+1][j]+1;
      down[i][j]=matrix[i][j]==0?0:down[i][j+1];
    }
  }
  //starting from largest size
  for(int size=min(row,col);size>0;size--){
    if(hasALloneBorder(size,right,down,row,col)){
      return size;
    }
  }
  return 0;

}

bool hasALloneBorder(int size, vector<vector<int>> &right, vector<vector<int>> &down,int row, int col){
  for(int i=0;i<=row-size;i++){
    for(int j=0;i<=col-size;j++){
      if(right[i][j]>=size && down[i][j]>=size && right[i+size-1][j]>=size && down[i][j+size-1]>=size)
        return true;
    }
  }
  return false;
}

```

* Maximal-square
https://leetcode.com/problems/maximal-square/#/description
Given a 2D binary matrix filled with 0's and 1's, find the largest square containing only 1's and return its area.

For example, given the following matrix:

1 0 1 0 0
1 0 1 1 1
1 1 1 1 1
1 0 0 1 0
Return 4.

```CPP
//similar as subarray, use dp to consider max square's edge len ending i,j
int maximalSquare(vector<vector<char>>& matrix) {
    int row = matrix.size();
    if(row==0)
        return 0;
    int col = matrix[0].size();


    //dp[i][j] is the max edge len for point ending (i,j)
    vector<vector<int>> dp(row,vector<int>(col,0));
    //first row and col
    int maxlen = 0;
    for(int i=0;i<row;i++){
        if(matrix[i][0]=='1'){
            dp[i][0] = 1;
            maxlen = 1;
        }
    }
    for(int j=0;j<col;j++){
        if(matrix[0][j]=='1'){
            dp[0][j] = 1;
            maxlen = 1;
        }
    }

    for(int i=1;i<row;i++){
        for(int j=1;j<col;j++){
            if(matrix[i][j]=='1'){
                //check from up left i-1,j-1, and current row [i][j-1], current col [i-1][j]
                dp[i][j] = min(min(dp[i-1][j],dp[i][j-1]),dp[i-1][j-1]) + 1;
                maxlen = maxlen>dp[i][j]?maxlen:dp[i][j];
            }else{
                dp[i][j] = 0;
            }
        }
    }

    return maxlen*maxlen;
}

```

# BackTracking

## Common logic

> DFS+Recursive

1.	DFS/recursive logical key is call back and each level just do one thing and every level do the same thing repeat
2.	Interface definition. For most problem, use reference in C++(&) so some data structure needs to be in every level and modified. Otherwise each level should be in tact
3.	Push_back() and pop_back() is key thing to go over all items, they should be balance (push should be paired with pop), when thinking the problem, every level(in DFS or recursive) should consider its own level, do not go into recursive logic next level. Same for set item true/false (visited in two dimensional array. etc)
4.	If not push/pop. Use local variable
5.	Put core recursive logic tact, judgement/return/error case should be outside the recursive loop.

```CPP
//Core Logic Code
//Core Recursive logic can be seens as
void help(int &ret, int start, void * param) {
	if (certain condition) {
		// process ret logic
		return;
	}

	for (i = start; i < param;i++) {
		one_res.push_back();  //used mostly in vector
    ret = f(); //some ret logic
		help(ret, i+1/i, param);
		one_res.pop_back(); //pop what pushed, for string case since we use local variable, no need to pop, noticing
	}
}



```

# Others

## BFPRT
In an unordered array, find the k'th smallest or largest value

first method is recursive:
1. select a pivot number
2. partition the collection into <,=,> 3 collections compared with pivot
3. check k's smallest location, then recursive

The issue is pivot choice could be random and worst case is O(N^2)

## Half Majority
https://leetcode.com/problems/majority-element/#/description
Given an array of size n, find the majority element. The majority element is the element that appears more than ⌊ n/2 ⌋ times.

```CPP
int majorityElement(vector<int>& nums) {
  int cand = 0;
  int times = 0;
  int len = nums.size();
  for (int i = 0; i < len; i++) {
    if (times == 0) {
      cand = nums[i];
      times = 1;
    } else if (nums[i] == cand) {
      times++;
    } else {
      times--;
    }
  }
  times = 0;
  for (int i = 0; i < len; i++) {
    if (nums[i] == cand) {
      times++;
    }
  }
  if (times > len / 2)
      return cand;
}

```

Extend. [K/N], then we just need to prepare K candidates


## Search a 2D matrix
https://leetcode.com/problems/search-a-2d-matrix-ii/#/description
Write an efficient algorithm that searches for a value in an m x n matrix. This matrix has the following properties:

Integers in each row are sorted in ascending from left to right.
Integers in each column are sorted in ascending from top to bottom.

```CPP
bool searchMatrix(vector<vector<int>>& matrix, int target) {
    int row = matrix.size();
    if(row==0) return false;
    int col = matrix[0].size();

    int x = 0;
    int y = col-1;
    while(x<row && y>=0){
        if(matrix[x][y]>target){
            y = y-1;
        }else if(matrix[x][y]<target){
            x = x + 1;
        }else{
            return true;
        }

    }
    return false;
}

```

## First missing positive
ideally we should have vector as 1,2,3,...n. so nums[i-1]=i

Just go through the array sequentially and for every index write the value at the index to the index specified by value, recursively placing any value at that location to its place and throwing away values > N. Then go again through the array looking for the spot where value doesn't match the index - that's the smallest value not in the array.

```CPP
int firstMissingPositive(vector<int>& nums) {
  int len = nums.size();
  int ret = 0;
  for(int i=0;i<len;i++){
      int target = nums[i];
      //recursively placing any value to location to its place, until find or no more place
      while(target>0 && target<=len && target!=nums[target-1]){
          swap(target,nums[target-1]);
      }
  }

  for(int i=0;i<len;i++){
      if(nums[i]!=i+1){
          ret = i+1;
          return ret;
      }
  }
  return len+1;
}
```
