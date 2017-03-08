//https://leetcode.com/problems/maximum-size-subarray-sum-equals-k/
 Given an array nums and a target value k, find the maximum length of a subarray that sums to k. If there isn't one, return 0 instead.
/*
Example 1:
Given nums = [1, -1, 5, -2, 3], k = 3,
return 4. (because the subarray [1, -1, 5, -2] sums to 3 and is the longest)

Example 2:
Given nums = [-2, -1, 2, 1], k = 1,
return 2. (because the subarray [-1, 2] sums to 1 and is the longest)

Follow Up:
Can you do it in O(n) time? 
*/

//Analysis, for those sum of array case problem, use sum up vector that sum[i]= nums[0]+...nums[i]

//Method 1: Direct solution, O(n^2)
class Solution {
public:
  int maxSubArrayLen(vector<int>& nums, int k) {
      int len = nums.size();
      //sum array is sum value addedup from begin of array until current index
      
      vector<int> sum(len+1,0);
      for(int i=0;i<len;i++){
          sum[i+1] = sum[i]+nums[i];
      }
      int max = 0;
      //added up to k equals to sum[j]-sum[i]=k
      //search for max len
      for(int i=0;i<=len;i++){
          for(int j=i+1;j<=len;j++){
              if(sum[j]-sum[i]==k){
                  max = max>(j-i)?max:j-i;
              }
          }
      }
      
      return max;
  }
};

//Method2: hash table: O(n)
/*
//key = sum[i]+k; val is index in sum array; 
//when key is found, calculate the len= index_found-index in map.
*/
class Solution {
public:
    int maxSubArrayLen(vector<int>& nums, int k) {
        int len = nums.size();
        //sum array is sum value addedup from begin of array until current index
        
        vector<int> sum(len+1,0);
        for(int i=0;i<len;i++){
            sum[i+1] = sum[i]+nums[i];
        }
        int max = 0;
        map<int,int> m;
        for(int i=0;i<=len;i++){
            if(m.find(sum[i]+k)==m.end()){
                m[sum[i]+k] = i;//record index
            }
            if(m.find(sum[i])!=m.end()){
                int len=i-m[sum[i]];
                max = max>len?max:len;
            }
        }
        return max;
    }
};

//method 2 can be optimized by one loop
class Solution {
public:
    int maxSubArrayLen(vector<int>& nums, int k) {
        unordered_map<int, int> sums;
        int cur_sum = 0;
        int max_len = 0;
        for (int i = 0; i < nums.size(); i++) {
            cur_sum += nums[i];
            if (cur_sum == k) {
                max_len = i + 1;
            } 
            if (sums.find(cur_sum) == sums.end()) {
                sums[cur_sum] = i;
            }    
            if (sums.find(cur_sum - k) != sums.end()) {
                max_len = max(max_len, i - sums[cur_sum - k]);
            }
        
        }
        return max_len;
    }
};
