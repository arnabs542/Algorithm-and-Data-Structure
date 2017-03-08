//https://leetcode.com/problems/sum-of-left-leaves/
/*
Find the sum of all left leaves in a given binary tree.

Example:

    3
   / \
  9  20
    /  \
   15   7
There are two left leaves in the binary tree, with values 9 and 15 respectively. Return 24.
*/
//method 1; BFS, check whether it is from left branch
class Solution {
public:
    int sumOfLeftLeaves(TreeNode* root) {
        if(!root)
            return 0;
            //int = 1 means left, int =-1 means right
        queue<pair<TreeNode*,int> > q; 
        int ret = 0;
        //BFS, since in DFS it is hard to differenicate whether leave is from left or right branch
        q.push(make_pair(root,0));//if we only have root, it is not left leave or right leave
        while(!q.empty()){
            int len = q.size();

            TreeNode* cur = q.front().first;
            int branch = q.front().second;
            if(cur->left){
                q.push(make_pair(cur->left,1));
            }
            if(cur->right){
                q.push(make_pair(cur->right,-1));
            }
            //make sure it is leave and left
            if(branch==1 && !cur->left && !cur->right)
                ret+=q.front().first->val;
            q.pop();
        }
        return ret;
    }
};

//method 2. recursive, more efficient
class Solution {
public:
    int sumOfLeftLeaves(TreeNode* root) {
        if(!root)
            return 0;
        return help(root,false);

    }
    
    int help(TreeNode* root, bool left){
        if(!root)
            return 0;
        if(!root->left && !root->right)
            return left==true?root->val:0;
        return help(root->left,true)+help(root->right,false);
    }
};
