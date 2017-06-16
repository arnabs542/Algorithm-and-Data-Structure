/*
https://leetcode.com/problems/arithmetic-slices-ii-subsequence/#/description
A sequence of numbers is called arithmetic if it consists of at least three elements and if the difference between any two consecutive elements is the same.

For example, these are arithmetic sequences:

1, 3, 5, 7, 9
7, 7, 7, 7
3, -1, -5, -9
The following sequence is not arithmetic.
1, 1, 2, 5, 7

The function should return the number of arithmetic subsequence slices in the array A.
The input contains N integers. Every integer is in the range of -231 and 231-1 and 0 ≤ N ≤ 1000. The output is guaranteed to be less than 231-1.


Example:
Input: [2, 4, 6, 8, 10]
Output: 7

Explanation:
All arithmetic subsequence slices are:
[2,4,6]
[4,6,8]
[6,8,10]
[2,4,6,8]
[4,6,8,10]
[2,4,6,8,10]
[2,6,10]
*/

int numberOfArithmeticSlices(vector<int>& A) {
    if(A.empty()) return 0;
    // for each dp, record its step and how many sub sequence for that step size
    vector<unordered_map<int,int>> dp(A.size());//[index, [step, count]]

    int res = 0;
    for(int i = 0; i < A.size(); ++i){
        for(int j = 0; j < i; ++j){
            if((long)A[i] - (long)A[j] > INT_MAX || (long)A[i] - (long)A[j] < INT_MIN) continue;

            int step = A[i] - A[j];
            dp[i][step] += 1;
            if(dp[j].find(step) != dp[j].end()){
                dp[i][step] += dp[j][step];
                res += dp[j][step];
            }
        }
    }
    return res;
}
