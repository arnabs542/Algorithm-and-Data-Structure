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
        int start = 0;
        unordered_map<char,int> m;
        int ret = 0;
        int counter = 0;
        for(int i=0;i<s.size();i++){
            m[s[i]]++;
            if(m[s[i]]>1){
                counter++;
            }

            while(counter>0){
                if(--m[s[start]]==1){//back to unique case
                    counter--;
                }
                start++;
            }
            ret = max(ret,i-start+1);
        }

        return ret;
    }
};


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
