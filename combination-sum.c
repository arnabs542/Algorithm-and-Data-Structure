//https://leetcode.com/problems/combination-sum/
/*
 Given a set of candidate numbers (C) and a target number (T), find all unique combinations in C where the candidate numbers sums to T.
The same repeated number may be chosen from C unlimited number of times.

Note:
    All numbers (including target) will be positive integers.
    The solution set must not contain duplicate combinations.

For example, given candidate set [2, 3, 6, 7] and target 7,
A solution set is:

[
  [7],
  [2, 2, 3]
]
*/
class Solution {
public:
    vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
        vector<vector<int>> ret;
        vector<int> one;
        help(ret,one,candidates,target,0);
        
        return ret;
    }
    
    void help(vector<vector<int>> &ret, vector<int> &one, vector<int>& candidates, int target, int start){
        if(target==0){
            ret.push_back(one);
            return;
        }
        if(target<0)
            return;
        
        for(int i=start;i<candidates.size();i++){
            one.push_back(candidates[i]);
            help(ret,one,candidates,target-candidates[i],i);
            one.pop_back();
        }
        
    }
};
