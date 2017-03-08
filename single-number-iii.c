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

//same as here
class Solution {
public:
    int singleNumber(vector<int>& nums) {
        int a=0;
        int b=0;
        //we need to implement a three-time counter(base 3) that if a bit appears three time ,it will be zero.
        //#curent  income  ouput
        //# ab      c/c       ab/ab
        //# 00      1/0       01/00
        //# 01      1/0       10/01
        //# 10      1/0       00/10
        // c is 1 for 3 times, ab counts back to 00.
        for(int c:nums){
            int ta=(~a&b&c)|(a&~b&~c);
            b=(~a&~b&c)|(~a&b&~c);
            a=ta;
        }
        //we need find the number that is 01,10 => 1, 00 => 0.
        return a|b;
    }
};
