/*
https://leetcode.com/problems/construct-string-from-binary-tree/#/description
You need to construct a string consists of parenthesis and integers from a binary tree with the preorder traversing way.

The null node needs to be represented by empty parenthesis pair "()". And you need to omit all the empty parenthesis pairs that don't affect the one-to-one mapping relationship between the string and the original binary tree.

Example 1:
Input: Binary tree: [1,2,3,4]
       1
     /   \
    2     3
   /
  4

Output: "1(2(4))(3)"

Explanation: Originallay it needs to be "1(2(4)())(3()())",
but you need to omit all the unnecessary empty parenthesis pairs.
And it will be "1(2(4))(3)".
Example 2:
Input: Binary tree: [1,2,3,null,4]
       1
     /   \
    2     3
     \
      4

Output: "1(2()(4))(3)"

Explanation: Almost the same as the first example,
except we can't omit the first parenthesis pair to break the one-to-one mapping relationship between the input and the output.
*/

string tree2str(TreeNode* t) {
    string ret = "";
    if(t==NULL)
        return ret;
    ret+=to_string(t->val);
    help(t,ret);
    return ret;

}

void help(TreeNode* root, string &ret){
    if(root->left!=NULL){
        ret+="(";
        ret+=to_string(root->left->val);
        help(root->left,ret);
        ret+=")";
    }else{
        if(root->right)
            ret+="()";
    }

    if(root->right!=NULL){
        ret+="(";
        ret+=to_string(root->right->val);
        help(root->right,ret);
        ret+=")";
    }
}
