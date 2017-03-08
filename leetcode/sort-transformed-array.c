//https://leetcode.com/problems/sort-transformed-array/
/*
Given a sorted array of integers nums and integer values a, b and c. Apply a function of the form f(x) = ax2 + bx + c to each element x in the array.
The returned array must be in sorted order.

Expected time complexity: O(n)

Example:
nums = [-4, -2, 2, 4], a = 1, b = 3, c = 5,
Result: [3, 9, 15, 33]

nums = [-4, -2, 2, 4], a = -1, b = 3, c = 5
Result: [-23, -5, 1, 7]
*/
class Solution {
public:
    vector<int> sortTransformedArray(vector<int>& nums, int a, int b, int c) {
/*
1.a>0, two ends in original array are bigger than center if you learned middle school math before.
2.a<0, center is bigger than two ends.

so use two pointers i, j and do a merge-sort like process. depending on sign of a, you may want to start from the beginning or end of the transformed array. For a==0 case, it does not matter what b's sign is.
*/      int len = nums.size();
        vector<int> ret(len,0);
        int i=0,j=len-1;
        //depending on which side is bigger, we can start to fill begin or end
        int index = a<0?0:(len-1);
        
        while(i<=j){
            if(a<0){
                //fill smallest first, start from index 0;
                ret[index] = 
                quad(nums[i], a, b, c) <= quad(nums[j], a, b, c) ? quad(nums[i++], a, b, c) : quad(nums[j--], a, b, c);
                index++;
            }else{
                //fill large first, start from index = len-1;
                ret[index] = 
                quad(nums[i], a, b, c) >= quad(nums[j], a, b, c) ? quad(nums[i++], a, b, c) : quad(nums[j--], a, b, c);        index--;        
            }
        }
        return ret;
    }
    
    int quad(int x, int a, int b, int c) {
        return a*x*x + b*x + c;
    }
};
