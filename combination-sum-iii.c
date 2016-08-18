//https://leetcode.com/problems/combination-sum-iii/
/*
Find all possible combinations of k numbers that add up to a number n, 
given that only numbers from 1 to 9 can be used and each combination should be a unique set of numbers.


Example 1:
Input: k = 3, n = 7
Output:
[[1,2,4]]

Example 2:
Input: k = 3, n = 9
Output:
[[1,2,6], [1,3,5], [2,3,4]]
*/
class Solution {
public:
  vector<vector<int>> combinationSum3(int k, int n) {
      vector<vector<int>> ret;
      vector<int> one;
      
      help(ret,one,1,n,k,0);
      return ret;
  }
  
  void help(vector<vector<int>> &ret, vector<int> one, int start, int target, int k, int cur){
      if(target==cur && k==0){
          ret.push_back(one);
          return;
      }
      if(cur<target){
          for(int i=start;i<=9;i++){
              //need to use push and pop, otherwise it will keep on pushing until last cur+i>target, may push too many
              //unnecesssary
              one.push_back(i);
              help(ret,one,i+1,target,k-1,cur+i);
              one.pop_back();
          }
      }
  }
};
