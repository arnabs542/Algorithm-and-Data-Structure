<!-- START doctoc generated TOC please keep comment here to allow auto update -->
<!-- DON'T EDIT THIS SECTION, INSTEAD RE-RUN doctoc TO UPDATE -->
**Table of Contents**  *generated with [DocToc](https://github.com/thlorenz/doctoc)*

- [Traversal](#traversal)
  - [pre order](#pre-order)
  - [In order](#in-order)
  - [Post order](#post-order)
  - [In order in BST and its variation](#in-order-in-bst-and-its-variation)
    - [In order traverse pattern](#in-order-traverse-pattern)
    - [next node(Descendant Node) via in order traversal](#next-nodedescendant-node-via-in-order-traversal)
    - [K-th Smallest](#k-th-smallest)
    - [Range problem](#range-problem)
    - [Closest value](#closest-value)
- [Sub-Tree problems](#sub-tree-problems)
  - [SubTree of another](#subtree-of-another)
- [Tree to Array/String](#tree-to-arraystring)
  - [Array to Tree](#array-to-tree)
  - [Reconstruct Tree](#reconstruct-tree)
    - [Re construct Tree from in-order and pre-order](#re-construct-tree-from-in-order-and-pre-order)
  - [Serialize and Deserialize Binary Tree](#serialize-and-deserialize-binary-tree)
  - [](#)
- [Traversal](#traversal-1)
  - [BFS](#bfs)
  - [DFS](#dfs)
  - [Morris Traversal](#morris-traversal)
- [BST](#bst)
  - [Common Logic](#common-logic)
  - [Insert/Find/Delete Node](#insertfinddelete-node)
    - [Find](#find)
    - [Insert](#insert)
    - [Delete](#delete)
  - [Tree is Balanced Binary tree?](#tree-is-balanced-binary-tree)
  - [Valid BST](#valid-bst)
  - [Recover BST](#recover-bst)
  - [Find largest BST sub tree in a binary tree](#find-largest-bst-sub-tree-in-a-binary-tree)
  - [Get the max distance between two nodes in Binary Tree](#get-the-max-distance-between-two-nodes-in-binary-tree)
- [Tree topology](#tree-topology)
  - [Find largest BST topology(return number of node in this topology) in Binary tree](#find-largest-bst-topologyreturn-number-of-node-in-this-topology-in-binary-tree)
  - [Dose A tree has B tree in its topology?](#dose-a-tree-has-b-tree-in-its-topology)
  - [Dose A tree has B tree in its subtree?](#dose-a-tree-has-b-tree-in-its-subtree)
  - [Calculate number of nodes in binary tree](#calculate-number-of-nodes-in-binary-tree)
  - [return all possible BST given N](#return-all-possible-bst-given-n)
- [Trie/prefix Tree](#trieprefix-tree)

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

Follow up: Inorder Successor in BST

https://leetcode.com/problems/inorder-successor-in-bst/

```CPP
TreeNode* inorderSuccessor(TreeNode* root, TreeNode* p) {

    TreeNode* ret;
    while(root!=NULL){
        if(root->val<=p->val){
            root = root->right;
        }else{
            ret = root;
            root = root->left;
        }
    }

    return ret;
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

##  In order in BST and its variation 

in general can be used as formation of

```CPP
stack<Treenode* node> s;
s.push(root)
while(!s.empty()){
  //Go to leftmost
  while(node->left){
      node = node->left;
      s.push(node);
  }
  //mark(could be print, count, any operation)
  print(s.top());
  //Go to right
  node = s.top()->right;
  //processed current, pop
  s.pop();
  
}

```

### In order traverse pattern

```CPP
void traverse(TreeNode *root) {
    //did some thing
    traverse(root->left);
    traverse(root->right);
}
```





### next node(Descendant Node) via in order traversal

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

### K-th Smallest

https://leetcode.com/problems/kth-smallest-element-in-a-bst/

```CPP
//https://leetcode.com/problems/kth-smallest-element-in-a-bst/
/*
Given a binary search tree, write a function kthSmallest to find the kth smallest element in it.
*/
//method 1: ierative
class Solution {
public:
  int kthSmallest(TreeNode* root, int k) {
    //in order traversal
    stack<TreeNode*> s;
    int cnt = 0;
    int ret = 0;
    while (true) {
      while (root) {
        s.push(root);
        root = root->left;
      }
      cnt++;
      root = s.top()->right;

      if (cnt == k) {
        break;
      }
      s.pop();

    }
    return s.top()->val;

  }
};

//recursive
class Solution {
private:
  int cnt = 0;
  int num;
public:
  int kthSmallest(TreeNode* root, int k) {
    cnt = k;
    help(root);
    return num;
  }

  void help(TreeNode* root) {
    if (root->left)
      help(root->left);
    cnt--;
    if (cnt == 0) {
      num = root->val;
      return;
    }
    if (root->right)
      help(root->right);
  }
};

```

### Range problem

* Print range

```CPP
//Print range
void printbstkeys(Tnode *root, int k1, int k2)
{
  if (root == NULL)
    return;
  printbstKey(root->left, k1, k2);
  if (root->data >= k1 && root->data <= k2)
    printf(" %d ", root->data);
  printbstKey(root->right, k1, k2);
  return;
}

/*
To avoid unwanted traversals we can compare current node's
data with K1 for left subtree and K2 for right subtree.
*/

void printbstkeys(Tnode *root, int k1, int k2)
{
  if (root == NULL)
    return;
  if (root->data >= k1)
    printbstKey(root->left, k1, k2);
  if (root->data >= k1 && root->data <= k2)
    printf(" %d ", root->data);
  if (root->data<k2)
    printbstKey(root->right, k1, k2);
  return;
}

```

* 


### Closest value

https://leetcode.com/problems/closest-binary-search-tree-value/

```CPP
//https://leetcode.com/problems/closest-binary-search-tree-value/
//recursive
class Solution {
public:
  int closestValue(TreeNode* root, double target) {
      /* 
      found the value via in order traverse, maintain cur and next, until cur<target<next or next<target<cur 
      */
      int cur = root->val;
      if(cur>target){
          root = root->left;
      }else{
          root = root->right;
      }
      if(root==NULL)
          return cur;
      int next = closestValue(root, target);
      
      return abs(cur-target)>abs(next-target)?next:cur;
  }
};

//iterative
class Solution {
public:
  int closestValue(TreeNode* root, double target) {
      /* 
      found the value via in order traverse, maintain cur and next, until cur<target<next or next<target<cur 
      */
      int cloest = root->val;
      while(root!=NULL){
          if(abs(cloest - target) >= abs(root->val- target))
              cloest = root->val;
          
          if(root->val>target){
              root = root->left;
          }else{
              root = root->right;
          }
      }
      return cloest;
  }
};

```

https://leetcode.com/problems/closest-binary-search-tree-value-ii/

Given a non-empty binary search tree and a target value, find k values in the BST that are closest to the target.

Note:
Given target value is a floating point.
You may assume k is always valid, that is: k ≤ total nodes.
You are guaranteed to have only one unique set of k values in the BST that are closest to the target.

```CPP
class Solution {
public:
  vector<int> closestKValues(TreeNode* root, double target, int k) {
    vector<int> ret;
    priority_queue<pair<double, int>> pq;

    dfs_help(root, target, k, pq);
    while (!pq.empty()) {
      pair<double, int> tmp = pq.top();
      ret.push_back(tmp.second);
      pq.pop();
    }
    return ret;
  }

  void dfs_help(TreeNode* root, double target, int k, priority_queue<pair<double, int>> &pq) {
    if (root == NULL)
      return;

    if (pq.size() < k) {
      pq.push(make_pair(abs(target - root->val), root->val));
    }
    else {
      if (abs(root->val - target)<abs(pq.top().first)) {
        pq.push(make_pair(abs(target - root->val), root->val));
        pq.pop();
      }
    }
    dfs_help(root->left, target, k, pq);
    dfs_help(root->right, target, k, pq);
  }
};

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

# Tree to Array/String

## Array to Tree

https://leetcode.com/problems/convert-sorted-array-to-binary-search-tree/

```CPP
class Solution {
public:
  TreeNode* sortedArrayToBST(vector<int>& nums) {

    return helper(nums, 0, nums.size() - 1);

  }

  TreeNode* helper(vector<int>& nums, int start, int end) {

    if (start>end)
      return NULL;
    TreeNode* node = (TreeNode*)malloc(sizeof(TreeNode));
    int mid = (start + end) / 2;
    node->val = nums[mid];
    node->left = helper(nums, start, mid - 1);
    node->right = helper(nums, mid + 1, end);

    return node;
  }
};


class Solution {
public:
  TreeNode* sortedListToBST(ListNode* head) {
    int len = 0;
    ListNode* cur = head;
    while (cur) {
      len++;
      cur = cur->next;
    }

    return sortedListToBSTConstruct(head, 0, len - 1);
  }


  TreeNode* sortedListToBSTConstruct(ListNode* &head, int start, int end) {
    if (start>end)
      return NULL;
    int mid = (start + end) / 2;
    TreeNode * left = sortedListToBSTConstruct(head, start, mid - 1);
    TreeNode* node = (TreeNode*)malloc(sizeof(TreeNode));
    node->val = head->val;
    head = head->next;
    TreeNode * right = sortedListToBSTConstruct(head, mid + 1, end);
    node->left = left;
    node->right = right;
    return node;
  }

};

```

## Reconstruct Tree

###Re construct Tree from in-order and post-order

https://leetcode.com/problems/construct-binary-tree-from-inorder-and-postorder-traversal/ 

Let us see the process of constructing tree from in[] = {4, 8, 2, 5, 1, 6, 3, 7} and post[] = {8, 4, 5, 2, 6, 7, 3, 1}

1) We first find the last node in post[]. The last node is “1”, we know this value is root as root always appear in the end of postorder traversal.

2) We search “1” in in[] to find left and right subtrees of root. Everything on left of “1” in in[] is in left subtree and everything on right is in right subtree.

```

         1
       /    \
[4, 8, 2, 5]   [6, 3, 7] 
```
3) We recur the above process for following two.
….b) Recur for in[] = {6, 3, 7} and post[] = {6, 7, 3}
…….Make the created tree as right child of root.
….a) Recur for in[] = {4, 8, 2, 5} and post[] = {8, 4, 5, 2}.
…….Make the created tree as left child of root.

```CPP

class Solution {
public:
    unordered_map<int, int> inorder_map;
    TreeNode* traverse(vector<int>& inorder, vector<int>& postorder, int start, int end, int &pivot){
        if(start > end)
            return NULL;
        
        int value = postorder[pivot];
        TreeNode *newnode = new TreeNode(value);
        pivot--;
        
        newnode->right = traverse(inorder, postorder, inorder_map[value]+1, end, pivot);
        newnode->left = traverse(inorder, postorder, start, inorder_map[value]-1, pivot);
        return newnode;
    }
    
    TreeNode* buildTree(vector<int>& inorder, vector<int>& postorder) {
        
        //reverse(postorder.begin(), postorder.end());
        
        for(int i = 0; i < postorder.size(); i++){
            inorder_map[inorder[i]] = i;
        }
        
        int pivot = inorder.size()-1;
        return traverse(inorder, postorder, 0, postorder.size()-1, pivot);
        
    }
};
```

### Re construct Tree from in-order and pre-order

https://leetcode.com/problems/construct-binary-tree-from-preorder-and-inorder-traversal/

Given preorder and inorder traversal of a tree, construct the binary tree.

Note:
You may assume that duplicates do not exist in the tree.

```
For example, given

preorder = [3,9,20,15,7]
inorder = [9,3,15,20,7]
Return the following binary tree:

    3
   / \
  9  20
    /  \
   15   7
```

```CPP

class Solution {
public:
    
    map<int,int> index;
    
    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {

        for (int i = 0; i < inorder.size(); i++){
            index[inorder[i]] = i;

        }
        return help(preorder, 0, inorder.size()-1, inorder,0,inorder.size()-1);
    }
    
    TreeNode* help(vector<int>& preorder, int preStart, int preEnd, 
                   vector<int>& inorder, int inStart, int inEnd)
    {
        if(preStart > preEnd || inStart > inEnd) 
            return NULL;
        
        if (inStart == inEnd)
            return new TreeNode(inorder[inStart]);
        
        TreeNode *root = new TreeNode(preorder[preStart]); //current recursive root
        
        int inRoot = index[preorder[preStart]]; //get the index of current root in inorder
        int left = inRoot - inStart;
        int right = inEnd - inRoot;
        
        root->left = help(preorder, preStart+1, preStart+left, inorder, inStart, inRoot-1);
        root->right = help(preorder, preStart+left+1, preEnd, inorder, inRoot+1, inEnd);
        
        return root;
    }
};
```



## Serialize and Deserialize Binary Tree
https://leetcode.com/problems/serialize-and-deserialize-binary-tree/#/description
```CPP
string serialize(TreeNode* root){
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

// Decodes your encoded data to tree.
TreeNode* deserialize(string data) {         
    if(data.empty())
        return NULL;
    int index = 0;
    return deserialize_helper(data, index);
}

 TreeNode* deserialize_helper(string& data, int & index) {
    if(data[index]=='#'){
        index++;
        if (index < data.size())
            index++;
        return NULL;
    }

    TreeNode* node = (TreeNode*)malloc(sizeof(TreeNode));
    string cur = "";
    int start = index;
    while(data[index]!=','){
        index++;
    }
    cur = data.substr(start,index-start);
    node->val = stoi(cur);
    index++; //pass ','

    node->left = deserialize_helper(data,index);
    node->right = deserialize_helper(data,index);

    return node;
}
```

## 

# Traversal



## BFS

```CPP
public Void BFS()
{
  Queue q = new Queue();
  q.push_back(root);//You don't need to write the root here, it will be written in the loop
  while (q.count > 0)
  {
    Node n = q.pop_front();
    Console.Writeln(n.Value); //Only write the value when you dequeue it
    if (n.left != null)
    {
      q.push_back(n.left);//enqueue the left child
    }
    if (n.right != null)
    {
      q.push_back(n.right);//enque the right child
    }
  }
}
```

## DFS

```CPP
void printLevel(BinaryTree *p, int level) {
  if (!p) return;
  if (level == 1) {
    cout << p->data << " ";
  }
  else {
    printLevel(p->left, level - 1);
    printLevel(p->right, level - 1);
  }
}

void printLevelOrder(BinaryTree *root) {
  int height = maxHeight(root);
  for (int level = 1; level <= height; level++) {
    printLevel(root, level);
    cout << endl;
  }
}

```


## Morris Traversal

* why we use recursive in tree traveral(pre,in,post): idea is to trversal to current node, node's left and return to current node, node'right and return to current node;
* basically visit the node 3 times
* Morris traveral try to minic recursive, visit node 3 times
* use lots of empty pointer




# BST 

## Common Logic

> Key idea is Recursive and do something for each node:

> Some 

>* collect same information for each node, and pass to its parents,
>* information has 3 items: left branch's, right branch's, and sub branch for which current node as root
>* repeat


## Insert/Find/Delete Node

### Find

```CPP
boolean isInBST(TreeNode* root, int target) {
    if (root == null) return false;
    if (root.val == target) return true;

    return isInBST(root->left, target)
        || isInBST(root->right, target);
}

//A better way
boolean isInBST(TreeNode* root, int target) {
    if (root == null) 
      return false;
    if (root->val == target)
        return true;
    if (root->val < target) 
        return isInBST(root->right, target);
    if (root->val > target)
        return isInBST(root->left, target);
    
}
```

### Insert

```CPP
TreeNode insertIntoBST(TreeNode* root, int val) {
    //find empty spot
    if (root == null) 
      return new TreeNode(val);

    if (root->val < val) 
        root->right = insertIntoBST(root->right, val);
    if (root.val > val) 
        root->left = insertIntoBST(root->left, val);
    return root;
}
```

### Delete

https://leetcode.com/problems/delete-node-in-a-bst/

Given a root node reference of a BST and a key, delete the node with the given key in the BST. Return the root node reference (possibly updated) of the BST.

need to find the node first

```CPP
TreeNode* deleteNode(TreeNode* root, int key) {
    if (root->val == key) {
        // found the node, delete
    } else if (root->val > key) {
        root->left = deleteNode(root->left, key);
    } else if (root->val < key) {
        root->right = deleteNode(root->right, key);
    }
    return root;
}
```

after found the node, we need to deal with delete, it could be one leaf, so just delete, or in middle, so need to link other branch node 


```CPP
class Solution {
public:
    TreeNode* deleteNode(TreeNode* root, int key) {
        if (root==NULL)
            return NULL;
        
        if (root->val == key) {
            if (root->left == NULL){
                return root->right; 
            }else if(root->right == NULL){
                return root->left; 
            }else {
              //otherwise, need to pop largest node in left branch, or smallest in right branch
              //in here, we just get smallest in right branch
              TreeNode* minNode = getMin(root->right);
              root->val = minNode->val;
              root->right = deleteNode(root->right, minNode->val);
            }
        } else if (root->val > key) {
            root->left = deleteNode(root->left, key);
        } else if (root->val < key) {
            root->right = deleteNode(root->right, key);
        }
        return root;
    }
    
    TreeNode* getMin(TreeNode* node) {
        // left in BST
        while (node->left != NULL) 
            node = node->left;
        return node;
    }
};
```

## Tree is Balanced Binary tree?
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

## Valid BST
Given a binary tree, determine if it is a valid binary search tree (BST).

Assume a BST is defined as follows:

The left subtree of a node contains only nodes with keys less than the node's key.

The right subtree of a node contains only nodes with keys greater than the node's key.

Both the left and right subtrees must also be binary search trees.

```CPP
bool isValidBST(TreeNode *root) {

    if(root == NULL)
        return true;

    return isBSThelper(root,LONG_MIN,LONG_MAX);

}

bool isBSThelper(TreeNode *root, long min, long max){
    if(root==NULL)
        return true;
    if(root->val>min && root->val <max){
        return isBSThelper(root->left, min,root->val) && isBSThelper(root->right,root->val,max);
    }else{
        return false;
    }
}
```

## Recover BST

https://leetcode.com/problems/recover-binary-search-tree/

Two elements of a binary search tree (BST) are swapped by mistake.
Recover the tree without changing its structure.

```
Example 1:

Input: [1,3,null,null,2]

   1
  /
 3
  \
   2

Output: [3,1,null,null,2]

   3
  /
 1
  \
   2
Example 2:

Input: [3,1,4,null,null,2]

  3
 / \
1   4
   /
  2

Output: [2,1,4,null,null,3]

  2
 / \
1   4
   /
  3
Follow up:

A solution using O(n) space is pretty straight forward.
Could you devise a constant space solution?
```

```CPP
/**
for example 6, 3, 4, 5, 2

find the first: 6, then find second, which is 2

*/

class Solution {
public:
    TreeNode* first = NULL;
    TreeNode* second = NULL;
    TreeNode* predecessor = NULL;
    
    void swap(TreeNode* a, TreeNode* b) {
        int tmp = a->val;
        a->val = b->val;
        b->val = tmp;
    }
    
    
    void findswap(TreeNode* root) {
        if(root == NULL)
            return;
          //traverse in order to get sorted order
        findswap(root->left);
        //inorder: predecessor should < root
        if(predecessor!=NULL && root->val < predecessor->val){
            //find the first
            if (first == NULL) 
                first = predecessor;
            //find second
            if (first !=NULL)  
                second = root;
        }
        predecessor = root;
        findswap(root->right);  
    }
    
    void recoverTree(TreeNode* node) {
        findswap(node);
        swap(first,second);  
    }
};
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

    if(root == NULL) return 0;
      int res = depth(root->left) + depth(root->right);
      return max(res, max(diameterOfBinaryTree(root->left), diameterOfBinaryTree(root->right)));
    }

    
    int depth(TreeNode* root){
        if(root == NULL) return 0;
        return  1+max(depth(root->left), depth(root->right));
    }
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


# Trie/prefix Tree

In computer science, a trie, or prefix tree, is an ordered tree data structure that is used to store a dynamic set or associative array where the keys are usually strings. Unlike a binary search tree, no node in the tree stores the key associated with that node; instead, its position in the tree defines the key with which it is associated. All the descendants of a node have a common prefix of the string associated with that node, and the root is associated with the empty string. Values are normally not associated with every node, only with leaves and some inner nodes that correspond to keys of interest. For the space-optimized presentation of prefix tree, see compact prefix tree.

* Root node dose not have character
* The characters added up from root to certain node represents the string to that node.
* Cons: memory occupation, 26^i for every level(i is the level), so we can implement using linked list or dynamic array


```CPP
class TrieNode {
public:
  // Initialize your data structure here.
  TrieNode() {
    end = false;
    for (int i = 0; i<26; i++) {
      child[i] = NULL;
    }
  }
  bool end;
  TrieNode *child[26];
};

class Trie {
public:
  Trie() {
    root = new TrieNode();
  }
  // Inserts a word into the trie.
  void insert(string word, TrieNode *root) {
    TrieNode *p = root;
    int len = word.size();
    for (int i = 0; i<len; i++) {
      int pos = word[i] - 'a';
      if (p->child[pos] == NULL) {
        p->child[pos] = new TrieNode();
      }
      p = p->child[pos];
    }
    p->end = true;
  }
  // Returns if the word is in the trie.
  bool search(string word) {
    TrieNode *p = root;
    int len = word.size();
    int pos;
    for (int i = 0; i<len; i++) {
      pos = word[i] - 'a';
      if (p->child[pos] != NULL) {
        p = p->child[pos];
      }
      else {
        return false;
      }
    }
    return p->end;
  }
  // Returns if there is any word in the trie
  // that starts with the given prefix.
  bool startsWith(string prefix) {
    TrieNode *p = root;
    int len = prefix.size();
    int pos;
    for (int i = 0; i<len; i++) {
      pos = prefix[i] - 'a';
      if (p->child[pos] != NULL) {
        p = p->child[pos];
      }
      else {
        return false;
      }
    }
  }
private:
  TrieNode* root;
};

```

