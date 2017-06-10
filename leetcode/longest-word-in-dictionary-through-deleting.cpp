//https://leetcode.com/problems/longest-word-in-dictionary-through-deleting/#/description
/*
Given a string and a string dictionary, find the longest string in the dictionary that can be formed by deleting some characters of the given string. If there are more than one possible results, return the longest word with the smallest lexicographical order. If there is no possible result, return the empty string.

Example 1:
Input:
s = "abpcplea", d = ["ale","apple","monkey","plea"]

Output:
"apple"
*/

string findLongestWord(string s, vector<string>& d) {
    string ret;
    for(int i=0;i<d.size();i++){
        int j = 0; //index for s.
        int k = 0; //index for d[i]
        for(j=0;j<s.size() && k<d[i].size();j++){
            if(s[j]==d[i][k])  //matches, we can move k, otherwise only move j
                k++;
        }
        if(k==d[i].size()){//whole string in d[i] matches
            if(k>ret.size() || k==ret.size() && ret>d[i])
            //either new one is longer or equal size but lexicographical smaller
                ret = d[i];
        }
    }
    return ret;
}
