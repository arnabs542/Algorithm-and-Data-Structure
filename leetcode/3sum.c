//https://leetcode.com/problems/3sum/
/*
Given an array S of n integers, are there elements a, b, c in S such that a + b + c = 0? Find all unique triplets in the array which gives the sum of zero.
Note: The solution set must not contain duplicate triplets.

For example, given array S = [-1, 0, 1, 2, -1, -4],
A solution set is:
[
  [-1, 0, 1],
  [-1, -1, 2]
]
*/
class Solution {
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        sort(nums.begin(),nums.end());
        vector<vector<int>> ret;
        for(int i=0;i<nums.size();i++){
            int target = -nums[i];
            int start = i+1;
            int end = nums.size()-1;
            while(start<end){
                if(nums[start]+nums[end]>target){
                    end--;
                }else if(nums[start]+nums[end]<target){
                    start++;
                }else{
                    vector<int> one;
                    one.push_back(nums[i]);
                    one.push_back(nums[start]);
                    one.push_back(nums[end]);
                    ret.push_back(one);
                    int begin = nums[start];
                    int finish = nums[end];
    
                    while(start<end && nums[start]==begin)
                        start++;
                    while(start<end && nums[end]==finish)
                        end--;
                }
            }
                    // Processing duplicates of Number 1
            while (i + 1 < nums.size() && nums[i + 1] == nums[i]) 
                i++;
        }
        
        return ret;
    }
};
