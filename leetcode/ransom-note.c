//https://leetcode.com/problems/ransom-note/
/*

Note:
You may assume that both strings contain only lowercase letters.

canConstruct("a", "b") -> false
canConstruct("aa", "ab") -> false
canConstruct("aa", "aab") -> true
*/
class Solution {
public:
    bool canConstruct(string ransomNote, string magazine) {
        unordered_map<char,int> m;
        for(int i=0;i<magazine.size();i++){
            m[magazine[i]]++;
        }
        
        for(int i=0;i<ransomNote.size();i++){
            if(m.find(ransomNote[i])==m.end())
                return false;
            else{
                if(--m[ransomNote[i]]<0)
                    return false;
            }
        }
        return true;
    }
};
