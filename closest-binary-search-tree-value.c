//https://leetcode.com/problems/closest-binary-search-tree-value/
//recursive
class Solution {
public:
  int closestValue(TreeNode* root, double target) {
      /* 
      found the value via in order traverse, maintain cur and next, until cur<target<next or next<target<cur 
      */
      int cur = root->val;
      if(cur>target){
          root = root->left;
      }else{
          root = root->right;
      }
      if(root==NULL)
          return cur;
      int next = closestValue(root, target);
      
      return abs(cur-target)>abs(next-target)?next:cur;
  }
};

//iterative
class Solution {
public:
  int closestValue(TreeNode* root, double target) {
      /* 
      found the value via in order traverse, maintain cur and next, until cur<target<next or next<target<cur 
      */
      int cloest = root->val;
      while(root!=NULL){
          if(abs(cloest - target) >= abs(root->val- target))
              cloest = root->val;
          
          if(root->val>target){
              root = root->left;
          }else{
              root = root->right;
          }
      }
      return cloest;
  }

};
