//https://leetcode.com/problems/maximum-gap/
/*
Given an unsorted array, find the maximum difference between the successive elements in its sorted form.
Try to solve it in linear time/space.
Return 0 if the array contains less than 2 elements.
You may assume all elements in the array are non-negative integers and fit in the 32-bit signed integer range
*/

class Solution {
public:
    int maximumGap(vector<int>& nums) {
    /*
Suppose all the n elements in nums fall within [l, u], the maximum gap will not be smaller than gap = (u - l) / (n - 1). However, this gap may become 0 and so we take the maximum of it with 1 to guarantee that the gap used to create the buckets is meaningful.
Then there will be at most m = (u - l) / gap + 1 buckets. For each number num, it will fall in the k = (num - l) / gap bucket. After putting all elements of nums in the corresponding buckets, we can just scan the buckets to compute the maximum gap.
The maximum gap is only dependent on the maximum number of the current bucket and the minimum number of the next neighboring bucket (the bucket should not be empty). So we only store the minimum and the maximum of each bucket. Each bucket is initialized as {minimum = INT_MAX, maximum = INT_MIN} and then updated while updating the buckets.
    */
        
        int max_g = INT_MIN; 
        int min_g = INT_MAX;
        int len = nums.size();
        if(len<=1)
            return 0;

        for(int i=0;i<len;i++){
            max_g = max(max_g,nums[i]);
            min_g = min(min_g,nums[i]);
        }
        int bucket_size = max(1, (max_g - min_g )/ (len - 1));
        int bucket_num  = (max_g - min_g)/bucket_size + 1;
        
        if(bucket_num <=1) 
            return (max_g - min_g); 
        vector<int> bucket_max(bucket_num, INT_MIN);
        vector<int> bucket_min(bucket_num, INT_MAX);
        vector<int> bucket_count(bucket_num, 0);
        int index;
        //using bucket, we basic sort this array 
        for(int i=0; i<len; i++){
            
            index = (nums[i] - min_g)/bucket_size;
            bucket_count[index]++;
            bucket_min[index] = min(bucket_min[index],nums[i]);
            bucket_max[index] = max(bucket_max[index],nums[i]);
        }
        
        int maxGap = INT_MIN;
        int last_max = min_g;//max number in last bucket
        for(int i=0; i<bucket_num; i++){
            if(bucket_count[i]>0){
                maxGap = max(maxGap, bucket_min[i]- last_max);
                last_max = bucket_max[i];
            }
        }
        return maxGap;
        
    }
};
