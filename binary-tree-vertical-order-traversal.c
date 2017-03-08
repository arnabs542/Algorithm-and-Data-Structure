//https://leetcode.com/problems/binary-tree-vertical-order-traversal/
/*
Given a binary tree, return the vertical order traversal of its nodes' values. (ie, from top to bottom, column by column).
If two nodes are in the same row and column, the order should be from left to right.

Examples:
    Given binary tree [3,9,20,null,null,15,7],
       3
      /\
     /  \
     9  20
        /\
       /  \
      15   7
    return its vertical order traversal as:
    [
      [9],
      [3,15],
      [20],
      [7]
    ]
    Given binary tree [3,9,8,4,0,1,7],
         3
        /\
       /  \
       9   8
      /\  /\
     /  \/  \
     4  01   7
    return its vertical order traversal as:
    [
      [4],
      [9],
      [3,0,1],
      [8],
      [7]
    ]
    Given binary tree [3,9,8,4,0,1,7,null,null,null,2,5] (0's right child is 2 and 1's left child is 5),
         3
        /\
       /  \
       9   8
      /\  /\
     /  \/  \
     4  01   7
        /\
       /  \
       5   2
    return its vertical order traversal as:
    [
      [4],
      [9,5],
      [3,0,1],
      [8,2],
      [7]
    ]
*/
class Solution {
public:
    vector<vector<int>> verticalOrder(TreeNode* root) {
        //hash table: key is shift, val is node, left child shift-1, right child shift+1
        //use map instead of unordered_map to sort key
        //use level traversal, so insure the high level nodes are print first
        map<int,vector<int>> m;
        vector<vector<int>> ret;
        if(root==NULL)
            return ret;
        //level traversal  
        //queue: first is node, second is its shift
        queue<pair<TreeNode*,int>> q;
        q.push(make_pair(root,0));
        while(!q.empty()){
            pair<TreeNode*,int> cur = q.front();
            m[cur.second].push_back(cur.first->val);
            if(cur.first->left){
                q.push(make_pair(cur.first->left,cur.second-1)); //left subtree
            }
            if(cur.first->right){
                q.push(make_pair(cur.first->right,cur.second+1)); //left subtree
            }
            q.pop();
        }
        for(auto i:m){
            ret.push_back(i.second);
        }
        return ret;
    }
};
