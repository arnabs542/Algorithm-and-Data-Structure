//https://leetcode.com/problems/create-maximum-number/
/*
Given two arrays of length m and n with digits 0-9 representing two numbers. Create the maximum number of length k <= m + n from digits of the two. The relative order of the digits from the same array must be preserved. Return an array of the k digits. You should try to optimize your time and space complexity.

Example 1:
nums1 = [3, 4, 6, 5]
nums2 = [9, 1, 2, 5, 8, 3]
k = 5
return [9, 8, 6, 5, 3]

Example 2:
nums1 = [6, 7]
nums2 = [6, 0, 4]
k = 5
return [6, 7, 6, 0, 4]

Example 3:
nums1 = [3, 9]
nums2 = [8, 9]
k = 3
return [9, 8, 9]
*/


class Solution {
public:
    vector<int> maxNumber(vector<int>& nums1, vector<int>& nums2, int k) {
        /*
        To create max number of length k from two arrays, you need to create max number of length i from array one and max number of length k-i from array two, then combine them together. After trying all possible i, you will get the max number created from two arrays.
        */
        int m = nums1.size(), n = nums2.size();
        vector<int> res(k, 0);
    
        for (int i = max(0, k - n); i <= min(k, m); ++i) {
            auto v1 = maxArray(nums1, i);
            auto v2 = maxArray(nums2, k - i);
            auto tmp = merge(v1, v2, k);
            if (greater(tmp, 0, res, 0)) 
                res = tmp;
        }
    
        return res;
    };
    //pick up largest k values in num array, perserve the sequence
    vector<int> maxArray(vector<int> num, int k) {
        vector<int> ret;
        //we need to drop these number from num vector
        int drop=num.size()-k;
        int i =0;
        
        for(i=0;i<num.size();i++){
            while(drop>0&&!ret.empty()&&num[i]>ret.back()){
                ret.pop_back();
                drop--;
            }
            ret.push_back(num[i]);
        }
        
        
        return ret;
    }
    
    bool greater(vector<int>& nums1, int i, vector<int>& nums2, int j) {
       while (i < nums1.size() && j < nums2.size() && nums1[i] == nums2[j]) {
            ++i;
            ++j;
        }
        if (j == nums2.size()) return true;
        if (i < nums1.size() && nums1[i] > nums2[j]) return true;
        return false;
    }
    
    vector<int> merge(vector<int>& v1, vector<int>& v2, int k){
        //merge sort
        vector<int> ans(k,0);
        for (int i = 0, j = 0, r = 0; r < k; ++r)
            ans[r] = greater(v1, i, v2, j) ? v1[i++] : v2[j++];
        return ans;
    }
    
};
