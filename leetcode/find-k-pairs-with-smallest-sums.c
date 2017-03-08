//https://leetcode.com/problems/find-k-pairs-with-smallest-sums/
/*
 You are given two integer arrays nums1 and nums2 sorted in ascending order and an integer k.
Define a pair (u,v) which consists of one element from the first array and one element from the second array.
Find the k pairs (u1,v1),(u2,v2) ...(uk,vk) with the smallest sums.

Example 1:
Given nums1 = [1,7,11], nums2 = [2,4,6],  k = 3
Return: [1,2],[1,4],[1,6]

The first 3 pairs are returned from the sequence:
[1,2],[1,4],[1,6],[7,2],[7,4],[11,2],[7,6],[11,4],[11,6]

Example 2:
Given nums1 = [1,1,2], nums2 = [1,2,3],  k = 2
Return: [1,1],[1,1]

The first 2 pairs are returned from the sequence:
[1,1],[1,1],[1,2],[2,1],[1,2],[2,2],[1,3],[1,3],[2,3]
*/

class Solution {
private:
  struct mycompare{
      bool operator()(pair<int, int>& p1, pair<int, int>& p2){
          return p1.first + p1.second < p2.first + p2.second;
      }
  };
public:
  vector<pair<int, int>> kSmallestPairs(vector<int>& nums1, vector<int>& nums2, int k) {
      vector<pair<int, int>> ret;
      //use min heap, so min k values is in heap, top of heap is max(min k value)
      priority_queue<pair<int, int>, vector<pair<int, int>>, mycompare> pq;
      for(int i=0;i<nums1.size();i++){
          for(int j=0;j<nums2.size();j++){
              //instead of directly push and check whether heap is larger than k then pop
              //do not push unnecessary, save time
              if(pq.size()<k){
                  pq.push(make_pair(nums1[i],nums2[j]));
              }else{
                  pair<int,int> cur_max = pq.top();
                  pair<int,int> newone = make_pair(nums1[i],nums2[j]);
                  if(cur_max.first+cur_max.second>nums1[i] + nums2[j]){
                      pq.push(newone);
                      pq.pop();
                  }
                      
              }
          }
      }
      
      while(!pq.empty()){
          ret.push_back(pq.top());
          pq.pop();
      }
      reverse(ret.begin(),ret.end());
      return ret;
  }
};
