<!-- START doctoc generated TOC please keep comment here to allow auto update -->
<!-- DON'T EDIT THIS SECTION, INSTEAD RE-RUN doctoc TO UPDATE -->
**Table of Contents**  *generated with [DocToc](https://github.com/thlorenz/doctoc)*

- [Linked List](#linked-list)
- [Skip List](#skip-list)
  - [Architecture](#architecture)
  - [Basic Operation](#basic-operation)

<!-- END doctoc generated TOC please keep comment here to allow auto update -->

# Linked List

* Find and return the intersections of two lists. List could have loop

```CPP
Node* getIntersectNode(Node* head1, Node* head2){
  //Get the intersection node for two list, list could have loop
  if(head1==NULL || head2==NULL)
    return NULL;

  Node* ret = NULL;
  Node * inter1 = checkCircle(head1);
  Node * inter2 = checkCircle(head2);

  //if one has circle but the other dose not, no intersection
  if(inter1==NULL && inter2!=NULL || inter1!=NULL && inter2==NULL){
    ret = NULL;
  }else if(inter1 == NULL && inter2 == NULL){
    ret = checkMerge(head1,head2,NULL);
  }else if(inter1!=NULL && inter2!=NULL){
    //both have circle
    ret = checkMergebothLoop(head1,inter1,head2,inter2);
  }

  return ret;
}

Node* checkMerge(Node* head1, Node* head2, Node* end){
  //check if two none-cicle list intersection, if so, return intersection point, otherwise NULL
  int len=0;
  while(head1->next!=end){
    head1 = head1->next;
    len++;
  }
  while(head2->next!=end){
    head2=head2->next;
    len--;
  }
  if(head1!=head2)
    return NULL;

  Node* cur1 = NULL;
  Node* cur2 = NULL;
  //if len>0, list1 is longer, otherwise list2 is longer
  cur1 = len>0 ? head1 : head2;
  cur2 = (cur1 == head1)? head2 : head1;
  len = abs(len);
  while(len>0){
    cur1=cur1->next;
    len--;
  }
  while(cur1!=cur2){
    cur1=cur1->next;
    cur2=cur2->next;
  }

  return cur1;

}

Node* checkMergebothLoop(Node* head1, Node* inter1, Node* head2, Node* inter2){

  //In this case, two lists intersects before going to loop
  if(inter1 == inter2){
    return checkMerge(head1,head2,inter1);
  }else{
    //In this case, two lists enter same loop or never intersect
    Node* cur1 = inter1->next;
    while(tmp!=inter1){
      if(cur1==inter2){
        return inter1; //two loop is same
      }
    }

    return NULL; //two loops are different

  }

}

Node* checkCircle(Node* head){
  //return intersection node if there is circle, otherwise NULL
  Node* slow = head;
  Node* fast = head;
  while(fast->next && fast->next->next){
    if(slow==fast){
      fast = head;
      break;
    }

    slow = slow->next;
    fast = fast->next->next;
  }
  if(!fast)
    return NULL;

  while(slow!=fast){
    slow = slow->next;
    fast = fast->next;
  }
  return slow;

}

```


* Check Whether a linked list is PalindromeList

The easy solution will be input a list into stack, and then compare.

If we need to have a solution which dose not require extra memory. we could revert the later half of the list, and then compare the later half with first half one by one.


```CPP

```

# Skip List

## Architecture


http://ticki.github.io/blog/skip-lists-done-right/

* Skip lists perform very well on rapid insertions because there are no rotations or reallocations.
* They’re simpler to implement than both self-balancing binary search trees and hash tables.
* You can retrieve the next element in constant time (compare to logarithmic time for inorder traversal for BSTs and linear time in hash tables).
* The algorithms can easily be modified to a more specialized structure (like segment or range “trees”, indexable skip lists, or keyed priority queues).
* Making it lockless is simple.
* It does well in persistent (slow) storage (often even better than AVL and EH).

## Basic Operation

https://leetcode.com/problems/design-skiplist/

Design a Skiplist without using any built-in libraries.

A Skiplist is a data structure that takes O(log(n)) time to add, erase and search. Comparing with treap and red-black tree which has the same function and performance, the code length of Skiplist can be comparatively short and the idea behind Skiplists are just simple linked lists.

For example: we have a Skiplist containing [30,40,50,60,70,90] and we want to add 80 and 45 into it. The Skiplist works this way:


Artyom Kalinin [CC BY-SA 3.0], via Wikimedia Commons

You can see there are many layers in the Skiplist. Each layer is a sorted linked list. With the help of the top layers, add , erase and search can be faster than O(n). It can be proven that the average time complexity for each operation is O(log(n)) and space complexity is O(n).

To be specific, your design should include these functions:

```
bool search(int target) : Return whether the target exists in the Skiplist or not.

void add(int num): Insert a value into the SkipList. 

bool erase(int num): Remove a value in the Skiplist. If num does not exist in the Skiplist, do nothing and return false. If there exists multiple num values, removing any one of them is fine.
```

See more about Skiplist : https://en.wikipedia.org/wiki/Skip_list

Note that duplicates may exist in the Skiplist, your code needs to handle this situation.

![skiplist](https://github.com/zhangruiskyline/Algorithm-and-Data-Structure/blob/master/img/skiplist.png)




