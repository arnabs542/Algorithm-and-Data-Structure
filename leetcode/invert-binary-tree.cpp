//https://leetcode.com/problems/invert-binary-tree/#/description
/*
Invert a binary tree.

     4
   /   \
  2     7
 / \   / \
1   3 6   9
to
     4
   /   \
  7     2
 / \   / \
9   6 3   1
*/

TreeNode* invertTree(TreeNode* root) {
    if(root==NULL)
        return NULL;

    TreeNode*tmp = root->left;
    root->left = invertTree(root->right);
    root->right = invertTree(tmp);

    return root;
}

//method 2: iterative: BFS
TreeNode* invertTree(TreeNode* root) {
    if(root==NULL)
        return NULL;
    TreeNode* ret = root;
    TreeNode* left;
    TreeNode* right;
    queue<TreeNode*> q;
    q.push(root);
    while(!q.empty()){
        TreeNode* cur = q.front();
        q.pop();
        left = cur->left;
        right = cur->right;
        cur->left = right;
        cur->right = left;
        if(left)
            q.push(left);
        if(right)
            q.push(right);

    }
    return ret;
}

//We can also use stack
TreeNode* invertTree(TreeNode* root) {
    if(root==NULL)
        return NULL;
    TreeNode* ret = root;
    TreeNode* left;
    TreeNode* right;
    stack<TreeNode*> s;
    s.push(root);
    while(!s.empty()){
        TreeNode* cur = s.top();
        s.pop();
        left = cur->left;
        right = cur->right;
        cur->left = right;
        cur->right = left;
        if(left)
            s.push(left);
        if(right)
            s.push(right);


    }
    return ret;
}
