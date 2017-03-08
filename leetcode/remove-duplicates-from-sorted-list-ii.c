//https://leetcode.com/problems/remove-duplicates-from-sorted-list-ii/
/*
Given a sorted linked list, delete all nodes that have duplicate numbers, leaving only distinct numbers from the original list.

For example,
Given 1->2->3->3->4->4->5, return 1->2->5.
Given 1->1->1->2->3, return 2->3.
*/

class Solution {
public:
  ListNode* deleteDuplicates(ListNode* head) {
      
      if(!head)
          return head;

      ListNode* dummy = new ListNode(0);
      dummy->next = head;
      ListNode* prev = dummy;
      ListNode* cur = head;
      bool found = false;
      ListNode *tmp;
      
      while(cur){
          while(cur->next!=NULL && cur->val==cur->next->val){
              cur = cur->next;
          }
          if(prev->next!=cur){
              prev->next = cur->next;
              cur = prev->next;
          }else{
              prev = prev->next;
              cur = cur->next;
          }
      }
      
      return dummy->next;
  }
};
