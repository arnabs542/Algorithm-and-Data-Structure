//https://leetcode.com/problems/plus-one-linked-list/
/*
Given a non-negative number represented as a singly linked list of digits, plus one to the number.
The digits are stored such that the most significant digit is at the head of the list.

Example:
Input:
1->2->3

Output:
1->2->4
*/

//Method 1: clean recursive one
class Solution {
public:
  ListNode* plusOne(ListNode* head) {
      if(!head)
          return head;
      
      int carry =  help(head);
      if(carry == 1){
          ListNode* newone = new ListNode(carry);
          newone->next = head;
          return newone;
      }else{
          return head;
      }
      
  }
  //return the carry
  int help(ListNode* head){
      int num;
      if(head->next==NULL){
          //reach end;
          num = head->val + 1;
      }else{
          num = head->val+help(head->next);
      }
      if(num<10){
          head->val = num;
          return 0;
      }else{
          head->val = 0;
          return 1;
      }
  }
};

//method 2: ierative: need to reverse list
class Solution {
public:
  ListNode* plusOne(ListNode* head) {
      if(!head)
          return head;
      
      reverse(&head);
      
      int carry = 0;
      int addsum = 1;
      ListNode* cur = head;
      ListNode* prev = cur;
      while(cur!=NULL){
          addsum += cur->val + carry;
          carry = 0;
          if(addsum<10){
              cur->val = addsum;
              break;
          }else{
              carry = 1;
              addsum = 0;
              cur->val = addsum;
              prev = cur;
              cur = cur->next;
          }
      }
      if(carry!=0){
          ListNode * newone = new ListNode(carry);
          prev->next = newone;
          newone->next = NULL;
      }
      
      reverse(&head);    
      
      return head;
  }
  
  void reverse(ListNode** head){
      ListNode *prev = NULL, *cur = *head;
      while (cur) {
          ListNode *next = cur->next;
          cur->next = prev;
          prev = cur;
          cur = next;
      }
      *head = prev;
  }
};
