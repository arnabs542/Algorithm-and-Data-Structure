//https://leetcode.com/problems/power-of-three/
//Given an integer, write a function to determine if it is a power of three. 
class Solution {
public:
    bool isPowerOfThree(int n) {
        if(n==1)
            return true;
        if(n<=0)
            return false;
            
        while(n%3==0){
            n = n/3;
            if(n==1)
                return true;
        }
        return false;
    }
};
