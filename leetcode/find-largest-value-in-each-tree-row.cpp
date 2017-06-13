/*
https://leetcode.com/problems/find-largest-value-in-each-tree-row/#/description
You need to find the largest value in each row of a binary tree.

Example:
Input:

          1
         / \
        3   2
       / \   \
      5   3   9

Output: [1, 3, 9]
*/

vector<int> largestValues(TreeNode* root) {
    //BFS with level information
    queue<TreeNode*> q;
    vector<int> ret;
    if(root==NULL)
        return ret;
    q.push(root);
    while(!q.empty()){
        int max_level = INT_MIN;
        int len = q.size();
        for(int i=0;i<len;i++){
            TreeNode* cur=q.front();
            max_level = max(max_level,cur->val);
            if(cur->left){
                q.push(cur->left);
            }
            if(cur->right){
                q.push(cur->right);
            }
            q.pop();
        }
        ret.push_back(max_level);

    }
    return ret;
}
