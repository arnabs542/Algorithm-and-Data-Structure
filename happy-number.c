//https://leetcode.com/problems/happy-number/
/*
Write an algorithm to determine if a number is "happy".

A happy number is a number defined by the following process: Starting with any positive integer, replace the number by the sum of the squares of its digits, and repeat the process until the number equals 1 (where it will stay), or it loops endlessly in a cycle which does not include 1. Those numbers for which this process ends in 1 are happy numbers.

Example: 19 is a happy number

12 + 92 = 82
82 + 22 = 68
62 + 82 = 100
12 + 02 + 02 = 1
*/

//Method 1: Loop detection using fast/slow
class Solution {
public:
  bool isHappy(int n) {
      //for any number, using this way it will form a loop
      //2,4,37,58,89,145,42,20,4. loop detected, so use same fast/slow method in linked list to detect loop
      int i = n;
      int j = next(n);
      while(i!=j){
          i = next(i);
          j = next(next(j));
      }
      return i==1;
  }
  
  int next(int n){
      int ret = 0;
      while(n){
          int a = n%10;
          ret+=a*a;
          n = n/10;
      }
      return ret;
  }
};

//Method 2: using hash
class Solution {
public:
  bool isHappy(int n) {
      //for largest INT:2,147,483,647, its sum of digit power 2 is 4+99*9(2,999,999,999)
      //so we maitain a 1000 length vector
      vector<int> v(1000,0);
      int dig = next(n);
      while(!v[dig]){
          v[dig] = 1;
          dig = next(dig);
          if(dig==1)
              return true;
      }
      return false;
  }
  
  int next(int n){
      int ret = 0;
      while(n){
          int a = n%10;
          ret+=a*a;
          n = n/10;
      }
      return ret;
  }
};
