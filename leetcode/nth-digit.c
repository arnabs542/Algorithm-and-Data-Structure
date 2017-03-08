//https://leetcode.com/problems/nth-digit/
/*
Find the nth digit of the infinite integer sequence 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, ...

Note:
n is positive and will fit within the range of a 32-bit signed integer (n < 231).

Example 1:
Input:
3

Output:
3
Example 2:

Input:
11
Output:
0

Explanation:
The 11th digit of the sequence 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, ... is a 0, which is part of the number 10.
*/


class Solution {
public:
    int findNthDigit(int n) {
        /*
        1-9:  9*1 
        10-99: 90*2 digits; 
        100-999,900*3 digit;  
        1000-9999,9000*4 digits
        n = sum of {9*10^(k-1) *k} + residual k>=1
        
        245th
        245-180-9=56;
        starting from 100, 56th number starting from 3 digit number(100), belongs to (56/3) = 18th from 100, 118, and real number is 56%3 = 2th of 118, 1.
        */
        //first calculate how many digits n has, k and digit
        long base = 9, digit = 1;
        while (n - base * digit > 0)
        {
            n -= base * digit;
            base *= 10;
            digit ++;
        }
      // step 2. calculate what the muber is.
        int index = n % digit;
        if (index == 0)
            index = digit;
        long num = 1;
        for (int i = 1; i < digit; i ++)
            num *= 10;
        num += (index == digit) ? n / digit - 1 : n / digit;

        // step 3. find out which digit in the number is we want.
        for (int i = index; i < digit; i ++)
            num /= 10;
        return num % 10;
    }
};
