//https://leetcode.com/problems/max-sum-of-sub-matrix-no-larger-than-k/
/*
Given a non-empty 2D matrix matrix and an integer k, 
find the max sum of a rectangle in the matrix such that its sum is no larger than k.

Example:
Given matrix = [
  [1,  0, 1],
  [0, -2, 3]
]
k = 2
The answer is 2. Because the sum of rectangle [[0, 1], [-2, 3]] is 2 and 2 is the max number no larger than k (k = 2).

Note:
The rectangle inside the matrix must have an area > 0.
What if the number of rows is much larger than the number of columns?
*/
class Solution {
public:
    int maxSumSubmatrix(vector<vector<int>>& matrix, int k) {
        if (matrix.empty()) return 0;
        /*
        The idea is to fix the left and right columns one by one and find the maximum sum contiguous rows for every left and right column pair. We basically find top and bottom row numbers (which have maximum sum) for every fixed left and right column pair
        */
        int row = matrix.size();
        int col = matrix[0].size();
        int l = 0;  //left
        int r = 0;  //right
        int ret = INT_MIN;
        
        
        for(l=0;l<col;l++){
            vector<int> sum(row,0);
            for(r=l;r<col;r++){
                for(int i=0;i<row;i++){
                    sum[i]+=matrix[i][r];
                }
                //find the max less than k for current sum vector. same as find max subarray in 1D array
                //which equals to cur max value for subarea with boudary (l,start)->(r,end) 
                //cur[i]-cur[j]<=k where i>j, cur[i]-k<=cur[j]
                set<int> s;
                s.insert(0);
                int cur = 0;
                int curMax = INT_MIN; //cur max in subarea bounded by l->r
                for(auto m:sum){
                    cur+=m;
                    set<int>::iterator it=s.lower_bound(cur-k);
                    if (it != s.end()) 
                        curMax = max(curMax, cur-*it);
                    s.insert(cur);
                }
                ret =max(ret, curMax);
            }
            
        }
        return ret;
    }
};
