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

//method2: use two pointers and sub array template
class Solution {
public:
    int lengthOfLongestSubstringKDistinct(string s, int k) {
        vector<int> map(128,0);//128 char
        int start=0;
        int end = 0;
        int counter = 0;
        int ret = 0;
        while(end<s.size()){
            if(map[s[end]]++==0){//meet a new distinct char, out loop to entend the end pointer
                counter++;
            }
            end++;
            while(counter>k){
                if(map[s[start]]--==1){//since current char only appears once, remove it will lead one less distinct char
                    counter--;
                }
                start++;
            }
            ret = max(ret,end-start);
        }
        return ret;
    }
};

