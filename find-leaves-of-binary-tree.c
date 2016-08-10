//https://leetcode.com/problems/find-leaves-of-binary-tree/
/*
Given a binary tree, collect a tree's nodes as if you were doing this: Collect and remove all leaves, repeat until the tree is empty.

Example:
Given binary tree

          1
         / \
        2   3
       / \     
      4   5    

Returns [4, 5, 3], [2], [1].

Explanation:

1. Removing the leaves [4, 5, 3] would result in this tree:

          1
         / 
        2          

2. Now removing the leaf [2] would result in this tree:

          1          

3. Now removing the leaf [1] would result in the empty tree:

          []         

Returns [4, 5, 3], [2], [1]. 
*/

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
  vector<vector<int>> ret;
  vector<vector<int>> findLeaves(TreeNode* root) {
      //DFS, check height, 
      //each level should have same height, like leaf nodes are height 0
      
      int hight= help(root);
      return ret;
      
  }
  //calculate height
  int help(TreeNode* root){
      //make sure leaf are height zero(or one)
      if(root==NULL)
          return 0;
      int height = 1 + max(help(root->left),help(root->right));
      
      //when new height calculated but we do not have vector to represent, init one
      
      if(ret.size()<height){
          vector<int> level;
         ret.push_back(level);
          
      } 
      
      ret[height-1].push_back(root->val);
      
      return height;
      
  }
};
