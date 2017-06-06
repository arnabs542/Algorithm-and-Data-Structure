//https://leetcode.com/problems/subarray-sum-equals-k/#/description

Given an array of integers and an integer k, you need to find the total number of continuous subarrays whose sum equals to k.

Example 1:
Input:nums = [1,1,1], k = 2
Output: 2

class Solution {
public:
    int subarraySum(vector<int>& nums, int k) {
        //notice if the array is all positive, it is different
        //easy way is to do O(N^2), calculate all subarry starting from 0->len-1, to end
        //if we want to do O(N), need a map to record
        int len = nums.size();
        int sum = 0;
        int ret = 0;
        map<int,int> m; //key is sum value, val is how many times it appears
        m[0] = 1;
        for(int i=0;i<len;i++){
            sum+=nums[i];
            if(m.find(sum-k)!=m.end())
                ret+=m[sum-k];
            m[sum]++;
        }
        return ret;
    }
};
