//https://leetcode.com/problems/kth-smallest-element-in-a-sorted-matrix/
/*
Given a n x n matrix where each of the rows and columns are sorted in ascending order, find the kth smallest element in the matrix.
Note that it is the kth smallest element in the sorted order, not the kth distinct element.

Example:
matrix = [
   [ 1,  5,  9],
   [10, 11, 13],
   [12, 13, 15]
],
k = 8,
return 13.
*/
//method 1: max heap:construct the max heap for first k small values.
//worst O(log(n)*n^2)
//mean O(log(n)*k+n^2)
class Solution {
public:
  int kthSmallest(vector<vector<int>>& matrix, int k) {
      int n = matrix.size(); //n*n matrix
      //construct the max heap for first k small values.
      priority_queue<int> pq;
      for(int i=0;i<n;i++){
          for(int j=0;j<n;j++){
              if(pq.size()<k){
                  pq.push(matrix[i][j]);
              }else{
                  if(matrix[i][j]<pq.top()){
                      pq.pop();
                      pq.push(matrix[i][j]);
                  }
              }
          }
      }
      return pq.top();
  }
};

//method 2: MIn heap, each time pop min, until k times. O(log(n)*k)
class Solution {
public:
  struct mycompare{
      bool operator()(pair<int,pair<int,int>> a, pair<int,pair<int,int>> b){
          return a.first>b.first;
      }
  };
  int kthSmallest(vector<vector<int>>& matrix, int k) {
      int n = matrix.size(); //n*n matrix
      //construct minheap, so top is min value.
      priority_queue <pair<int,pair<int,int>>, vector<pair<int,pair<int,int>>>, mycompare> pq;
      //insert all first col, 
      for(int i=0;i<n;i++){
          pq.push(make_pair(matrix[i][0],make_pair(i,0)));
      }
      //pick any value [row,col+1] where [row,col] is location of top of heap, so it is definitely larger than top of heap.
      //insert to heap, and pop top(min value)
      int ret;
      while(k--){
          int val=pq.top().first;
          int x=pq.top().second.first;
          int y=pq.top().second.second;
          ret = val;
          pq.pop();
          if(y<n-1){
              pq.push(make_pair(matrix[x][y+1],make_pair(x,y+1)));
          }
      }
      
      return ret;
  }
};

//method 2:
