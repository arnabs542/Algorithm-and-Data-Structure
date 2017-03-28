# Traversal

## pre order
* For a given node, push into stack, order is center, right, left
* pop the stack and print right away, repeat step 1 for popped value

```CPP
void preorder(TreeNode* root){
  stack<int> s;
  s.push(root);
  while(!s.empty()){
    TreeNode* cur = s.top();
    s.pop();
    printf("node is %d",cur->val);
    if(cur->right){
      s.push(root->right);
    }
    if(cur->left){
      s.push(root->left);
    }
  }
}
```
## In order
* For any node, first push whole left edge of node
* if there is no left branch then pop one, move to right node, and repeat step 1
* Basic idea is to parse the tree into different levels of left(or right) edges
```CPP
void inOrder(TreeNode* root){
  stack<int> s;
  while(!s.empty() || root!=NULL){
    if(root!=NULL){
      s.push(root);
      root = root->left;
    }else{
      TreeNode* cur = s.top();
      printf("node is %d",cur->val);
      s.pop();
      root = cur->right;
    }
  }
}
```

## Post order
* In pre order case, we print out center, left, right. post order requires left, right, center
* so we can push stack center, right, left, and reverse use another stack
```CPP
void postOrder(TreeNode* root){
  stack<int> s1, s2;
  s1.push(root);
  while(!1s.empty()){
    TreeNode* cur = s1.top();
    s1.pop();
    s2.push(cur);
    if(cur->left){
      s1.push(root->left);
    }
    if(cur->right){
      s1.push(root->right);
    }
  }
  while(!s2.empty()){
    printf("node is %d",s2.top()->val);
    s2.pop();
  }
}
```

* Method 2: Only to use one stack. The advantage of using stack is you can always returns to last visited node
