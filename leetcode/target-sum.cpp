/*
https://leetcode.com/problems/target-sum/#/description

You are given a list of non-negative integers, a1, a2, ..., an, and a target, S. Now you have 2 symbols + and -. For each integer, you should choose one from + and - as its new symbol.

Find out how many ways to assign symbols to make sum of integers equal to target S.

Example 1:
Input: nums is [1, 1, 1, 1, 1], S is 3.
Output: 5
Explanation:

-1+1+1+1+1 = 3
+1-1+1+1+1 = 3
+1+1-1+1+1 = 3
+1+1+1-1+1 = 3
+1+1+1+1-1 = 3

There are 5 ways to assign symbols to make the sum of nums be target 3.
*/

int findTargetSumWays(vector<int>& nums, int S) {
    int cnt=0;
    help(nums,S,0,0,cnt);
    return cnt;
}

void help(vector<int>& nums, int S, int index,int sum, int & res){
    if(index==nums.size()){
        if(sum==S)
            res++;
        return;
    }
    int cur=nums[index];
    help(nums,S,index+1,sum+cur,res);  //assign '+' to cur
    help(nums,S,index+1,sum-cur,res);  //assign '-' to cur
}
