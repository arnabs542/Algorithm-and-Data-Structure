//https://leetcode.com/problems/wiggle-sort/
/*
Given an unsorted array nums, reorder it in-place such that nums[0] <= nums[1] >= nums[2] <= nums[3]....
For example, given nums = [3, 5, 2, 1, 6, 4], one possible answer is [1, 6, 2, 5, 3, 4].
*/

class Solution {
public:
    void wiggleSort(vector<int>& nums) {
        //odd position smaller than even one
        int len = nums.size();
        
        for(int i=0;i<len-1;i++){
            if(i%2==1){
                //odd position
                if(nums[i]<nums[i+1]){
                    swap(nums[i],nums[i+1]);
                }
            }else{
                if(nums[i]>nums[i+1]){
                    swap(nums[i],nums[i+1]);
                }
            }
        }
    }
};
