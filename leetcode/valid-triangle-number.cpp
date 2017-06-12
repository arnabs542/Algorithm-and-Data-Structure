//https://leetcode.com/problems/valid-triangle-number/
/*
Given an array consists of non-negative integers, your task is to count the number of triplets chosen from the array that can make triangles if we take them as side lengths of a triangle.

Example 1:
Input: [2,2,3,4]
Output: 3
Explanation:
Valid combinations are:
2,3,4 (using the first 2)
2,3,4 (using the second 2)
2,2,3
*/

int triangleNumber(vector<int>& nums) {
    //3 sum problem
    int len = nums.size();
    sort(nums.begin(),nums.end());
    int ret = 0;
    for(int i=2;i<len;i++){
        int l=0;
        int r=i-1;
        while(l<r){
            if(nums[l]+nums[r]>nums[i]){
                ret+=r-l;
                r--;
            }else
                l++;
        }
    }
    return ret;
}
