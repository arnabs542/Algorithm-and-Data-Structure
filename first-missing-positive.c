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

//method 2: put the value to its index
int firstMissingPositive(vector<int>& nums) {
/*
ideally we should have vector as 1,2,3,...n. so nums[i-1]=i

Just go through the array sequentially and for every index write the value at the index to the index specified by value, 
recursively placing any value at that location to its place and throwing away values > N. 
Then go again through the array looking for the spot where value doesn't match the index - that's the smallest value not in the array. 
*/
    int len = nums.size();
    int ret = 0;
    for(int i=0;i<len;i++){
        int target = nums[i];
        //recursively placing any value at that location to its place and throwing away values > N
        while(target>0 && target<=len && target!=nums[target-1]){ //index starts from 0, so target-1 is real index
            swap(target,nums[target-1]);
        }
    }

    for(int i=0;i<len;i++){
        if(nums[i]!=i+1){
            ret = i+1;
            return ret;
        }
    }
return len+1;

}
