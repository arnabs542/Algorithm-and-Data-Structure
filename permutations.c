//https://leetcode.com/problems/permutations/
/*
 Given a collection of distinct numbers, return all possible permutations.

For example,
[1,2,3] have the following permutations:

[
  [1,2,3],
  [1,3,2],
  [2,1,3],
  [2,3,1],
  [3,1,2],
  [3,2,1]
]
*/
class Solution {
public:
  vector<vector<int>> permute(vector<int>& nums) {
      vector<vector<int>> ret;
      vector<int> cur;
      vector<bool> visit(nums.size(),false);
      
      permute_helper(ret,cur,nums,visit,nums.size());
      
      return ret;
      
  }
  
  void permute_helper(vector<vector<int>>& ret, vector<int>& cur,vector<int>& nums, vector<bool> visit, int len){
      if(cur.size()==len){
          ret.push_back(cur);
          return;
      }
      
      for(int i=0;i<len;i++){
          if(visit[i]==false){
              cur.push_back(nums[i]);
              visit[i]=true;
              permute_helper(ret,cur,nums,visit,len);
              cur.pop_back();
              visit[i]=false;
          }
      }
  }
};
