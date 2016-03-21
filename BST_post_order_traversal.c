//https://leetcode.com/problems/binary-tree-postorder-traversal/
//http://articles.leetcode.com/binary-tree-post-order-traversal
//Method 1: recursive
vector<int> postorderTraversal(TreeNode* root) {
    vector<int> ret;
    if(root == NULL)
        return ret;
    post_help(root,ret);
    return ret;
}

void post_help(TreeNode* root, vector<int> &ret){
    if(root== NULL)
        return;
    if(root->left)
        post_help(root->left,ret);
    if(root->right)
        post_help(root->right,ret);
    ret.push_back(root->val);
}

//method 2: iterative: when traversal to left end, needs to travel up and travel to right again before visit root.
//so need two nodes to check whether it is go down to go up
vector<int> postorderTraversal(TreeNode* root) {
    //The key point is when travel to leaf nodes, and then travel back to upper level
    //upper level will be re visited, need to mark re visited
    vector<int> ret;
    if(root == NULL)
        return ret;
    TreeNode* cur;
    stack<TreeNode*> s;
    s.push(root);
    TreeNode* prev = NULL;
    while(!s.empty()){
        cur = s.top();
        if(!prev || prev->left==cur || prev->right == cur){// go down the tree
            if(cur->left){
                s.push(cur->left);
            }else if(cur->right){
                s.push(cur->right);
            }
        }else if(cur->left==prev){//search up from left subtree
            if(cur->right){
                s.push(cur->right);
            }
        }else{//search up from right tree, or reach to leaf 
            ret.push_back(cur->val);
            s.pop();
        }
        prev = cur;
    }
   return ret; 
}

//method3: use reversed pre order
vector<int> postorderTraversal(TreeNode* root) {
    stack<TreeNode*> s; 
    vector<int> ret;
    if(root!=NULL) s.push(root);
    while(!s.empty()) {
        TreeNode *cur = s.top();
        s.pop();
        ret.push_back(cur->val);
        if(cur->left) s.push(cur->left);
        if(cur->right) s.push(cur->right);
    }
    reverse(ret.begin(),ret.end());
    return ret;
}

//method 4: same as reversed pre order, use two stacks
vector<int> postorderTraversal(TreeNode* root) {
    stack<TreeNode*> s;
    stack<TreeNode*> out;
    vector<int> ret;
    if(root!=NULL) s.push(root);
    while(!s.empty()) {
        TreeNode *cur = s.top();
        out.push(cur);
        s.pop();
        if(cur->left) s.push(cur->left);
        if(cur->right) s.push(cur->right);
    }
    while(!out.empty()){
        ret.push_back(out.top()->val);
        out.pop();
    }
    return ret;
}
