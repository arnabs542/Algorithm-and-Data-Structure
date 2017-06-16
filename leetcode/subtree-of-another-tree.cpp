/*
https://leetcode.com/problems/subtree-of-another-tree/#/description
Given two non-empty binary trees s and t, check whether tree t has exactly the same structure and node values with a subtree of s. A subtree of s is a tree consists of a node in s and all of this node's descendants. The tree s could also be considered as a subtree of itself.

Example 1:
Given tree s:

     3
    / \
   4   5
  / \
 1   2
Given tree t:
   4
  / \
 1   2
Return true, because t has the same structure and node values with a subtree of s.
Example 2:
Given tree s:

     3
    / \
   4   5
  / \
 1   2
    /
   0
Given tree t:
   4
  / \
 1   2
Return false.
*/

bool isSubtree(TreeNode* s, TreeNode* t) {
    if(t==NULL)
        return true;
    if(s==NULL)
        return false;
    return  isSame(s, t) || isSubtree(s->left, t) || isSubtree(s->right, t);
}

bool isSame(TreeNode* ns, TreeNode *nt){
    if(ns==NULL && nt==NULL)
        return true;
    if(ns==NULL || nt==NULL)
        return false;
    if(ns->val!=nt->val)
        return false;

    return isSame(ns->left,nt->left) && isSame(ns->right,nt->right);
}
