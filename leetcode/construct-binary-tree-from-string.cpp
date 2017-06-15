/*
https://leetcode.com/problems/construct-binary-tree-from-string/#/description

You need to construct a binary tree from a string consisting of parenthesis and integers.
The whole input represents a binary tree. It contains an integer followed by zero, one or two pairs of parenthesis. The integer represents the root's value and a pair of parenthesis contains a child binary tree with the same structure.
You always start to construct the left child node of the parent first if it exists.

Example:
Input: "4(2(3)(1))(6(5))"
Output: return the tree root node representing the following tree:

       4
     /   \
    2     6
   / \   /
  3   1 5
*/

TreeNode* str2tree(string s) {
    int i=0;
    return s.size()==0?NULL:help(s,i);
}

TreeNode* help(string &s, int& i){
    int sign = 1;
    if(s[i]=='-'){
        i++;
        sign = -1;
    }
    int num = 0;
    while(isdigit(s[i])){
        num = num*10+s[i]-'0';
        i++;
    }
    num = num*sign;

    TreeNode* node = new TreeNode(num);
    //utilize the feature that each level each node will meet two '(', the first is left and second is right
    if (s[i] == '(') {
        node->left = help(s, ++i);
        i++;    // )
    }
    if (s[i] == '(') {
        node->right = help(s, ++i);
        i++;    // )
    }
    return node;
}
