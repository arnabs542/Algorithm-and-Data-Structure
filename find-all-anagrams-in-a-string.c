//https://leetcode.com/problems/find-all-anagrams-in-a-string/
/*
Given a string s and a non-empty string p, find all the start indices of p's anagrams in s.

Strings consists of lowercase English letters only and the length of both strings s and p will not be larger than 20,100.

The order of output does not matter.

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
*/

//method 1: O(nmlog(m))
class Solution {
public:
    vector<int> findAnagrams(string s, string p) {
        //this is a O(nm) solution. time limit pass
        int len = p.size();
        vector<int> ret;
        if(s.size()<len)
            return ret;
        sort(p.begin(),p.end());
        for(int i=0;i<=s.size()-len;i++){
            string cur = s.substr(i,len);
            if(isanag(cur,p))
                ret.push_back(i);
        }
        return ret;
    }
    
    bool isanag(string a, string b){
        sort(a.begin(),a.end());
        
        for(int i=0;i<a.size();i++){
            if(a[i]!=b[i])
                return false;
        }
        return true;
    }
};

//method 2: O(n)
class Solution {
public:
    vector<int> findAnagrams(string s, string p) {
        //this is a O(nm) solution. time limit pass
        int len = p.size();
        vector<int> ret;
        if(s.size()<len)
            return ret;
        vector<int> m(256,0);
        vector<int> dict(256,0); 
        //map<char,int> m; //key is char, val is count
        //map<char,int> dict; //key is char, val is count
        for(int i=0;i<len;i++){
            dict[p[i]]++;
            m[s[i]]++;
        }
        if(m==dict)
            ret.push_back(0);
        for(int i=len;i<s.size();i++){
            m[s[i-len]]--;
            m[s[i]]++;
            if(m==dict)
                ret.push_back(i-len+1);
        }
        return ret;
    }

};
