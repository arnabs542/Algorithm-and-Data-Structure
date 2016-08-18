//https://leetcode.com/problems/anagrams/
/*
Given an array of strings, group anagrams together.

For example, given: ["eat", "tea", "tan", "ate", "nat", "bat"], 
Return:

[
  ["ate", "eat","tea"],
  ["nat","tan"],
  ["bat"]
]
*/

class Solution {
public:
  vector<vector<string>> groupAnagrams(vector<string>& strs) {
      vector<vector<string>> ret;
      map<string,vector<string>> m;
      for(int i=0;i<strs.size();i++){
          string cur = strs[i];
          sort(cur.begin(),cur.end());
          m[cur].push_back(strs[i]);
      }
      for(auto i:m){
          vector<string> one;
          one = i.second;
          ret.push_back(one);
      }
      return ret;
  }
};
