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

# Find largest BST sub tree in a binary tree

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