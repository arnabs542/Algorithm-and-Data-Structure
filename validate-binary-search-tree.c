//https://leetcode.com/problems/validate-binary-search-tree/
//method 1: iterative
class Solution {
public:
  bool isValidBST(TreeNode *root) {
      if(root==NULL)
          return true;
      //Iterative, Since in order traverse of BST should be an array in ascend order
      stack<TreeNode*> s;
      TreeNode *node = root;
      TreeNode *cur;
      //long min=LONG_MIN;
      while(!s.empty() || node){
          while(node){
              s.push(node);
              node = node->left;
          }
          cur = s.top();
          s.pop();
          if(cur->val <s.top()->val){
              node = cur->right;
          }else{
              return false;
          }
          
      }
      
      return true;
  }
};

//method 2: recursive:
#include <climits>
class Solution {
public:
  bool isValidBST(TreeNode *root) {
      
      if(root == NULL)
          return true;
      
      return isBSThelper(root,LONG_MIN,LONG_MAX);

  }
  bool isBSThelper(TreeNode *root, long min, long max){
      if(root==NULL)
          return true;
      if(root->val>min && root->val <max){
          return isBSThelper(root->left, min,root->val) && isBSThelper(root->right,root->val,max);
      }else{
          return false;
      }
  }
};
