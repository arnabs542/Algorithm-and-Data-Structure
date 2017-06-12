//https://leetcode.com/problems/split-array-with-equal-sum/
/*
Given an array with n integers, you need to find if there are triplets (i, j, k) which satisfies following conditions:

0 < i, i + 1 < j, j + 1 < k < n - 1
Sum of subarrays (0, i - 1), (i + 1, j - 1), (j + 1, k - 1) and (k + 1, n - 1) should be equal.
where we define that subarray (L, R) represents a slice of the original array starting from the element indexed L to the element indexed R.
Example:
Input: [1,2,1,2,1,2,1]
Output: True
Explanation:
i = 1, j = 3, k = 5.
sum(0, i - 1) = sum(0, 0) = 1
sum(i + 1, j - 1) = sum(2, 2) = 1
sum(j + 1, k - 1) = sum(4, 4) = 1
sum(k + 1, n - 1) = sum(6, 6) = 1
*/

bool splitArray(vector<int>& nums) {
        //get a middle cut, and then calculate left and right cur respectively see find whether there is equal
        int len = nums.size();
        if(len<7)
            return false;

        vector<int> sum(len,0);
        sum[0] = nums[0];
        for(int i=1;i<len;i++){
            sum[i]=sum[i-1]+nums[i];
        }
        //i is left cut, j is middle cut, k is right cut
        for(int j=3;j<len-3;j++){
            unordered_set<int> s; //record sum in for subarray, for each different middle cut we have new set for split
            for(int i=0;i<j-1;i++){
                if(sum[i-1]==sum[j-1]-sum[i])
                    s.insert(sum[i-1]); //one subarray in left cut candidate
            }

            for(int k=j+2;k<len-1;k++){
                if(sum[len-1]-sum[k]==sum[k-1]-sum[j] && s.find(sum[len-1]-sum[k])!=s.end()) //find right cut and equals to left
                    return true;
            }
        }
        return false;

    }
