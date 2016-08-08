//https://leetcode.com/problems/closest-binary-search-tree-value-ii/
/*
Given a non-empty binary search tree and a target value, find k values in the BST that are closest to the target.

Note:
Given target value is a floating point.
You may assume k is always valid, that is: k ≤ total nodes.
You are guaranteed to have only one unique set of k values in the BST that are closest to the target.
*/

class Solution {
public:
  vector<int> closestKValues(TreeNode* root, double target, int k) {
      vector<int> ret;
      priority_queue<pair<double,int>> pq;
      
      dfs_help(root,target,k, pq);
      while(!pq.empty()){
          pair<double,int> tmp = pq.top();
          ret.push_back(tmp.second);
          pq.pop();
      }
      return ret;
  }
  
  void dfs_help(TreeNode* root, double target, int k, priority_queue<pair<double,int>> &pq){
      if(root==NULL)
          return;
      
      pq.push(make_pair(abs(target-root->val),root->val));
      
      if(pq.size() > k) 
          pq.pop();
      
      dfs_help(root->left, target, k, pq);
      dfs_help(root->right, target, k, pq);
  }
};
