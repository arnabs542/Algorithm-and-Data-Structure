//https://leetcode.com/problems/binary-tree-level-order-traversal-ii/
/*
Given a binary tree, return the bottom-up level order traversal of its nodes' values. (ie, from left to right, level by level from leaf to root).

For example:
Given binary tree [3,9,20,null,null,15,7],
    3
   / \
  9  20
    /  \
   15   7
return its bottom-up level order traversal as:
[
  [15,7],
  [9,20],
  [3]
]
*/

class Solution {
public:
    vector<vector<int>> levelOrderBottom(TreeNode* root) {
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
        reverse(ret.begin(),ret.end());
        return ret;        
    }
};
