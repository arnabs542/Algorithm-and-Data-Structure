//https://leetcode.com/problems/single-number-iii/
/*
Given an array of numbers nums, in which exactly two elements appear only once and all the other elements appear exactly twice. 
Find the two elements that appear only once.
For example:
Given nums = [1, 2, 1, 3, 2, 5], return [3, 5].
Note:
    The order of the result is not important. So in the above example, [5, 3] is also correct.
    Your algorithm should run in linear runtime complexity. Could you implement it using only constant space complexity?
*/
class Solution {
public:
    vector<int> singleNumber(vector<int>& nums) {
        /*
    1.assume that A and B are the two elements which we want to find;
    2.use XOR for all elements,the result is : r = A^B,we just need to distinguish A from B next step;
    3.if we can find a bit '1' in r,then the bit in corresponding position in A and B must be different.We can use {last = r & (~(r-1))} to get the last bit 1 int r;
    4.we use last to divide all numbers into two groups,then A and B must fall into the two distrinct groups.XOR elements in eash group,get the A and B.
        */
        vector<int> ret(2, 0);
        int x = 0;
        //XOR
        for(int i=0;i<nums.size();i++){
            x^=nums[i];
        }
        int last = x&(~(x-1));
        int a=0;
        int b=0;
        for (int i=0; i<nums.size(); ++i)
        {
            if ((last & nums[i]) != 0)
                ret[0] ^= nums[i];
            else
                ret[1] ^= nums[i];
        }
        return ret;
    }
};
