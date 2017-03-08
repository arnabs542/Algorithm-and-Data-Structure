//https://leetcode.com/problems/wiggle-subsequence/
/*
A sequence of numbers is called a wiggle sequence if the differences between successive numbers strictly alternate between positive and negative. The first difference (if one exists) may be either positive or negative. A sequence with fewer than two elements is trivially a wiggle sequence.
For example, [1,7,4,9,2,5] is a wiggle sequence because the differences (6,-3,5,-7,3) are alternately positive and negative. In contrast, [1,4,7,2,5] and [1,7,4,5,5] are not wiggle sequences, the first because its first two differences are positive and the second because its last difference is zero.
Given a sequence of integers, return the length of the longest subsequence that is a wiggle sequence. A subsequence is obtained by deleting some number of elements (eventually, also zero) from the original sequence, leaving the remaining elements in their original order.

Examples:
Input: [1,7,4,9,2,5]
Output: 6
The entire sequence is a wiggle sequence.

Input: [1,17,5,10,13,15,10,5,16,8]
Output: 7
There are several subsequences that achieve this length. One is [1,17,10,13,10,16,8].

Input: [1,2,3,4,5,6,7,8,9]
Output: 2
*/

//method 1: 
//using two anchor points to records the wiggle nums.
class Solution {
public:
int wiggleMaxLength(vector<int>& nums) {
    int len = nums.size();
    if(len<=1)
        return len;
    vector<int> dp(len,0);
    dp[0] = 1;
    int last2 = nums[0];
    int last1;

    int i=1;
    while (i < len && nums[i] == nums[i-1]) {  // beginning eg 5, 5, 5, 1
  		dp[i] = 1;
  		i++;
  	}
    //going through all equals in begining, start to count
    dp[i] = 2;
    last1 = nums[i];
    i++;

    for(;i<len;i++){
        if((nums[i]>last1)&&(last1<last2) || (nums[i]<last1)&&(last1>last2)){
            dp[i] = dp[i-1] +1;
            last2 = last1;
            last1 = nums[i];
        }else{
            dp[i] = dp[i-1];
            last1 = nums[i]; //as it is keeping on increase or decrease, need to update anchor point
        }
    }
    
    return dp[len-1];
  }
};

//method 2: nice and clean, record up and down trend. greedy
class Solution {
public:
    int wiggleMaxLength(vector<int>& nums) {
        int len = nums.size();
        if(len<=1)
            return len;
        int up=1;//record last up trend num
        int down=1;
        for(int i=1;i<len;i++){
            if(nums[i]>nums[i-1])
                up = down +1;
            if(nums[i]<nums[i-1])
                down = up +1;
        }
        
        return max(up,down);

    }
};
