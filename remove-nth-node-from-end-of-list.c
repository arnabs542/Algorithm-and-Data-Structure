//https://leetcode.com/problems/remove-nth-node-from-end-of-list/

/*
Given linked list: 1->2->3->4->5, and n = 2.
After removing the second node from the end, the linked list becomes 1->2->3->5.
*/

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        ListNode* dummy;
        dummy->next = head;
        ListNode* cur = dummy;
        ListNode* ahead = dummy;
        
        for(int i=0;i<=n;i++){
            ahead = ahead->next;
            if(ahead==NULL && i<n)
                return head;
        }
        
        while(ahead!=NULL){
            cur=cur->next;
            ahead=ahead->next;
        }
        cur->next = cur->next->next;

        return dummy->next;
        
    }
};
