//
/*Given an unsorted array nums, reorder it such that nums[0] < nums[1] > nums[2] < nums[3]....
Example:
(1) Given nums = [1, 5, 1, 1, 6, 4], one possible answer is [1, 4, 1, 5, 1, 6]. 
(2) Given nums = [1, 3, 2, 2, 3, 1], one possible answer is [2, 3, 1, 3, 1, 2].
Note:
You may assume all input has valid answer.
Follow Up:
Can you do it in O(n) time and/or in-place with O(1) extra space?
*/
class Solution {
public:
    void wiggleSort(vector<int>& nums) {
        int len=nums.size();
        vector<int> tmp = nums;
        std::sort(tmp.begin(),tmp.end());
        int k = (1+len)/2; //ending of first half k-1
        int j = len; //ending of second half j-1
        //pick up from end of first half and second half, to start of first half and second half
        for(int i=0;i<len;i++){
            nums[i] = i&1?tmp[--j]:tmp[--k];
        }

    }
};

/*
Given an unsorted array nums, reorder it in-place such that nums[0] <= nums[1] >= nums[2] <= nums[3]....

For example, given nums = [3, 5, 2, 1, 6, 4], one possible answer is [1, 6, 2, 5, 3, 4].
*/

//since the requirement is equal, just needs to swap adjcent sorted
class Solution {
public:
    void wiggleSort(vector<int> &nums) {
        sort(nums.begin(), nums.end());
        if (nums.size() <= 2) return;
        for (int i = 2; i < nums.size(); i += 2) {
            swap(nums[i], nums[i - 1]);
        }
    }
};
