//https://leetcode.com/problems/intersection-of-two-linked-lists/
/*
Write a program to find the node at which the intersection of two singly linked lists begins.
For example, the following two linked lists:

A:          a1 → a2
                   ↘
                     c1 → c2 → c3
                   ↗            
B:     b1 → b2 → b3
begin to intersect at node c1.

Notes:
If the two linked lists have no intersection at all, return null.
The linked lists must retain their original structure after the function returns.
You may assume there are no cycles anywhere in the entire linked structure.
Your code should preferably run in O(n) time and use only O(1) memory.
*/

class Solution {
public:
    ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
        /*
        Find the length of both the linked lists say : a_len and b_len
Find the len Diff = (a_len ~ b_len)
Traverse the longer linked list by lenDiff
Now traverse both the lists at the same time
Check whether nodes are same, if yes then we have found the intersection point
        */
         if (headA == NULL || headB == NULL) {
            return NULL;
            }
        int lenA = getLen(headA);
        int lenB = getLen(headB);
        
        while(lenA>lenB){
            headA = headA->next;
            lenA--;
        }
        while(lenB>lenA){
            headB = headB->next;
            lenB--;
        }
        while(headA!=NULL && headB!=NULL && headA!=headB){
            headA=headA->next;
            headB=headB->next;
        }
        return headA;
 
    }
    
    int getLen(ListNode* node) {
    int len = 0;
    while (node != NULL) {
        len++;
        node = node->next;
        }
        return len;
    }

};
