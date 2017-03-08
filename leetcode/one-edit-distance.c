//https://leetcode.com/problems/one-edit-distance/
//Given two strings S and T, determine if they are both one edit distance apart.
class Solution {
public:
    bool isOneEditDistance(string s, string t) {
        /*
        3 cases: insert, delete, or substitute
        */
        int len_s = s.size();
        int len_t = t.size();
        if(len_s-len_t>1 or len_t-len_s>1)
            return false;        
        if(s==t)
            return false;
        if(len_t<len_s)
            return isOneEditDistance(t,s);
        bool diff = false; 
        //Here we can not use len_s since s size could increase
        for(int i=0;i<s.size();i++){
            if(s[i]!=t[i]){
                if(!diff){
                    //found the first diff, 
                    if(len_s==len_t)
                        s[i]=t[i];
                    else
                        s.insert(i,1,t[i]);
                    diff = true;
                }else{
                    //found the second diff, false
                    return false;
                }
            }
            
        }

        return true;
    }
};
