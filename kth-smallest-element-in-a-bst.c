//https://leetcode.com/problems/kth-smallest-element-in-a-bst/
/*
Given a binary search tree, write a function kthSmallest to find the kth smallest element in it.
*/
//method 1: ierative
class Solution {
public:
    int kthSmallest(TreeNode* root, int k) {
        //in order traversal
        stack<TreeNode*> s;
        int ret = 0;
        while(true){
            while(root){
                s.push(root);
                root=root->left;
            }
            k--;
            root = s.top()->right;
            
            if(k==0){
                break;
            }
            s.pop();
            
        }
        return s.top()->val;
        
    }
};

//recursive
class Solution {
private:
    int cnt=0;
    int num;
public:
    int kthSmallest(TreeNode* root, int k) {
        cnt = k;
        help(root);
        return num;
    }
    
    void help(TreeNode* root){
        if(cnt>0){
            if(root->left)
                help(root->left);
            cnt--;
            if(cnt==0){
                num = root->val;
                return;
            }
            if(root->right)
                help(root->right);  
        }
    }
};
