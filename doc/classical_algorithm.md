## KMP

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

## BFPRT
In an unordered array, find the k'th smallest or largest value

first method is recursive:
1. select a pivot number
2. partition the collection into <,=,> 3 collections compared with pivot
3. check k's smallest location, then recursive

The issue is pivot choice could be random and worst case is O(N^2)




## Check if one string is Rotation of another string

the easy way is to append the s1+s1, and check whether s2 is substring of s1.

How do we achieve O(N). s1+s1 exhaustive list all substring



## reverse string


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


## Longest Substring Without Repeating Characters
https://leetcode.com/problems/longest-substring-without-repeating-characters/#/description

> substring problems: (if ending at certain position. sub problem:)

In this problem, it is longest substring without duplicate ending at i

```CPP
//method 1: use a map to record position
int lengthOfLongestSubstring(string s) {
    int start = 0;
    int end = 0;
    int counter = 0; //how many char has more than once
    vector<int> map(128,0);
    int ret = 0;
    while(end<s.size()){
        //for unique char
        if(map[s[end]]==1){
            counter++;
        }
        map[s[end]]++;
        end++;
        //not unique so counter>0
        while(counter>0){
            if(--map[s[start]]==1){
                counter--;
            }
            start++;
        }
        ret = max(ret,end-start);
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

## Minimum windows substring
https://leetcode.com/problems/minimum-window-substring/#/description
Given a string S and a string T, find the minimum window in S which will contain all the characters in T in complexity O(n).

For example,
S = "ADOBECODEBANC"
T = "ABC"
Minimum window is "BANC".
