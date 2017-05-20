//https://leetcode.com/problems/basic-calculator/#/description
/*
Implement a basic calculator to evaluate a simple expression string.

The expression string may contain open ( and closing parentheses ), the plus + or minus sign -, non-negative integers and empty spaces .

You may assume that the given expression is always valid.

Some examples:
"1 + 1" = 2
" 2-1 + 2 " = 3
"(1+(4+5+2)-3)+(6+8)" = 23*/

int calculate(string s) {
  int len = s.size();
  int sign = 1;
  int ret = 0;
  int num = 0;
  stack<int> nums,ops;
  for(int i=0;i<len;i++){
      if(isdigit(s[i])){
        num = num*10+(s[i]-'0');
      }else{
        //not number anymore, so we would need to get the current calculation num and accumulated ret
        ret+=sign*num;
        num = 0;
        if(s[i]=='+') sign = 1;
        if(s[i]=='-') sign = -1;
        if(s[i]=='('){
            nums.push(ret);  //cache the results before bracket
            ops.push(sign);  //cache the sign before bracket
            ret = 0;
            sign = 1;
        }
        if (s[i] == ')' && ops.size()) {
            ret = ops.top() * ret + nums.top(); //finish the calculation of current bracket, so get cached
            ops.pop();
            nums.pop();
        }
    }
}
ret += sign * num;
return ret;
}
