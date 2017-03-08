https://leetcode.com/problems/sum-root-to-leaf-numbers/

class Solution {
public:
    int sumNumbers(TreeNode* root) {
        string path = "";
        int sum = 0;
        if(root==NULL)
            return sum;
        sum_tree(root,path,sum);
        return sum;
    }
    
    void sum_tree(TreeNode* root, string path, int& sum){
        if(root==NULL){
            return;
        }
        path = path + to_string(root->val);
        if(root->left==NULL && root->right==NULL){
            sum = sum + stoi(path);
            return;
        }
        sum_tree(root->left,path ,sum);
        sum_tree(root->right, path,sum);
    }
}
