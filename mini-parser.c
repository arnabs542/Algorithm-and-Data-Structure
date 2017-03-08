//https://leetcode.com/problems/mini-parser/
/*
Given a nested list of integers represented as a string, implement a parser to deserialize it.
Each element is either an integer, or a list -- whose elements may also be integers or other lists.
Note: You may assume that the string is well-formed:

String is non-empty.
String does not contain white spaces.
String contains only digits 0-9, [, - ,, ].
Example 1:

Given s = "324",
You should return a NestedInteger object which contains a single integer 324.

Example 2:
Given s = "[123,[456,[789]]]",
Return a NestedInteger object containing a nested list with 2 elements:

1. An integer containing value 123.
2. A nested list containing two elements:
    i.  An integer containing value 456.
    ii. A nested list with one element:
         a. An integer containing value 789.
*/

class Solution {
public:
    NestedInteger deserialize(string s) {
        NestedInteger ni;
        int index = 0;
        if(s.size()==0)
            return ni;
        if(s[0]=='[')
            ni = help_list(s,index); // it has nested list, continue.
        else{
            ni = help_num(s,index);  //it only has number
        }
            
        return ni;
    }
    
    NestedInteger help_list(string &s, int &index){
        NestedInteger ret;
        index++; //to skip '['
        while(index<s.size()){
            if(s[index]=='['){
                ret.add(help_list(s,index));
            }else if(isdigit(s[index])||s[index]=='-'){
                ret.add(help_num(s,index));
            }else if(s[index]==','){
                index++; //skip
            }else if(s[index]==']'){
                index++;
                break;  //reach end of current list
            }
        }
        
        return ret;
        
    }
    //set index to reference so change inside this will affect.
    NestedInteger help_num(string &s, int &index){
        int positive = 1;
        if(s[index]=='-'){
            index++;
            positive = -1;
        }
        int num = 0;
        while(index<s.size() && isdigit(s[index])){
            num = num*10 + (s[index]-'0');
            index++;
        }
        
        return NestedInteger(positive*num);
    }
};
