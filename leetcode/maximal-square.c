//https://leetcode.com/problems/maximal-square/
/*
Given a 2D binary matrix filled with 0's and 1's, find the largest square containing only 1's and return its area.
For example, given the following matrix:

1 0 1 0 0
1 0 1 1 1
1 1 1 1 1
1 0 0 1 0
Return 4.
*/
class Solution {
public:
    int maximalSquare(vector<vector<char>>& matrix) {
        if (matrix.empty() || matrix[0].empty()) return 0;
        int M = matrix.size(), N = matrix[0].size(), res = 0;
        /*we define the state to be the maximal size of the square that can be achieved at point (i, j), denoted as P[i][j]. Remember that we use size instead of square as the state (square = size^2)
        
        First, it is obvious that for the topmost row (i = 0) and the leftmost column (j = 0), P[i][j] = matrix[i][j]. This is easily understood. Let's suppose that the topmost row of matrix is like [1, 0, 0, 1]. Then we can immediately know that the first and last point can be a square of size 1 while the two middle points cannot make any square, giving a size of 0. Thus, P = [1, 0, 0, 1], which is the same as matrix. The case is similar for the leftmost column. Till now, the boundary conditions of this DP problem are solved.
        Suppose matrix = [[0, 1], [1, 1]], it is obvious that P[0][0] = 0, P[0][1] = P[1][0] = 1, what about P[1][1]? Well, to give a square of size larger than 1 in P[1][1], all of its three neighbors (left, up, left-up) should be non-zero, right? In this case, the left-up neighbor P[0][0] = 0, so P[1][1] can only be 1, which means that it contains the square of itself.

Now you are near the solution. In fact, P[i][j] = min(P[i - 1][j], P[i][j - 1], P[i - 1][j - 1]) + 1 in this case.
        */
        vector<vector<int>> dp(M, vector<int>(N, 0));
        for (int i = 0; i < M; ++i) {
            if (matrix[i][0] == '1'){
                dp[i][0] = 1; 
                res = 1;
            }
        }
         for (int j = 0; j < N; ++j) {
             if (matrix[0][j] == '1') {
                 dp[0][j] = 1; 
                 res = 1;
             }
         }
         for (int i = 1; i < M; ++i) {
             for (int j = 1; j < N; ++j) {
                 if (matrix[i][j] == '1') {
                    dp[i][j] = min(dp[i-1][j-1], min(dp[i-1][j], dp[i][j-1])) + 1;
                    res = max(res, dp[i][j]);
                 }else{
                     dp[i][j] = 0;
                 }
             }
         }
         return res * res;
    }
};
