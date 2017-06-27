/*
https://leetcode.com/problems/maximum-distance-in-arrays/#/description
Given m arrays, and each array is sorted in ascending order. Now you can pick up two integers from two different arrays (each array picks one) and calculate the distance. We define the distance between two integers a and b to be their absolute difference |a-b|. Your task is to find the maximum distance.

Example 1:
Input:
[[1,2,3],
 [4,5],
 [1,2,3]]
Output: 4
Explanation:
One way to reach the maximum distance 4 is to pick 1 in the first or third array and pick 5 in the second array.
*/

int maxDistance(vector<vector<int>>& arrays) {
    int left = arrays[0][0], right = arrays[0].back(), ret = 0;
    for(int i = 1; i < arrays.size(); i++)
    {
        ret = max(ret, max(abs(arrays[i][0] - right), abs(arrays[i].back() - left))); //make sure we do not pick same vector
        left = min(left, arrays[i][0]);
        right = max(right, arrays[i].back());
    }
    return ret;
}
