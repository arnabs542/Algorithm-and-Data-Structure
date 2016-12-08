//https://leetcode.com/problems/first-missing-positive/
/*
Given an unsorted integer array, find the first missing positive integer.
For example,
Given [1,2,0] return 3,
and [3,4,-1,1] return 2.

Your algorithm should run in O(n) time and uses constant space.
*/
//Method 1: Use bitmap
class Solution {
public:
    int firstMissingPositive(vector<int>& nums) {
        int size = nums.size();
        
        if(size == 0)
            return 1;
        int ret;
        int len = size/32;
        
        int bin = 0;
        int shift = 0;
        vector<int> bitvec(len+1,0);
        for(int i=0;i<size;i++){
            if(nums[i]>0){
                bin = (nums[i]/32);
                shift = (nums[i]%32);
                bitvec[bin] |= 0x1<<shift;
            }
            
        }
        
        for(int j=0;j<=len;j++){
            if(bitvec[j]!=0xFFFFFFFF){
                for(int k=0;k<32;k++){
                    if(j==0 && k==0)
                        continue;
                    if((bitvec[j]&(0x1<<k))==0){
                        ret = k+32*j;
                        goto done;
                    }
                }
            }
        }
done:
        return ret;
    }
};
