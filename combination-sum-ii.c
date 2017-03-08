//https://leetcode.com/problems/combination-sum-ii/
/*
Given a collection of candidate numbers (C) and a target number (T), find all unique combinations in C 
where the candidate numbers sums to T.
Each number in C may only be used once in the combination.

Note:
All numbers (including target) will be positive integers.
The solution set must not contain duplicate combinations.
For example, given candidate set [10, 1, 2, 7, 6, 1, 5] and target 8, 
A solution set is: 
[
  [1, 7],
  [1, 2, 5],
  [2, 6],
  [1, 1, 6]
]
*/

class Solution {
public:
  vector<vector<int>> combinationSum2(vector<int>& candidates, int target) {
      vector<vector<int>> ret;
      vector<int> r;
      if(candidates.empty())
          return ret;
      
      sort(candidates.begin(),candidates.end());
      help(candidates,target,0, candidates.size(),r,ret);
      
      return ret;
      
  }
  
  void help(vector<int>& candidates, int target, int start,int len, vector<int>& r, vector<vector<int>>& ret){
      if(target <0)
          return;
      
      if(target==0){
          ret.push_back(r);
          return;
      }
      
      for(int i=start;i<len;i++){
          /*if start a new check, do not ignore, otherwise can skip 
          suppose [10,1,2,7,6,1,5] ->sorted [1,1,2,5,6,7,10]
          so if we checked the first item as 1, [1,1,6];[1,2,5];[1,7]
          we do not need to check 1 for the second item in [1,1,2,5,6,7,10] again
          */
          if(i>start && candidates[i]==candidates[i-1])
              continue;
          if(candidates[i]<=target){
              r.push_back(candidates[i]);
              help(candidates,target-candidates[i],i+1,len,r,ret);
              r.pop_back();
          }else{//as vector is sorted, so if cureent single digit is larger than sum, skip all checks
              break;
          }
      }
      
      
  }
};
