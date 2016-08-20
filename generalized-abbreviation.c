//https://leetcode.com/problems/generalized-abbreviation/
/*
Write a function to generate the generalized abbreviations of a word.

Example:
Given word = "word", return the following list (order does not matter):
["word", "1ord", "w1rd", "wo1d", "wor1", "2rd", "w2d", "wo2", "1o1d", "1or1", "w1r1", "1o2", "2r1", "3d", "w3", "4"]
*/

class Solution {
public:
  vector<string> generateAbbreviations(string word) {
      /*
      this is a combination problem:
      for each char in word, either we keep it or abbreviate it
      */
      vector<string> ret;
      string one = "";
      help(ret,word,0,one,0);
      return ret;
  }
  
  /*
  current char can be either keep itself, or abbreviated by len. 
  //pos is the current char's position in word. len is abbrevaite len
  */
  void help(vector<string> &ret, string& word, int pos, string cur, int len){
      if(pos==word.size()){
          if(len>0){
              cur+=to_string(len);
          }
          ret.push_back(cur);
          return;
      }
      
      help(ret,word,pos+1,cur,len+1);  //current char is abbreviated.
      //current char is kept. get the len for last abbreviation, reset len to 0 since abbreviation is done 
      help(ret,word,pos+1,cur+(len>0?to_string(len):"")+word[pos],0);
  }
};
