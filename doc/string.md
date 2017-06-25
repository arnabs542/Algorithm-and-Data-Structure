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
      - [String as calculator](#string-as-calculator)
      - [Expression operators](#expression-operators)
    - [Data structure to string or vice verse](#data-structure-to-string-or-vice-verse)
  - [Check if one string is Rotation of another string](#check-if-one-string-is-rotation-of-another-string)

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
                    if(m[s[l]]==0){ //move out s[l], substring will not include whole t
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

#### String as calculator

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


#### Expression operators

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

### Data structure to string or vice verse

> Key idea is recursive, and manipulate index in function. Need to split clearly what each layer should perform



* construct binary tree from string

https://leetcode.com/problems/construct-binary-tree-from-string/#/description

You need to construct a binary tree from a string consisting of parenthesis and integers.
The whole input represents a binary tree. It contains an integer followed by zero, one or two pairs of parenthesis. The integer represents the root's value and a pair of parenthesis contains a child binary tree with the same structure.
You always start to construct the left child node of the parent first if it exists.

Example:
Input: "4(2(3)(1))(6(5))"
Output: return the tree root node representing the following tree:

       4
     /   \
    2     6
   / \   /
  3   1 5

```CPP
TreeNode* str2tree(string s) {
    int i=0;
    return s.size()==0?NULL:help(s,i);
}

TreeNode* help(string &s, int& i){
    int sign = 1;
    if(s[i]=='-'){
        i++;
        sign = -1;
    }
    int num = 0;
    while(isdigit(s[i])){
        num = num*10+s[i]-'0';
        i++;
    }
    num = num*sign;

    TreeNode* node = new TreeNode(num);
    //utilize the feature that each level each node will meet two '(', the first is left and second is right
    if (s[i] == '(') {
        node->left = help(s, ++i);
        i++;    // )
    }
    if (s[i] == '(') {
        node->right = help(s, ++i);
        i++;    // )
    }
    return node;
}
```

## Check if one string is Rotation of another string

the easy way is to append the s1+s1, and check whether s2 is substring of s1.

How do we achieve O(N). s1+s1 exhaustive list all substring

## Rearrange string

* Key idea is to use hash map and priority queue. hash map's key is char and val is how many times it appears, pq is to record via map's val

* Every time just to process map and pq. pop pq with counter decrease and re push to pq

### Rearrange String k Distance Apart
https://leetcode.com/problems/rearrange-string-k-distance-apart/#/description
Given a non-empty string s and an integer k, rearrange the string such that the same characters are at least distance k from each other.
All input strings are given in lowercase letters. If it is not possible to rearrange the string, return an empty string "".

Example 1:
s = "aabbcc", k = 3
Result: "abcabc"

The same letters are at least distance 3 from each other.
Example 2:
s = "aaabc", k = 3
Answer: ""

It is not possible to rearrange the string.
Example 3:
s = "aaadbbcc", k = 2
Answer: "abacabcd"
Another possible answer is: "abcabcda"
The same letters are at least distance 2 from each other.

```CPP
string rearrangeString(string s, int k) {
    int len = s.size();
    if(k==0)
        return s;

    map<char,int> m;
    for(int i=0;i<s.size();i++){
        m[s[i]]++;
    }
    string ret = "";

    priority_queue<pair<int,char>> pq;  //count and char
    for(auto i:m){
        pq.push(make_pair(i.second,i.first)); //heap via char's occurence count
    }

    while(!pq.empty()){
        vector<pair<int,char>> tmp;
        int cnt = min(len,k);
        for(int i=0;i<cnt;i++){
            if(!pq.empty()){
                pair<int,char> cur = pq.top();
                if(--cur.first>0)
                    tmp.push_back(cur);
                ret+=cur.second;
                pq.pop();
                len--;
            }else{
                return "";
            }
        }
        for(int i=0;i<tmp.size();i++){
            pq.push(tmp[i]);
        }
    }

    return ret;
}
```

Another method
```CPP
string rearrangeString(string s, int k) {
    int len = s.size();
    if(k==0)
        return s;

    vector<int> cnt(26,0);
    for(int i=0;i<len;i++)
        cnt[s[i]-'a']++;
    string ret = "";
    //keep track of the most left position that one character can appear.
    vector<int> valid(26,0);

    for(int i=0;i<len;i++){
        int pos = findMaxleft(cnt, valid, i);
        if(pos==-1)
            return "";
        cnt[pos]--;
        valid[pos] = i+k;
        ret += char('a'+pos);

    }
    return ret;
}

int findMaxleft(vector<int> &cnt, vector<int> &valid, int index){
    int pos = -1;
    int v = INT_MIN;
    for(int i=0;i<cnt.size();i++){
       if(cnt[i]>0 && cnt[i]>v && index>=valid[i]){
           v = cnt[i];
           pos = i;
       }
   }
   return pos;
}
```

### Task schedule
https://leetcode.com/problems/task-scheduler/#/description
Given a char array representing tasks CPU need to do. It contains capital letters A to Z where different letters represent different tasks.Tasks could be done without original order. Each task could be done in one interval. For each interval, CPU could finish one task or just be idle.

However, there is a non-negative cooling interval n that means between two same tasks, there must be at least n intervals that CPU are doing different tasks or just be idle.

You need to return the least number of intervals the CPU will take to finish all the given tasks.

Example 1:
Input: tasks = ['A','A','A','B','B','B'], n = 2
Output: 8
Explanation: A -> B -> idle -> A -> B -> idle -> A -> B.

```CPP
int leastInterval(vector<char>& tasks, int n) {
    map<char,int> m;
    for(int i=0;i<tasks.size();i++){
        m[tasks[i]]++;
    }
    priority_queue<int> pq; //heap for task's count
    for(auto i:m){
        pq.push(i.second);
    }
    int ret = 0;
    int cycle = n+1;
    while(!pq.empty()){
        int t = 0;
        vector<int> tmp;
        for(int i=0;i<cycle;i++){
            if(!pq.empty()){
                tmp.push_back(pq.top());
                pq.pop();
                t++;
            }
        }
        for (int i=0;i<tmp.size();i++) {
            if (--tmp[i]>0) {
                pq.push(tmp[i]);
            }
        }
        ret += !pq.empty() ? cycle : t;
    }

    return ret;
}
```
