/*
https://leetcode.com/problems/arithmetic-slices/#/description
A sequence of number is called arithmetic if it consists of at least three elements and if the difference between any two consecutive elements is the same.
For example, these are arithmetic sequence:

1, 3, 5, 7, 9
7, 7, 7, 7
3, -1, -5, -9
The following sequence is not arithmetic.
1, 1, 2, 5, 7

Example:
A = [1, 2, 3, 4]
return: 3, for 3 arithmetic slices in A: [1, 2, 3], [2, 3, 4] and [1, 2, 3, 4] itself.
*/

int numberOfArithmeticSlices(vector<int>& A) {
    //dp[i] is number of Arithmetic ending i,
    // dp[i] = dp[i-1] +1; //all sequence from last increase plus new 3 item sequnce
    int len = A.size();
    if(len<3)
        return false;
    vector<int> dp(len,0);
    int step = A[1]-A[0];
    for(int i=2;i<len;i++){
        if (step == A[i]-A[i-1]){
            dp[i] = dp[i-1] + 1;
        }
        step = A[i]-A[i-1];
    }
    int ret = 0;
    for(int i=0;i<len;i++){
        ret+=dp[i];
    }
    return ret;
}
