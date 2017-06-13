/*
https://leetcode.com/problems/partition-equal-subset-sum/#/description
Given a non-empty array containing only positive integers, find if the array can be partitioned into two subsets such that the sum of elements in both subsets is equal.

Example 1:
Input: [1, 5, 11, 5]
Output: true
Explanation: The array can be partitioned as [1, 5, 5] and [11].

Example 2:
Input: [1, 2, 3, 5]
Output: false
Explanation: The array cannot be partitioned into equal sum subsets.
*/


bool canPartition(vector<int>& nums) {
    int len = nums.size();
    int sum =0;
    for(int i=0;i<len;i++){
        sum+=nums[i];
    }
    if(sum%2!=0)
        return false;
    int target = sum/2;
    //dp[i][j] means whether the specific sum j can be gotten from the first i numbers
    vector<vector<bool>> dp(len+1,vector<bool>(target+1,false));
    dp[0][0] = true;

    for(int i=1;i<=len;i++){
        for(int j=1;j<=target;j++){
            dp[i][j] = dp[i-1][j]; //first we can do somthing that do not choose i item
            if(nums[i-1]<=j)
                dp[i][j] = (dp[i][j] || dp[i-1][j-nums[i-1]]); //pick i item
        }
    }
    return dp[len][target];
}
