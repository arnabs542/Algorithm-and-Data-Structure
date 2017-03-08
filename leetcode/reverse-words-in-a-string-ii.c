//https://leetcode.com/problems/reverse-words-in-a-string-ii/
/*
 Given an input string, reverse the string word by word. A word is defined as a sequence of non-space characters.
The input string does not contain leading or trailing spaces and the words are always separated by a single space.

For example,
Given s = "the sky is blue",
return "blue is sky the".
Could you do it in-place without allocating extra space? 
*/
//method 1:
class Solution {
public:
    void reverseWords(string &s) {
        if(s.length()<2)
            return;
        reverse_str(s,0,s.size()-1);
        int start = 0;
        int end =0;
        while(start<s.size()){
            if(isspace(s[end]) || s[end]=='\0'){
                reverse_str(s,start,end-1);
                start = end + 1;
            }
            end++;
        }
    }
    void reverse_str(string &s, int start, int end){
        char tmp;
        while(start<end){
            tmp=s[start];
            s[start]=s[end];
            s[end]=tmp;
            start++;
            end--;
        }
    }
};

//method 2: use the default reverse function
class Solution {
public:
    void reverseWords(string &s) {
        reverse(s.begin(), s.end());
        int n = s.length(), start = 0, end = 0;
        while (start < n) {
            while (end < n && !isspace(s[end])) 
                end++;
            reverse(s.begin() + start, s.begin() + end); 
            start = ++end;
        }
        
    }
};
