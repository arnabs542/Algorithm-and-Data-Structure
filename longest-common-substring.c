/http://www.lintcode.com/en/problem/longest-common-substring/
/*
Given two strings, find the longest common substring.
Return the length of it.

The characters in substring should occur continuously in original string. 
This is different with subsequence.

Example
Given A = "ABCD", B = "CBCE", return 2.

Challenge 
O(n x m) time and memory.
*/
class Solution {
public:    
    /**
     * @param A, B: Two string.
     * @return: the length of the longest common substring.
     */
    int longestCommonSubstring(string &A, string &B) {
        /*
        DP:LCS[i][j] is longest common substring for A[0:i-1] B[0:j-1]
        */        
        int m=A.size();
        int n=B.size();
        vector<vector<int>> LCS(m+1,vector<int>(n+1,0));
        int ret =0;
        for(int i=1;i<=m;i++){
            for(int j=1;j<=n;j++){
                if(A[i-1]==B[j-1]){
                    LCS[i][j]=LCS[i-1][j-1]+1;
                    ret = LCS[i][j]>ret?LCS[i][j]:ret;
                }else{
                    LCS[i][j] = 0;
                }
            }
        }
        
        return ret;

    }
};
