//https://leetcode.com/problems/convert-a-number-to-hexadecimal/
/*
Given an integer, write an algorithm to convert it to hexadecimal. For negative integer, two’s complement method is used.
*/
class Solution {
public:
    string toHex(int num) {
        string res;
        unsigned int n = num>=0?num:~(abs(num)-1);
        while (n) {
            int bit = n & 0xF;
            if (bit < 10)
                res = char('0' + bit) + res;
            else
                res = char('a' + bit - 10) +res ;
            n >>= 4;
        }
        return res.empty() ? "0" : res;
    }

};
