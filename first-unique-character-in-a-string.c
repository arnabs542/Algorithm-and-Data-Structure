//https://leetcode.com/problems/first-unique-character-in-a-string/
/*Given a string, find the first non-repeating character in it and return it's index. If it doesn't exist, return -1.
Examples:
s = "leetcode"
return 0.
s = "loveleetcode",
return 2.
*/
//method 1: use array
class Solution {
public:
    int firstUniqChar(string s) {
        int alphabet[26] = {0};
        for(int i=0;i<s.size();i++){
            alphabet[s[i]-'a']++;
        }
        int ret = INT_MAX;
        int i = 0;
        while(i<s.size()){
            if(alphabet[s[i]-'a']==1)
                return i;
            i++;
        }
        return -1;
    }
};

//method 2: use hash table to record each char's position
class Solution {
public:
    int firstUniqChar(string s) {
        map<char,vector<int>> m;//key is char,val is index(s)
        for(int i=0;i<s.size();i++){
            m[s[i]].push_back(i);
        }
        int ret = INT_MAX;
        bool found = false;
        for(auto ch: m){
            //only unique character
            if(ch.second.size()==1){
                found = true;
                ret = min(ret,ch.second[0]);
            }
        }
        if(!found)
            return -1;
        return ret;
    }
};
