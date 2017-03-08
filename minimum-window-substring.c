//https://leetcode.com/problems/minimum-window-substring/
/*
Given a string S and a string T, find the minimum window in S which will contain all the characters in T in complexity O(n).

For example,
S = "ADOBECODEBANC"
T = "ABC"
Minimum window is "BANC".

Note:
If there is no such window in S that covers all characters in T, return the empty string "".
*/
class Solution {
public:
  string minWindow(string s, string t) {
      string ret="";
      int start = 0;
      int end = 0;
      int d = INT_MAX;  //length of window size
      int head = 0; //start of sub string 
      vector<int> m(128,0);
      
      for(int i=0;i<t.size();i++){
          m[t[i]]++;
      }
      int counter = t.size();    
      while(end<s.size()){
          if(m[s[end]]-->0)  //find it is in t
              counter--;
          end++;
          //found all in t, 
          while(counter==0){
             if(end-start<d){
                 d = end-start;
                 head = start;
             }
             //we move start pointer to try to find another instance, we need to add back the hash table and counter.
             if(m[s[start]]++==0)
                  counter++;
             start++;
          }
      }
      
      return d==INT_MAX?"":s.substr(head,d);

  }
};
