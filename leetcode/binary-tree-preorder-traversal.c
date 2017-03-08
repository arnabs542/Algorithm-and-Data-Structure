//https://leetcode.com/problems/binary-tree-preorder-traversal/
//recursive is easy, here is ierative 
class Solution {
public:
    vector<int> preorderTraversal(TreeNode* root) {
        vector<int> ret;
        stack<TreeNode*> s;
        while(true){
            while(root){
                s.push(root);
                ret.push_back(s.top()->val);
                root = root->left;
            }
            if(s.empty())
                break;
            root = s.top()->right;
            s.pop();
        }
        return ret;
    }
};
