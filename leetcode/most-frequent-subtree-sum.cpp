/*
https://leetcode.com/problems/most-frequent-subtree-sum/#/description

Given the root of a tree, you are asked to find the most frequent subtree sum. The subtree sum of a node is defined as the sum of all the node values formed by the subtree rooted at that node (including the node itself). So what is the most frequent subtree sum value? If there is a tie, return all the values with the highest frequency in any order.

Examples 1
Input:

  5
 /  \
2   -3
return [2, -3, 4], since all the values happen only once, return all of them in any order.
Examples 2
Input:

  5
 /  \
2   -5
return [2], since 2 happens twice, however -5 only occur once.
Note: You may assume the sum of values in any subtree is in the range of 32-bit signed integer.
*/

vector<int> findFrequentTreeSum(TreeNode* root) {
    map<int,int> m;
    vector<int> ret;
    if(root==NULL)
        return ret;
    int max_cnt = 0;
    int sum = help(root,m,max_cnt);

    for(auto i:m){
        if(i.second==max_cnt){
            ret.push_back(i.first);
        }
    }
    return ret;

}

int help(TreeNode* root, map<int,int> &m, int &max_cnt){
    int ret = root->val;
    if(root->left){
        ret += help(root->left,m,max_cnt);
    }
    if(root->right){
        ret += help(root->right,m,max_cnt);
    }

    max_cnt = max(++m[ret],max_cnt);
    return ret;
}
