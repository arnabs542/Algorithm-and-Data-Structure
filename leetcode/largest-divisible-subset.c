//https://leetcode.com/problems/largest-divisible-subset/
/*
Given a set of distinct positive integers, 
find the largest subset such that every pair (Si, Sj) of elements in this subset satisfies: Si % Sj = 0 or Sj % Si = 0.
If there are multiple solutions, return any subset is fine.

Example 1:
nums: [1,2,3]
Result: [1,2] (of course, [1,3] will also be ok)

Example 2:
nums: [1,2,4,8]
Result: [1,2,4,8]
*/

class Solution {
public:
    vector<int> largestDivisibleSubset(vector<int>& nums) {
        /*
        first we can sort the nums.
        dp[i] is current max length of subset to satisfy requirements. 
        i indicates index of subset, 
        dp[i] = max(dp[j] + 1) if (nums[i]%dp[j]==0), 0<=j<i
        */
        vector<int> ret;
        int len = nums.size();
        if(len==0)
            return ret;
        
        std::sort(nums.begin(),nums.end());
        
        vector<int> dp(len,0);
        vector<int> former(len,0);
        
        int max_len =0;  //max len of subset
        int index;  //max value's index in subset
        
        for(int i=0;i<len;i++){
            for(int j=i;j>=0;j--){
                //since set is already divisible, if current number can divide max num in current set, it can divide all in that set
                if(nums[i]%nums[j]==0 && dp[i]<dp[j]+1){
                    dp[i] = dp[j]+1;
                    former[i] = j;  //point to former element index in subset
                }
            }
            if(dp[i]>max_len){
                max_len = dp[i];
                index = i;
            }
            
        }
        
        
        for(int i=0;i<max_len;i++){
            
            ret.insert(ret.begin(),nums[index]);
            index = former[index];
        }
        
        return ret;
    }
};
