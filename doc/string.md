<!-- START doctoc generated TOC please keep comment here to allow auto update -->
<!-- DON'T EDIT THIS SECTION, INSTEAD RE-RUN doctoc TO UPDATE -->
**Table of Contents**  *generated with [DocToc](https://github.com/thlorenz/doctoc)*

- [Basic String operation](#basic-string-operation)
  - [find/substr](#findsubstr)
  - [Insert/Pushback](#insertpushback)
  - [Subdomain](#subdomain)
- [Substring problem](#substring-problem)
  - [Two pointers problem](#two-pointers-problem)
    - [Common solution Summary](#common-solution-summary)
    - [string partition](#string-partition)
    - [Permutation](#permutation)
    - [Task Schedule](#task-schedule)
  - [Substring Problem from 2 or more strings](#substring-problem-from-2-or-more-strings)
    - [Longest Word in Dictionary through Deleting](#longest-word-in-dictionary-through-deleting)
    - [Find substring in String](#find-substring-in-string)
    - [String Partition (Partition Labels)](#string-partition-partition-labels)
    - [KMP](#kmp)
      - [KMP application](#kmp-application)
- [Subsequence Problem](#subsequence-problem)
- [Palindrome Problem](#palindrome-problem)
  - [Valid Palindrome with 1 delete](#valid-palindrome-with-1-delete)
    - [Valid Palindrome with N delete](#valid-palindrome-with-n-delete)
- [String BFS/Recursive](#string-bfsrecursive)
  - [Combination](#combination)
  - [Expression Coding/Decoding](#expression-codingdecoding)
    - [String Compression](#string-compression)
    - [String as calculator](#string-as-calculator)
    - [Ecoding/Decoding String Expression](#ecodingdecoding-string-expression)
      - [Minimum remove to valid parenthese](#minimum-remove-to-valid-parenthese)
    - [Expression operators (Via DFS)](#expression-operators-via-dfs)
    - [Word Ladder](#word-ladder)
  - [Data structure to string or vice verse](#data-structure-to-string-or-vice-verse)
    - [Serialize and Deserialize Binary Tree](#serialize-and-deserialize-binary-tree)
  - [Check if one string is Rotation of another string](#check-if-one-string-is-rotation-of-another-string)
- [Misc](#misc)
  - [String to Time](#string-to-time)

<!-- END doctoc generated TOC please keep comment here to allow auto update -->


# Basic String operation

## find/substr

```CPP
//find to get position index for certain character in string
char c;
int i = str.find(c);

//substr
string substr (size_t pos = 0, size_t len = npos) const;

```

## Insert/Pushback

```CPP
//insert to any position, 

s.insert(s.begin(), c) //insert c in begining
s.insert(s.end(), v.begin(), v.end())  //append v string to s string

s.push_back(c)  //insert c in bakc
s.pop_bakc(); //delete last
```

## Subdomain

https://leetcode.com/problems/subdomain-visit-count/

```CPP
vector<string> subdomainVisits(vector<string>& cpdomains) {
        unordered_map<string, int> count;
        for (auto cd : cpdomains) {
            int i = cd.find(" ");
            int num = stoi(cd.substr (0, i));
            string s = cd.substr (i + 1);
            for (int i = 0; i < s.size(); ++i)
                if (s[i] == '.')
                    count[s.substr(i + 1)] += num;  //so we get all sub domain 
            count[s] += num;  //need to add full domain
        }
        vector<string> res;
        for (auto k : count)
            res.push_back (to_string(k.second) + " " + k.first);
        return res;
    }
```

# Substring problem


## Two pointers problem

### Common solution Summary
* use two pointers to mark left and right,
* use a map<char,int> to record how many times a char occur. or index of certain char
  * move r first to pay off map val
* may need to use some reference cnt to check condition satisfy
* map val could be <0(overpay, leave for l move), but cnt only changes when condition matches

### string partition

https://leetcode.com/problems/partition-labels/

A string S of lowercase letters is given. We want to partition this string into as many parts as possible so that each letter appears in at most one part, and return a list of integers representing the size of these parts.

Example 1:
Input: S = "ababcbacadefegdehijhklij"
Output: [9,7,8]
Explanation:
The partition is "ababcbaca", "defegde", "hijhklij".
This is a partition so that each letter appears in at most one part.
A partition like "ababcbacadefegde", "hijhklij" is incorrect, because it splits S into less parts.

```C++
class Solution {
public:
    vector<int> partitionLabels(string S) {
        unordered_map<char, int> m;
        vector<int> res;
        for(int i = 0; i < S.size(); i++){
            m[S[i]] = i; //record right most index.
        }
        int i = 0;
        int l = 0;
        while(i < S.size()){
            int r = m[S[i]];
            //check for current index level, all index smaller will not have char beyond right most fast
            while(i < r){
                r = max(r, m[S[i]]);
                i++;
            }
            res.push_back(r-l+1);
            l = r+1;
            i++;
        }
        return res;
    }
};
```

### Permutation

https://leetcode.com/problems/permutation-in-string/#/description

Given two strings s1 and s2, write a function to return true if s2 contains the permutation of s1. In other words, one of the first string's permutations is the substring of the second string.

Example 1:
Input:s1 = "ab" s2 = "eidbaooo"
Output:True
Explanation: s2 contains one permutation of s1 ("ba").
Example 2:
Input:s1= "ab" s2 = "eidboaoo"
Output: False

```CPP
bool checkInclusion(string s1, string s2) {
    if(s1.size()==0)
        return true;
    vector<int> m(128,0);
    int l = 0;
    int r = 0;
    for(int i=0;i<s1.size();i++){
        m[s1[i]]--;  //s2 own s1
    }
    for(int l=0,r=0;r<s2.size();r++){
        if(++m[s2[r]]>0){//s2 has more than own s1 or s2 current char is not in s1
            while(--m[s2[l++]]!=0){
                //move left, until m[s2[r]] is no longer larger than 0(==0)
            }
        }
        if(r-l+1==s1.size())  {
            return true;
        }
    }

    return false;
}
```

Or we can do map check for l and r move

```CPP
bool checkInclusion(string s1, string s2) {
    if(s1.size()==0)
        return true;
    unordered_map<char,int> m;
    int l = 0;
    int r = 0;
    int cnt = 0;
    for(int i=0;i<s1.size();i++){
        m[s1[i]]++;  //s2 own s1
        cnt++;
    }
    for(int l=0,r=0;r<s2.size();r++){
        if(m.find(s2[r])!=m.end() && m[s2[r]]-->0){
            //m[s2[r]] could be smaller than 0, so s2[r] pays off and have more, leaving for l to move
            cnt--;
            while(cnt==0){//include all in s1
                if(r-l+1==s1.size())  {
                    return true;
                }
                if(m.find(s2[l])!=m.end() && m[s2[l]]++==0){
                    cnt++;
                }
                l++;
            }
        }
    }
    return false;
}
```

### Task Schedule

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


## Substring Problem from 2 or more strings

> Common problem description:

  * whether one string is substring of another
  * Further more: substring through some modification

> Common solution

  * two pointers for original string and target string.
  * original pointer keeps on moving, target pointer only moves when certain condition meet

### Longest Word in Dictionary through Deleting

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
### Find substring in String
Implemention of strstr()
```
const char * strstr ( const char * str1, const char * str2 );

```
Returns a pointer to the first occurrence of str2 in str1, or a null pointer if str2 is not part of str1.

```CPP
const char * strstr ( const char * str1, const char * str2 ){
	for(;;++str1){
		char *h = str1;
		for(char *n = str2;;++n,++h){
			if(!*n) return str1;
			if(*h!=*n) break;
		}
		if(!*h) return NULL;
	}
}

```

### String Partition (Partition Labels)

A string S of lowercase English letters is given. We want to partition this string into as many parts as possible so that each letter appears in at most one part, and return a list of integers representing the size of these parts.

https://leetcode.com/problems/partition-labels/
 
```
Example 1:

Input: S = "ababcbacadefegdehijhklij"
Output: [9,7,8]
Explanation:
The partition is "ababcbaca", "defegde", "hijhklij".
This is a partition so that each letter appears in at most one part.
A partition like "ababcbacadefegde", "hijhklij" is incorrect, because it splits S into less parts.
```

```CPP
vector<int> partitionLabels(string S) {
    unordered_map<char, int> m;
    vector<int> res;
    for(int i = 0; i < S.size(); i++){
        m[S[i]] = i; //record right most index for each char.
    }
    int i = 0;
    int l = 0;
    // record the end index of the current sub string
    while(i < S.size()){
        int r = m[S[i]];
        //check for current index level, all index smaller will not have char beyond right most fast
        while(i < r){
            r = max(r, m[S[i]]);
            i++;
        }
        res.push_back(r-l+1);
        l = r+1;
        i++;
    }
    return res;
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

#### KMP application

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

# Subsequence Problem
https://leetcode.com/problems/is-subsequence/#/description
A subsequence of a string is a new string which is formed from the original string by deleting some (can be none) of the characters without disturbing the relative positions of the remaining characters. (ie, "ace" is a subsequence of "abcde" while "aec" is not).

```
Example 1:
s = "abc", t = "ahbgdc"
Return true.

Example 2:
s = "axc", t = "ahbgdc"
Return false.
```


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

# Palindrome Problem

## Valid Palindrome with 1 delete

https://leetcode.com/problems/valid-palindrome-ii/

Given a non-empty string s, you may delete at most one character. Judge whether you can make it a palindrome.

```
Example 1:
Input: "aba"
Output: True
Example 2:
Input: "abca"
Output: True
Explanation: You could delete the character 'c'.
```

```CPP
bool validPalindrome(string s) {
        int i =0;
        int j = s.size()-1;
        while(i<j){
            if (s[i] != s[j]) {
                //search for first not same pair a*****b 
                int i1 = i, j1 = j - 1, i2 = i + 1, j2 = j;
                while (i1 < j1 && s[i1] == s[j1]) {
                    i1++; 
                    j1--;
                };
                while (i2 < j2 && s[i2] == s[j2]) {
                    i2++; j2--;
                };
                //we can go to middle
                return i1 >= j1 || i2 >= j2;
            }
            i++;
            j--;
        }
        return true;
    }
```

### Valid Palindrome with N delete

extend the delete into N

```CPP
bool validPalindrome(string s) {
    return valid(s, 0, s.length() - 1, 1);
}

bool valid(string& s, int i, int j, int d) { // d: num of chars you can delete at most
    //we have checked all
    if (i >= j) 
      return true;
    if (s[i] == s[j])
      return valid(s, i + 1, j - 1, d);
    else
      //we already delete all d
      if (d<=0)
        return false;
      //delete either from start side or end side
      return valid(s, i + 1, j, d - 1) || valid(s, i, j - 1, d - 1);
}
```

# String BFS/Recursive

Typically this problem will have incoming string stream, with each char represent certain meaning(could be char, number, or encoding way), and need to process this stream to get some results.

* Common solution: Use some index to pass over and recursively modify, index better to be reference type
* BFS to visit all char in string and do sth

## Combination

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

## Expression Coding/Decoding

Key of all these problem are caching the sign, and caching intermidtate(* ,/ or bracket) results in stack

### String Compression

https://leetcode.com/problems/string-compression/

Given an array of characters chars, compress it using the following algorithm:

Begin with an empty string s. For each group of consecutive repeating characters in chars:

If the group's length is 1, append the character to s.
Otherwise, append the character followed by the group's length.
The compressed string s should not be returned separately, but instead be stored in the input character array chars. Note that group lengths that are 10 or longer will be split into multiple characters in chars.

After you are done modifying the input array, return the new length of the array.

 
Follow up:
Could you solve it using only O(1) extra space?

``` 

Example 1:

Input: chars = ["a","a","b","b","c","c","c"]
Output: Return 6, and the first 6 characters of the input array should be: ["a","2","b","2","c","3"]
Explanation: The groups are "aa", "bb", and "ccc". This compresses to "a2b2c3".

```

```CPP
int compress(vector<char>& chars) {
        
        if(chars.size()<2){
            return chars.size();
        }
        

        char cur = chars[0];
        int frequency = 1;
        int index = 0;
        
        for(int i=1;i<chars.size();i++){
            if(chars[i]!=cur){
                if(frequency >1){
                    //one for char, one for frequency
                    chars[index++] = cur;
                    string num = to_string(frequency);
                    for(int j=0;j<num.size();j++){
                        chars[index++] = num[j];
                    }
                    
                }else{
                    //only one
                    chars[index++] = cur;
                }

                //start new
                cur = chars[i];
                frequency = 1;
                
            }else{
               frequency++; 
            }
        }
        
        //process end
        if(frequency >1){
            chars[index++] = cur;
            string num = to_string(frequency);
            for(int j=0;j<num.size();j++){
                chars[index++] = num[j];
            }
        }else{
            chars[index++] = cur;
        }
        
        return index;
        
    }
```

### String as calculator

https://leetcode.com/problems/basic-calculator/

Implement a basic calculator to evaluate a simple expression string.

The expression string may contain open ( and closing parentheses ), the plus + or minus sign -, non-negative integers and empty spaces .

```
Example 1:

Input: "1 + 1"
Output: 2
Example 2:

Input: " 2-1 + 2 "
Output: 3
Example 3:

Input: "(1+(4+5+2)-3)+(6+8)"
Output: 23
```

```CPP

/*
digit: it should be one digit from the current number
'+': number is over, we can add the previous number and start a new number
'-': same as above
'(': push the previous result and the sign into the stack, set result to 0, just calculate the new result within the parenthesis.
')': pop out the top two numbers from stack, first one is the sign before this pair of parenthesis, second is the temporary result before this pair of parenthesis. We add them together.
*/
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
            if(s[i]=='+') 
              sign = 1;
            if(s[i]=='-') 
              sign = -1;
            if(s[i]=='('){
                nums.push(ret);
                ops.push(sign);
                ret = 0;
                sign = 1;
            }
            if (s[i] == ')' && ops.size()) {
                ret = ops.top() * ret + nums.top();
                ops.pop(); 
                nums.pop();
            }
        }
    }
    ret += sign * num;
    return ret;
    }
```

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
            //this is last recorded sign, so we always evaludate when we have current is sign, but evaludate last 
            if(sign=='*'){
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

https://leetcode.com/problems/basic-calculator-iii/

Implement a basic calculator to evaluate a simple expression string.

The expression string may contain open ( and closing parentheses ), the plus + or minus sign -, non-negative integers and empty spaces .

The expression string contains only non-negative integers, +, -, *, / operators , open ( and closing parentheses ) and empty spaces . The integer division should truncate toward zero.

You may assume that the given expression is always valid. All intermediate results will be in the range of [-2147483648, 2147483647].

Some examples:

"1 + 1" = 2
" 6-4 / 2 " = 4
"2*(5+5*2)/3+(6/2+8)" = 21
"(2+6* 3+5- (3*14/7+2)*5)+3"=-12

```CPP
    int calculate(string s) {
        int i = 0;
        return expr(s, i);
    }
    
    int expr(string& s, int& i) {
        vector<int> nums;
        char op = '+';
        for (; i < s.length() && op != ')'; i++) {
            if (s[i] == ' ') 
                continue;
            int n;
            if(s[i] == '('){
                n = expr(s, ++i);
            }else{
                n = num(s, i); 
            }
            //check last operator 
            switch(op) {
                case '+' : nums.push_back(n); break;
                case '-' : nums.push_back(-n); break;
                case '*' : nums.back() *= n; break;
                case '/' : nums.back() /= n; break;
            } 

            op = s[i];
        }
        int res = 0;
        for (int n : nums) 
            res += n;
        return res;
    }
    
    int num(string& s, int& i) {
        int n = 0;
        while(i < s.length() && isdigit(s[i]))
            n = s[i++] - '0' + 10 * n;
        return n;
    }
```

### Ecoding/Decoding String Expression

#### Minimum remove to valid parenthese

https://leetcode.com/problems/minimum-remove-to-make-valid-parentheses/

Given a string s of '(' , ')' and lowercase English characters. 

Your task is to remove the minimum number of parentheses ( '(' or ')', in any positions ) so that the resulting parentheses string is valid and return any valid string.

Formally, a parentheses string is valid if and only if:

It is the empty string, contains only lowercase characters, or
It can be written as AB (A concatenated with B), where A and B are valid strings, or
It can be written as (A), where A is a valid string.
 
```
Example 1:

Input: s = "lee(t(c)o)de)"
Output: "lee(t(c)o)de"
Explanation: "lee(t(co)de)" , "lee(t(c)ode)" would also be accepted.
```

```CPP
    string minRemoveToMakeValid(string s) {
          stack<int> st;
          for (auto i = 0; i < s.size(); ++i) {
            if (s[i] == '(') st.push(i);
            if (s[i] == ')') {
                
              if (!st.empty()) 
                  st.pop();
              else 
                  s[i] = '*'; //invalid, need to remove
            }
          }
        //ideally we should have empty stack 
          while (!st.empty()) {
            s[st.top()] = '*';
            st.pop();
          }
          s.erase(remove(s.begin(), s.end(), '*'), s.end());
          return s;
    }
```


### Expression operators (Via DFS)

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

### Word Ladder

https://leetcode.com/problems/word-ladder/

Given two words (beginWord and endWord), and a dictionary's word list, find the length of shortest transformation sequence from beginWord to endWord, such that:

Only one letter can be changed at a time.
Each transformed word must exist in the word list.
Note:

Return 0 if there is no such transformation sequence.
All words have the same length.
All words contain only lowercase alphabetic characters.
You may assume no duplicates in the word list.
You may assume beginWord and endWord are non-empty and are not the same.

```
Example 1:

Input:
beginWord = "hit",
endWord = "cog",
wordList = ["hot","dot","dog","lot","log","cog"]

Output: 5

Explanation: As one shortest transformation is "hit" -> "hot" -> "dot" -> "dog" -> "cog",
return its length 5.
Example 2:

Input:
beginWord = "hit"
endWord = "cog"
wordList = ["hot","dot","dog","lot","log"]

Output: 0

Explanation: The endWord "cog" is not in wordList, therefore no possible transformation.
```

```CPP
int ladderLength(string beginWord, string endWord, vector<string>& wordList) {
    unordered_set<string> s(wordList.begin(), wordList.end());
    queue<string> q;
    q.push(beginWord);
    int step = 1;
    while (!q.empty()) {
        //one iteration to replace all possible char for a word
        int n = q.size();
        for (int i = 0; i < n; i++) {
            string word = q.front();
            q.pop();
            if (word == endWord) {
                return step;
            }
            //visited, remove
            s.erase(word);
            for (int j = 0; j < word.size(); j++) {
                //replace a char
                char c = word[j];
                for (int k = 0; k < 26; k++) {
                    word[j] = 'a' + k;
                    if (s.find(word) != s.end()) {
                        q.push(word);
                    }
                 }
                 //restore original
                word[j] = c;
            }
        }
        step++;
    }
    return 0;
}
```

## Data structure to string or vice verse

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

### Serialize and Deserialize Binary Tree
https://leetcode.com/problems/serialize-and-deserialize-binary-tree/#/description
```CPP
string serialize(TreeNode* root){
  string ret;
  SerializeTreeHelper(ret, root);
  return ret;
}

void SerializeTreeHelper(string &s, TreeNode* root){
  if(root==NULL){
    s = s+'#';
    s = s+',';
  }else{
    s = s+to_string(root->val);
    s = s+',';
    SerializeTreeHelper(s,root->left);
    SerializeTreeHelper(s,root->right);
  }
}

// Decodes your encoded data to tree.
TreeNode* deserialize(string data) {         
    if(data.empty())
        return NULL;
    int index = 0;
    return deserialize_helper(data, index);
}

 TreeNode* deserialize_helper(string& data, int & index) {
    if(data[index]=='#'){
        index++;
        if (index < data.size())
            index++;
        return NULL;
    }

    TreeNode* node = (TreeNode*)malloc(sizeof(TreeNode));
    string cur = "";
    int start = index;
    while(data[index]!=','){
        index++;
    }
    cur = data.substr(start,index-start);
    node->val = stoi(cur);
    index++; //pass ','

    node->left = deserialize_helper(data,index);
    node->right = deserialize_helper(data,index);

    return node;
}
```

## Check if one string is Rotation of another string

the easy way is to append the s1+s1, and check whether s2 is substring of s1.

How do we achieve O(N). s1+s1 exhaustive list all substring


# Misc

## String to Time

https://leetcode.com/problems/next-closest-time/



Given a time represented in the format "HH:MM", form the next closest time by reusing the current digits. There is no limit on how many times a digit can be reused.

You may assume the given input string is always valid. For example, "01:34", "12:09" are all valid. "1:34", "12:9" are all invalid.

```
Example 1:

Input: "19:34"
Output: "19:39"
Explanation: The next closest time choosing from digits 1, 9, 3, 4, is 19:39, which occurs 5 minutes later.  It is not 19:33, because this occurs 23 hours and 59 minutes later.
Example 2:

Input: "23:59"
Output: "22:22"
Explanation: The next closest time choosing from digits 2, 3, 5, 9, is 22:22. It may be assumed that the returned time is next day's time since it is smaller than the input time numerically.
```

```CPP
string nextClosestTime(string time) {
    //insert all digit in sorted order
    set<char> sorted;
    for(auto c:time){
        if(c==':') 
            continue;
        sorted.insert(c);
    }
   
    string res = time;
    //from end, mm to hh
    for(int i = time.size() -1; i>=0; i--){
        if(time[i] == ':' ) 
            continue;
        auto it = sorted.find(time[i]);
         if(*it != *sorted.rbegin()){// not the largest number
            it++; // go to the next element
            res[i] = *it;
            //valid time mm<60 and hh<24 and at least 3 digits
            if((i>=3 && stoi(res.substr(3,2))<60) ||(i<2&&stoi(res.substr(0,2))<24))       
                return res;      
         } 
         res[i]=*sorted.begin(); // take the smallest number
    }
    return res; 
    
}
```