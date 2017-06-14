/*
https://leetcode.com/problems/basic-calculator-ii/#/description
Implement a basic calculator to evaluate a simple expression string.
The expression string contains only non-negative integers, +, -, *, / operators and empty spaces . The integer division should truncate toward zero.
You may assume that the given expression is always valid.

Some examples:
"3+2*2" = 7
" 3/2 " = 1
" 3+5 / 2 " = 5
*/

int calculate(string s) {
    //key is to have a value in stack and operator saved
    int len = s.size();
    stack<int> saved;
    int cur = 0;
    char sign = '+';
    for(int i=0;i<len;i++){
        if(isdigit(s[i])){
            cur = cur*10+s[i]-'0';
        }
        if(!isdigit(s[i]) && !isspace(s[i]) || i == s.size()-1){
            if(sign=='+') saved.push(cur);
            if(sign=='-') saved.push(-cur);
            if(sign=='*'){
                int tmp = saved.top();
                saved.pop();
                saved.push(tmp*cur);
            }
            if(sign=='/'){
                int tmp = saved.top();
                saved.pop();
                saved.push(tmp/cur);
            }
            cur = 0;
            sign = s[i];
        }
    }

    int ret = 0;
    while(!saved.empty()){
        ret+=saved.top();
        saved.pop();
    }
    return ret;
}
