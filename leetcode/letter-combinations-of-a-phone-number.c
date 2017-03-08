//https://leetcode.com/problems/letter-combinations-of-a-phone-number/
/*
Given a digit string, return all possible letter combinations that the number could represent.

A mapping of digit to letters (just like on the telephone buttons) is given below.
Input:Digit string "23"
Output: ["ad", "ae", "af", "bd", "be", "bf", "cd", "ce", "cf"].
*/

class Solution {
private:
  vector<string> dic;
public:
  vector<string> letterCombinations(string digits) {
      vector<string> ret;
      /* for this question, we need to create a look-up dictionary */
     
      if(digits.empty())
          return ret;
      string one_res;
      dic.push_back(" ");
      dic.push_back(" ");
      dic.push_back("abc");  //index 2
      dic.push_back("def");
      dic.push_back("ghi");
      dic.push_back("jkl");
      dic.push_back("mno");
      dic.push_back("pqrs");
      dic.push_back("tuv");
      dic.push_back("wxyz");
      
      int len = digits.size();

      help(ret,one_res,digits,0);
      return ret;        
  }
  
  void help(vector<string> &ret, string one_res, string& digits,int idx){
      if(idx==digits.size()){
          ret.push_back(one_res);
          return;
      }
      //DO not over counts.
      string letter = dic[digits[idx]-'0'];
      for(int j=0;j<letter.size();j++){
          help(ret,one_res+letter[j],digits,idx+1);
      }

  }
};
