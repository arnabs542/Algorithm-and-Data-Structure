//https://leetcode.com/problems/average-of-levels-in-binary-tree/#/description
/*
Given a non-empty binary tree, return the average value of the nodes on each level in the form of an array.
Example 1:
Input:
    3
   / \
  9  20
    /  \
   15   7
Output: [3, 14.5, 11]
Explanation:
The average value of nodes on level 0 is 3,  on level 1 is 14.5, and on level 2 is 11. Hence return [3, 14.5, 11].
*/

vector<double> averageOfLevels(TreeNode* root) {
    queue<TreeNode*> q;
    vector<double> ret;
    if(root==NULL)
        return ret;

    q.push(root);
    while(!q.empty()){
        int len = q.size();
        double sum = 0;
        for(int i=0;i<len;i++){
            TreeNode* cur = q.front();
            sum+=cur->val;
            q.pop();
            if(cur->left) q.push(cur->left);
            if(cur->right) q.push(cur->right);
        }
        ret.push_back(sum/len);
    }
    return ret;
}
