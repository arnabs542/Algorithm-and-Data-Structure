//https://leetcode.com/problems/minimum-absolute-difference-in-bst/#/description
/*
Given a binary search tree with non-negative values, find the minimum absolute difference between values of any two nodes.
Example:
Input:

   1
    \
     3
    /
   2

Output:
1
Explanation:
The minimum absolute difference is 1, which is the difference between 2 and 1 (or between 2 and 3).
*/

int getMinimumDifference(TreeNode* root) {
    int diff = INT_MAX, val =INT_MAX;
    help_inorder(root,val,diff);
    return diff;
}

void help_inorder(TreeNode* root, int &val, int &diff){
    if(root->left)
        help_inorder(root->left,val,diff);
    diff = min(diff,abs(root->val-val));
    val = root->val;
    if(root->right)
        help_inorder(root->right,val,diff);
}

//method 2:
int diff = INT_MAX;
int val = INT_MAX;
int getMinimumDifference(TreeNode* root) {
    if(root->left) getMinimumDifference(root->left);
    diff = min(diff,abs(root->val-val));
    val = root->val;
    if (root->right) getMinimumDifference(root->right);
    return diff;
}
