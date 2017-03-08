//https://leetcode.com/problems/remove-k-digits/
/*
Given a non-negative integer num represented as a string, remove k digits from the number so that the new number is the smallest possible.

Note:
The length of num is less than 10002 and will be ≥ k.
The given num does not contain any leading zero.
Example 1:

Input: num = "1432219", k = 3
Output: "1219"
Explanation: Remove the three digits 4, 3, and 2 to form the new number 1219 which is the smallest.
Example 2:

Input: num = "10200", k = 1
Output: "200"
Explanation: Remove the leading 1 and the number is 200. Note that the output must not contain leading zeroes.
Example 3:

Input: num = "10", k = 2
Output: "0"
Explanation: Remove all the digits from the number and it is left with nothing which is 0.
*/
class Solution {
public:
    string removeKdigits(string num, int k) {
        string ret;
        int len = num.size();
        if( len == k) return string("0");
        //while the last number is larger than the new one, 
        // keep poping out the last number until a smaller one appears
        for(int i=0;i<num.size();i++){
            while(!ret.empty() && k>0 && ret.back()>num[i]){
                ret.pop_back();
                k--;
            }
            ret.push_back(num[i]);
        }
                // for monotonically increasing string
        // discard the last k digits
        // e.g. 123456 k=3
        while (k != 0){
            k--;
            ret.pop_back();
        }
        
       // for sol with leading zeros
        // e.g. 10200 k=1
        while(ret[0] == '0') ret.erase(0,1);
        
        return ret.length() == 0 ? "0" : ret;
    }
};
