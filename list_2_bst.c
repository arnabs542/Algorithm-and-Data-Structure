https://leetcode.com/problems/convert-sorted-list-to-binary-search-tree/

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    TreeNode* sortedListToBST(ListNode* head) {
        int len = 0;
        ListNode* cur = head;
        while(cur){
            len++;
            cur = cur->next;
        }
        
        return sortedListToBSTConstruct(head, 0, len-1);
    } 

        
    TreeNode* sortedListToBSTConstruct(ListNode* &head, int start, int end){
        if(start>end)
            return NULL;
        int mid = (start+end)/2; 
        TreeNode * left = sortedListToBSTConstruct(head,start,mid-1);
        TreeNode* node = (TreeNode*)malloc(sizeof(TreeNode));
        node->val = head->val;
        head=head->next;
        TreeNode * right  = sortedListToBSTConstruct(head,mid+1,end);
        node->left = left;
        node->right = right;
        return node;
    }

};
