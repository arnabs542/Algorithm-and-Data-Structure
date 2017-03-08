//https://leetcode.com/problems/rotate-function/
/*
 Given an array of integers A and let n to be its length.
Assume Bk to be an array obtained by rotating the array A k positions clock-wise, we define a "rotation function" F on A as follow:

F(k) = 0 * Bk[0] + 1 * Bk[1] + ... + (n-1) * Bk[n-1].
Calculate the maximum value of F(0), F(1), ..., F(n-1).

Note:
n is guaranteed to be less than 10^5.

Example:
A = [4, 3, 2, 6]

F(0) = (0 * 4) + (1 * 3) + (2 * 2) + (3 * 6) = 0 + 3 + 4 + 18 = 25
F(1) = (0 * 6) + (1 * 4) + (2 * 3) + (3 * 2) = 0 + 4 + 6 + 6 = 16
F(2) = (0 * 2) + (1 * 6) + (2 * 4) + (3 * 3) = 0 + 6 + 8 + 9 = 23
F(3) = (0 * 3) + (1 * 2) + (2 * 6) + (3 * 4) = 0 + 2 + 12 + 12 = 26
So the maximum value of F(0), F(1), F(2), F(3) is F(3) = 26.
*/

class Solution {
public:
    int maxRotateFunction(vector<int>& A) {
        /*
        F(k) = 0 * Bk[0] + 1 * Bk[1] + ... + (n-1) * Bk[n-1]
        F(k-1) = (n-1) * BK[0] + 0 * BK[1] +...+ (n-2)*BK[n-1]
        F(K)-F(k-1) = Bk[1] + ... + Bk[n-1] -(n-1)*BK[0]
                = sum - n*BK[0]
        F(K) = F(k-1) - sum + n*BK[0]
        */
        int shift = 0;
        int len = A.size();
        int ret = INT_MIN;
        if(A.empty())
            return 0;
        int sum1=0;
        int sum2=0;
        for(int i=0;i<len;i++){
            sum1+=A[i];
            sum2+=i*A[i];
        }
        int F = sum2;
        for(int i=0;i<len;i++){
            F = F-sum1+len*A[i];
            ret = ret>F?ret:F;
        }
        return ret;
    }
};
