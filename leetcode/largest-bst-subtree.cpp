//https://leetcode.com/problems/largest-bst-subtree/#/description
class Solution {
public:
    int largestBSTSubtree(TreeNode* root){
      int ret = 0;  //current node as sub tree root, largest BST number
      int min, max; //current node as sub tree root, min and max values in sub BST tree
      bool b = isBST(ret,min,max,root);
      return ret;
    }

    bool isBST(int &ret, int &min, int &max, TreeNode* root){
      if(!root)
        return true;

      int left_size=0, right_size=0;
      int left_min, left_max, right_min, right_max;

      bool left_b = isBST(left_size,left_min,left_max,root->left);
      bool right_b = isBST(right_size, right_min, right_max, root->right);

      if(left_b && right_b){

        if((!root->left || left_max<root->val) && (!root->right || right_min > root->val)){
          //tree that has current node as root is BST
          ret = left_size+right_size+1;
          min = root->left?left_min:root->val;
          max = root->right?right_max:root->val;
          return true;
        }
      }
      //tree that has current node as root is not BST, then return left or right's largest BST
      ret = left_size>right_size?left_size:right_size;
      return false;
    }
};
