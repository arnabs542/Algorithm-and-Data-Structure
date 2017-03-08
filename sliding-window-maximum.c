//https://leetcode.com/problems/sliding-window-maximum/
/*
Given an array nums, there is a sliding window of size k which is moving from the very left of the array to the very right. You can only see the k numbers in the window. Each time the sliding window moves right by one position.

For example,
Given nums = [1,3,-1,-3,5,3,6,7], and k = 3.

Window position                Max
---------------               -----
[1  3  -1] -3  5  3  6  7       3
 1 [3  -1  -3] 5  3  6  7       3
 1  3 [-1  -3  5] 3  6  7       5
 1  3  -1 [-3  5  3] 6  7       5
 1  3  -1  -3 [5  3  6] 7       6
 1  3  -1  -3  5 [3  6  7]      7
Therefore, return the max sliding window as [3,3,5,5,6,7].
*/

class Solution {
public:
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        //use deque, make sure the queue is always in sorted order with front the largest item's index
        vector<int> ret;
        deque<int> dq; //push the index into vector with num[v[i]] in descending order
        for(int i=0;i<nums.size();i++){
            if(!dq.empty() && (dq.front()==i-k)){
                //the max value's index in deque reach the window size, need to pop out.
                    dq.pop_front();
            }
            while(!dq.empty() && nums[dq.back()]<nums[i]){
                dq.pop_back();
            }
            dq.push_back(i);
            if (i>=k-1)
                ret.push_back(nums[dq.front()]);
        }
        return ret;
    }
};
