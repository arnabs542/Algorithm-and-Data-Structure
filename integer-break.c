//https://leetcode.com/problems/integer-break/
/*
Given a positive integer n, break it into the sum of at least two positive integers and maximize the product of those integers. Return the maximum product you can get.
For example, given n = 2, return 1 (2 = 1 + 1); given n = 10, return 36 (10 = 3 + 3 + 4).
Note: you may assume that n is not less than 2.
*/
class Solution {
public:
  int integerBreak(int n) {
        /*
        BP:max_product[i] is max value with breaking i;
        break max_product[i] = (i-1)*1;(i-2)*2;(i-3)*3...
        in general, if any i can be broken into (i-j;j), new max = max(max(i-j),(i-j)) * max(j,max(j)
        */
      vector<int> max_product(n+1,1);
      for(int i=2;i<=n;i++){
          for(int j=1;j<i;j++){
              max_product[i] = max(max(i-j, max_product[i-j]) * max(j, max_product[j]), max_product[i]);
              
          }
      }
      return max_product[n];
  }
};
