//https://leetcode.com/problems/maximum-subarray/
/*
Find the contiguous subarray within an array (containing at least one number) which has the largest sum.

For example, given the array [-2,1,-3,4,-1,2,1,-5,4],
the contiguous subarray [4,-1,2,1] has the largest sum = 6.
*/
//method 1: 
class Solution {
public:
    int maxSubArray(vector<int>& nums) {
        //build up the sum[i] that value equals the sum of{nums[0]..nums[i]}
        //min is min value from sum[0]->sum[i-1]
        //so max sub array is sum[i]-min
        int len = nums.size();
        vector<int> sum(len+1,0);
        sum[0] = 0;
        int ret = INT_MIN;
        int min = 0;
        for(int i=1;i<=len;i++){
            sum[i] = sum[i-1]+nums[i-1];
            ret = ret>(sum[i]-min)?ret:(sum[i]-min);
            min = sum[i]<min?sum[i]:min;
        }
        
        return ret;
    }
};

//method 2: DP 
class Solution {
public:
    int maxSubArray(vector<int>& nums) {
        /*
        DP:
        max(i,j) is max value in range(i,j)
        max(i,j) = 
        1. max(max(i,j-1),sum(i,j-1)+nums[j])  
        2: 0 (if max(i,j-1)+nums[j]<0, )
        */
        int len = nums.size();
        int max = INT_MIN;
        int sum = 0;

        for(int i =0;i<len;i++){
            sum = sum+nums[i];
            max = max>sum?max:sum;
            if(sum<0){
                sum = 0;
            }
        }
        return max;
    }
};


/*
Follow up this question to:
Given an array of integers A and an integer k, 
find a subarray that contains the largest sum, subject to a constraint that the sum is less than k?
*/

/*
make use of method to have sum/cum value. so find cum[i]-cum[j]<=k with largest value
 cum[i]-k<=cum[j], 
O(nlog(n))
*/
int best_cumulative_sum(int ar[],int N,int K)
{
    set<int> cumset;
    cumset.insert(0);
    int best=0,cum=0;
    for(int i=0;i<N;i++)
    {
        cum+=ar[i];
        set<int>::iterator sit=cumset.upper_bound(cum-K);
        if(sit!=cumset.end())
            best=max(best,cum-*sit);
        cumset.insert(cum);
    }
}
