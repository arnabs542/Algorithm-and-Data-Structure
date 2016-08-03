//https://leetcode.com/problems/inorder-successor-in-bst/
//method 1: iterative
class Solution {
public:
  TreeNode* inorderSuccessor(TreeNode* root, TreeNode* p) {
      /*
      root.val > p.val. In this case, root can be a possible answer, so we store the root node first and call it res. However, we don't know if there is anymore node on root's left that is larger than p.val. So we move root to its left and check again.

      root.val <= p.val. In this case, root cannot be p's inorder successor, neither can root's left child. So we only need to consider root's right child, thus we move root to its right and check again.
      */
      TreeNode* ret;
      while(root!=NULL){
          if(root->val<=p->val){
              root = root->right;
          }else{
              ret = root;
              root = root->left;
          }
          
      }
      return ret;
  }
};

//method 2: recursive
class Solution {
public:
  TreeNode* inorderSuccessor(TreeNode* root, TreeNode* p) {
      if(root == NULL)
          return NULL;
      if(root->val<=p->val){
          return inorderSuccessor(root->right,p);
      }else{
          TreeNode* left = inorderSuccessor(root->left,p);
          if(left==NULL)
              return root;
          else
              return left;
      }
  }
};
