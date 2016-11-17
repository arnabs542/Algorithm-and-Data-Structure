//https://leetcode.com/problems/132-pattern/
/*
 Given a sequence of n integers a1, a2, ..., an, a 132 pattern is a subsequence ai, aj, ak such that i < j < k and ai < ak < aj. Design an algorithm that takes a list of n numbers as input and checks whether there is a 132 pattern in the list.

Note: n will be less than 15,000.
Example 1:

Input: [1, 2, 3, 4]
Output: False
Explanation: There is no 132 pattern in the sequence.

Example 2:
Input: [3, 1, 4, 2]
Output: True

Explanation: There is a 132 pattern in the sequence: [1, 4, 2].

Example 3:
Input: [-1, 3, 2, 0]
Output: True
Explanation: There are three 132 patterns in the sequence: [-1, 3, 2], [-1, 3, 0] and [-1, 2, 0].
*/
class Solution {
public:
    bool find132pattern(vector<int>& nums) {
        /*
        
    Have a stack, each time we store a new number, we first pop out all numbers that are smaller than that number. The numbers that are popped out becomes candidate for s3.
    We keep track of the maximum of such s3.
    Once we encounter any number smaller than s3, we know we found a valid sequence since s1 < s3 implies s1 < s2.

        */
        int s3=INT_MIN;
        stack<int> s; //for s3, top will be max s3 value;
        for(int i=nums.size()-1;i>=0;i--){
            if(nums[i]<s3)
                return true;
            else{
                while(!s.empty() && nums[i]>s.top()){
                    s3 = max(s3,s.top());
                    s.pop();
                }
            }
            s.push(nums[i]);
        }
        
        return false;
    }
};
