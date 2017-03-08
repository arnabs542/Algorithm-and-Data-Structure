//https://leetcode.com/problems/linked-list-cycle-ii/
/*
Given a linked list, return the node where the cycle begins. If there is no cycle, return null.
Note: Do not modify the linked list.
*/
class Solution {
public:
    ListNode *detectCycle(ListNode *head) {
        /*
        start to cycle begin is n, cycle length is m, and slow and fast pointers meet k after cycle begin
        2(n+k)=n+k+m
        n = m-k,
        */
        
        
        if(head==NULL || head->next==NULL)
            return NULL;
        int slow_len = 0;
        int fast_len = 0;
        ListNode * slow = head->next;
        slow_len +=1;
        ListNode * fast = head->next->next;
        fast_len+=2;
        bool found = false;
        while(fast!=NULL && fast->next != NULL){
            if(slow==fast){
                found = true;
                break;
            }
            slow = slow->next;
            slow_len +=1;
            fast = fast->next->next;
            fast_len+=2;
        }
        
        if(!found)
            return NULL;
        //cycle found
        //from meet point, if move to m-k = n steps will go to cycle start
        slow = head;
        while(fast!=slow){
            fast = fast->next;
            slow = slow->next;
        }
        return fast; 
    }
};
