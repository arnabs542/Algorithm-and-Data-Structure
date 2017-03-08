//https://leetcode.com/problems/sqrtx/
//Implement int sqrt(int x).
class Solution {
public:
    int mySqrt(int x) {
        long low=1;
        long high = x;
        
        while(low<=high){
            long mid = low+(high-low)/2;
            if(mid*mid==x)
                return mid;
            else if(mid*mid<x)
                low = mid+1;
            else
                high = mid-1;
        }
        
        return high;
    }
};
