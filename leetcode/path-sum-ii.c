//https://leetcode.com/problems/path-sum-ii/
/*
 Given a binary tree and a sum, find all root-to-leaf paths where each path's sum equals the given sum.
For example:
Given the below binary tree and sum = 22,

              5
             / \
            4   8
           /   / \
          11  13  4
         /  \    / \
        7    2  5   1

return

[
   [5,4,11,2],
   [5,8,4,5]
]
*/
class Solution {
public:
    vector<vector<int>> pathSum(TreeNode* root, int sum) {
        vector<vector<int>> ret;
        vector<int> onepath;
        if(root)
            DFS(root,ret,onepath,sum-root->val);
        return ret;
        
    }
    
    void DFS(TreeNode* root, vector<vector<int>> &ret,vector<int> onepath, int target){
        onepath.push_back(root->val);
        
        if((target == 0) && !root->left && !root->right){
            ret.push_back(onepath);
            return;
        }
        
        if(root->left)
            DFS(root->left,ret,onepath,target-(root->left->val));
        if(root->right)
            DFS(root->right,ret,onepath,target-(root->right->val));
        
    }
};


//if we use reference instead of parameter, then we need to pop, but it save lots of memeory
class Solution {
public:
    vector<vector<int>> pathSum(TreeNode* root, int sum) {
        vector<vector<int>> ret;
        vector<int> one;
        if(root)
            help(ret,one,sum-root->val,root);
        return ret;
    }
    
    void help(vector<vector<int>> &ret, vector<int> &one, int sum, TreeNode* root){
        one.push_back(root->val);
        //reach the leaf node and sum to target
        if(sum==0 && !root->left && !root->right){
            ret.push_back(one);
            return;
        }
        
        if(root->left){
            help(ret,one,sum-(root->left->val),root->left);
            one.pop_back();
            
        }
        if(root->right){
            help(ret,one,sum-(root->right->val),root->right);
            one.pop_back();
        }
        
    }
};
