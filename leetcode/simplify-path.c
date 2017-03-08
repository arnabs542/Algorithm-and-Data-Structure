//https://leetcode.com/problems/simplify-path/
/*
Given an absolute path for a file (Unix-style), simplify it.

For example,
path = "/home/", => "/home"
path = "/a/./b/../../c/", => "/c"
*/
class Solution {
public:
    string simplifyPath(string path) {
        vector<string> s;
        string ret;
        string cur;//cur single path string
        for(int i=0;i<path.size();i++){
            if(path[i]=='/'){
                continue;
            }
            int j = i;
            while(j<path.size() && path[j]!='/'){
                j++;
            }
            cur = path.substr(i,j-i);
            if(cur==".."){
                if(!s.empty())
                    s.pop_back();
            }else{
                if(cur!=".")
                    s.push_back(cur);
            }
            i=j;
        }
        if(s.size()==0)
            return "/";
        
       for(int i=0;i<s.size();i++){
            ret+="/"+s[i];
        }
        return ret;
        
    }
};
