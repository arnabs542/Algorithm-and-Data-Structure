# Array,Queue,Stack,Priority Queue(Heap)

## Heap

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

## Stack

* Min Stack
maintain a min stack that query  minimum value in stack is O(1)

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

* Convert a stack to Queue
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
  if(stack_pop.empty())
    while(!stack_push.empty()){
      stack_pop.push(stack_push.top());
      stack_push.pop();
    }
    int ret = stack_pop.top();
    stack_pop.pop();
    return ret;
}
```


* Revert stack recursively



### Examples


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
