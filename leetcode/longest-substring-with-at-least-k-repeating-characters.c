//https://leetcode.com/problems/longest-substring-with-at-least-k-repeating-characters/
/*
Find the length of the longest substring T of a given string (consists of lowercase letters only) such that every character in T appears no less than k times.

Example 1:
Input:
s = "aaabb", k = 3
Output:
3

The longest substring is "aaa", as 'a' is repeated 3 times.
Example 2:
Input:
s = "ababbc", k = 2
Output:
5

The longest substring is "ababb", as 'a' is repeated 2 times and 'b' is repeated 3 times.
*/

//method 1:
class Solution {
public:
    int longestSubstring(string s, int k) {
        int ret = 0;
        int start = 0;
        int end = 0;
        if(s.size()<k)
            return ret;
        while(start<(s.size()-k)){
            //key is char and val is cnts;
            unordered_map<char,int> m;
            int cur_end = start;
            for(end=start;end<s.size();end++){
                m[s[end]]++;
                //this is to ensure that all chars have occurred at least k times
                bool found = true;
                for(auto j:m){
                    if(j.second<k)
                        found = false;
                }
                if(found){
                    ret = max(ret,end-start+1);
                    cur_end = end;
                }

            }
            start = cur_end+1;
        }
        return ret;
    }
};

//method 2: method 1 needs to go through all map value to ensure all have cnts>=k, which is time consuming
//use the bit vector
class Solution {
public:
    int longestSubstring(string s, int k) {
        int ret = 0;
        int start = 0;
        int end = 0;
        while (start+k < s.size()) {
           int count[26] = {0};
           int mask = 0;
           int cur_end = start;
           for (end = start; end < s.size(); ++end) {
               int i = s[end] - 'a';
               count[i]++;
               if (count[i]<k) 
                    mask |= (1 << i);
               else   
                    mask &= (~(1 << i));
               
               if (mask == 0) {
                   ret = max(ret, end-start+1);
                   cur_end = end;
               }
           }
           start = cur_end+1;
        }
        return ret;
    }
};
