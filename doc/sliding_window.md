<!-- START doctoc generated TOC please keep comment here to allow auto update -->
<!-- DON'T EDIT THIS SECTION, INSTEAD RE-RUN doctoc TO UPDATE -->
**Table of Contents**  *generated with [DocToc](https://github.com/thlorenz/doctoc)*

- [Sliding Windows](#sliding-windows)
  - [Maximum Average Subarray](#maximum-average-subarray)
    - [Maximum Average Subarray/fixed sliding window](#maximum-average-subarrayfixed-sliding-window)
    - [Maximum Average Subarray/dynamic sliding window](#maximum-average-subarraydynamic-sliding-window)
  - [Maximum value in sliding window](#maximum-value-in-sliding-window)
  - [Mini Sub string](#mini-sub-string)
  - [Longest Substring with At Most Two Distinct Characters](#longest-substring-with-at-most-two-distinct-characters)
    - [Fruit Into Baskets](#fruit-into-baskets)
  - [Longest Substring Without Repeating Characters](#longest-substring-without-repeating-characters)
  - [Longest Substring with Same Letters after K change](#longest-substring-with-same-letters-after-k-change)
    - [Max Consecutive Ones with K changes](#max-consecutive-ones-with-k-changes)
  - [Permutation in a String](#permutation-in-a-string)
  - [Find All Anagrams in a String](#find-all-anagrams-in-a-string)
  - [Smallest Window containing Substring](#smallest-window-containing-substring)
  - [Longest Substring Without Repeating Characters](#longest-substring-without-repeating-characters-1)

<!-- END doctoc generated TOC please keep comment here to allow auto update -->

# Sliding Windows

```CPP
int left = 0, right = 0;

while (right < s.size()) {
  //Increase the window size 
    window.add(s[right]);
    right++;

    while (window_can_be_shrink) {
        //reduce the window
        window.remove(s[left]);
        left++;
    }
}
```

## Maximum Average Subarray 

### Maximum Average Subarray/fixed sliding window

https://leetcode.com/problems/maximum-average-subarray-i/

Given an array consisting of n integers, find the contiguous subarray of given length k that has the maximum average value. And you need to output the maximum average value.

```CPP
double findMaxAverage(vector<int>& nums, int k) {
    double sum=0;
    for(int i=0;i<k;i++)
        sum+=nums[i];
    double res=sum;
    for(int i=k;i<nums.size();i++){
        sum+=nums[i]-nums[i-k];
        res=max(res,sum);
    }
    return res/k;
}
```

### Maximum Average Subarray/dynamic sliding window

https://leetcode.com/problems/maximum-average-subarray-ii/

Given an array consisting of n integers, find the contiguous subarray whose length is greater than or equal to k that has the maximum average value. And you need to output the maximum average value.

```
Example 1:
Input: [1,12,-5,-6,50,3], k = 4
Output: 12.75
Explanation:
when length is 5, maximum average value is 10.8,
when length is 6, maximum average value is 9.16667.
Thus return 12.75.
```

## Maximum value in sliding window

https://leetcode.com/problems/sliding-window-maximum/

You are given an array of integers nums, there is a sliding window of size k which is moving from the very left of the array to the very right. You can only see the k numbers in the window. Each time the sliding window moves right by one position.

Return the max sliding window.

 
```
Example 1:

Input: nums = [1,3,-1,-3,5,3,6,7], k = 3
Output: [3,3,5,5,6,7]
Explanation: 
Window position                Max
---------------               -----
[1  3  -1] -3  5  3  6  7       3
 1 [3  -1  -3] 5  3  6  7       3
 1  3 [-1  -3  5] 3  6  7       5
 1  3  -1 [-3  5  3] 6  7       5
 1  3  -1  -3 [5  3  6] 7       6
 1  3  -1  -3  5 [3  6  7]      7
```

```CPP
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        //use deque, make sure the queue is always in sorted order with front the largest item's index
        vector<int> ret;
        deque<int> dq; //store index, with num[index] monotonic decreasing from front
        for(int i=0;i<nums.size();i++){
            if(!dq.empty() && (dq.front()==i-k)){
                //the max value's index in deque reach the window size, need to pop out.
                    dq.pop_front();
            }
            while(!dq.empty() && nums[dq.back()]<nums[i]){
                dq.pop_back();
            }
            dq.push_back(i);
            if (i>=k-1)
                ret.push_back(nums[dq.front()]);
        }
        return ret;
    }
```



## Mini Sub string

Given a string S and a string T, find the minimum window in S which will contain all the characters in T in complexity O(n).

```
Example:

Input: S = "ADOBECODEBANC", T = "ABC"
Output: "BANC"
Note:

If there is no such window in S that covers all characters in T, return the empty string "".
If there is such window, you are guaranteed that there will always be only one unique minimum window in S.
```

We use the pattern and code will be 

```CPP

class Solution {
public:
    string minWindow(string s, string t) {
        string s, t;

        int left = 0, right = 0;
        string res = s;

        // two counters
        unordered_map<char, int> window;
        unordered_map<char, int> needs;
        for (char c : t) 
          needs[c]++;

        // record how many char in windows match condition
        int match = 0; 

        while (right < s.size()) {
            char c1 = s[right];
            if (needs.count(c1)) {
                window[c1]++; // 
                if (window[c1] == needs[c1])
                    //  c1 has same occurance in needs and window
                    match++;
            }
            right++;

            // all chars match
            while (match == needs.size()) {
                if (right - left < minLen) {
                    // update min sgtring
                    start = left;
                    minLen = right - left;
                  }
                char c2 = s[left];
                if (needs.count(c2)) {
                    window[c2]--; // remove from window
                    if (window[c2] < needs[c2])
                        // c2 dose not meet requirements
                        match--;
                }
                left++;
            }
        }
        return minLen == INT_MAX ?"" : s.substr(start, minLen);
    }
};


```

## Longest Substring with At Most Two Distinct Characters

https://leetcode.com/explore/interview/card/google/59/array-and-strings/3054/

Given a string s , find the length of the longest substring t  that contains at most 2 distinct characters.

```
Example 1:

Input: "eceba"
Output: 3
Explanation: t is "ece" which its length is 3.
Example 2:

Input: "ccaabbb"
Output: 5
Explanation: t is "aabbb" which its length is 5.
```

```CPP
    int lengthOfLongestSubstringTwoDistinct(string s) {
        int start = 0;
        unordered_map<char,int> m;
        int ret = 0;
        for(int i=0;i<str.size();i++){
            m[str[i]]++;
            while(m.size()>k){
                if(--m[str[start]]==0){ //move this start char position will eliminate one char in map, so reduce size
                    m.erase(str[start]);
                }
                start++;
            }
            ret = max(ret,i-start+1);
        }
        return ret;         
    }
```

### Fruit Into Baskets

In a row of trees, the i-th tree produces fruit with type tree[i].

You start at any tree of your choice, then repeatedly perform the following steps:

Add one piece of fruit from this tree to your baskets.  If you cannot, stop.
Move to the next tree to the right of the current tree.  If there is no tree to the right, stop.
Note that you do not have any choice after the initial choice of starting tree: you must perform step 1, then step 2, then back to step 1, then step 2, and so on until you stop.

You have two baskets, and each basket can carry any quantity of fruit, but you want each basket to only carry one type of fruit each.

What is the total amount of fruit you can collect with this procedure?

```CPP
    int totalFruit(vector<int>& tree) {
                //Find out the longest length of subarrays with at most 2 different numbers
        unordered_map<int, int> count;
        int i, j;
        int ret = 0;
        for (i = 0, j = 0; j < tree.size(); ++j) {
            count[tree[j]]++;
            while (count.size() > 2) {
                count[tree[i]]--;
                if (count[tree[i]] == 0)
                    count.erase(tree[i]);
                i++;
            }
            ret = max(ret,j-i+1);
        }
        return ret;
    }
```

## Longest Substring Without Repeating Characters

https://leetcode.com/problems/longest-substring-without-repeating-characters/

```CPP
  static int findLength(const string& str) {

      int start = 0, end = 0;
      unordered_map<char, int> m;
      int res = 0; // record longest length

      for(end=0;end<str.size();end++) {
          m[str[end]]++;
          //repeating char appear, so move left
          while (m[str[end]] > 1) {
              m[str[start]]--;
              start++;
          }
          res = max(res, end - start+1);
      }
      return res;

  }
```

## Longest Substring with Same Letters after K change

https://www.educative.io/courses/grokking-the-coding-interview/R8DVgjq78yR

https://leetcode.com/problems/longest-repeating-character-replacement/

Given a string s that consists of only uppercase English letters, you can perform at most k operations on that string.
In one operation, you can choose any character of the string and change it to any other uppercase English character.
Find the length of the longest sub-string containing all repeating letters you can get after performing the above operations.


```
Example 1:

Input:
s = "ABAB", k = 2

Output:
4

Explanation:
Replace the two 'A's with two 'B's or vice versa.
 

Example 2:

Input:
s = "AABABBA", k = 1

Output:
4

Explanation:
Replace the one 'A' in the middle with 'B' and form "AABBBBA".
The substring "BBBB" has the longest repeating letters, which is 4.
```

```CPP
    int characterReplacement(string s, int k) {
          int start = 0, end = 0;
          unordered_map<char,int> m;
          int maxRepeat = 0;  //at any given window, max 
          int res = 0; // record longest length

          for(end=0;end<s.size();end++) {
              m[s[end]]++;
              maxRepeat = max(maxRepeat, m[s[end]]);
              //we can change at most K
              if (end - start + 1 - maxRepeat > k) {
                m[s[start]]--;
                start++;
              }
              res = max(res, end - start+1);
          }
          return res;  
    }
```

### Max Consecutive Ones with K changes

https://leetcode.com/problems/max-consecutive-ones-iii/

https://www.educative.io/courses/grokking-the-coding-interview/B6VypRxPolJ

Given an array containing 0s and 1s, if you are allowed to replace no more than ‘k’ 0s with 1s, find the length of the longest contiguous subarray having all 1s.

```
Example 1:

Input: Array=[0, 1, 1, 0, 0, 0, 1, 1, 0, 1, 1], k=2
Output: 6
Explanation: Replace the '0' at index 5 and 8 to have the longest contiguous subarray of 1s having length 6.
Example 2:

Input: Array=[0, 1, 0, 0, 1, 1, 0, 1, 1, 0, 0, 1, 1], k=3
Output: 9
Explanation: Replace the '0' at index 6, 9, and 10 to have the longest contiguous subarray of 1s having length 9.
```



```CPP
int longestOnes(vector<int>& arr, int K) {
      int start = 0, end = 0;
      int maxOnes = 0;  //at any given window, max 
      int res = 0; // record longest length

      for(end=0;end<arr.size();end++) {
          if(arr[end]==1)
            maxOnes++;
          //we can change at most K
          if (end - start + 1 - maxOnes > K) {
            if(arr[start]==1)
              maxOnes--;
            start++;
          }
          res = max(res, end - start+1);
      }
      return res;       
}
```

## Permutation in a String

https://www.educative.io/courses/grokking-the-coding-interview/N8vB7OVYo2D

https://leetcode.com/problems/permutation-in-string/

Given two strings s1 and s2, write a function to return true if s2 contains the permutation of s1. In other words, one of the first string's permutations is the substring of the second string.

 
```
Example 1:

Input: s1 = "ab" s2 = "eidbaooo"
Output: True
Explanation: s2 contains one permutation of s1 ("ba").
Example 2:

Input:s1= "ab" s2 = "eidboaoo"
Output: False
```

```CPP
static bool findPermutation(const string &str, const string &pattern) {
        if(pattern.size()==0)
            return true;
        unordered_map<char,int> m;
        int l = 0;
        int r = 0;
        int cnt = 0;
        for(int i=0;i<pattern.size();i++){
            m[pattern[i]]++;  
            cnt++;
        }
        for(int l=0,r=0;r<str.size();r++){
            if(m.find(str[r])!=m.end() && m[str[r]]-->0){
                //m[s2[r]] could be smaller than 0, so s2[r] pays off and have more, leaving for l to move
                cnt--;
                while(cnt==0){//include all in pattern
                    if(r-l+1==pattern.size())  {
                        return true;
                    }
                    //if size > pattern, move left pointer
                    if(m.find(str[l])!=m.end() && m[str[l]]++==0){
                        cnt++;
                    }
                    l++;
                }
            }
        }
        return false;
  }
```

A more descriptive solution is

1. Create a HashMap to calculate the frequencies of all characters in the pattern.

2. Iterate through the string, adding one character at a time in the sliding window.

3. If the character being added matches a character in the HashMap, decrement its frequency in the map. If the character frequency becomes zero, we got a complete match.

4. If at any time, the number of characters matched is equal to the number of distinct characters in the pattern (i.e., total characters in the HashMap), we have gotten our required permutation.

5. If the window size is greater than the length of the pattern, shrink the window to make it equal to the size of the pattern. At the same time, if the character going out was part of the pattern, put it back in the frequency HashMap.

```CPP
bool checkInclusion(string pattern, string str) {
    if(pattern.size()==0)
        return true;
    unordered_map<char,int> m;
    int l = 0;
    int r = 0;
    int cnt = 0;
    for(int i=0;i<pattern.size();i++){
        m[pattern[i]]++;  
    }
    for(r=0;r<str.size();r++){
        if(m.find(str[r])!=m.end()){
            m[str[r]]--;  
            //find all occurence for this letter
            if(m[str[r]]==0){
                cnt++;
            }
        }
        
        if(cnt == m.size() && (r-l+1)==pattern.size()){
            return true;
        }
        if(r>=pattern.size()-1){
            if(m.find(str[l])!=m.end()){
                if(m[str[l]]==0)
                    cnt--;
                m[str[l]]++;

            }
            l++;
        }


    }
    return false;
}
```


## Find All Anagrams in a String

https://leetcode.com/problems/find-all-anagrams-in-a-string/

Given a string s and a non-empty string p, find all the start indices of p's anagrams in s.

Strings consists of lowercase English letters only and the length of both strings s and p will not be larger than 20,100.

The order of output does not matter.

```
Example 1:

Input:
s: "cbaebabacd" p: "abc"

Output:
[0, 6]

Explanation:
The substring with start index = 0 is "cba", which is an anagram of "abc".
The substring with start index = 6 is "bac", which is an anagram of "abc".
Example 2:

Input:
s: "abab" p: "ab"

Output:
[0, 1, 2]

Explanation:
The substring with start index = 0 is "ab", which is an anagram of "ab".
The substring with start index = 1 is "ba", which is an anagram of "ab".
The substring with start index = 2 is "ab", which is an anagram of "ab".
```


The same solution as before:

```CPP
class Solution {
public:
    vector<int> findAnagrams(string s, string t) {
        vector<int> res;
        int left = 0, right = 0;
        unordered_map<char, int> needs;
        unordered_map<char, int> window;
        for (char c : t) needs[c]++;
        int match = 0;

        while (right < s.size()) {
            char c1 = s[right];
            if (needs.count(c1)) {
                window[c1]++;
                if (window[c1] == needs[c1])
                    match++;
            }
            right++;

            while (match == needs.size()) {
                //match anagrams
                if (right - left == t.size()) {
                    res.push_back(left);
                }
                char c2 = s[left];
                if (needs.count(c2)) {
                    window[c2]--;
                    if (window[c2] < needs[c2])
                        match--;
                }
                left++;
            }
        }
        return res;
    }
};
```

## Smallest Window containing Substring

https://leetcode.com/problems/minimum-window-substring/

Given a string S and a string T, find the minimum window in S which will contain all the characters in T in complexity O(n).

```
Example:

Input: S = "ADOBECODEBANC", T = "ABC"
Output: "BANC"
```


##  Longest Substring Without Repeating Characters

https://leetcode.com/problems/longest-substring-without-repeating-characters/

```
Example 1:

Input: "abcabcbb"
Output: 3 
Explanation: The answer is "abc", with the length of 3. 
Example 2:

Input: "bbbbb"
Output: 1
Explanation: The answer is "b", with the length of 1.
Example 3:

Input: "pwwkew"
Output: 3
Explanation: The answer is "wke", with the length of 3. 
             Note that the answer must be a substring, "pwke" is a subsequence and not a substring.
```

* For substring, slide window is no brainer

```CPP
class Solution {
public:
    int lengthOfLongestSubstring(string s) {
            int left = 0, right = 0;
            unordered_map<char, int> window;
            int res = 0; // record longest length

            while (right < s.size()) {
                char c1 = s[right];
                window[c1]++;
                right++;
                //repeating char appear, so move left
                while (window[c1] > 1) {
                    char c2 = s[left];
                    window[c2]--;
                    left++;
                }
                res = max(res, right - left);
            }
            return res;
    }
};
```