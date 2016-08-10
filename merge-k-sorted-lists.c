//https://leetcode.com/problems/merge-k-sorted-lists/
//Merge k sorted linked lists and return it as one sorted list. Analyze and describe its complexity.

/*
Method 1: heap sort
complexity: heap size is k, so insert is log(k), k list with n items in each, nklog(k)
*/
class Solution {
public:
  struct mycompare{
      bool operator()(ListNode* a, ListNode* b){
          return a->val>b->val;
      }
  };

  ListNode* mergeKLists(vector<ListNode*>& lists) {
      ListNode* ret = NULL;

      //construct min heap
      priority_queue<ListNode*, vector<ListNode*>, mycompare> pq; 
      ListNode* dummy = new ListNode(0);
      ListNode* head = dummy;
      for(int i=0; i<lists.size(); i++){ 
          if(lists[i]){ 
              pq.push(lists[i]);
          }
      }
      //complexity: heap size is k, so insert is log(k), k list with n items in each, nklog(k)
      while(!pq.empty()){
          head->next = pq.top();
          head = head->next;
          if(head->next)
              pq.push(head->next);
          pq.pop();
      }
      
      return dummy->next;
      
  }
};

/*
Method 2: leverage merge 2 list
//complexity: 
//n+2n+3n..kn= O(nk^2)
*/
class Solution {
public:
  ListNode* mergeKLists(vector<ListNode*>& lists) {
      ListNode* ret = NULL;
      if(lists.size()==0)
          return ret;
      ret=lists[0];
      for(int i=1;i<lists.size();i++){
          ret=merge2list(ret, lists[i]);
      }
      
      return ret;
      
  }
  
  ListNode* merge2list(ListNode* l1, ListNode* l2){
      ListNode* dummy = new ListNode(0);
      ListNode* head = dummy;
      while(l1&&l2){
          if(l1->val<l2->val){
              head->next = l1;
              head=head->next;
              l1 = l1->next;
          }else{
              head->next = l2;
              head=head->next;   
              l2 = l2->next;
          }
      }
      if(l1)
          head->next = l1;
      if(l2)
          head->next = l2;
          
      return dummy->next;
  }
};

//Method 3, use same merge 2 list, but in binary way
/*
//complexity: suppose each list is n length. vector size is k
//2n * k/2 + 4n * k/4 + ... + (2^x)n * k/(2^x) = nk * x
//2^x = k, x=log(k)
//total is nklog(k)
*/
ListNode* mergeKLists(vector<ListNode*>& lists) {
    if (lists.empty()) return NULL;
    int end = lists.size()-1;
    int begin = 0;

    while (end>0) {
        begin = 0;
        while(begin<end){
            lists[begin] = merge2list(lists[begin], lists[end]);
            begin++;
            end--;
        }
    }
    
    return lists.front();
    
}
