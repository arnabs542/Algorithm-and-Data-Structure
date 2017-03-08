//https://leetcode.com/problems/find-the-duplicate-number/
/*
Given an array nums containing n + 1 integers where each integer is between 1 and n (inclusive), prove that at least one duplicate number must exist. 
Assume that there is only one duplicate number, find the duplicate one.
*/
//method 1: easy way: Hash table
class Solution {
public:
    int findDuplicate(vector<int>& nums) {
        unordered_map<int,int> m;
        int ret;
        for(int i=0;i<nums.size();i++){
            m[nums[i]]++;
            if(m[nums[i]]>1){
                ret = nums[i];
                break;
            }
        }
        return ret;
    }
};

//method 2: Binary search
class Solution {
public:
    int findDuplicate(vector<int>& nums) {
        //sort, then binary search
        /*
At first the search space is numbers between 1 to n. Each time I select a number mid (which is the one in the middle) and count all the numbers equal to or less than mid. Then if the count is more than mid, the search space will be [1 mid] otherwise [mid+1 n]. I do this until search space is only one number.        

finally we should have start+1=end or start = end,         
        */
        sort(nums.begin(),nums.end());
        int start = 0;
        int end = nums.size()-1;
        
        while(start<end){
            int mid=start+(end-start)/2;
            int nogreater = count(nums,nums[mid]);
            if(nogreater>nums[mid]){
                end = mid;
            }else{
                start = mid+1;
            }
        }
        
        return nums[end];
    }
    //count how many equal or less than nums[mid]
    int count(vector<int>& nums, int target){
        int cnt = 0;
        for (int i=0;i<nums.size();i++)
            if (nums[i] <= target)
                cnt++;
        return cnt;
    }
};
