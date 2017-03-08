//https://leetcode.com/problems/strobogrammatic-number-ii/
/*
A strobogrammatic number is a number that looks the same when rotated 180 degrees (looked at upside down).
Find all strobogrammatic numbers that are of length = n.

For example,
Given n = 2, return ["11","69","88","96"].
*/
class Solution {
private:
  vector<int> dig;
  map<int,int> m;
public:
  vector<string> findStrobogrammatic(int n) {
      dig.push_back(0);
      dig.push_back(1);
      dig.push_back(6);
      dig.push_back(8);
      dig.push_back(9);
      m[6] = 9;
      m[9] = 6;
      m[8] = 8;
      m[1] = 1;
      m[0] = 0;
      vector<string> ret;
      string s = "";
      if(n==1){
          ret.push_back("0");
          ret.push_back("1");
          ret.push_back("8");
          return ret;
      }
      
      if(n%2==0){
          help(ret,s,n);
      }else if(n%2==1){
          help(ret,"0",n-1);
          help(ret,"1",n-1);
          help(ret,"8",n-1);
      }
      
      return ret;
  }
  
  void help(vector<string> &ret, string s, int n){
      if(n==0){
          if(s[0]!='0'){//filter out those with 0 as starting(and ending by rule)
              ret.push_back(s);
          }
          return;
      }
      for(int i=0;i<dig.size();i++){
          string start = to_string(dig[i]);
          string end = to_string(m[dig[i]]);
          help(ret,start+s+end,n-2);
      }
      return;
  }
};
