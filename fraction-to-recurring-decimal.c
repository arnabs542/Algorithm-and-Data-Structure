//https://leetcode.com/problems/fraction-to-recurring-decimal/
/*
Given two integers representing the numerator and denominator of a fraction, return the fraction in string format.
If the fractional part is repeating, enclose the repeating part in parentheses.

For example,
    Given numerator = 1, denominator = 2, return "0.5".
    Given numerator = 2, denominator = 1, return "2".
    Given numerator = 2, denominator = 3, return "0.(6)".
*/
class Solution {
public:
  string fractionToDecimal(int numerator, int denominator) {
      /*
      the key to this problem is on how to identify the recurring parts. After doing some examples using pen and paper, you may find that for the decimal parts to recur, the remainders should recur. So we need to maintain the remainders we have seen. Once we see a repeated remainder, we know that we have reached the end of the recurring parts and should enclose it with a ). However, we still need to insert the ( to the correct position. So we maintain a mapping from each remainder to the position of the corresponding quotient digit of it in the recurring parts. Then we use this mapping to retrieve the starting position of the recurring parts        
      */
      string s = "";
      if((numerator>0)&&(denominator<0)||(numerator<0)&&(denominator>0)){
          s+= '-';
      }
      long n = numerator < 0 ? (long)numerator * (-1) : (long)numerator;
      long d = denominator < 0 ? (long)denominator * (-1) : (long)denominator;
      s+=to_string(n/d);
      if(n%d==0)
          return s;
      s+=".";
      unordered_map<long,int> m;
      long r = (n%d);
      r*=10;

      //if r==0, then we are done
      while(r){
          long res = r/d;
          //found repeat, noticing we need to have numerator as key
          if(m.find(r)!=m.end()){
              s.insert(m[r],1,'(');
              s+=')';
              return s;
          }
          m[r] = s.size();  //mark where to insert '(' at begining the repeating  
          s+=to_string(res);  //add divide result
          r=(r%d)*10;
      }
      
      return s;
  }
};
