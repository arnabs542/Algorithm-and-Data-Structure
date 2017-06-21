/*
https://leetcode.com/problems/move-zeroes/#/description

Given an array nums, write a function to move all 0's to the end of it while maintaining the relative order of the non-zero elements.
For example, given nums = [0, 1, 0, 3, 12], after calling your function, nums should be [1, 3, 12, 0, 0].

Note:
You must do this in-place without making a copy of the array.
Minimize the total number of operations.
*/

void moveZeroes(vector<int>& nums) {
    int len = nums.size();
    int next = 0;
    for(int i=0;i<len;i++){
        if(nums[i]==0){
            next = i+1;
            while(next<len && nums[next]==0)
                next++;
            if(next!=len)
                swap(nums[i],nums[next]);
        }
    }
}

//method 2:
void moveZeroes(vector<int>& nums) {
    int next = 0;
    // move all the nonzero elements advance
    for (int i=0; i<nums.size(); i++) {
        if (nums[i] != 0) {
            nums[next] = nums[i];
            next++;
        }
    }
    while(next<nums.size()) {
        nums[next] = 0;
        next++;
    }
}
