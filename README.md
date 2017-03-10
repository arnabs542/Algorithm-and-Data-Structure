# Array,Queue,Stack,Priority Queue(Heap)

## Basic data structure
### Heap

Heap is implemented as tree structure in logic view and array in physical view:

```shell
For node in index i:
Children: left: 2*i+1; right: 2*i+2
Parent: (i-1)/2
```

Time complexity for construct the heap is:

```shell
O(N): 1*log(1)+2*log(2)...+n*log(n) = O(N)
```

## Application and Examples

* Min Stack:

maintain a min stack that query  minimum value in stack is O(1). idea is to maintain two stacks, regular one and the other one whose peek/top records the min value

```CPP
//Basic idea is to maintain two stacks, regular one and the other one whose peek/top records the min value

stack<int> data_s; //regular stack
stack<int> min_s; //stack that records min val of current stack

void push(int input){
  if(min_s.empty() || min_s.top()>input){
    min_s.push(input);
  }else{
    min_s.push(min_s.top());
  }
  data_s.push(input);
}

void pop(){
  if(!min_s.empty())
     min_s.pop();
  if(!data_s.empty())
    data_s.pop();
}

int getMin(){
  if(!min_s.empty())
    return ERROR;
  return min_s.top();
}
```

* Convert a stack to Queue:

The idea is to Use two stacks, one for push, one for pop to mimic the queue tail and head
```CPP
// Use two stacks, one for push, one for pop to mimic the queue tail and head

stack<int> stack_push;
stack<int> stack_pop;

void Push(int input){
  stack_push.push(input);
}

int pop(){
  if(stack_push.empty()&&stack_pop.empty())
    return;
  //put all push stack items into pop stack,
  //Ensure that pop stack is empty before transfer
  if(stack_pop.empty()){
    while(!stack_push.empty()){
      stack_pop.push(stack_push.top());
      stack_push.pop();
    }
  }
  int ret = stack_pop.top();
  stack_pop.pop();
  return ret;
}
```

* Revert stack recursively without extra new stack:

The idea is to use function recursively because recursive uses stack
```CPP
stack<int> s;
void reverse(stack<int> &s){
  if(s.empty())
    return;
  int ret = getAndRemoveLastElement(s);
  reverse(s);
  s.push(ret);
}
//this function will delete last/bottom of current stack. return top of current stack
int getAndRemoveLastElement(stack<int> &s){
  int cur = s.top();
  s.pop();
  if(s.empty())
    return cur;
  int last = getAndRemoveLastElement(s);
  s.push(cur);
  return last;
}

```

* Update Largest/Smallest value in sliding window

1. use dequeue(double linked list), new item will be inserted into tail.
2. store the index instead of the value in dequeue.
3. when updating, remove tail of dequeue until new value is the index of Smallest in dequeue. ensure the head of dequeue is index of Largest
4. ensure the dequeue is in decreasing order from head to tail


```CPP
## With fix size window
std::deque<int> dq;
for(int i=0;i<array.size();i++){

  //update dequeue structure to ensure decreasing order from head to tail.
  while(!dq.empty() && array[dq.end()]<array[i]){
    dq.pop_back()
  }
  dq.push_back(i); //store index

  if(dq.front()>=i-w) //head index expires. w is window size
    dq.pop_front();
}
```

* Create a max-tree(Assume no duplicate values.)

We can use max heap and heap insert.
```CPP
struct TreeNode{
  int val;
  TreeNode* left;
  TreeNode* right;
};

TreeNode * getMaxtree_method1(vector<int> array){
  int len = array.size();
  std::vector<TreeNode> node;
  //init heap tree
  for(int i=0;i<array.size();i++){
    node[i] = new TreeNode(array[i]);
  }
  //heap sort array
  for(int i=0;i<len;i++){
    heapSort(array,i);
  }
  //Build up the max tree
  for(int i=0;i<array.size();i++){
    int left_child = 2*i+1;
    int right_child = 2*i+2;
    if(left_child<array.size())
      node[i]->left = node[left_child];
    if(right_child<array.size())
      node[i]->right = node[right_child]
  }
  return node[0];
}

void heapSort(vector<int> &array, int index){
  while(index!=0){
    int parent = (index-1)/2;
    if(array[parent]<array[index]){
      swap(array[parent],array[index]);
      index = parent;
    }else{
      break;
    }
  }
}
```


but we can also use __monotonic stack__

> for a given item in array, find its values from its left and right which are larger than it and are cloest to current item.

> For a input size N array, return size N pairs of values (left, right), in which left is the cloest larger value from left side of current item, and right is the cloest larger value from right side of current item

Algorithm:
```CPP
stack<int> s; //monotonic stack, values are increasing from top to bottom
vector<pair<int,int>> ret;
int left,right,input;
for(int i=0;i<array.size();i++){
  input = array[i];

  while(!s.empty() && input>s.top()){
    s.pop(); //will get the left and right for this popped value;
    left = stack.empty()?NULL:s.top(); //since monotonic, current top after pop should be larger
    right = input; //input is larger than popped
    ret.push_back(make_pair(left,right));
  }
  s.push(input);
}
//if there are still values in stack, it is monotonic, so right larger is NULL
while(!s.empty()){
  right = NULL;
  s.pop();
  left = stack.empty()?NULL:s.top();
  ret.push_back(make_pair(left,right));
}

return ret;
```

We can use this monotonic stack way to create the max-tree:

1. For any value, check left and right cloest larger value.
2. compare these two, put itself as child of smaller between left and right.

It will be a binary tree, not necessary full balanced binary tree
```CPP
struct TreeNode{
  int val;
  TreeNode* left;
  TreeNode* right;
};

TreeNode * getMaxtree_method2(vector<int> array){
  stack<TreeNode> s; //monotonic stack for TreeNode value
  map<TreeNode,TreeNode> Parents; //key is node, val is its parents
  std::vector<TreeNode*> node;
  //init TreeNode array
  for(int i=0;i<array.size();i++){
    node[i] = new TreeNode(array[i]);
  }
  //for each node in array, find its left cloest larger and right cloest larger, put into map
  for(int i=0;i<array.size();i++){
    int input = array[i];
    int left,right;
    while(!s.empty() && s.top()->val<input){
      TreeNode cur = s.top();
      s.pop();
      left = stack.empty()? NULL: s.top();
      right = new TreeNode(input);
      parents[cur] = left==NULL || left->val<right->val?left:right;
    }
    s.push(node[i]);
  }
  //go through all array, and stack still have value
  while(!s.empty()){
    //Right is always null since we are to the end of the array
    TreeNode cur = s.top();
    s.pop();
    left = stack.empty()?NULL:s.top();
    parents[cur] = left;
  }
  //Build up the tree
  TreeNode* head;
  TreeNode* Parent;
  for(int i=0;i<array.size();i++){
    parent = parents[node[i]];
    if(parent==NULL){
      head = node[i]; //found tree root
    }else if(parent->left == NULL){
      parent->left = node[i];
    }else{
      parent->right = node[i];
    }
  }

  return head;
}
```

* Use this data structure for other Problem_07_MaxTree

Max rectangle 

* Top K problem
