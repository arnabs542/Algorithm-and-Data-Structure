https://leetcode.com/problems/perfect-squares/
/*
Given a positive integer n, find the least number of perfect square numbers (for example, 1, 4, 9, 16, ...) which sum to n.
For example, given n = 12, return 3 because 12 = 4 + 4 + 4; given n = 13, return 2 because 13 = 4 + 9.
*/

#include <math.h>
class Solution {
public:
    int numSquares(int n) {
        //using DP:
        /*
        num[i] is least number of perfect square numbers for i,
        minsquare = min of nums[i]
        nums[i] = min(nums[i-j*j] + 1, nums[i]) 
          */
          
        vector<int> nums(n+1,n); //init: any number can be composed of all "1"
        nums[0] = 0;
        int min_len = 0;
        int minsquare = n;
        int size = sqrt(n);
        
        for(int i=1;i<=n;i++){
            for(int j=1;j<=size;j++){
                if(i>=j*j){
                    nums[i] = min(nums[i-j*j]+1,nums[i]);
                }else{
                    break;
                }
            }
        }
        
        return nums[n];
    }
};
