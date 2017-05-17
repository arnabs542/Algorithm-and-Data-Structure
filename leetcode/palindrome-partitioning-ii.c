//https://leetcode.com/problems/palindrome-partitioning-ii/
/*
Given a string s, partition s such that every substring of the partition is a palindrome.
Return the minimum cuts needed for a palindrome partitioning of s.

For example, given s = "aab",
Return 1 since the palindrome partitioning ["aa","b"] could be produced using 1 cut.
*/

class Solution {
public:
    int minCut(string s) {
        /*
        cut[i] is minimum cut at char i,
        cut[i] = min{1 + cut[j], cut[i]}, where j < i and substring [j, i] is palindrome
        */

        int len = s.size();
        vector<int>cut;
        for(int i=0;i<=len;i++)
            cut.push_back(i-1);


        vector<vector<bool>>isPal (len,vector<bool>(len, false)); //isPal[i,j] indicate whether s[i->j] is pal

        for(int i=len-1;i>=0;i--){
            for(int j=i; j<len; j++) {
                if((i+1>j-1 || isPal[i+1][j-1]) && s[i]==s[j])
                    isPal[i][j] = true;
            }
        }

        for(int i=1;i<=len;i++){
            for(int j=0;j<i;j++){
                if(isPal[j][i-1]) // check if substring [j, i-1] is palindrome
                    cut[i] = min(cut[i], 1 + cut[j]);
            }
        }

        return cut[len];
    }

};


//optimize
int minCut(string s) {
    /*
    isPal[i][j] , which is whether s[i..j] forms a pal
    cut[i], which is the minCut for s[i..n-1]
    */

    int len = s.size();
    vector<int>cut(len,0);
    vector<vector<bool>>isPal (len,vector<bool>(len, false)); //isPal[i,j] indicate whether s[i->j] is pal

    for(int i=len-1;i>=0;i--){
        cut[i] = len-1-i;
        for(int j=i; j<len; j++) {
            if(s[i]==s[j] && (j-i<2 || isPal[i+1][j-1])){
                isPal[i][j] = true;
                if(j==len-1)
                    cut[i]=0;
                else
                    cut[i]=min(cut[i],cut[j+1]+1);
            }
        }
    }
    return cut[0];
}
