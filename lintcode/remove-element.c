//http://www.lintcode.com/en/problem/remove-element/
/*
Given an array and a value, remove all occurrences of that value in place and return the new length.
keep the order
Example
Given an array [0,4,4,0,0,2,4,4], value=4
return 4 and front four elements of the array is [0,0,0,2]
*/
class Solution {
public:
    /** 
     *@param A: A list of integers
     *@param elem: An integer
     *@return: The new length after remove
     */
    int removeElement(vector<int> &A, int elem) {
        int start = 0;
        int n = A.size();
        for(int i = 0; i < n; i++)
            if (elem != A[i]) {
                A[start++] = A[i];
            }
        return start;
    }
};
