//https://leetcode.com/problems/longest-substring-without-repeating-characters/
/*
Given a string, find the length of the longest substring without repeating characters.
Examples:

Given "abcabcbb", the answer is "abc", which the length is 3.
Given "bbbbb", the answer is "b", with the length of 1.
Given "pwwkew", the answer is "wke", with the length of 3. Note that the answer must be a substring, "pwke" is a subsequence and not a substring.
*/
class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        vector<int> m(128,0); //char map
        int start=0;
        int end =0;
        int ret = 0;
        int counter = 0;
        while(end<s.size()){
            //found some char already existing
            if(m[s[end]]==1){
                counter++;
            }
            m[s[end]]++;
            end++;
            while(counter>0){
                //if remove current char can lead the substring back to unique
                if(--m[s[start]]==1){
                    counter--;
                }
                start++;
            }
            ret = max(ret,end-start);
        }
        return ret;
    }
};

//method 2: use hash table
class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        vector<int> m(128,0); //char map
        int start=0;
        int end =0;
        int ret = 0;
        int counter = 0;
        while(end<s.size()){
            //found some char already existing
            if(m[s[end]]==1){
                counter++;
            }
            m[s[end]]++;
            end++;
            while(counter>0){
                //if remove current char can lead the substring back to unique
                if(--m[s[start]]==1){
                    counter--;
                }
                start++;
            }
            ret = max(ret,end-start);
        }
        return ret;
    }
};
