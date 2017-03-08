//https://leetcode.com/problems/binary-tree-level-order-traversal/
/*
Given a binary tree, return the level order traversal of its nodes' values. (ie, from left to right, level by level).

For example:
Given binary tree [3,9,20,null,null,15,7],
    3
   / \
  9  20
    /  \
   15   7
return its level order traversal as:
[
  [3],
  [9,20],
  [15,7]
]
*/

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
 
 //use queue size to record num of nodes in each level
 
class Solution {
public:
    vector<vector<int>> levelOrder(TreeNode* root) {
        vector<vector<int>> ret;
        vector<int> one;
        if(!root)
            return ret;
        
        queue<TreeNode*> q;
        q.push(root);
        while(!q.empty()){
            //use queue size to check each level size
            int len = q.size();
            for(int i=0;i<len;i++){
                TreeNode* cur = q.front();
                q.pop();
                one.push_back(cur->val);
                if(cur->left)
                    q.push(cur->left);
                if(cur->right)
                    q.push(cur->right);
            }
            ret.push_back(one);
            one.clear();
        }
        return ret;
    }
};
