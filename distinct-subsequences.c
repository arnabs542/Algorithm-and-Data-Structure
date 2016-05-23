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
