//https://leetcode.com/problems/self-crossing/
/*
You are given an array x of n positive numbers. You start at point (0,0) and moves x[0] metres to the north, then x[1] metres to the west, x[2] metres to the south, x[3] metres to the east and so on. In other words, after each move your direction changes counter-clockwise.

Write a one-pass algorithm with O(1) extra space to determine, if your path crosses itself, or not.

Example 1:
Given x = [2, 1, 1, 2],
┌───┐
│   │
└───┼──>
    │

Return true (self crossing)
Example 2:
Given x = [1, 2, 3, 4],
┌──────┐
│      │
│
│
└────────────>

Return false (not self crossing)
Example 3:
Given x = [1, 1, 1, 1],
┌───┐
│   │
└───┼>

Return true (self crossing)
*/

class Solution {
public:
/*
No crossing is produced when the path keeps going either 'inward' or 'outward'.
A path without crossing is either one of the two above cases or a combination of both (an outward path transit into an inward path).
*/
    bool isSelfCrossing(vector<int>& x) {
        int i; 
        // started 'outside', walk until 'inside' a rectangle
        for(i=2; i<x.size()&&x[i]>x[i-2]; i++);
        // out->in transition step(x[i]>=x[i-2]-x[i-4])
        if( i>2 && x[i] >= x[i-2]-(i==3?0:x[i-4]) ) 
            x[i-1] -= x[i-3];
        // we are inside a rectangle now, check for crossing
        for(i++; i<x.size()&&x[i]<x[i-2]; i++);
        // crossing detected if end is not reached
        return i<x.size();
    
    }
};
