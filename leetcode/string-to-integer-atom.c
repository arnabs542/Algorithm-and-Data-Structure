//https://leetcode.com/problems/string-to-integer-atoi/
class Solution {
public:
  int myAtoi(string str) {
      int len=str.size();
      long res = 0;
      int sign = 1;
      bool sign_found = false;
      
      if(len==0)
          return 0;
      int index = str.find_first_not_of(' ');
      if(str[index]=='-'||str[index]=='+'){
          sign = str[index]=='-'?-1:1;
          index++;
      }        
      for(int i=index;i<len;i++){

          if(isdigit(str[i])){
              res = res*10+str[i]-'0';
              if(res*sign >= INT_MAX) return INT_MAX;
              if(res*sign <= INT_MIN) return INT_MIN;  
          }else{
              break;
          }
          
      }    
      return (int) (res*sign);
  }
};
