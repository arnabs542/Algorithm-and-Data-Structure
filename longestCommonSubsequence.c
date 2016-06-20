//http://www.lintcode.com/en/problem/longest-common-subsequence/

/*
Clarification
What's the definition of Longest Common Subsequence?

https://en.wikipedia.org/wiki/Longest_common_subsequence_problem
http://baike.baidu.com/view/2020307.htm
Example
For "ABCD" and "EDCA", the LCS is "A" (or "D", "C"), return 1.

For "ABCD" and "EACB", the LCS is "AC", return 2.
*/
class Solution {
public:
    /**
     * @param A, B: Two strings.
     * @return: The length of longest common subsequence of A and B.
     */
    int longestCommonSubsequence(string A, string B) {
        // LCS[i][j] is longest common subsequence for A[0:i-1] and B[0:j-1]
        int len_A = A.size();
        int len_B = B.size();
        vector<vector<int>> LCS(len_A+1,vector<int>(len_B+1,0));
        
        for(int i=1;i<=len_A;i++){
            for(int j=1;j<=len_B;j++){
                if(A[i-1]==B[j-1])
                    LCS[i][j] = LCS[i-1][j-1]+1;
                else
                    LCS[i][j] = max(LCS[i-1][j],LCS[i][j-1]);
            }
        }
        
        return LCS[len_A][len_B];
    }
};
