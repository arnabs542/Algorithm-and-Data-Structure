//https://leetcode.com/problems/add-strings/
/*
Given two non-negative numbers num1 and num2 represented as string, return the sum of num1 and num2.

Note:

The length of both num1 and num2 is < 5100.
Both num1 and num2 contains only digits 0-9.
Both num1 and num2 does not contain any leading zero.
You must not use any built-in BigInteger library or convert the inputs to integer directly.
*/

class Solution {
public:
    string addStrings(string num1, string num2) {

        string ret;
        int carry = 0;
        int i = num1.size()-1;
        int j = num2.size()-1;
        while(i>=0 || j>=0){
            int cur = carry;
            if(i>=0){
                cur += (num1[i--]-'0');
            }
            if(j>=0){
                cur += (num2[j--]-'0');
            }
            carry = cur/10;
            ret+=to_string(cur%10);
        }
        if(carry!=0){
            ret+=to_string(carry);
        } 
        reverse(ret.begin(),ret.end());
        return ret;
    }
};
