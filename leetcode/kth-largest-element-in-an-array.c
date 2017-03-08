//https://leetcode.com/problems/kth-largest-element-in-an-array/
/*
Find the kth largest element in an unsorted array. Note that it is the kth largest element in the sorted order, not the kth distinct element.

For example,
Given [3,2,1,5,6,4] and k = 2, return 5.
Note: 
You may assume k is always valid, 1 ≤ k ≤ array's length.
*/

class Solution {
public:
  //for max heap, we need compare function which is not default less, but larger
  struct mycompare{
      bool operator()(int a, int b){
          return a>b;
      }
  };

  int findKthLargest(vector<int>& nums, int k) {
      //should have a max heap size k, where top is the minimum of max k values.
      priority_queue<int,vector<int>,mycompare> pq;
      for(int i=0;i<nums.size();i++){
          if(pq.size()<k){
              pq.push(nums[i]);
          }else{
              if(nums[i]>pq.top()){
                  pq.pop();
                  pq.push(nums[i]);
              }
          }
      }
      
      return pq.top();
  }
};
