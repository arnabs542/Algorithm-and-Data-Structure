//https://leetcode.com/problems/count-of-range-sum/
/*
 Given an integer array nums, return the number of range sums that lie in [lower, upper] inclusive.
Range sum S(i, j) is defined as the sum of the elements in nums between indices i and j (i ≤ j), inclusive.

Note:
A naive algorithm of O(n2) is trivial. You MUST do better than that.

Example:
Given nums = [-2, 5, -1], lower = -2, upper = 2,
Return 3.
The three ranges are : [0, 0], [2, 2], [0, 2] and their respective sums are: -2, -1, 2.
*/



class Solution {
public:
    int countRangeSum(vector<int>& nums, int lower, int upper) {
        int size=nums.size();
        if(size==0)  return 0;
        vector<long> sums(size+1, 0);
        for(int i=0; i<size; i++)  sums[i+1]=sums[i]+nums[i];
        return help(sums, 0, size+1, lower, upper);
    }

    /*** [start, end)  ***/
    int help(vector<long>& sums, int start, int end, int lower, int upper){
        /*** only-one-element, so the count-pair=0 ***/
        if(end-start<=1)  return 0;
        int mid=(start+end)/2;
        int count=help(sums, start, mid, lower, upper)
                + help(sums, mid, end, lower, upper);

        int m=mid, n=mid, t=mid, len=0;

        vector<long> cache(end-start, 0);
        for(int i=start, s=0; i<mid; i++, s++){

            while(m<end && sums[m]-sums[i]<lower) m++;
            while(n<end && sums[n]-sums[i]<=upper) n++;
            count+=n-m;
            /*** cache will merge-in-the-smaller-part-of-list2 ***/
            while(t<end && sums[t]<sums[i]) cache[s++]=sums[t++];
            cache[s]=sums[i];
            len=s;
        }

        for(int i=0; i<=len; i++)  sums[start+i]=cache[i];
        return count;
    }
};

//Method 2:
int countRangeSum(vector<int>& nums, int lower, int upper) {
    int len = nums.size();
    int ret = 0;
    long long sum = 0;
    // lower<=sum[i]-sum[j]<=upper
    //j (0=< j< i) satisfy sum[i]-upper=< sum[j]<=-sum[i]-lower.
    multiset<long long> s; //multi set allow same item
    s.insert(0); //since one number itself can be see as range, insert 0 to collect one number case
    for(int i=0;i<len;i++){
        sum+=nums[i];
        //count how many in that range
        ret+=std::distance(s.lower_bound(sum-upper),s.upper_bound(sum-lower));
        s.insert(sum);
    }
    return ret;
}
