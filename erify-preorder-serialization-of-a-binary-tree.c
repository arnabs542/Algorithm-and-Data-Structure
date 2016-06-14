//https://leetcode.com/problems/verify-preorder-serialization-of-a-binary-tree/
/*
One way to serialize a binary tree is to use pre-order traversal. When we encounter a non-null node, we record the node's value. If it is a null node, we record using a sentinel value such as #.

     _9_
    /   \
   3     2
  / \   / \
 4   1  #  6
/ \ / \   / \
# # # #   # #
For example, the above binary tree can be serialized to the string "9,3,4,#,#,1,#,#,2,#,6,#,#", where # represents a null node.
*/
class Solution {
public:
    bool isValidSerialization(string preorder) {
        /*
        When adding a node, capacity--;
        When adding a non-NULL node, it means we obtains two more leafs, then capacity +=2.
        The final capacity should be equal to 0
        */
        if (preorder.empty()) 
            return false;

        int sz=preorder.size(),idx=0;
        int capacity=1;
        for (idx=0;idx<sz;idx++){
            if (preorder[idx]==',') continue;
            capacity--;
            if (capacity<0) 
                return false;
            if (preorder[idx]!='#') 
                capacity+=2;
            while(idx<sz && preorder[idx]!=',') //for data more than one char
                idx++;
        }
        return capacity==0;
    }
};
