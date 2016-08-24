//https://leetcode.com/problems/longest-substring-with-at-most-k-distinct-characters/
/*
Given a string, find the length of the longest substring T that contains at most k distinct characters.
For example, Given s = “eceba” and k = 2,
T is "ece" which its length is 3. 
*/
class Solution {
public:
    int lengthOfLongestSubstringKDistinct(string s, int k) {
        int len = 0;
        int ret = 0;
        int start = 0;
        unordered_map<char,int> m;
        for(int i=0;i<s.size();i++){
            m[s[i]]++;
            if(m.size()<=k){
                ret = max(ret,i-start+1);
            }
            while(m.size()>k){
                //if reduce certain char's occurance can remove it, we can reduce map size by one, 
                if(--m[s[start]]==0){
                    m.erase(s[start]);
                }
                start++;
            }
        }
        
        return ret;
    }
};
