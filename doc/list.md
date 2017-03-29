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
