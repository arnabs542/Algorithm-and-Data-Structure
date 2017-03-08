//https://leetcode.com/problems/flatten-binary-tree-to-linked-list/
//method 1: recursive
void flatten(TreeNode* root) {
    //idea is to branch root(cur node)'s left child's right most to root->right, recursive
    if (root==NULL) return;
    flatten(root->left);
    flatten(root->right);
    
    TreeNode* tmp=root->right;
    root->right = root->left;
    root->left = NULL;
    //to the left's most right.
    while(root->right){
        root = root->right;
    }
    root->right = tmp;
}

//method 2: iterative: same idea as method 1
void flatten(TreeNode* root) {
    if (root==NULL) return;
    TreeNode * cur=root, * prev;
    while (cur) {
        if (cur->left==NULL) 
            cur=cur->right;
        else {
            prev=cur->left;
            while(prev->right) 
                prev=prev->right;
            prev->right=cur->right;
            cur->right=cur->left;
            cur->left=NULL;
        }
    }
}

