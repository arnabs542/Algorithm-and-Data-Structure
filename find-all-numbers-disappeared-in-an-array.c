//https://leetcode.com/problems/find-all-numbers-disappeared-in-an-array/
/*
Given an array of integers where 1 ≤ a[i] ≤ n (n = size of array), some elements appear twice and others appear once.
Find all the elements of [1, n] inclusive that do not appear in this array.
Could you do it without extra space and in O(n) runtime? You may assume the returned list does not count as extra space.

Example:

Input:
[4,3,2,7,8,2,3,1]
Output:
[5,6]
*/
//method 1: on the fly change
class Solution {
public:
    vector<int> findDisappearedNumbers(vector<int>& nums) {
        /*
        First iteration to negate values at position whose equal to values appear in array. Second iteration to collect all position whose value is positive, which are the missing values. Complexity is O(n) Time and O(1) space
        */
        int n = nums.size();
        vector<int> ret;
        for(int i=0;i<n;i++){
            int index = abs(nums[i])-1;  //since numbers are 1->n, but index is 0->n-1
            if(nums[index]>0)
                nums[index] = -nums[index];
        }
        
        for(int i=0;i<n;i++){
            if(nums[i]>0)
                ret.push_back(i+1);
        }
        
        return ret;
    }
};

//method 2: bit vector
class Solution {
public:
    vector<int> findDisappearedNumbers(vector<int>& nums) {
        int n=nums.size();
        //numbers from 1->n;
        int len = (n/32)+1;
        vector<int> ret;
        vector<int> bitv(len,0);
        //create bitmap
        for(int i=0;i<n;i++){
            int index = nums[i]/32;
            int pos = nums[i]%32;
            bitv[index]|=(0x1<<pos);
        }
        //check through the bit vector to fill
        for(int i=0;i<len;i++){
            for(int j=0;j<32;j++){
                if(i==0 && j==0)
                    continue;  //skip 0
                if(i*32+j>n)  //more than largest n
                    goto done;
                if((bitv[i]&(0x1<<j))==0){
                    ret.push_back(i*32+j);
                }
            }
        }
done:        
        return ret;
    }
};
