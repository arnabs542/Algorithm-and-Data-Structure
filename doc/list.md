<!-- START doctoc generated TOC please keep comment here to allow auto update -->
<!-- DON'T EDIT THIS SECTION, INSTEAD RE-RUN doctoc TO UPDATE -->
**Table of Contents**  *generated with [DocToc](https://github.com/thlorenz/doctoc)*

- [Linked List](#linked-list)
  - [Fine the Cycle in Linked List](#fine-the-cycle-in-linked-list)
- [Skip List](#skip-list)
  - [Architecture](#architecture)
    - [A naïve (but common) implementation](#a-na%C3%AFve-but-common-implementation)
    - [Improved Version](#improved-version)
  - [Applications](#applications)
  - [Redis Sorted Set](#redis-sorted-set)
    - [Source code](#source-code)

<!-- END doctoc generated TOC please keep comment here to allow auto update -->

# Linked List

## Fine the Cycle in Linked List

> Fast/Slow pointer

```CPP
bool hasCycle(ListNode* head) {
    ListNode* fast; 
    ListNode* slow;
    fast = slow = head;
    while (fast != null && fast->next != null) {
        fast = fast->next->next;
        slow = slow->next;

        if (fast == slow) return true;
    }
    return false;
}
```

This will find whether there is cycle, we can also find the interdection

```CPP
ListNode* detectCycle(ListNode* head) {
    ListNode* fast; 
    ListNode* slow;
    fast = slow = head;
    while (fast != null && fast.next != null) {
        fast = fast.next.next;
        slow = slow.next;
        if (fast == slow) break;
    }
    // 上面的代码类似 hasCycle 函数
    slow = head;
    while (slow != fast) {
        fast = fast.next;
        slow = slow.next;
    }
    return slow;
}
```

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

### A naïve (but common) implementation


Our skip list consists of (in this case, three) lists, stacked such that the n‘th list visits a subset of the node the n - 1‘th list does. This subset is defined by a probability distribution, which we will get back to later.

![skiplist1](https://github.com/zhangruiskyline/Algorithm-and-Data-Structure/blob/master/img/skiplist1.png)


Self-balancing Binary Search Trees often have complex algorithms to keep the tree balanced, but skip lists are easier: They aren’t trees, they’re similar to trees in some ways, but they are not trees.

Every node in the skip list is given a “height”, defined by the highest level containing the node (similarly, the number of decendants of a leaf containing the same value). As an example, in the above diagram, “42” has height 2, “25” has height 3, and “11” has height 1.

When we insert, we assign the node a height, following the probability distribution: ```p(n)=2 ^(l-n)```. To obtain this distribution, we flip a coin until it hits tails, and count the flips:

```CPP
define generate_level():
    // First we apply some mask which makes sure that we don't get a level
    // above our desired level. Then we find the first set bit.
    ffz(random() & ((1 << max_level) - 1))
```

By this distribution, statistically the parent layer would contain half as many nodes, so searching is amortized ```O(log n) ```.



```CPP
// Recursive skip list insertion function.
define insert(elem, root, height, level):
    if right of root < elem:
        //If right isn't "overshot" (i.e. we are going to long), we go right.
        return insert(elem, right of root, height, level)
    else:
        if level = 0:
            // We're at bottom level and the right node is overshot, hence
            // we've reached our goal, so we insert the node inbetween root
            // and the node next to root.
            old ← right of root
            right of root ← elem
            right of elem ← old
        else:
            if level ≤ height:
                // Our level is below the height, hence we need to insert a
                // link before we go on.
                old ← right of root
                right of root ← elem
                right of elem ← old

            // Go a level down.
            return insert(elem, below root, height, level - 1)
```

As an example, here’s a diagram, the curved lines marks overshoots/edges where a new node is inserted:

![skiplist2](https://github.com/zhangruiskyline/Algorithm-and-Data-Structure/blob/master/img/skiplist2.png)


### Improved Version

if there is n elements, we likely to have 2n storage sapce, which is certainly no small amount, especially if you consider what each node contains, a pointer to the inner data, the node right and down, giving 5 pointers in total, so a single structure of n nodes consists of approximately 6n pointers.



But memory isn’t even the main concern! When you need to follow a pointer on every decrease (apprx. 50% of all the links), possibly leading to cache misses. It turns out that there is a really simple fix for solving this:

Instead of linking vertically, a good implementation should consist of a singly linked list, in which each node contains an array (representing the nodes above) with pointers to later nodes:

![skiplist3](https://github.com/zhangruiskyline/Algorithm-and-Data-Structure/blob/master/img/skiplist3.png)

If you represent the links (“shortcuts”) through dynamic arrays, you will still often get cache miss. Particularly, you might get a cache miss on both the node itself (which is not data local) and/or the dynamic array. As such, I recommend using a fixed-size array (beware of the two negative downsides: 1. more space usage, 2. a hard limit on the highest level, and the implication of linear upperbound when h > c. Furthermore, you should keep small enough to fit a cache line.).

Searching is done by following the top shortcuts as long as you don’t overshoot your target, then you decrement the level and repeat, until you reach the lowest level and overshoot. Here’s an example of searching for “22”:

![skiplist4](https://github.com/zhangruiskyline/Algorithm-and-Data-Structure/blob/master/img/skiplist4.png)

```CPP
define search(skip_list, needle):
    // Initialize to the first node at the highest level.
    level ← max_level
    current_node ← root of skip_list

    loop:
        // Go right until we overshoot.
        while level'th shortcut of current_node < needle:
            current_node ← level'th shortcut of current_node

        if level = 0:
            // We hit our target.
            return current_node
        else:
            // Decrement the level.
            level ← level - 1
```


## Applications

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

![skiplist](https://github.com/zhangruiskyline/Algorithm-and-Data-Structure/blob/master/img/skiplist.gif)

```CPP

//The right pointer point to the node in the same level but bigger than this. And the down pointer point to the node in the next level with the same value.

struct Node {
    Node *right;
    Node *down;
    int val;
    Node(Node *right, Node *down, int val): right(right), down(down), val(val) {}
};

class Skiplist {
    Node* head;
    //each node contains an array (representing the nodes above) with pointers to later nodes
    vector<Node*> next;
    
public:
    Skiplist() { 
        head = new Node(NULL,NULL, 0);
    }

    bool search(int num) {
        Node *p = head;
        while(p) {
            while(p->right && p->right->val < num) {
               p = p->right; 
            }
            if(!p->right || p->right->val > num) {
                p = p->down;
            } else {
               return true; 
            }
                
        }
        return false;
    }

    void add(int num) {
        next.clear();
        Node *p = head;
        while(p) {
            while(p->right && p->right->val < num) 
                p = p->right;
            next.push_back(p);
            p = p->down;
        }

        Node* downNode = NULL;
        //not all higher levels need to insert, flip coin to decide
        bool insertUp = true;
        while(insertUp && next.size()) {
            Node *ins = next.back();
            next.pop_back();
            //first insert will be current lowest level , so no down node
            ins->right = new Node(ins->right, downNode, num);
            //mark down node to be current insert node
            downNode = ins->right;

            insertUp = (rand() & 1) == 0;
        }
        //add a level
        if(insertUp) {
            head = new Node(new Node(NULL, downNode, num), head, 0);
        }
    }

    bool erase(int num) {
        Node *p = head;
        bool seen = false;
        while(p) {
            while(p->right && p->right->val < num) 
                p = p->right;
            if(!p->right || p->right->val > num) 
                p = p->down;
            else {
                seen = true;
                Node* toRemove = p->right;
                p->right = p->right->right;
                p = p->down;
                delete toRemove;
            }
        }
        return seen;
    }
};

```

## Redis Sorted Set

How is the Redis sorted set implemented?
Redis provides a data structure called “sorted sets” which are,

* similarly to Redis Sets, non repeating collections of Strings. The difference is that every member of a Sorted Set is associated with a score, that is used in order to take the sorted set ordered, from the smallest to the greatest score. While members are unique, scores may be repeated.

I was curious what data structure Redis sorted sets used, since they allow efficient ordering of the set members on two different orderings: lexicographically, and by associated score.

Looking at the source, we find that there is no fundamentally new data structure; only two old ones: a hash table and a skip list.

* ZSETs are ordered sets using two data structures to hold the same elements in order to get O(log(N)) INSERT and REMOVE operations into a sorted data structure. The elements are added to a hash table mapping Redis objects to scores. At the same time the elements are added to a skip list mapping scores to Redis objects (so objects are sorted by scores in this “view”).

** HashMap: Map redis Object to Score
** Skip List: same item added into Skip List to maintain order


### Source code

https://github.com/redis/redis/blob/unstable/src/t_zset.c


