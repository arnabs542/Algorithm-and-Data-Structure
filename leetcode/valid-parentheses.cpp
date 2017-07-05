//https://leetcode.com/problems/valid-parentheses/#/description
/*
Given a string containing just the characters '(', ')', '{', '}', '[' and ']', determine if the input string is valid.
The brackets must close in the correct order, "()" and "()[]{}" are all valid but "(]" and "([)]" are not
*/

bool isValid(string s) {
    stack<char> sc;
    for(int i=0;i<s.size();i++){
        if(s[i]=='(')
            sc.push(')');
        else if(s[i]=='[')
            sc.push(']');
        else if(s[i]=='{')
            sc.push('}');
        else if(sc.empty()||sc.top()!=s[i]){
            return false;
        }else{
            sc.pop();
        }

    }
    return sc.empty();
}
