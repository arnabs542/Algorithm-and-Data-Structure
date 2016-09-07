//https://leetcode.com/problems/super-pow/
/*
Your task is to calculate ab mod 1337 where a is a positive integer and b is an extremely large positive integer given in the form of an array.

Example1:
a = 2
b = [3]
Result: 8
Example2:

a = 2
b = [1,0]
Result: 1024
*/

class Solution {
public:
    const int base = 1337;
    int superPow(int a, vector<int>& b) {
    //f(a,1234567) = f(a, 1234560) * f(a, 7) % k = f(f(a, 123456),10) * f(a,7)%k;
        int ret = 0;
        if(b.size()==0)
            return 1;
        int last = b.back();
        b.pop_back();
        return powmod(superPow(a,b),10)*powmod(a,last)%base;
        
    }
    
    int powmod(int a, int b){
        //a^b%base, where b<10
        a=a%base;
        int ret = 1;
        for(int i=0;i<b;i++){
            ret = a*ret%base;
        }
        return ret;
    }
};
