//https://leetcode.com/problems/combination-sum-iv/
/*
Given an integer array with all positive numbers and no duplicates, find the number of possible combinations that add up to a positive integer target.

Example:

nums = [1, 2, 3]
target = 4

The possible combination ways are:
(1, 1, 1, 1)
(1, 1, 2)
(1, 2, 1)
(1, 3)
(2, 1, 1)
(2, 2)
(3, 1)

Note that different sequences are counted as different combinations.

Therefore the output is 7.
*/

//Some obvious solution will be recursive and simple DP, but will result in time out in implementation
class Solution {
public:
    int combinationSum4(vector<int>& nums, int target) {
        /*
        dp:
        dp[i] is total number of combinations that sums up to i
        dp[i] = sum of dp[j] if i-j is in nums
        */
        
        vector<int>dp(target+1,0);
        for(int i=0;i<nums.size();i++){
            if(nums[i]<=target)
                dp[nums[i]] = 1;
        }
        
        for(int i=1;i<=target;i++){
            for(int j=1;j<i;j++){
                if(std::find(nums.begin(), nums.end(), i-j) != nums.end()){
                    dp[i]+=dp[j];
                }
            }
        }
        
        return dp[target];
    }
};

class Solution {
public:
    int combinationSum4(vector<int>& nums, int target) {
        if (target == 0) {
            return 1;
        }
        std:sort(nums.begin(),nums.end());
        int res = 0;
        for (int i = 0; i < nums.size(); i++) {
            if (target >=nums[i]) {
                res += combinationSum4(nums, target - nums[i]);
            }
        }
        return res;
    }
};


//Correct solution
class Solution {
public:
    int combinationSum4(vector<int>& nums, int target) {
        /*
        dp:
        dp[i] is total number of combinations that sums up to i
        dp[i] = sum of dp[j] if i-j is in nums
        */
        
        vector<int>dp(target+1,0);
        std::sort(nums.begin(),nums.end());
        for(int i=1;i<=target;i++){
            for(int j=0;j<nums.size();j++){
                if(nums[j]>i)
                    break;
                else if(nums[j]==i)
                    dp[i]+=1;
                else
                    dp[i] +=dp[i-nums[j]];
            }
        }
        
        return dp[target];
    }
};
