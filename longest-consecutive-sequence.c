//https://leetcode.com/problems/longest-consecutive-sequence/
/*
Given an unsorted array of integers, find the length of the longest consecutive elements sequence.

For example,
Given [100, 4, 200, 1, 3, 2],
The longest consecutive elements sequence is [1, 2, 3, 4]. Return its length: 4.

Your algorithm should run in O(n) complexity.
*/
//method 1: O(nlog(n))
class Solution {
public:
  int longestConsecutive(vector<int>& nums) {
      std::sort(nums.begin(),nums.end());
      int max = 1;
      int cnt = 1;
      for(int i=1;i<nums.size();i++){
          if(nums[i]==nums[i-1]){
              continue;
          }
          
          if(nums[i]==nums[i-1]+1){
              cnt++;
              max = cnt>max?cnt:max;
          }else{
              cnt = 1;
          }
      }
      
      return max;
  }
};

//If int are positive, bit vector 
class Solution {
public:
    int longestConsecutive(vector<int>& nums) {
        //method 2: use bit vector.
        int cnt = 0;
        int max = 0;
        int num_max = 0;
        for(int i=0;i<nums.size();i++){
            num_max = num_max>nums[i]?num_max:nums[i];
        }
        
        int bv_len = num_max/8+1;
        vector<int> bv(bv_len,0);
        for(int i=0;i<nums.size();i++){
            int idx = nums[i]/8;
            int shift = nums[i]%8;
            bv[idx] = bv[idx]|(0x1<<shift);
        }
        
        for(int i=0;i<=num_max;i++){
            int idx = i/8;
            int shift = i%8;
            if((bv[idx]&(0x1<<shift))!=0){
                cnt++;
                max = cnt>max?cnt:max;
            }else{
                cnt = 0;
            }
        }
        
        return max;
    }
};

//method 3: use hash set
class Solution {
public:
    int longestConsecutive(vector<int> &num) {
        //maintain two sets. first record all num
        //second record which do we searched
        unordered_set<int> record(num.begin(),num.end());
        unordered_set<int> searched;
        int res = 1;
        for(int n : num){
            if(searched.find(n)!=searched.end()) continue;
                searched.insert(n);
            int prev = n-1,next = n+1;
            while(record.find(prev)!=record.end()) 
                searched.insert(prev--);
            while(record.find(next)!=record.end()) 
                searched.insert(next++);
            res = max(res,next-prev-1);
        }
        return res;
    }
};
