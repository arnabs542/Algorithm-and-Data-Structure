//https://leetcode.com/problems/number-of-connected-components-in-an-undirected-graph/
/*
Given n nodes labeled from 0 to n - 1 and a list of undirected edges (each edge is a pair of nodes), write a function to find the number of connected components in an undirected graph.
Example 1:

     0          3
     |          |
     1 --- 2    4
Given n = 5 and edges = [[0, 1], [1, 2], [3, 4]], return 2.

Example 2:
     0           4
     |           |
     1 --- 2 --- 3
Given n = 5 and edges = [[0, 1], [1, 2], [2, 3], [3, 4]], return 1. 
*/

class Solution {
public:
  int countComponents(int n, vector<pair<int, int>>& edges) {
  /*
  find root for each node, if same root, link together by union find
  */
      vector<int> root(n,0);
      for(int i=0;i<n;i++){
          root[i] = i;
      }
      
      for(int i=0;i<edges.size();i++){
          int v1 = edges[i].first;
          int v2 = edges[i].second;
          int root1 = find(root,v1);
          int root2 = find(root,v2);
          if(root1!=root2){//union two parts into one
              root[root1] = root2;
          }
          
      }
      
      int cnt = 0;
      for(int i=0;i<root.size();i++){
          if(root[i]==i)
              cnt++;
      }
      
      return cnt;
  }
  
  int find(vector<int> root, int v){
      while(root[v]!=v){//until find root is itself, not more parent node/root.
          root[v] = root[root[v]]; //path compression, directly find the final root
          v = root[v];
      }
      return v;
  }
};
