//https://leetcode.com/problems/two-sum-iv-input-is-a-bst/description/
/*
Given a Binary Search Tree and a target number, return true if there exist two elements in the BST such that their sum is equal to the given target.

Example 1:
Input:
    5
   / \
  3   6
 / \   \
2   4   7

Target = 9

Output: True
Example 2:
Input:
    5
   / \
  3   6
 / \   \
2   4   7

Target = 28

Output: False
*/

bool findTarget(TreeNode* root, int k) {
    vector<int> v;
    tree2vec(v,root);
    int l = 0;
    int r = v.size()-1;
    while(l<r){
        if(v[l]+v[r]<k){
            l++;
        }else if(v[l]+v[r]>k){
            r--;
        }else{
            return true;
        }
    }

    return false;

}

void tree2vec(vector<int> &v, TreeNode* root){
    if(root->left)
        tree2vec(v,root->left);
    v.push_back(root->val);
    if(root->right)
        tree2vec(v,root->right);
}


//method 2

bool findTarget(TreeNode* root, int k) {
    unordered_set<int> set;
    return dfs(root, set, k);
}

bool dfs(TreeNode* root, unordered_set<int>& set, int k){
    if(root == NULL)return false;
    if(set.count(k - root->val))return true;
    set.insert(root->val);
    return dfs(root->left, set, k) || dfs(root->right, set, k);
}
