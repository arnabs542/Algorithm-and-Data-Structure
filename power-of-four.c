//https://leetcode.com/problems/power-of-four/
class Solution {
public:
    bool isPowerOfFour(int num) {
        if(num==1)
            return true;
        if(num<=0)
            return false;
            
        while(num%4==0){
            num = num/4;
            if(num==1)
                return true;
        }
        return false;
    }
};

//method 2:
class Solution {
public:
    bool isPowerOfFour(int num) {
        return ((num-1)&num)==0 && (num-1)%3==0;
    }
};
