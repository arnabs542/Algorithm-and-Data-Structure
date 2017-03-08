//https://leetcode.com/problems/power-of-two/
//Given an integer, write a function to determine if it is a power of two. 
class Solution {
public:
  bool isPowerOfTwo(int n) {
      if(n==1)
          return true;
      if(n<=0)
          return false;
          
      while(n%2==0){
          n = n/2;
          if(n==1)
              return true;
      }
      return false;
      
  }
}

//method 2: use bit shift
class Solution {
public:
    bool isPowerOfTwo(int n) {
        return n > 0 && (n & (n-1))==0;
    }
};
