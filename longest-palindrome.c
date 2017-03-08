//https://leetcode.com/problems/longest-palindrome/
/*
Given a string which consists of lowercase or uppercase letters, find the length of the longest palindromes that can be built with those letters.
This is case sensitive, for example "Aa" is not considered a palindrome here.

Note:
Assume the length of given string will not exceed 1,010.

Example:

Input:
"abccccdd"

Output:
7

Explanation:
One longest palindrome that can be built is "dccaccd", whose length is 7.
*/
class Solution {
public:
    int longestPalindrome(string s) {
        vector<int> c(256,0);
        for(int i=0;i<s.size();i++){
            c[s[i]]++;
        }
        int ret = 0;
        int odd = 0;
        for(auto j:c){
            if(j&1){
                odd++;
            }
        }
        //if there is odd, we can leave one odd char in middle
        return s.size()-odd+(odd > 0);
    }
};
