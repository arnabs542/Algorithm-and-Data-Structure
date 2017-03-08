//https://leetcode.com/problems/unique-binary-search-trees-ii/
/*
Given an integer n, generate all structurally unique BST's (binary search trees) that store values 1...n.

For example,
Given n = 3, your program should return all 5 unique BST's shown below.

   1         3     3      2      1
    \       /     /      / \      \
     3     2     1      1   3      2
    /     /       \                 \
   2     1         2                 3
*/

class Solution {
public:
/*
for root at i, the unique BST has left child as all unique BST between 1 to i-1, has right child as all unique BST between i+1 to n. And the overall results have root traverse from 1 to n. So this intuitively lead to a recursive solution.
*/
  vector<TreeNode*> generateTrees(int n) {
      vector<TreeNode*> ret;
      if(n<1) 
          return ret;
      
      return help(1,n);
  }
  
  vector<TreeNode*> help(int start, int end){
      vector<TreeNode*> ret;
      if(start>end){
          ret.push_back(NULL);
          return ret;
      }
      for(int i=start;i<=end;i++){
          vector<TreeNode*> left = help(start,i-1);
          vector<TreeNode*> right = help(i+1,end);
          for(auto l:left){
              for(auto r:right){
                  TreeNode* root = new TreeNode(i);
                  root->left = l;
                  root->right = r;
                  ret.push_back(root);
              }
          }
      }
      return ret;
  }
};
