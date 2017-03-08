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


//method 2:
//Find the maximum integer that is a power of 3 and check if it is a multiple of the given input.
public boolean isPowerOfThree(int n) {
    //maxPowerOfThree = 1162261467
    return n > 0 && (1162261467 % n == 0);
}
//method 3: use hash set
public boolean isPowerOfThree(int n) {
    unordered_set<int> s(1, 3, 9, 27, 81, 243, 729, 2187, 6561, 19683, 59049, 177147, 531441, 1594323, 4782969, 14348907, 43046721, 129140163, 387420489, 1162261467);
    return s.find(n)!=s.end();
}
