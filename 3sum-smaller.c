//https://leetcode.com/problems/3sum-smaller/
/*
Given an array of n integers nums and a target, find the number of index triplets i, j, k with 0 <= i < j < k < n that satisfy the condition nums[i] + nums[j] + nums[k] < target.
For example, given nums = [-2, 0, 1, 3], and target = 2.

Return 2. Because there are two triplets which sums are less than 2:
[-2, 0, 1]
[-2, 0, 3]
*/
//method 1: use same as 3sum to count all
class Solution {
public:
    int threeSumSmaller(vector<int>& nums, int target) {
        sort(nums.begin(),nums.end());
        int ret = 0;
        for(int i=0;i<nums.size();i++){
            int new_target = target-nums[i];
            int start = i+1;
            int end = nums.size()-1;
            while(start<end){
                if(nums[start]+nums[end]>=new_target){
                    end--;
                }else{
                    //if largest nums[end]+nums[start]+nums[i] smaller than target, 
                    //then all end index > start will have same value
                    int tmp_end = end;
                    while(start<tmp_end){
                        ret++;
                        tmp_end--;
                    }
                    start++;
                    
                }
            }
        }
        
        return ret;        
    }
};

//method 2: since we know triplet in certain range should work
class Solution {
public:
    int threeSumSmaller(vector<int>& nums, int target) {
        if(nums.size()<3)
            return 0;
        sort(nums.begin(),nums.end());
        int ret = 0;
        for(int i=0;i<nums.size()-2;i++){
            int start=i+1;
            int end=nums.size()-1;
            while(start<end){
                if(nums[i]+nums[start]+nums[end]<target){
                    //all in this range will serve
                    ret += end-start;
                    start++;
                }else{
                    end--;
                }
            }
        }
        
        return ret;        
    }
};
