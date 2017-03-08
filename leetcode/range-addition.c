//https://leetcode.com/problems/range-addition/
/*
Assume you have an array of length n initialized with all 0's and are given k update operations.
Each operation is represented as a triplet: [startIndex, endIndex, inc] which increments each element of subarray A[startIndex ... endIndex] (startIndex and endIndex inclusive) with inc.
Return the modified array after all k operations were executed.

Example:
Given:

  length = 5,
  updates = [
      [1,  3,  2],
      [2,  4,  3],
      [0,  2, -2]
  ]

Output:
    [-2, 0, 3, 5, 3]
Explanation:

Initial state:
[ 0, 0, 0, 0, 0 ]
After applying operation [1, 3, 2]:
[ 0, 2, 2, 2, 0 ]
After applying operation [2, 4, 3]:
[ 0, 2, 5, 5, 3 ]
After applying operation [0, 2, -2]:
[-2, 0, 3, 5, 3 ]
*/

class Solution {
public:
  vector<int> getModifiedArray(int length, vector<vector<int>>& updates) {
/*
Put inc at startIndex allows the inc to be carried to the next index starting from startIndex when we do the sum accumulation.
Put -inc at endIndex + 1 simply means cancel out the previous carry from the next index of the endIndex, because the previous carry should not be counted beyond endIndex.
//refer 303. Range Sum Query - Immutable:

*/ 
    vector<int> ret(length+1,0);
    for(int i=0;i<updates.size();i++){
        int start = updates[i][0]; 
        int end = updates[i][1];
        int value = updates[i][2];
        ret[start] += value;
        ret[end+1]-=value;

    }
    
    for(int i=1;i<length;i++){
        ret[i]+=ret[i-1];
    }
    ret.pop_back();
    return ret;
  }
};
