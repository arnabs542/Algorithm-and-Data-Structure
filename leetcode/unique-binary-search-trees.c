//https://leetcode.com/problems/unique-binary-search-trees/
/*
Given n, how many structurally unique BST's (binary search trees) that store values 1...n?

For example,
Given n = 3, there are a total of 5 unique BST's.

   1         3     3      2      1
    \       /     /      / \      \
     3     2     1      1   3      2
    /     /       \                 \
   2     1         2                 3
*/

class Solution {
public:
  int numTrees(int n) {
      /*
       we can choose i as root, so 1->i-1 is left side, and i+1->n is right side
       g(n) is the num of unique tree for sequnce length of n,
       f(i,n) is num of unique tree when choosing i as root?
       g[n] = f(1,n) + f(2,n) + f(3,n) ...+ f(n,n)
       and we can see
       [1,2,3,4,5,6], f(3,6) = g(1,2)*g(4,5,6) = g(2)*g(3)
       f(i,n) = g(i-1)*g(n-i)
       so g(n) = g(0)*g(n-1)+g(1)*g(n-1)...+g(n-1)*g(0)
      */
      vector<int>g(n+1,0);
      g[0] = 1; 
      g[1] = 1;
      for(int i=2;i<=n;i++){
          for(int j=1;j<=i;j++){
              g[i] += g[j-1]*g[i-j];
          }
      }
      
      return g[n];
  }
};
