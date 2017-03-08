//https://leetcode.com/problems/rectangle-area/
/*
Rectangle Area
Assume that the total area is never beyond the maximum possible value of int.
*/
class Solution {
public:
    int computeArea(int A, int B, int C, int D, int E, int F, int G, int H) {
        int area1 = (C-A)*(D-B);
        int area2 = (G-E)*(H-F);
        int overlap = 0;
        if(E>=C || F>=D || G<=A || H<=B)    return area1+area2; // no overlap
        return area1+area2 - (min(C,G) - max(A,E)) * (min(D,H) - max(B,F)); //areas of the two rectangle - overlap
        }
};
