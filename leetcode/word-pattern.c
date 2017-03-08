//https://leetcode.com/problems/word-pattern/
/*
Given a pattern and a string str, find if str follows the same pattern.
Here follow means a full match, such that there is a bijection between a letter in pattern and a non-empty word in str.

Examples:

    pattern = "abba", str = "dog cat cat dog" should return true.
    pattern = "abba", str = "dog cat cat fish" should return false.
    pattern = "aaaa", str = "dog cat cat dog" should return false.
    pattern = "abba", str = "dog dog dog dog" should return false.
Notes:
You may assume pattern contains only lowercase letters, and str contains lowercase letters separated by a single space. 
*/
class Solution {
public:
  bool wordPattern(string pattern, string str) {
      unordered_map<char,string> m1; 
      unordered_map<string,char> m2;
      int start = 0;
      int i;
      for(i=0;i<pattern.size();i++){
          if(start>=str.size()) //search to the end of str
              break;
          
          string sub = find_substr(str,start);
          
          if(m1.find(pattern[i])!=m1.end() && m1[pattern[i]]!=sub)
              return false;
          if(m2.find(sub)!=m2.end() && m2[sub]!=pattern[i])
              return false;

          m1[pattern[i]] = sub;
          m2[sub]= pattern[i];

          start +=sub.size() + 1;
      }
      //check either pattern has more or str has more, both return false
      if(i<pattern.size() || start<str.size())
          return false;
      return true;
  }
  
  string find_substr(string in, int pos){
      int len = 0;
      int start = pos;
      //make sure we have check end of string
      while(in[pos]!='\0' && in[pos]!=' '){
          pos++;
          len++;
      }
      
      return in.substr(start,len);
  }
};
