<!-- START doctoc generated TOC please keep comment here to allow auto update -->
<!-- DON'T EDIT THIS SECTION, INSTEAD RE-RUN doctoc TO UPDATE -->
**Table of Contents**  *generated with [DocToc](https://github.com/thlorenz/doctoc)*

- [Traversal](#traversal)
  - [pre order](#pre-order)
  - [In order](#in-order)
  - [Post order](#post-order)
  - [next node(Descendant Node) via in order traversal](#next-nodedescendant-node-via-in-order-traversal)
- [Sub-Tree problems](#sub-tree-problems)
  - [SubTree of another](#subtree-of-another)
- [Serialize and Deserialize Binary Tree](#serialize-and-deserialize-binary-tree)
- [Morris Traversal](#morris-traversal)
- [adjust two nodes that is switched in BST](#adjust-two-nodes-that-is-switched-in-bst)
- [Recursive to collect information in tree](#recursive-to-collect-information-in-tree)
  - [Tree is Binary tree?](#tree-is-binary-tree)
  - [Find largest BST sub tree in a binary tree](#find-largest-bst-sub-tree-in-a-binary-tree)
  - [Get the max distance between two nodes in Binary Tree](#get-the-max-distance-between-two-nodes-in-binary-tree)
- [Tree topology](#tree-topology)
  - [Find largest BST topology(return number of node in this topology) in Binary tree](#find-largest-bst-topologyreturn-number-of-node-in-this-topology-in-binary-tree)
  - [Dose A tree has B tree in its topology?](#dose-a-tree-has-b-tree-in-its-topology)
  - [Dose A tree has B tree in its subtree?](#dose-a-tree-has-b-tree-in-its-subtree)
  - [Calculate number of nodes in binary tree](#calculate-number-of-nodes-in-binary-tree)
  - [return all possible BST given N](#return-all-possible-bst-given-n)

<!-- END doctoc generated TOC please keep comment here to allow auto update -->

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

## next node(Descendant Node) via in order traversal

* assume there is parent pointer. for any given node, get its next via in order


```CPP
TreeNode* Descendant(TreeNode* node){
  //try to find cur node's right child,
  //then descendant is right child's left most branch

  if(node->right!=NULL){
    return getLeftMost(node->right);
  }else{
    TreeNode* parent = node->parents;
    //if root or current node is parent's left child, return directly
    //otherwise keep on going until condition meet
    while(parent==NULL && parent->left!=node){
      node = parent;
      parent = node->parents;
    }
    return parent;
  }

}

TreeNode* getLeftMost(TreeNode* node){
  if(node->left==NULL)
    return node;
  while(node->left){
    node = node->left;
  }
  return node;
}

```


# Sub-Tree problems

> Key idea is to use recursive to process, with some help function, procee some logic inside help function

## SubTree of another
https://leetcode.com/problems/subtree-of-another-tree/#/description
Given two non-empty binary trees s and t, check whether tree t has exactly the same structure and node values with a subtree of s. A subtree of s is a tree consists of a node in s and all of this node's descendants. The tree s could also be considered as a subtree of itself.
```CPP
bool isSubtree(TreeNode* s, TreeNode* t) {
    if(t==NULL)
        return true;
    if(s==NULL)
        return false;
    return  isSame(s, t) || isSubtree(s->left, t) || isSubtree(s->right, t);
}

bool isSame(TreeNode * ns, TreeNode * nt){
    if(ns==NULL && nt==NULL)
        return true;
    if(ns==NULL || nt==NULL)
        return false;
    if(ns->val!=nt->val)
        return false;

    return isSame(ns->left,nt->left) && isSame(ns->right,nt->right);
}

```

# Serialize and Deserialize Binary Tree

```CPP
string SerializeTree(TreeNode* root){
  string ret;
  SerializeTreeHelper(ret, root);
  return ret;
}

void SerializeTreeHelper(string &s, TreeNode* root){
  if(root==NULL){
    s = s+'#';
    s = s+',';
  }else{
    s = s+to_string(root->val);
    s = s+',';
    SerializeTreeHelper(s,root->left);
    SerializeTreeHelper(s,root->right);
  }
}

TreeNode* DeserializeTree(string s){
  if(s.empty())
    return NULL;
  int index = 0;
  return DeserializeTreehelp(s, index);
}

TreeNode* DeserializeTreehelp(string &s, index &i){
  if(s[index]=='#'){
    index++;
    if(index<s.size()){
      index ++; //pass ','
      return NULL;
    }
  }else{
    TreeNode* node = (TreeNode*)malloc(sizeof(TreeNode));
    string cur = "";
    int start = index;
    while(data[index]!=','){
        index++;
    }
    cur = data.substr(start,index-start);
    node->val = stoi(cur);
    index++; //pass ','

    node->left = DeserializeTreehelp(s,index);
    node->right = DeserializeTreehelp(s,index);

    return node;
  }
}
```

# Morris Traversal

* why we use recursive in tree traveral(pre,in,post): idea is to trversal to current node, node's left and return to current node, node'right and return to current node;
* basically visit the node 3 times
* Morris traveral try to minic recursive, visit node 3 times
* use lots of empty pointer



# adjust two nodes that is switched in BST

* first step is to find two nodes are switched, using in order traversal.
* if plain array is not monotonically increasing, record the beginning of first decreasing subarray and end of last decreasing subarray
* switch these two

```CPP
void recoverTree(TreeNode* root) {
  vector<TreeNode*> tree_array;
  inorderTraveral(tree_array,root);

  //find beginning of first decreasing subarray
  TreeNode* head;
  for(int i=0;i<tree_array.size()-1;i++){
    if(tree_array[i]->val>tree_array[i+1]->val){
      head = tree_array[i];
      break;
    }
  }
  //find the end of last decreasing subarray
  TreeNode* tail;
  for(int i=tree_array.size()-1;i>0;i--){
    if(tree_array[i]->val<tree_array[i-1]->val){
      tail = tree_array[i];
      break;
    }
  }
  if(head == NULL && tail == NULL)
      return;
    int tmp = head->val;
    head->val = tail->val;
    tail->val = tmp;
  }

void inorderTraveral(vector<TreeNode*> &tree_array, TreeNode* root){
  if(root==NULL)
    return;
  inorderTraveral(tree_array,root->left);
  tree_array.push_back(root);
  inorderTraveral(tree_array,root->right);
}
```
# Recursive to collect information in tree

> Key idea is Recursive and collect same information for each node:

>* collect same information for each node, and pass to its parents,
>* information has 3 items: left branch's, right branch's, and sub branch for which current node as root
>* repeat

## Tree is Binary tree?
```CPP
bool isBalanced(TreeNode* root) {
  if(root==NULL)
    return true;

  if(isBalanced(root->left) && isBalanced(root->right)){ //check each branch BST?
    if(abs(height(root->left)-height(root->right))<=1)  //check node as root's sub branch is BST
      return true;
  }

  return false;

}

int height(TreeNode* root){
  if(root==NULL)
    return 0;
  int left = height(root->left);
  int right = height(root->right);

  return max(left,right) +1;
}
```

## Find largest BST sub tree in a binary tree

* For any node, check if its left and right branch is BST
* if yes, max(left)<cur<min(right), then cur node is root of BST, return to next level
* if not, compare left and right

* need to ensure left and right branches return same structure
  * min and max values in branch
  * root of largest BST in branch
  * number of nodes in largest BST in branch
* For current node, after collecting all these information, it can integrate and return same structure to its parents

> Key idea is to build same structure that both current node, left branch and right branch can use and use recursive to collect all information

> Current node needs to be visited/return 3 times, best method is recursive

```CPP
int largestBSTSubtree(TreeNode* root){
  int ret = 0;  //current node as sub tree root, largest BST number
  int min, max; //current node as sub tree root, min and max values in sub BST tree
  bool b = isBST(ret,min,max,root);
  return ret;
}

bool isBST(int &ret, int &min, int &max, TreeNode* root){
  if(!root)
    return true;

  int left_size=0, right_size=0;
  int left_min, left_max, right_min, right_max;

  bool left_b = isBST(left_size,left_min,left_max,root->left);
  bool right_b = isBST(right_size, right_min, right_max, root->right);

  if(left_b && right_b){

    if((!root->left || left_max<root->val) && (!root->right || right_min > root->val)){
      //tree that has current node as root is BST
      ret = left_size+right_size+1;
      min = root->left?left_min:root->val;
      max = root->right?right_max:root->val;
      return true;
    }
  }
  //tree that has current node as root is not BST, then return left or right's largest BST
  ret = left_size>right_size?left_size:right_size;
  return false;
}
```

## Get the max distance between two nodes in Binary Tree

* we can think left depth + itself + right depth is max depth for current node as root
* recursive, every node follow standard, we got all max_depth for all nodes as root

```CPP
//https://leetcode.com/problems/diameter-of-binary-tree/
int diameterOfBinaryTree(TreeNode* root) {
      if(!root)
        return 0;
      int ret = 0;
      help(root,ret);
      return ret-1;  //node number-1
}
int help(TreeNode* root, int &max_depth){
  if(root==NULL)
    return 0;

  int depth_left = help(root->left, max_depth);
  int depth_right = help(root->right, max_depth);
  int depth_cur = depth_left + depth_right + 1; //max length for cur node as root
  max_depth = max(depth_cur, max_depth);
  return max(depth_left,depth_right)+1;  //max branch length for current node/height
}
```
# Tree topology

## Find largest BST topology(return number of node in this topology) in Binary tree

* Topology is not sub tree, we can cut some leaf nodes/branch

## Dose A tree has B tree in its topology?

* check A's node == root of B , then traveral B, and A traversal the same way
* O(M*N): M is node number of A, N is node numer of B

## Dose A tree has B tree in its subtree?

* convert A and B to string, then check whether B's string is a substring of A's string

## Calculate number of nodes in binary tree

## return all possible BST given N

* suppose
