//https://leetcode.com/problems/missing-number/
/*
 Given an array containing n distinct numbers taken from 0, 1, 2, ..., n, find the one that is missing from the array.

For example,
Given nums = [0, 1, 3] return 2. 
*/

//method 1: XOR

//method2: if array is sorted
class Solution {
public:
    int missingNumber(vector<int>& nums) {
        sort(nums.begin(),nums.end());
        int l=0;
        int r=nums.size()-1;
        while(l<=r){
            int mid = l+(r-l)/2;
            if(nums[mid]>mid){
                r=mid-1;
            }else{
                l = mid+1;
            }
        }
        return l;
    }

};