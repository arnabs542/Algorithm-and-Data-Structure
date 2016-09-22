//https://leetcode.com/problems/powx-n/
O(log(n))

class Solution {
public:
    double myPow(double x, int n) {
        if(n==0)
            return 1;
        double ret = myPow(x,n/2);
        int sig = 1;
        if(n<0) sig = -1;
        if(n%2){
            ret = sig==-1?(1/x*ret*ret):x*ret*ret;
        }else{
            ret = ret*ret;
        }
        
        return ret;
    }
};
