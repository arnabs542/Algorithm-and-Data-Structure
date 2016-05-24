//https://leetcode.com/problems/distinct-subsequences/

/*
Given a string S and a string T, count the number of distinct subsequences of T in S.
A subsequence of a string is a new string which is formed from the original string by deleting some (can be none) of the characters 
without disturbing the relative positions of the remaining characters. 
(ie, "ACE" is a subsequence of "ABCDE" while "AEC" is not).
Here is an example:
S = "rabbbit", T = "rabbit"

Return 3.
*/

//Method1: brutal force, compare one by one
//recursive, worst case stack memory consumption is O(n)
class Solution {
public:
    int numDistinct(string s, string t) {
        //recursive:
        //worst case stack size if O(n), memory
        
        if (s.size() < t.size()) return 0;
        if (t.empty()) return 1;

        int num = 0;
        for (int i = 0; i < s.size(); ++i) {
            if (s[i] == t[0]) {
                string si = s.substr(i + 1);
                string ti = t.substr(1);
                num += numDistinct(si, ti);
            }
        }

        return num;
    }
};

//Method 2: DP
class Solution {
public:
    int numDistinct(string s, string t) {
        //DP
        /*
        f[i][j] denote number of distinct subsequences of t[0:j] in s[0:i]
        if t[j]=s[i] 
        case 1: match t[j] to s[i], then f[i][j] = f[i-1][j-1]. 
        case 2: match t[j] to s[0:i-1], then f[i][j] = f[i-1][j]. 
        so f[i][j] = f[i-1][j-1]+f[i-1][j]
        
        if t[j]!=s[i], then 
         f[i][j] = f[i-1][j]. 
         
        */
        if (s.size() < t.size()) return 0;
        if (t.empty()) return 1;

        vector<vector<int> > f(s.size() + 1, vector<int>(t.size() + 1, 0));
        
        for(int i=0;i<s.size();i++){
            f[i][0] = 1;
            for(int j=0;j<t.size();j++){
                if(s[i]==t[j]){
                    f[i+1][j+1] = f[i][j+1]+f[i][j];
                }else{
                    f[i+1][j+1] = f[i][j+1];
                }
            }
            
        }
        
        return f[s.size()][t.size()];
    }
};
