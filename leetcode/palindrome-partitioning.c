//https://leetcode.com/problems/palindrome-partitioning/
/*
Given a string s, partition s such that every substring of the partition is a palindrome.
Return all possible palindrome partitioning of s.

For example, given s = "aab",
Return
[
  ["aa","b"],
  ["a","a","b"]
]
*/

class Solution {
public:
  vector<vector<string>> partition(string s) {
      vector<vector<string>> ret;
      vector<string> one;
      
      help(ret,one,s,0);
      
      return ret;
  }
  
  void help(vector<vector<string>> &ret, vector<string> &one, string &s, int start){
      if(start==s.size()){
          ret.push_back(one);
          return;
      }
      //for loop counts all substr with same start pos, with increasing size
      //every recursive increase start by one
      for(int i=start;i<s.size();i++){
          string cur = s.substr(start,i-start+1);
          if(ispalindrome(cur)){
              one.push_back(cur);
              help(ret,one,s,i+1);
              one.pop_back();
          }
      }
  }
  
  bool ispalindrome(string in){
      int len = in.size();
      int start = 0;
      int end = len-1;
      while(start<end){
          if(in[start]!=in[end]){
              return false;
          }
          start++;
          end--;
      }
      return true;
  }
};
