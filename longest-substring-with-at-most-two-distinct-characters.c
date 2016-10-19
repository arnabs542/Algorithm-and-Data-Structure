//https://leetcode.com/problems/longest-substring-with-at-most-two-distinct-characters/
/*
 Given a string, find the length of the longest substring T that contains at most 2 distinct characters.
For example, Given s = “eceba”,
T is "ece" which its length is 3. 
*/
class Solution {
public:
    int lengthOfLongestSubstringTwoDistinct(string s) {
        int start = 0;
        unordered_map<char,int> m;
        int ret = 0;
        for(int i=0;i<s.size();i++){
            m[s[i]]++;
            if(m.size()<=2){
                ret = max(ret,i-start+1);
            }
            while(m.size()>2){
                if(--m[s[start]]==0){ //move this start char position will eliminate one char in map, so reduce size
                    m.erase(s[start]);
                }
                start++;
            }
        }
        return ret;      
    }
};
