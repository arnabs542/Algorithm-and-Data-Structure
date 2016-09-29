//https://leetcode.com/problems/range-sum-query-mutable/
/*
Given an integer array nums, find the sum of the elements between indices i and j (i ≤ j), inclusive.
The update(i, val) function modifies nums by updating the element at index i to val.

Example:

Given nums = [1, 3, 5]

sumRange(0, 2) -> 9
update(1, 2)
sumRange(0, 2) -> 8
*/
class NumArray {
private:
    vector<int> tree;
    int len = 0;
public:
    NumArray(vector<int> &nums) {
        len = nums.size();
        tree.resize(2*len,0);
        for(int i=len,j=0;i<2*len;i++,j++){
            tree[i] = nums[j];
        }
        for(int i=len-1;i>=0;i--){
            tree[i] = tree[2*i]+tree[2*i+1];
        }
    }

    void update(int i, int val) {
        int shift = tree[len+i] - val;
        int index = len+i;
        while(index>=1) {
            tree[index] = tree[index] - shift;
            index = index/2;
        }
    }

    int sumRange(int i, int j) {
        // get leaf with value 'i'
        i += len;
        // get leaf with value 'j'
        j += len;
        int sum = 0;
        while (i <= j) {
            if ((i % 2) == 1) {
               sum += tree[i];
               i++;
            }
            if ((j % 2) == 0) {
               sum += tree[j];
               j--;
            }
            i /= 2;
            j /= 2;
        }
        return sum;
    }
};
