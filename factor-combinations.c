//https://leetcode.com/problems/factor-combinations/
/*
Numbers can be regarded as product of its factors. For example,

8 = 2 x 2 x 2;
  = 2 x 4.
Write a function that takes an integer n and return all possible combinations of its factors.

Note: 
You may assume that n is always positive.
Factors should be greater than 1 and less than n.
Examples: 
input: 1
output: 
[]
input: 37
output: 
[]
input: 12
output:
[
  [2, 6],
  [2, 2, 3],
  [3, 4]
]
input: 32
output:
[
  [2, 16],
  [2, 2, 8],
  [2, 2, 2, 4],
  [2, 2, 2, 2, 2],
  [2, 4, 4],
  [4, 8]
]
*/

class Solution {
public:
  vector<vector<int>> getFactors(int n) {
      vector<vector<int>> ret;
      vector<int> one;
      help(ret,one,n,2);
      return ret;

  }
  
  void help(vector<vector<int>> &ret, vector<int> &one, int n,int start){
      if(n==1){
          if(one.size()>1)//filter out dupicate and one=[n]
              ret.push_back(one);
          return;
      }
      
      //everytime calculate remain after divide, start is used so that we do not need to count back(smaller) number
      //using this start method, we can avoid dupicate: such as [2,6] and [6,2] since item picks should be larger than
      //start
      for(int i=start;i<=n;i++){
          if(n%i==0){
              one.push_back(i);
              help(ret,one,n/i,i);
              one.pop_back();
          }
      }        
  }
};
