//https://leetcode.com/problems/linked-list-random-node/
/*
Given a singly linked list, return a random node's value from the linked list. Each node must have the same probability of being chosen.

Follow up:
What if the linked list is extremely large and its length is unknown to you? Could you solve this efficiently without using extra space?
*/

/*
Reservoir sampling is a family of randomized algorithms for randomly choosing a sample of k items from a list S containing n items, where n is either a very large or unknown number. Typically n is large enough that the list doesn't fit into main memory.
•	Keep the first item in memory.
•	When i-th item comes
--With 1/i probability, replace the first item with new item
--With (1-1/i) probability, keep item
*/

class Solution {
private:
  ListNode* head;
public:
  /** @param head The linked list's head. Note that the head is guanranteed to be not null, so it contains at least one node. */
  Solution(ListNode* head) {
      this->head = head;
  }
  
  /** Returns a random node's value. */
  int getRandom() {
      int ret = head->val;
      ListNode* node = head;
      node = node->next;
      int len = 2;
      while(node){
          int j = rand()%len;
          if(j==0){
              ret = node->val;
          }
          node = node->next;
          len++;
      }
      return ret;
  }
};
