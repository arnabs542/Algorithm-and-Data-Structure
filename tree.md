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

* In Post order traversal, we would like to revisit this node 3 times
  * first occur, push stack, then go to left branch
  * finished left branch, then return to current node and process right branch
  * after process right branch, return to current node and finally print

* use an extra node prev to indicate prev printed node
  * if prev is left child, means left branch has been visited, go to right branch
  * else if prev is right child, means both left and right branches are visited. go up and process current, and pop
  * if prev is not left nor right, which means left branches is not processed yet, go left

```CPP
void postOrder(TreeNode* root){
  TreeNode* prev = root;
  TreeNode* cur = NULL;
  stack<TreeNode*> s;
  s.push(root);
  while(!s.empty()){
    cur = s.top();
    if(cur->left!=NULL && prev !=cur->left && prev!=cur->right){
      //still not visited cur's both branches
      s.push(cur->left);
    }else if(cur->right!=NULL && prev!=cur->right){
      //finished left branch, see if we can go right branch
      s.push(cur->right);
    }else{
      printf("node is %d\n", cur->val);
      prev = cur;
      s.pop();
    }
  }
}
```

# Serialize and Deserialize Binary Tree 
