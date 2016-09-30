//https://leetcode.com/problems/binary-tree-postorder-traversal/
class Solution {
public:
    vector<int> postorderTraversal(TreeNode* root) {
        vector<int> ret;
        stack<TreeNode*> s;
        //push root-right-left, then reverse
        while(true){
            while(root){
                s.push(root);
                ret.push_back(root->val);
                root = root->right;
            }
            if(s.empty())
                break;
            root = s.top()->left;
            s.pop();
        }
        reverse(ret.begin(),ret.end());
        return ret;
    }
};
