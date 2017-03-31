//https://leetcode.com/problems/recover-binary-search-tree/

class Solution {
public:
    void recoverTree(TreeNode* root) {
      vector<TreeNode*> tree_array;
      inorderTraveral(tree_array,root);

      //find beginning of first decreasing subarray
      TreeNode* head;
      for(int i=0;i<tree_array.size()-1;i++){
        if(tree_array[i]->val>tree_array[i+1]->val){
          head = tree_array[i];
          break;
        }
      }
      //find the end of last decreasing subarray
      TreeNode* tail;
      for(int i=tree_array.size()-1;i>0;i--){
        if(tree_array[i]->val<tree_array[i-1]->val){
          tail = tree_array[i];
          break;
        }
      }
    if(head == NULL && tail == NULL)
        return;
      int tmp = head->val;
      head->val = tail->val;
      tail->val = tmp;
    }

    void inorderTraveral(vector<TreeNode*> &tree_array, TreeNode* root){
      if(root==NULL)
        return;
      inorderTraveral(tree_array,root->left);
      tree_array.push_back(root);
      inorderTraveral(tree_array,root->right);
    }
};
