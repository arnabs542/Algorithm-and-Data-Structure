//leetcode:https://leetcode.com/problems/longest-increasing-subsequence/

int lengthOfLIS(vector<int>& nums) {
    int len = nums.size();
    if(len==0)
        return 0;
    vector<int> LIS(len, 1);
    int max = 0;

    /*  
    DP: LIS(i) number of LIS ending position i,
    transition function: LIS[i] = max(LIS[j]+1,LIS[i]);j<i
    
    nums: 1,3,6,7,9,4,10,5,6
    LIS:  1,2,3,4,5,3,6,4,5,
    
    O(n^2)
    */
    for(int i=0;i<len;i++){
        for(int j=0;j<i;j++){
            if(nums[i]>nums[j]){
                LIS[i] = (LIS[j]+1)>LIS[i]? (LIS[j]+1):LIS[i];
            }
        }
        max = max>=LIS[i]?max:LIS[i];
    }
    return max;
}
