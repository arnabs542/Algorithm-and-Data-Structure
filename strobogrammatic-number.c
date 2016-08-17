//https://leetcode.com/problems/strobogrammatic-number/
/*
A strobogrammatic number is a number that looks the same when rotated 180 degrees (looked at upside down).
Write a function to determine if a number is strobogrammatic. The number is represented as a string.
For example, the numbers "69", "88", and "818" are all strobogrammatic.
*/
class Solution {
public:
  bool isStrobogrammatic(string num) {
      map<int,int> m;//key is number and val  is 180 degress flipped number
      m[6] = 9;
      m[9] = 6;
      m[8] = 8;
      m[1] = 1;
      m[0] = 0;
      int start = 0;
      int end = num.size()-1;
      while(start<=end){
          int dig = num[start]-'0';
          int flip = num[end]-'0';
          if(m.find(dig)==m.end()||m.find(flip)==m.end()){
              return false;   
          }
          if(m[dig]!=flip){
              return false;
          }
          start++;
          end--;
      }
      return true;
  }
};
