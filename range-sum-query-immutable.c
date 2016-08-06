//https://leetcode.com/problems/range-sum-query-immutable/
/*
Given an integer array nums, find the sum of the elements between indices i and j (i ≤ j), inclusive.

Example:
Given nums = [-2, 0, 3, -5, 2, -1]

sumRange(0, 2) -> 1
sumRange(2, 5) -> -1
sumRange(0, 5) -> -3
*/
class NumArray {
public:
  vector<int> addup;
  NumArray(vector<int> &nums) {
      int len = nums.size();
      int sum= 0;
      addup.push_back(sum);
      for(int i=0;i<len;i++){
          sum = sum+nums[i];
          addup.push_back(sum);
      }
  }

  int sumRange(int i, int j) {
      return addup[j+1]-addup[i];
  }
};
