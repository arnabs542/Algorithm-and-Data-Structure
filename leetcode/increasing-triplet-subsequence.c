//
/*
Given an unsorted array return whether an increasing subsequence of length 3 exists or not in the array.

Formally the function should:
Return true if there exists i, j, k 
such that arr[i] < arr[j] < arr[k] given 0 ≤ i < j < k ≤ n-1 else return false.
Your algorithm should run in O(n) time complexity and O(1) space complexity.

Examples:
Given [1, 2, 3, 4, 5],
return true.

Given [5, 4, 3, 2, 1],
return false.
*/

/*
Method 1:
record smallest and second smallest
*/
bool increasingTriplet(int* nums, int size)
{
    int first = INT_MAX, second = INT_MAX;
    for(int i = 0; i < size; i++)
    {
        if(nums[i] <= first) first = nums[i]; //the equal condition here is quite essential;
        else if(nums[i] <= second) second = nums[i];
        else return true;
    }
    return false;
}

/*
DP
*/

bool increasingTriplet(vector<int>& nums) {
    //DP
    /*
    dp[i]: how many increasing subsequence in current index
    */
    int len = nums.size();
    vector<int> dp(len,1);
    for(int i=1;i<len;i++){
        for(int j=0;j<i;j++){
            if(nums[j]<nums[i]){
                dp[i] = dp[j] + 1;
                if(dp[i]==3)
                    return true;
            }
        }
    }
    
    return false;
}
