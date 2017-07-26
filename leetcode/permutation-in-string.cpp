//https://leetcode.com/problems/permutation-in-string/#/description
/*
Given two strings s1 and s2, write a function to return true if s2 contains the permutation of s1. In other words, one of the first string's permutations is the substring of the second string.

Example 1:
Input:s1 = "ab" s2 = "eidbaooo"
Output:True
Explanation: s2 contains one permutation of s1 ("ba").
Example 2:
Input:s1= "ab" s2 = "eidboaoo"
Output: False
*/

bool checkInclusion(string s1, string s2) {
    if(s1.size()==0)
        return true;
    vector<int> m(128,0);
    int l = 0;
    int r = 0;
    for(int i=0;i<s1.size();i++){
        m[s1[i]]--;  //s2 own s1
    }
    for(int l=0,r=0;r<s2.size();r++){
        if(++m[s2[r]]>0){//s2 has more than own s1 or s2 current char is not in s1
            while(--m[s2[l++]]!=0){
                //move left, until m[s2[r]] is no longer larger than 0(==0)
            }
        }
        if(r-l+1==s1.size())  {
            return true;
        }
    }

    return false;
}
