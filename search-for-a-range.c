//https://leetcode.com/problems/search-for-a-range/
/*
Given a sorted array of integers, find the starting and ending position of a given target value.
Your algorithm's runtime complexity must be in the order of O(log n).
If the target is not found in the array, return [-1, -1].
For example,
Given [5, 7, 7, 8, 8, 10] and target value 8,
return [3, 4].
*/

//BST

class Solution {
public:
  vector<int> searchRange(vector<int>& nums, int target) {
      int len=nums.size();
      vector<int> ret;
      int start = -1;
      int end = -1;
      
      int l=0;
      int r= len-1;
      bool found = false;
      
      while(l<=r){
          int mid=l+(r-l)/2;
          if(nums[mid]>target){
              r = mid-1;
          }else if(nums[mid]<target){
              l = mid+1;
          }else if(nums[mid]==target){
              found = true;
              start = mid;
              end = mid;
              break;
          }
      }
      
      if(found){
          while(nums[start]==target && start>=0)
              start--;
          while(nums[end]==target && end<len)
              end ++;
          start++;
          end--;
      }
      
      ret.push_back(start);
      ret.push_back(end);
      
      return ret;
  }
};
