
/*
https://leetcode.com/problems/restore-ip-addresses/#/description
Given a string containing only digits, restore it by returning all possible valid IP address combinations.

For example:
Given "25525511135",
return ["255.255.11.135", "255.255.111.35"]. (Order does not matter)
*/

vector<string> restoreIpAddresses(string s) {
       vector<string> ret;
       vector<int> cur;//one single results

       int len = s.size();
       if((len<4) || (len>12))
           return ret;

       help(ret,s,cur,0,4);

       return ret;

   }

   void help(vector<string> &ret, string s,vector<int> &cur, int start,int seg){

       if(s.size()-start>seg*4)//invalid IP
           return;
       if(s.size()-start<seg)
           return;

       if((seg == 0) && (start ==s.size())){
           string res;
           for(int j=0;j<4;j++){
               res+=to_string(cur[j]);
               res+='.';
           }
           res.pop_back();//pop back last dot
           ret.push_back(res);
       }

       int cur_digit = 0;
       for(int i=start;i<start+3;i++){
           cur_digit = cur_digit*10+(s[i]-'0');
           if(cur_digit<=255){
               cur.push_back(cur_digit);
               help(ret,s,cur,i+1,seg-1);
               cur.pop_back();
           }
           if(cur_digit==0)
               break;
       }

   }
