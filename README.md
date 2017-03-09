# Array,Queue,Stack,Priority Queue(Heap)

## Heap

Heap is implemented as tree structure in logic view and array in physical view:

```CPP
For node in index i:
Children: left: 2*i+1; right: 2*i+2
Parent: (i-1)/2
```

Time complexity for construct the heap is:

```shell
O(N): 1*log(1)+2*log(2)...+n*log(n) = O(N)
```

## Stack

### Application

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
