//https://leetcode.com/problems/palindrome-pairs/
/*
Given a list of unique words. Find all pairs of distinct indices (i, j) in the given list, so that the concatenation of the two words, i.e. words[i] + words[j] is a palindrome.

Example 1:
Given words = ["bat", "tab", "cat"]
Return [[0, 1], [1, 0]]
The palindromes are ["battab", "tabbat"]
Example 2:
Given words = ["abcd", "dcba", "lls", "s", "sssll"]
Return [[0, 1], [1, 0], [3, 2], [2, 4]]
The palindromes are ["dcbaabcd", "abcddcba", "slls", "llssssll"]
*/
//method 1: O(n^2)
class Solution {
public:
    vector<vector<int>> palindromePairs(vector<string>& words) {
        vector<vector<int>> ret;
        for(int i=0;i<words.size();i++){
            for(int j=i+1;j<words.size();j++){
                vector<int> cur;
                if(ispali(words[i]+words[j])){
                    cur.push_back(i);
                    cur.push_back(j);
                    ret.push_back(cur);
                    cur.clear();
                }
                if(ispali(words[j]+words[i])){
                    cur.push_back(j);
                    cur.push_back(i);
                    ret.push_back(cur);
                    cur.clear();
                }                
                    
            }
        }
        return ret;
    }
    
    bool ispali(string s){
        int start = 0;
        int end=s.size()-1;
        while(start<end){
            if(s[start]!=s[end]){
                return false;
            }
            start++;
            end--;
        }
        return true;
        
    }
};

//O(n)

class Solution {
public:
    vector<vector<int>> palindromePairs(vector<string>& words) {
        /*
        Partition the word into left and right, and see 1) if there exists a candidate in map equals the left side of current word, and right side of current word is palindrome, so concatenate(current word, candidate) forms a pair: left | right | candidate. 2) same for checking the right side of current word: candidate | left | right.
        */
        
        //key is string and value is index
        vector<vector<int>> ret;
        unordered_map<string,int> m;
        
        for(int i=0;i<words.size();i++){
            m[words[i]]=i;
        }
// edge case: if empty string "" exists, find all palindromes to become pairs ("", self)
            if(m.find("")!=m.end()){
                for(int i = 0; i < words.size(); i++){
                    if(i == m[""]) continue;
                    if(ispali(words[i])) ret.push_back({m[""], i}); 
                    // 1) if self is palindrome, here ans covers concatenate("", self) 
                }
            }
        
        for(int i=0;i<words.size();i++){
            for(int j=0;j<words[i].size();j++){
                string s1=words[i].substr(0,j);
                string s2=words[i].substr(j);
                string rs1 = reverse(s1);
                string rs2 = reverse(s2);
                //found s2 pali s1 and rs1 both in map and not itself, s1+s2+rs1 is pali
                if(ispali(s2) && m.find(rs1)!=m.end() && m[rs1]!=i){
                    ret.push_back({i,m[rs1]});
                }
                //found s1 pali s2 and rs2 both in map and not itself, s2+s1+rs2 is pali
                if(ispali(s1) && m.find(rs2)!=m.end() && m[rs2]!=i){
                    ret.push_back({m[rs2],i});
                }
            }
        }
        return ret;
    }
    
    string reverse(string s){
        int start = 0;
        int len = s.size();
        string ret = s;
        while(start<len){
            ret[start]=s[len-1-start];
            start++;
        }
        return ret;
        
    }
    
    bool ispali(string s){
        int start=0;
        int end=s.size()-1;
        while(start<end){
            if(s[start]!=s[end]){
                return false;
            }
            start++;
            end--;
        }
        return true;
    }
};
