//https://leetcode.com/problems/integer-replacement/
/*
 Given a positive integer n and you can do operations as follow:

    If n is even, replace n with n/2.
    If n is odd, you can replace n with either n + 1 or n - 1.

What is the minimum number of replacements needed for n to become 1?

Example 1:
Input:
8
Output:
3

Explanation:
8 -> 4 -> 2 -> 1

Example 2:
Input:
7
Output:
4
Explanation:
7 -> 8 -> 4 -> 2 -> 1
or
7 -> 6 -> 3 -> 2 -> 1
*/

class Solution {
public:
    int integerReplacement(int n) {
        /*
        111011 -> 111010 -> 11101 -> 11100 -> 1110 -> 111 -> 1000 -> 100 -> 10 -> 1
        And yet, this is not the best way because
        
        111011 -> 111100 -> 11110 -> 1111 -> 10000 -> 1000 -> 100 -> 10 -> 1
        See? Both 111011 -> 111010 and 111011 -> 111100 remove the same number of 1's, but the second way is better.
        
        So, we just need to remove as many 1's as possible,
        */
        int ret = 0;
        if(n==INT_MAX)
            return 32;
        
        while(n!=1){
            if(n%2!=0){
                if(n==3 || bitcount(n-1)<bitcount(n+1)){
                    n = n-1;
                }else{
                    n = n+1;
                }
            }else{
                n = n/2;
            }
            ret++;
        }
        return ret;
    }
    
    int bitcount(int n){
    	int count = 0;
    	if(n == 0) count = 0;
    
    	do{
    		count++;
    	}while(n&=(n-1));
    	
    	return count;
    }
};
