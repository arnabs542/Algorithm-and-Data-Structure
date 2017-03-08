//https://leetcode.com/problems/subsets/
/*
 Given a set of distinct integers, nums, return all possible subsets.

Note: The solution set must not contain duplicate subsets.

For example,
If nums = [1,2,3], a solution is:
[
  [3],
  [1],
  [2],
  [1,2,3],
  [1,3],
  [2,3],
  [1,2],
  []
]
*/
class Solution {
public:
  vector<vector<int>> subsets(vector<int>& nums) {
      vector<vector<int>> ret;
      vector<int> one;
      ret.push_back(one); //push_back the empty set;
      help(ret,one,nums,0);
      return ret;
  }
  
  void help(vector<vector<int>> &ret, vector<int> &one, vector<int>& nums, int start ){
      
      for(int i=start;i<nums.size();i++){
          one.push_back(nums[i]);
          ret.push_back(one);
          help(ret,one,nums,i+1);
          one.pop_back();
      }
      
  }
};
