//https://leetcode.com/problems/count-primes/
/*
Count the number of prime numbers less than a non-negative number, n.
Let's start with a isPrime function. To determine if a number is prime, we need to check if it is not divisible by any number less than n. The runtime complexity of isPrime function would be O(n) and hence counting the total prime numbers up to n would be O(n2). Could we do better?
As we know the number must not be divisible by any number > n / 2, we can immediately cut the total iterations half by dividing only up to n / 2. Could we still do better?

Let's write down all of 12's factors:
2 × 6 = 12
3 × 4 = 12
4 × 3 = 12
6 × 2 = 12
As you can see, calculations of 4 × 3 and 6 × 2 are not necessary. Therefore, we only need to consider factors up to √n because, if n is divisible by some number p, then n = p × q and since p ≤ q, we could derive that p ≤ √n.
Our total runtime has now improved to O(n1.5), which is slightly better. Is there a faster approach?
 is not a prime because it is divisible by 2, which means all multiples of 4 must also be divisible by 2 and were already marked off. So we can skip 4 immediately and go to the next number, 5. Now, all multiples of 5 such as 5 × 2 = 10, 5 × 3 = 15, 5 × 4 = 20, 5 × 5 = 25, ... can be marked off. There is a slight optimization here, we do not need to start from 5 × 2 = 10. Where should we start marking off?

In fact, we can mark off multiples of 5 starting at 5 × 5 = 25, because 5 × 2 = 10 was already marked off by multiple of 2, similarly 5 × 3 = 15 was already marked off by multiple of 3. Therefore, if the current number is p, we can always mark off multiples of p starting at p2, then in increments of p: p2 + p, p2 + 2p, ... Now what should be the terminating loop condition?
*/

class Solution {
public:
  int countPrimes(int n) {
      int cnt = 0;
      vector<bool> prime(n,true);
      prime[0] = false;
      prime[1] = false;
      /* we only need to consider factors up to √n because, if n is divisible by some number p, then n = p × q and since p ≤ q, we could derive that p ≤ √n.
      */
      for(int i=2;i*i<n;i++){
          if(prime[i]){//if it is already none prime, skip
              for(int j=i*i;j<n;j=j+i){
                  prime[j] = false;
              }
          }    
      }
      for(int i=2;i<n;i++){
          if(prime[i])
              cnt++;
      }
      return cnt;
  }
};
