//https://leetcode.com/problems/super-ugly-number/
/*
Write a program to find the nth super ugly number.

Super ugly numbers are positive numbers whose all prime factors are in the given prime list primes of size k. 
For example, [1, 2, 4, 7, 8, 13, 14, 16, 19, 26, 28, 32] is the sequence of the first 12 super ugly numbers 
given primes = [2, 7, 13, 19] of size 4.

Note:
(1) 1 is a super ugly number for any given primes.
(2) The given numbers in primes are in ascending order.
(3) 0 < k ≤ 100, 0 < n ≤ 106, 0 < primes[i] < 1000.
*/

class Solution {
public:
    int nthSuperUglyNumber(int n, vector<int>& primes) {
        //DP, Keep k pointers and update them in each iteration. Time complexity is O(kn).
        /*
    Every ugly number is constructed from multiply a previous ugly number by one of the primes in the list. If current ugly number is ugly[i] , Index[j] is the index of the smallest of all ugly numbers that we already constructed , such that prime[j]*ugly[index[j]] is not found yet.
    
    index[j] will keep on evolving.first it will be only 0 which corresponding to ugly[0], then once a new ugly is matched, it will be updated by adding one.
        */
        vector<int> ugly(n,INT_MAX);
        int len = primes.size();
        vector<int> index(len,0);
        ugly[0] = 1;
        for(int i=1;i<n;i++){
            for(int j=0;j<len;j++){
                ugly[i] = min(ugly[i],ugly[index[j]]*primes[j]);
            }
            for(int j=0;j<len;j++){
                if(ugly[i]==ugly[index[j]]*primes[j])
                    index[j]++;
            }
        }
        
        return ugly[n-1];
    }
};
