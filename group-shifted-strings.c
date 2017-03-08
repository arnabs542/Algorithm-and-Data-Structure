//https://leetcode.com/problems/group-shifted-strings/
/*
Given a string, we can "shift" each of its letter to its successive letter, for example: "abc" -> "bcd". We can keep "shifting" which forms the sequence:
"abc" -> "bcd" -> ... -> "xyz"
Given a list of strings which contains only lowercase alphabets, group all strings that belong to the same shifting sequence.

For example, given: ["abc", "bcd", "acef", "xyz", "az", "ba", "a", "z"], 
A solution is:

[
  ["abc","bcd","xyz"],
  ["az","ba"],
  ["acef"],
  ["a","z"]
]
*/
class Solution {
public:
  vector<vector<string>> groupStrings(vector<string>& strings) {
      //encode its shifting feature as "s[1] - s[0], s[2] - s[1], ..., s[n - 1] - s[n - 2],".
      map<string,vector<string>> m;
      vector<vector<string>> ret;
      for(int i=0;i<strings.size();i++){
          m[encode_string(strings[i])].push_back(strings[i]);
      }
      for(auto i:m){
          vector<string> one = i.second;
          sort(one.begin(),one.end());
          ret.push_back(one);
      }
      sort(ret.begin(),ret.end());
      return ret;
  }
  
  string encode_string(string s){
      int len = s.size();
      string ret = "";
      for(int i=1;i<len;i++){
          int diff = s[i]-s[i-1];
          if(diff<0)
              diff = diff + 26;
          ret += to_string(diff);
      }
      //why we need to add len, to avoid test case like ["aa","bb","b"]
      return ret;
  }
};
