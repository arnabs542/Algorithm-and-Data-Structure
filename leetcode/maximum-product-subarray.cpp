//https://leetcode.com/problems/maximum-product-subarray/#/description

Find the contiguous subarray within an array (containing at least one number) which has the largest product.

For example, given the array [2,3,-2,4],
the contiguous subarray [2,3] has the largest product = 6.

int maxProduct(vector<int>& nums) {
    int prod = 1;
    int ret = INT_MIN;
    int begin = 1;
    int end = 1;
    int len = nums.size();
    for(int i=0;i<nums.size();i++){
        begin*=nums[i];
        end*=nums[len-1-i];
        ret = max(ret,max(begin,end));
        begin = begin==0?1:begin;
        end = end==0?1:end;
    }
    return ret;
}

//method 2:
int maxProduct(vector<int>& nums) {
    int max_cur = nums[0]; //max until currrent index
    int min_cur = nums[0]; //min until current index
    int ret = nums[0];
    for(int i=1;i<nums.size();i++){
        if(nums[i]<0)
            swap(max_cur,min_cur);

        max_cur = max(nums[i],max_cur*nums[i]);
        min_cur = min(nums[i],min_cur*nums[i]);
        ret = max(ret,max_cur);
    }
    return ret;
}
