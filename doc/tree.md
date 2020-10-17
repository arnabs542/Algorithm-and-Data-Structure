<!-- START doctoc generated TOC please keep comment here to allow auto update -->
<!-- DON'T EDIT THIS SECTION, INSTEAD RE-RUN doctoc TO UPDATE -->
**Table of Contents**  *generated with [DocToc](https://github.com/thlorenz/doctoc)*

- [Traversal](#traversal)
  - [pre order](#pre-order)
    - [Construct Tree from pre-order](#construct-tree-from-pre-order)
  - [In order](#in-order)
  - [Post order](#post-order)
  - [Level Traversal](#level-traversal)
  - [Combine different order](#combine-different-order)
    - [Boudary of BST](#boudary-of-bst)
  - [In order in BST and its variation](#in-order-in-bst-and-its-variation)
    - [Common Pattern](#common-pattern)
    - [In order traverse pattern](#in-order-traverse-pattern)
    - [Inorder Successor in BST](#inorder-successor-in-bst)
    - [next node(Descendant Node) via in order traversal](#next-nodedescendant-node-via-in-order-traversal)
    - [K-th Smallest](#k-th-smallest)
    - [Range problem](#range-problem)
    - [Closest value](#closest-value)
- [Recursive(Most important for Tree problem)](#recursivemost-important-for-tree-problem)
  - [Common Recursive way](#common-recursive-way)
    - [Top Down](#top-down)
    - [Bottom Up](#bottom-up)
  - [Common Example](#common-example)
    - [Sorted Array to BST](#sorted-array-to-bst)
    - [Symmetric](#symmetric)
    - [Count Univalue Subtrees](#count-univalue-subtrees)
    - [Lowest Common Ancestor of a Binary Tree](#lowest-common-ancestor-of-a-binary-tree)
    - [Path Sum](#path-sum)
      - [Check Path sum exists](#check-path-sum-exists)
      - [All path to a sum](#all-path-to-a-sum)
        - [Count Paths for a Sum](#count-paths-for-a-sum)
      - [Path Sum(no need to be leaf)](#path-sumno-need-to-be-leaf)
      - [Sum Root to Leaf Numbers](#sum-root-to-leaf-numbers)
      - [Path With Given Sequence](#path-with-given-sequence)
      - [Max path Sum](#max-path-sum)
    - [Larger/smaller item in Tree path](#largersmaller-item-in-tree-path)
    - [Valid sequence in Tree](#valid-sequence-in-tree)
    - [Pseudo-Palindromic Paths in a Binary Tree](#pseudo-palindromic-paths-in-a-binary-tree)
    - [lonely Node](#lonely-node)
    - [Unique Binary Search Trees](#unique-binary-search-trees)
- [Sub-Tree problems](#sub-tree-problems)
  - [SubTree of another](#subtree-of-another)
  - [SubTree prune and trim](#subtree-prune-and-trim)
  - [Split Tree into SubTree](#split-tree-into-subtree)
    - [Maximum Product of Splitted Binary Tree](#maximum-product-of-splitted-binary-tree)
    - [Delete Nodes And Return Forest](#delete-nodes-and-return-forest)
- [Tree<->Array](#tree-array)
  - [Array to Tree](#array-to-tree)
  - [Reconstruct Tree](#reconstruct-tree)
    - [Re construct Tree from in-order and pre-order](#re-construct-tree-from-in-order-and-pre-order)
    - [Re construct Tree from in-order and post-order](#re-construct-tree-from-in-order-and-post-order)
  - [Serialize and Deserialize Binary Tree](#serialize-and-deserialize-binary-tree)
    - [Find Duplicate Subtrees](#find-duplicate-subtrees)
- [Traversal](#traversal-1)
  - [BFS](#bfs)
  - [DFS](#dfs)
  - [Morris Traversal](#morris-traversal)
  - [Example](#example)
    - [Vertical Order Traversal of a Binary Tree](#vertical-order-traversal-of-a-binary-tree)
- [BST](#bst)
  - [Common Logic](#common-logic)
  - [Insert/Find/Delete Node](#insertfinddelete-node)
    - [Find](#find)
    - [Insert](#insert)
      - [Insert Max Tree](#insert-max-tree)
    - [Delete](#delete)
      - [Delete Leaves With a Given Value](#delete-leaves-with-a-given-value)
      - [Delete node in BST](#delete-node-in-bst)
  - [Tree is Balanced Binary tree?](#tree-is-balanced-binary-tree)
  - [Valid BST](#valid-bst)
  - [Level Tranversal](#level-tranversal)
    - [minimum depth](#minimum-depth)
    - [Level Order Successor](#level-order-successor)
    - [Connect Level Order Siblings/Populating Next Right](#connect-level-order-siblingspopulating-next-right)
      - [Connect All Level Order Siblings](#connect-all-level-order-siblings)
    - [Right Side view](#right-side-view)
    - [Deepest leaves sum](#deepest-leaves-sum)
    - [Lowest common Ancestor](#lowest-common-ancestor)
  - [Recover BST](#recover-bst)
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
vector<int> preorderTraversal(TreeNode* root) {
    vector<int> answer;
    stack<TreeNode*> s;
    if (root) {
        s.push(root);
    }
    TreeNode* cur;
    while (!s.empty()) {
        cur = s.top();
        s.pop();
        answer.push_back(cur->val);     // visit the root
        if (cur->right) {
            s.push(cur->right);         // push right child to stack if it is not null
        }
        if (cur->left) {
            s.push(cur->left);          // push left child to stack if it is not null
        }
    }
    return answer;
}
```

```CPP
    vector<int> preorderTraversal(TreeNode* root) {
        vector<int> ret;
        help(root, ret);
        return ret;
        
    }
    
    void help(TreeNode* root, vector<int>& v){
        if(!root) 
            return;
        v.push_back(root->val);
        help(root->left, v);
        help(root->right, v);
    }
```

### Construct Tree from pre-order

https://leetcode.com/problems/construct-binary-search-tree-from-preorder-traversal/

```CPP
TreeNode* bstFromPreorder(vector<int>& A) {
    int i = 0;
    return build(A, i, INT_MAX);
}

TreeNode* build(vector<int>& A, int& i, int bound) {
    if (i == A.size() || A[i] > bound) 
        return NULL;
    TreeNode* root = new TreeNode(A[i++]);
    //left branch is less than root
    root->left = build(A, i, root->val);
    root->right = build(A, i, bound);
    return root;
}
```

> Stack solution

```CPP
TreeNode* bstFromPreorder(vector<int>& preorder) {
    TreeNode* root = new TreeNode(preorder[0]);
    
    stack<TreeNode*> s; 
    s.push(root);
    
    for(int i = 1; i<preorder.size(); ++i){ 
        
        if( preorder[i] < s.top()->val ) { 
            //next is left if smaller than current top
            s.top()->left = new TreeNode(preorder[i]);
            s.push(s.top()->left);
        }
        else { // right            
            TreeNode* node;
            
            // when we reach a value greater than preoder[i], 
            //previous popped value will be the parent
            while( !s.empty() && s.top()->val < preorder[i] ) {
                node = s.top(); 
                s.pop();
            }
            node->right = new TreeNode(preorder[i]); 
            s.push(node->right);   
        }
    }
    
    return root;
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

```CPP
    vector<int> postorderTraversal(TreeNode* root) {
        vector<int> ret;
        help(root, ret);
        return ret;
    }

    
    void help(TreeNode* root, vector<int>& v){
        if(!root) 
            return;
        
        help(root->left, v);
        help(root->right, v);
        v.push_back(root->val);
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

## Level Traversal 

https://leetcode.com/problems/binary-tree-level-order-traversal/

```CPP
    vector<vector<int>> levelOrder(TreeNode* root) {
        queue<TreeNode*> q;
        vector<vector<int>> ret;
        if(!root)
            return ret;
        
        q.push(root);
        
        while(!q.empty()){
            int size = q.size();
            vector<int> one;
            for(int i=0;i<size;i++){
                TreeNode* cur = q.front();
                q.pop();
                one.push_back(cur->val);
                if(cur->left)
                    q.push(cur->left);
                if(cur->right)
                    q.push(cur->right);
            }
            ret.push_back(one);
        }
        
        return ret;
    }
```

```CPP
//we can have DFS way also

vector<vector<int>> ret;

void buildVector(TreeNode *root, int depth)
{
    if(root == NULL) return;
    if(ret.size() == depth)
        ret.push_back(vector<int>());
    
    ret[depth].push_back(root->val);
    buildVector(root->left, depth + 1);
    buildVector(root->right, depth + 1);
}

vector<vector<int> > levelOrder(TreeNode *root) {
    buildVector(root, 0);
    return ret;
}
```


## Combine different order 

### Boudary of BST
https://leetcode.com/problems/boundary-of-binary-tree/

Given a binary tree, return the values of its boundary in anti-clockwise direction starting from root. Boundary includes left boundary, leaves, and right boundary in order without duplicate nodes.  (The values of the nodes may still be duplicates.)

```CPP


//node.right is right bound if node is right bound;
//node.left could also be right bound if node is right bound && node has no right child;

//if node is left bound, add it before 2 child - pre order;
//if node is right bound, add it after 2 child - post order;
//A leaf node that is neither left or right bound belongs to the bottom line;


vector<int> boundaryOfBinaryTree(TreeNode* root) {
    vector<int> bounds;
    if (root) {
        bounds.push_back(root->val);
        getBounds(root->left, bounds, true, false);
        getBounds(root->right, bounds, false, true);
    }
    return bounds;
}

void getBounds(TreeNode* node, vector<int>& res, bool lb, bool rb) {
    if (!node)  
        return;
    //left bound first
    if (lb) 
        res.push_back(node->val);
    //leaf
    if (!lb && !rb && !node->left && !node->right)  
        res.push_back(node->val);
//node.left is left bound if node is left bound;
//node.right could also be left bound if node is left bound && node has no left child;
    getBounds(node->left, res, lb, rb && !node->right);
    getBounds(node->right, res, lb && !node->left, rb);
    if (rb) 
        res.push_back(node->val);
}

```

##  In order in BST and its variation 

### Common Pattern

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

### Inorder Successor in BST

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

# Recursive(Most important for Tree problem)

## Common Recursive way

### Top Down

"Top-down" means that in each recursive call, we will visit the node first to come up with some values, and pass these values to its children when calling the function recursively. So the "top-down" solution can be considered as a kind of preorder traversal. To be specific, the recursive function top_down(root, params) works like this:

Recursive in tree to accomplish something, may need help to record some parameter

```
1. return specific value for null node
2. update the answer if needed                      // answer <-- params
3. left_ans = top_down(root.left, left_params)      // left_params <-- root.val, params
4. right_ans = top_down(root.right, right_params)   // right_params <-- root.val, params 
5. return the answer if needed                      // answer <-- left_ans, right_ans
```

### Bottom Up 

"Bottom-up" is another recursive solution. In each recursive call, we will firstly call the function recursively for all the children nodes and then come up with the answer according to the returned values and the value of the current node itself. This process can be regarded as a kind of postorder traversal. Typically, a "bottom-up" recursive function bottom_up(root) will be something like this:

```
1. return specific value for null node
2. left_ans = bottom_up(root.left)          // call function recursively for left child
3. right_ans = bottom_up(root.right)        // call function recursively for right child
4. return answers    
```

## Common Example

### Sorted Array to BST

```CPP
TreeNode* sortedArrayToBST(vector<int>& nums) {
    if(nums.size()==0)
        return NULL;
    
    return help(nums,0,nums.size()-1);;
}

TreeNode* help( vector<int>& nums,int start, int end){
    if(start>end)
        return NULL;
    
    int mid = start+(end-start)/2;
    TreeNode* root =  new TreeNode(nums[mid]);
    root->left = help(nums,start,mid-1);
    root->right = help(nums,mid+1,end);
    
    return root;
    
}
```

### Symmetric

https://leetcode.com/problems/symmetric-tree/

```CPP
bool isSymmetric(TreeNode* root) {
    
    if(root==NULL)
        return true;
    
    return help(root->left, root->right);
    
}

bool help(TreeNode* l, TreeNode* r){
    if(l==NULL){
        return r==NULL;
    }
    if(r==NULL){
        return l==NULL;
    }
    
    if(l->val!=r->val){
        return false;
    }else{
        return help(l->left, r->right) && help(l->right, r->left);
    }
    
    
}
```

### Count Univalue Subtrees
https://leetcode.com/problems/count-univalue-subtrees/

Given the root of a binary tree, return the number of uni-value subtrees.

A uni-value subtree means all nodes of the subtree have the same value.

```CPP
int countUnivalSubtrees(TreeNode* root) {
    int ret = 0;
    isUnivalTree(root, ret);
    
    return ret;
}

bool isUnivalTree(TreeNode* root, int &cnt){
    if(root==NULL)
        return true;
    //bottom up
    bool leftUnival = isUnivalTree(root->left, cnt);
    bool rightUnival = isUnivalTree(root->right, cnt);
    //ensure both branch are unival, and then compare current node with branch
    if(leftUnival && rightUnival && 
       (root->left==NULL || root->left->val == root->val)
      && (root->right==NULL || root->right->val == root->val)){
        
        cnt++;
        return true;
        
    }else {
        return false;
    }
}
```

### Lowest Common Ancestor of a Binary Tree

https://leetcode.com/problems/lowest-common-ancestor-of-a-binary-tree/

```CPP
//this solution works even if node may not exist in tree

TreeNode* ret=NULL;

TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
    help(root, p, q);
    return ret;
    
}

bool help(TreeNode* root, TreeNode* p, TreeNode* q){
    
    if(root==NULL)
        return false;
    //found p,q in left or right branch
    int l = help(root->left, p, q)?1:0;
    int r = help(root->right, p, q)?1:0;
    //found p,q in current node
    int mid = (p==root || q==root)? 1:0;
    
    //if we found both p,q in 2 out of 3
    if ((mid+l+r)>=2)
        ret=root;
    
    return mid+l+r>0;
    
}
```

if we know node may exist in tree

```CPP

```


### Path Sum

#### Check Path sum exists

https://leetcode.com/problems/path-sum/

```CPP
    bool hasPathSum(TreeNode* root, int sum) {
        
        if(root==NULL)
            return false;

        
        if(root->left==NULL && root->right==NULL){
            if(root->val == sum)
                return true;
            else
                return false;
        }
        
        return hasPathSum(root->left, sum-root->val) || hasPathSum(root->right, sum-root->val);


    }
```

#### All path to a sum 

https://leetcode.com/problems/path-sum-ii/

Given a binary tree and a sum, find all root-to-leaf paths where each path's sum equals the given sum.

Note: A leaf is a node with no children.
```
Example:

Given the below binary tree and sum = 22,

      5
     / \
    4   8
   /   / \
  11  13  4
 /  \    / \
7    2  5   1
Return:

[
   [5,4,11,2],
   [5,8,4,5]
]
```

```CPP
vector<vector<int>> pathSum(TreeNode* root, int sum) {
    vector<vector<int>> ret;
    vector<int> one;
    if(!root)
        return ret;
    help(root,sum-root->val,ret,one);
    return ret;
}

void help(TreeNode* root, int sum, vector<vector<int>>& ret, vector<int> &one){
    one.push_back(root->val);
    //reach the end
    if(root->left==NULL && root->right==NULL){
        if(sum==0)
            ret.push_back(one);
        one.pop_back();
        return;
    }
    if(root->left){
        help(root->left,sum-root->left->val,ret,one);
    }
    if(root->right){
        help(root->right,sum-root->right->val,ret,one);
    }
    one.pop_back();
        
}
```

##### Count Paths for a Sum

https://leetcode.com/problems/path-sum-iii/

https://www.educative.io/courses/grokking-the-coding-interview/xV2J7jvN1or

You are given a binary tree in which each node contains an integer value.
Find the number of paths that sum to a given value.
The path does not need to start or end at the root or a leaf, but it must go downwards (traveling only from parent nodes to child nodes).

```CPP
int pathSum(TreeNode* root, int sum) {
    int ret = 0;
    if(root==NULL)
        return 0;
    return help(root, 0, sum) + pathSum(root->left, sum)+ pathSum(root->right, sum);
}

int help(TreeNode* root, int last, int& sum){
    if(!root) 
        return 0;
    int cur = last + root->val;
    
    if (cur==sum)
        return  1+ help(root->left, cur, sum) + help(root->right, cur, sum);
    else
        return  help(root->left, cur, sum) + help(root->right, cur, sum);
}
```

```CPP
    int pathSum(TreeNode* root, int sum) {
        vector<int> cur;
        int cnt = 0;
        help(root,  cur, sum, cnt);
        return cnt;
    }
    
    void help(TreeNode* root, vector<int> cur, int sum, int& cnt){
        if(root==NULL)
            return;
        
        cur.push_back(root->val);
        
        int path_sum = 0;
        // find the sums of all sub-paths ending in current node, so reverse go through vector
        for (int i=cur.size()-1;i>=0;i--) {
          path_sum += cur[i];
          if (path_sum == sum) {
            cnt++;
          }
        }
        
            
        help(root->left, cur, sum, cnt);
        help(root->right, cur, sum, cnt);

        // remove the current node from the path to backtrack,
        cur.pop_back();

    }
```

* Improved solution 3

```CPP
//record all prefix sums in  hash table. For current prefix sum x, check if (x - target) appears in the hash table.
int pathSum(TreeNode* root, int sum) {
        unordered_map<int, int> m;

        
        int total = 0;
        helper(root, 0, sum, total, m);
        return total;
    }
    
    void helper(TreeNode *p, int cur, int sum, int &total, unordered_map<int, int> &m) {
        if (!p) return;
        
        cur += p->val;
        
        if(cur==sum){
            total++;
        }
        
        if (m.find(cur - sum) != m.end()) 
            total += m[cur - sum];
        m[cur]++;
        
        helper(p->left, cur, sum, total, m);
        helper(p->right, cur, sum, total, m);
        
        m[cur]--;
    }
```

#### Path Sum(no need to be leaf)

https://leetcode.com/problems/path-sum-iii/

You are given a binary tree in which each node contains an integer value.

Find the number of paths that sum to a given value.

The path does not need to start or end at the root or a leaf, but it must go downwards (traveling only from parent nodes to child nodes).

The tree has no more than 1,000 nodes and the values are in the range -1,000,000 to 1,000,000.

```
Example:

root = [10,5,-3,3,2,null,11,3,-2,null,1], sum = 8

      10
     /  \
    5   -3
   / \    \
  3   2   11
 / \   \
3  -2   1

Return 3. The paths that sum to 8 are:

1.  5 -> 3
2.  5 -> 2 -> 1
3. -3 -> 11
```

```CPP
int pathSum(TreeNode* root, int sum) {
    int ret = 0;
    if(!root)
        return ret;
    //BFS traversal for tree
    queue<TreeNode*> q;
    q.push(root);
    while(!q.empty()){
        TreeNode* cur=q.front();
        if(cur->left)
            q.push(cur->left);
        if(cur->right)
            q.push(cur->right);
        //for each node as root, calculate its path sum
        help(cur,sum-(cur->val),ret);
        q.pop();
    }
    
    return ret;
}

void help(TreeNode* root, int sum, int &ret){
    if(sum==0)
        ret++;

    if(root->left)
        help(root->left,sum-(root->left->val),ret);
    if(root->right)
        help(root->right,sum-(root->right->val),ret);
        
}
```

we can have DFS way also

```CPP
int pathSum(TreeNode* root, int sum) {
    int ret = 0;
    if(root==NULL)
        return 0;
    return help(root, 0, sum) + pathSum(root->left, sum)+ pathSum(root->right, sum);
}

int help(TreeNode* root, int last, int& sum){
    if(!root) 
        return 0;
    int cur = last + root->val;
    
    if (cur==sum)
        return  1+ help(root->left, cur, sum) + help(root->right, cur, sum);
    else
        return  help(root->left, cur, sum) + help(root->right, cur, sum);
}
```

#### Sum Root to Leaf Numbers

https://leetcode.com/problems/sum-root-to-leaf-numbers/

Given a binary tree containing digits from 0-9 only, each root-to-leaf path could represent a number.
An example is the root-to-leaf path 1->2->3 which represents the number 123.
Find the total sum of all root-to-leaf numbers.

Note: A leaf is a node with no children.

```
Example:

Input: [4,9,0,5,1]
    4
   / \
  9   0
 / \
5   1
Output: 1026
Explanation:
The root-to-leaf path 4->9->5 represents the number 495.
The root-to-leaf path 4->9->1 represents the number 491.
The root-to-leaf path 4->0 represents the number 40.
Therefore, sum = 495 + 491 + 40 = 1026.
```

```CPP
int sumNumbers(TreeNode* root) {
    int cur_sum =0;
    int total_sum = 0;
    help(root, cur_sum, total_sum);
    return total_sum;
}

void help(TreeNode* root, int cur_sum, int& total_sum){
    if(!root) {
        return;
    }
    
    cur_sum = cur_sum*10 + root->val;
    
    if(root->left == NULL && root->right==NULL){
        total_sum+=cur_sum;
        return;
    }
        

    if(root->left)
        help(root->left, cur_sum, total_sum);
    if(root->right)
        help(root->right, cur_sum, total_sum);
    
}
```

#### Path With Given Sequence

https://www.educative.io/courses/grokking-the-coding-interview/m280XNlPOkn

Given a binary tree and a number sequence, find if the sequence is present as a root-to-leaf path in the given tree.

```CPP
static bool findPath(TreeNode *root, const vector<int> &sequence) {
    if (root == nullptr) {
      return sequence.empty();
    }

    return findPathRecursive(root, sequence, 0);
  }

 private:
  static bool findPathRecursive(TreeNode *currentNode, const vector<int> &sequence,
                                int sequenceIndex) {
    if (currentNode == nullptr) {
      return false;
    }

    if (sequenceIndex >= sequence.size() || currentNode->val != sequence[sequenceIndex]) {
      return false;
    }

    // if the current node is a leaf, add it is the end of the sequence, we have found a path!
    if (currentNode->left == nullptr && currentNode->right == nullptr &&
        sequenceIndex == sequence.size() - 1) {
      return true;
    }

    // recursively call to traverse the left and right sub-tree
    // return true if any of the two recursive call return true
    return findPathRecursive(currentNode->left, sequence, sequenceIndex + 1) ||
           findPathRecursive(currentNode->right, sequence, sequenceIndex + 1);
  }
```


#### Max path Sum

https://leetcode.com/problems/binary-tree-maximum-path-sum/

Given a non-empty binary tree, find the maximum path sum.

For this problem, a path is defined as any sequence of nodes from some starting node to any node in the tree along the parent-child connections. The path must contain at least one node and does not need to go through the root.

```
Example 1:

Input: [1,2,3]

       1
      / \
     2   3

Output: 6
Example 2:

Input: [-10,9,20,null,null,15,7]

   -10
   / \
  9  20
    /  \
   15   7

Output: 42
```

```CPP
int maxPathSum(TreeNode* root) {
    int ret = INT_MIN;
    help(root, ret);
    return ret;
}

int help(TreeNode* root, int &maxPath){
    if (!root) 
        return 0;
    int l = max(0, help(root->left, maxPath));
    int r = max(0, help(root->right, maxPath));
    maxPath = max(maxPath, l + r + root->val);
    return root->val + max(l, r);
}
```




### Larger/smaller item in Tree path

https://leetcode.com/problems/count-good-nodes-in-binary-tree/

Given a binary tree root, a node X in the tree is named good if in the path from root to X there are no nodes with a value greater than X.

Return the number of good nodes in the binary tree.

```CPP
int goodNodes(TreeNode* root) {
    return help(root, root->val);
    
}

int help(TreeNode* root, int largest){
    if(root==NULL){
        return 0;
    }
    //largest is largest value along the path so far
    largest = max(root->val, largest);
    int ret = root->val >= largest ? 1 : 0;
    //count both left and right, and possible current node
    ret+= help(root->left, largest) + help(root->right, largest);
    return ret;
    
}
```


### Valid sequence in Tree
https://leetcode.com/problems/check-if-a-string-is-a-valid-sequence-from-root-to-leaves-path-in-a-binary-tree/

Given a binary tree where each path going from the root to any leaf form a valid sequence, check if a given string is a valid sequence in such binary tree. 

We get the given string from the concatenation of an array of integers arr and the concatenation of all values of the nodes along a path results in a sequence in the given binary tree.

 
```
Example 1:
Input: root = [0,1,0,0,1,0,null,null,1,0,0], arr = [0,1,0,1]
Output: true
Explanation: 
The path 0 -> 1 -> 0 -> 1 is a valid sequence (green color in the figure). 
Other valid sequences are: 
0 -> 1 -> 1 -> 0 
0 -> 0 -> 0

Example 2:
Input: root = [0,1,0,0,1,0,null,null,1,0,0], arr = [0,0,1]
Output: false 
Explanation: The path 0 -> 0 -> 1 does not exist, therefore it is not even a sequence.


Example 3:
Input: root = [0,1,0,0,1,0,null,null,1,0,0], arr = [0,1,1]
Output: false
Explanation: The path 0 -> 1 -> 1 is a sequence, but it is not a valid sequence.
```

```CPP
bool isValidSequence(TreeNode* root, vector<int>& arr) {
    return help(root, arr, 0);

}

bool help(TreeNode* root, vector<int>& arr, int index){
    //array too long or not match or to end
    
    
    if(root==NULL || index>=arr.size() || root->val != arr[index]){
       return false;
    }

        //to leaf
    if (root->left==NULL && root->right==NULL)
       if(index+1 == arr.size())
            return true;

    return help(root->left, arr, index+1) || help(root->right, arr, index+1);
        
}
```

### Pseudo-Palindromic Paths in a Binary Tree

https://leetcode.com/problems/pseudo-palindromic-paths-in-a-binary-tree/

Given a binary tree where node values are digits from 1 to 9. A path in the binary tree is said to be pseudo-palindromic if at least one permutation of the node values in the path is a palindrome.

Return the number of pseudo-palindromic paths going from the root node to leaf nodes.

```CPP
int pseudoPalindromicPaths (TreeNode* root) {
    //need to check whether there is only one item occur odd times
    return help(root, 0);
}

int help(TreeNode* root, int cnt){
    if (root==NULL) 
        return 0;
    //XOR to eliminate even number
    cnt ^= 1 << (root->val - 1);
    int ret = help(root->left, cnt) + help(root->right, cnt);
    //reach leaf
    if (root->left ==NULL && root->right==NULL)
        if ((cnt & (cnt - 1)) == 0) 
            ret++;
    return ret; 
}
```

### lonely Node

https://leetcode.com/problems/find-all-the-lonely-nodes/

```CPP
vector<int> getLonelyNodes(TreeNode* root) {
    vector<int> ret;
    help(root, ret);
    return ret;
}

void help(TreeNode* root, vector<int>& ret){
    if(root==NULL)
        return;
    if (root->left && !root->right)
        ret.push_back(root->left->val);
    if (!root->left && root->right)
        ret.push_back(root->right->val);
    help(root->left, ret);
    help(root->right, ret);
}
```

### Unique Binary Search Trees

https://leetcode.com/problems/unique-binary-search-trees-ii/

Given an integer n, generate all structurally unique BST's (binary search trees) that store values 1 ... n.

```CPP
/*
for root at i, the unique BST has left child as all unique BST between 1 to i-1, has right child as all unique BST between i+1 to n. And the overall results have root traverse from 1 to n. So this intuitively lead to a recursive solution.
*/
vector<TreeNode*> generateTrees(int n) {
        vector<TreeNode*> ret;
        if(n<1) 
            return ret;
        
        return help(1,n);
    }
    
    vector<TreeNode*> help(int start, int end){
        vector<TreeNode*> ret;
        if(start>end){
            ret.push_back(NULL);
            return ret;
        }
        for(int i=start;i<=end;i++){
            
            vector<TreeNode*> right = help(i+1,end);
            vector<TreeNode*> left = help(start,i-1);
            for(int r=0;r<right.size();r++){
                for(int l=0;l<left.size();l++){
                    TreeNode* root = new TreeNode(i);
                    root->left = left[l];
                    root->right = right[r];
                    ret.push_back(root);
                }
            }
        }
        return ret;
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

## SubTree prune and trim
https://leetcode.com/problems/binary-tree-pruning/

We are given the head node root of a binary tree, where additionally every node's value is either a 0 or a 1.
Return the same tree where every subtree (of the given tree) not containing a 1 has been removed.
(Recall that the subtree of a node X is X, plus every node that is a descendant of X.)

```CPP
  TreeNode* pruneTree(TreeNode* root) {
      if(root==NULL)
          return NULL;
      
      root->left = pruneTree(root->left);
      root->right= pruneTree(root->right);
      
      if(root->left==NULL && root->right==NULL && root->val==0)
          return NULL;
      else
          return root;
  }
```

https://leetcode.com/problems/trim-a-binary-search-tree/

Given a binary search tree and the lowest and highest boundaries as L and R, trim the tree so that all its elements lies in [L, R](R>=L). You might need to change the root of the tree, so the result should return the new root of the trimmed binary search tree.

```CPP
TreeNode* trimBST(TreeNode* root, int L, int R) {
    if(root==NULL)
        return NULL;
    
    root->left = trimBST(root->left, L, R);
    root->right = trimBST(root->right, L, R);
    //remove entire left and root
    if(root->val<L) {
        return root->right;
    }
    //remove entire right and root
    if(root->val>R){
        return root->left;
    }
    
    return root;
}
```


## Split Tree into SubTree

### Maximum Product of Splitted Binary Tree
https://leetcode.com/problems/maximum-product-of-splitted-binary-tree/

Given a binary tree root. Split the binary tree into two subtrees by removing 1 edge such that the product of the sums of the subtrees are maximized.

```CPP
class Solution {
public:
    long long total_sum=0;
    
    long long ret =0;
    
    int MOD=1e9+7;
    
    int maxProduct(TreeNode* root) {
        if(root==NULL)
            return 0;
        //First pass, get the total sum.Now we have the right total sum of the whole tree.
        //Second pass, find the biggest product.
        total_sum=subtreeSum(root);
        subtreeSum(root);
        return ret%MOD;
    }
    
    int subtreeSum(TreeNode* root){
        if(root==NULL)
            return 0;
        long long sub_sum = root->val + subtreeSum(root->left) + subtreeSum(root->right);
         //Get the max product after making current subtree as a separate tree
        ret=max(ret,sub_sum*(total_sum-sub_sum));   
        
        return sub_sum;
    }
};
```

### Delete Nodes And Return Forest
Given the root of a binary tree, each node in the tree has a distinct value.After deleting all nodes with a value in to_delete, we are left with a forest (a disjoint union of trees).Return the roots of the trees in the remaining forest.  You may return the result in any order.
```
Example 1:
Input: root = [1,2,3,4,5,6,7], to_delete = [3,5]
Output: [[1,2,null,4],[6],[7]]
```

```CPP
class Solution {
public:
    set<int> remove;
    
    vector<TreeNode*> delNodes(TreeNode* root, vector<int>& to_delete) {
        
        vector<TreeNode*> ret;
        for(int i=0;i<to_delete.size();i++){
            remove.insert(to_delete[i]);
        }
        help(root, ret, true);
        return ret;

    }
    
    TreeNode* help(TreeNode* root, vector<TreeNode*>& ret, bool isRoot){
        
        if (root == NULL) 
            return NULL;
        bool deleted = remove.find(root->val) != remove.end();
        
        if(isRoot && !deleted){
            //root, won't be delete
            ret.push_back(root);
        }
        //if current node delete, branch will be root
        root->left = help(root->left, ret, deleted);
        root->right = help(root->right, ret, deleted);
            
        return deleted ? NULL : root;
        
    }
};
```


# Tree<->Array

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

/*
Say we have 2 arrays, PRE and IN.
Preorder traversing implies that PRE[0] is the root node.
Then we can find this PRE[0] in IN, say it's IN[5].
Now we know that IN[5] is root, so we know that IN[0] - IN[4] is on the left side, IN[6] to the end is on the right side.
Recursively doing this on subarrays, we can build a tree out of it :)
*/

class Solution {
public:
    
    map<int,int> inorder_index;
    
    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
        
        //build in-order map
        for (int i = 0; i < inorder.size(); i++){
            inorder_index[inorder[i]] = i;

        }
        //start pivot is root
        int pivot = 0;
        return help(preorder, inorder, 0, inorder.size()-1, pivot);
    }
    
    TreeNode* help(vector<int>& preorder, vector<int>& inorder, int start, int end, int &pivot)
    {
        if(start>end) 
            return NULL;
        
        //current recursive root from pre order, 
        int val = preorder[pivot];
        TreeNode *root = new TreeNode(val); 
        pivot++;
        
        
        root->left = help(preorder, inorder, start, inorder_index[val]-1, pivot);
        root->right = help(preorder, inorder, inorder_index[val]+1, end, pivot);
        
        return root;
    }
};
```

### Re construct Tree from in-order and post-order

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
        //always pick up last in post-order as root
        newnode->right = traverse(inorder, postorder, inorder_map[value]+1, end, pivot);
        newnode->left = traverse(inorder, postorder, start, inorder_map[value]-1, pivot);
        return newnode;
    }
    
    TreeNode* buildTree(vector<int>& inorder, vector<int>& postorder) {
        
        //build inorder map from post order, check for each tree/sub-tree root as pivot
        
        for(int i = 0; i < inorder.size(); i++){
            inorder_map[inorder[i]] = i;
        }
        //post order , root is last, start as pivot
        int pivot = inorder.size()-1;
        //takes as the arguments the left and right boundaries for the current subtree in the inorder traversal.
        return traverse(inorder, postorder, 0, postorder.size()-1, pivot);
        
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

### Find Duplicate Subtrees 

https://leetcode.com/problems/find-duplicate-subtrees/

Given the root of a binary tree, return all duplicate subtrees.For each kind of duplicate subtrees, you only need to return the root node of any one of them.Two trees are duplicate if they have the same structure with the same node values.

```CPP

/*
A unique sub-tree can be uniquely identified by its serialized string;
using post order traversal we can gradualy collect all unique tree-serializations with their associated nodes, with 1 traversal;
then you can see if there is any serialization is associated with more than 1 sub-tree nodes, then you know there is duplicated sub-tree nodes;
*/


unordered_map<string, vector<TreeNode*>> m;

vector<TreeNode*> findDuplicateSubtrees(TreeNode* root) {
    vector<TreeNode*> dups;
    serialize(root);
    for (auto it: m)
        if (it.second.size() > 1) 
            dups.push_back(it.second[0]);
    return dups;
}

string serialize(TreeNode* node) {
    if (!node) return "";
    string s = "(" + serialize(node->left) + to_string(node->val) + serialize(node->right) + ")";
    m[s].push_back(node);
    return s;
}
```


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

## Example

### Vertical Order Traversal of a Binary Tree

https://leetcode.com/problems/vertical-order-traversal-of-a-binary-tree/

Given a binary tree, return the vertical order traversal of its nodes values.

For each node at position (X, Y), its left and right children respectively will be at positions (X-1, Y-1) and (X+1, Y-1).

Running a vertical line from X = -infinity to X = +infinity, whenever the vertical line touches some nodes, we report the values of the nodes in order from top to bottom (decreasing Y coordinates).

```CPP
vector<vector<int>> verticalTraversal(TreeNode* root) {
    //from left, -1, from right, +1
    map<int, map<int, set<int>>> m;
    //Node : coordinate
    queue<pair<TreeNode*, pair<int, int>>> q;
    q.push({root, {0, 0}});
    while (!q.empty()) {
        auto p = q.front();
        q.pop();
        TreeNode* node = p.first;
        int x = p.second.first, y = p.second.second;
        m[x][y].insert(node -> val);
        if (node -> left) {
            q.push({node -> left, {x - 1, y + 1}});
        }
        if (node -> right) {
            q.push({node -> right, {x + 1, y + 1}});
        }
    }
    vector<vector<int>> ret;
    for (auto p : m) {
        vector<int> one;
        for (auto q : p.second) {
            one.insert(one.end(), q.second.begin(), q.second.end());
        }
        ret.push_back(one);
    }
    return ret;
}
```



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

#### Insert Max Tree

https://leetcode.com/problems/maximum-binary-tree-ii/

We are given the root node of a maximum tree: a tree where every node has a value greater than any other value in its subtree.

```
Example 1:
Input: root = [4,1,3,null,null,2], val = 5
Output: [5,4,null,1,3,null,null,2]
Explanation: A = [1,4,2,3], B = [1,4,2,3,5]


Example 2:
Input: root = [5,2,4,null,1], val = 3
Output: [5,2,4,null,1,null,3]
Explanation: A = [2,1,5,4], B = [2,1,5,4,3]



Example 3:
Input: root = [5,2,3,null,1], val = 4
Output: [5,2,4,null,1,3]
Explanation: A = [2,1,5,3], B = [2,1,5,3,4]
```


```CPP
TreeNode* insertIntoMaxTree(TreeNode* root, int val) {
    if (root && root->val > val){
        root->right = insertIntoMaxTree(root->right, val);
        return root;
    }
    TreeNode* node = new TreeNode(val);
    node->left = root;
    
    return node;
    
}
```

we can also solve it iteratively

```CPP
TreeNode* insertIntoMaxTree(TreeNode* root, int val) {
    TreeNode* node = new TreeNode(val);
    TreeNode* cur = root;
    
    if(cur->val < val){
        node->left = cur;
        return node;
    }
    
    while(cur->right && cur->right->val > val){
        cur = cur->right;
    }
    
    node->left = cur->right;
    cur->right = node;
    
    return root;
    
}
```

### Delete

#### Delete Leaves With a Given Value

Given a binary tree root and an integer target, delete all the leaf nodes with value target.

Note that once you delete a leaf node with value target, if it's parent node becomes a leaf node and has the value target, it should also be deleted (you need to continue doing that until you can't).

```CPP
TreeNode* removeLeafNodes(TreeNode* root, int target) {
    TreeNode* ret = root;
    
    if(root==NULL){
        return NULL;
    }
    
    //recursive to get branch, if ==target, will set NULL and remove 
    root->left = removeLeafNodes(root->left, target);
    root->right = removeLeafNodes(root->right, target);
    
    if(root->left==NULL && root->right==NULL && root->val==target){
        root = NULL;
        return NULL;
    }
    
    return ret;
}
```

#### Delete node in BST

https://leetcode.com/problems/delete-node-in-a-bst/

Given a root node reference of a BST and a key, delete the node with the given key in the BST. Return the root node reference (possibly updated) of the BST.

need to find the node first. after found the node, we need to deal with delete, it could be one leaf, so just delete, or in middle, so need to link other branch node 

```CPP

/*

1. If the target node has no child, we can simply remove the node.
2. If the target node has one child, we can use its child to replace itself.
3. If the target node has two children, replace the node with its in-order successor or predecessor node and delete that node.
*/


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

## Level Tranversal

### minimum depth

Find the minimum depth of a binary tree. The minimum depth is the number of nodes along the shortest path from the root node to the nearest leaf node.

https://leetcode.com/problems/minimum-depth-of-binary-tree/

https://www.educative.io/courses/grokking-the-coding-interview/3jwVx84OMkO

1. BFS way

```CPP
static int findDepth(TreeNode *root) {
    if (root == nullptr) {
      return 0;
    }

    queue<TreeNode *> queue;
    queue.push(root);
    int minimumTreeDepth = 0;
    while (!queue.empty()) {
      minimumTreeDepth++;
      int levelSize = queue.size();
      for (int i = 0; i < levelSize; i++) {
        TreeNode *currentNode = queue.front();
        queue.pop();

        // check if this is a leaf node
        if (currentNode->left == nullptr && currentNode->right == nullptr) {
          return minimumTreeDepth;
        }

        // insert the children of current node in the queue
        if (currentNode->left != nullptr) {
          queue.push(currentNode->left);
        }
        if (currentNode->right != nullptr) {
          queue.push(currentNode->right);
        }
      }
    }
    return minimumTreeDepth;
  }
```

2. DFS

```CPP
int minDepth(TreeNode *root) {
    if(root== NULL) return 0;
    if (root->left==NULL && root->right==NULL){
        return 1;
    }
    //here to define INT_MAX otherwise compare may need unexpected results
    int left_depth = INT_MAX;
    int right_depth = INT_MAX;
    if(root->left)
        left_depth = minDepth(root->left)+1;
        
    if(root->right)
        right_depth = minDepth(root->right)+1;
    
    return left_depth<right_depth?left_depth:right_depth;

}
```

### Level Order Successor

https://www.educative.io/courses/grokking-the-coding-interview/7nO4VmA74Lr

Given a binary tree and a node, find the level order successor of the given node in the tree. The level order successor is the node that appears right after the given node in the level order traversal.

```CPP
static TreeNode *findSuccessor(TreeNode *root, int key) {
    if (root == nullptr) {
      return nullptr;
    }

    queue<TreeNode *> queue;
    queue.push(root);
    while (!queue.empty()) {
      TreeNode *currentNode = queue.front();
      queue.pop();
      // insert the children of current node in the queue
      if (currentNode->left != nullptr) {
        queue.push(currentNode->left);
      }
      if (currentNode->right != nullptr) {
        queue.push(currentNode->right);
      }

      // break if we have found the key
      if (currentNode->val == key) {
        break;
      }
    }

    return queue.front();
  }
```

### Connect Level Order Siblings/Populating Next Right

https://leetcode.com/problems/populating-next-right-pointers-in-each-node/

https://www.educative.io/courses/grokking-the-coding-interview/m2YYxXDOJ03

Given a binary tree, connect each node with its level order successor. The last node of each level should point to a null node.

```CPP
Node* connect(Node* root) {
    if(root==NULL)
        return root;
    
    queue<Node*> q;
    q.push(root);
    
    while(!q.empty()){
        
        int len=q.size();
        //level by level
        for(int i=0;i<len;i++){
            Node* cur=q.front();
            q.pop();
            //not to right most
            if(i<len-1)
                cur->next=q.front();
            else
                cur->next=NULL;
            if(cur->left)
                q.push(cur->left);
            if(cur->right)
                q.push(cur->right);
        }
    }
    
    return root;
        
}
```


#### Connect All Level Order Siblings

https://www.educative.io/courses/grokking-the-coding-interview/NE5109Jl02v 

extended version, if current level -> next could be point to next level's begining

```CPP
Node* connect(Node* root) {
    if(root==NULL)
        return root;
    
    queue<Node*> q;
    q.push(root);
    Node* prev = NULL;
    
    while(!q.empty()){
        
        int len=q.size();
        //level by level
        for(int i=0;i<len;i++){
            Node* cur=q.front();
            q.pop();
            //not to right most
            if(prev!=NULL)
              prev->next = cur;

            prev = cur;
            if(cur->left)
                q.push(cur->left);
            if(cur->right)
                q.push(cur->right);
        }
    }
    
    return root;
        
}

```

### Right Side view

Given a binary tree, imagine yourself standing on the right side of it, return the values of the nodes you can see ordered from top to bottom.

https://leetcode.com/problems/binary-tree-right-side-view/

https://www.educative.io/courses/grokking-the-coding-interview/B8nj5RB1LJo

```CPP
vector<int> rightSideView(TreeNode* root) {
    vector<int> ret;
    if(root==NULL)
            return ret;
    queue<TreeNode*> q;
    q.push(root);
    while(!q.empty()){

        int len=q.size();
        //level by level
        for(int i=0;i<len;i++){
            TreeNode* cur=q.front();
            q.pop();
            //right most
            if(i==len-1)
                ret.push_back(cur->val);

            if(cur->left)
                q.push(cur->left);
            if(cur->right)
                q.push(cur->right);
        }
    }
    return ret;
}
```

### Deepest leaves sum


https://leetcode.com/problems/deepest-leaves-sum/

Given a binary tree, return the sum of values of its deepest leaves.
 
```
Example 1:

Input: root = [1,2,3,4,5,null,6,7,null,null,null,null,8]
Output: 15
```

```CPP
//calculate sum of each level
//last sum is deepest level

int deepestLeavesSum(TreeNode* root) {
    int res = 0, i;
    queue<TreeNode*> q;
    q.push(root);
    while (q.size()) {
        res = 0;//start new level
        for (i = q.size() - 1; i >= 0; --i) {
            TreeNode* node = q.front(); 
            q.pop();
            res += node->val;
            if (node->right) 
                q.push(node->right);
            if (node->left)  
                q.push(node->left);
        }
    }
    return res;
}
```

### Lowest common Ancestor

https://leetcode.com/problems/lowest-common-ancestor-of-a-binary-tree/

Given a binary tree, find the lowest common ancestor (LCA) of two given nodes in the tree.

According to the definition of LCA on Wikipedia: “The lowest common ancestor is defined between two nodes p and q as the lowest node in T that has both p and q as descendants (where we allow a node to be a descendant of itself).”

Given the following binary tree:  root = [3,5,1,6,2,0,8,null,null,7,4]

```
Example 1:

Input: root = [3,5,1,6,2,0,8,null,null,7,4], p = 5, q = 1
Output: 3
Explanation: The LCA of nodes 5 and 1 is 3.
Example 2:

Input: root = [3,5,1,6,2,0,8,null,null,7,4], p = 5, q = 4
Output: 5
Explanation: The LCA of nodes 5 and 4 is 5, since a node can be a descendant of itself according to the LCA definition.
```

```CPP
TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
    if(root==NULL)
        return NULL;
    
    if(root ==p||root ==q)
        return root;
    TreeNode* Left = lowestCommonAncestor(root->left,p,q);
    TreeNode* Right = lowestCommonAncestor(root->right,p,q);
    //found the root that has p,q in each side
    if((Left!=NULL) && (Right!=NULL))
        return root;
    //if not found, then there could be node only in left or right, return that node and recursive will search for up level
    //bottom up approach
    if(Left!=NULL)
        return Left;
    if(Right!=NULL)
        return Right;
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
