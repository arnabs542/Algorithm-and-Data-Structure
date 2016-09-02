http://www.lintcode.com/problem/remove-duplicates-from-sorted-array/
/*
Given a sorted array, remove the duplicates in place such that each element appear only once and return the new length. 
Do not allocate extra space for another array, you must do this in place with constant memory. 
For example, Given input array A = [1,1,2], Your function should return length = 2, and A is now [1,2].
*/
class Solution {
public:
    /**
     * @param A: a list of integers
     * @return : return an integer
     */
    int removeDuplicates(vector<int> &nums) {
        int start = 0;
        if(nums.size()==0)
            return 0;

        for(int i=1;i<nums.size();i++){
            if(nums[start]!=nums[i]){
                nums[++start] = nums[i];
            }
        }
        
        return start+1;
    }
};
