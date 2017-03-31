//https://leetcode.com/problems/diameter-of-binary-tree/

class Solution {
public:
    int diameterOfBinaryTree(TreeNode* root) {
          if(!root)
            return 0;
          int ret = 0;
          help(root,ret);
          return ret-1;
    }
    int help(TreeNode* root, int &max_depth){
      if(root==NULL)
        return 0;

      int depth_left = help(root->left, max_depth);
      int depth_right = help(root->right, max_depth);
      int depth_cur = depth_left + depth_right + 1;
      max_depth = max(depth_cur, max_depth);
      return max(depth_left,depth_right)+1;
    }
};
