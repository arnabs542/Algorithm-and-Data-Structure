//https://leetcode.com/problems/permutations-ii/
/*
 Given a collection of numbers that might contain duplicates, return all possible unique permutations.

For example,
[1,1,2] have the following unique permutations:
[
  [1,1,2],
  [1,2,1],
  [2,1,1]
]
*/
class Solution {
public:
  vector<vector<int>> permuteUnique(vector<int>& nums) {
      vector<vector<int>> ret;
      vector<int> cur;
      vector<bool> visit(nums.size(),false);
      std::sort(nums.begin(),nums.end());
      permute_helper(ret,cur,nums,visit,nums.size());
      
      return ret;
      
  }
  
  void permute_helper(vector<vector<int>>& ret, vector<int>& cur,vector<int>& nums, vector<bool> visit, int len){
      if(cur.size()==len){
          ret.push_back(cur);
          return;
      }
      int prev = INT_MAX;
      for(int i=0;i<len;i++){
          if(visit[i]==false && nums[i]!=prev){
              cur.push_back(nums[i]);
              visit[i]=true;
              prev = nums[i];
              permute_helper(ret,cur,nums,visit,len);
              cur.pop_back();
              visit[i]=false;
          }
      }
  }
};
