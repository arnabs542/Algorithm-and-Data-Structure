//https://leetcode.com/problems/encode-and-decode-strings/
/*
Design an algorithm to encode a list of strings to a string. The encoded string is then sent over the network and is decoded back to the original list of strings.

Machine 1 (sender) has the function:

string encode(vector<string> strs) {
  // ... your code
  return encoded_string;
}
Machine 2 (receiver) has the function:
vector<string> decode(string s) {
  //... your code
  return strs;
}
So Machine 1 does:

string encoded_string = encode(strs);
and Machine 2 does:

vector<string> strs2 = decode(encoded_string);
strs2 in Machine 2 should be the same as strs in Machine 1.

Implement the encode and decode methods.
*/

class Codec {
public:
  // Encodes a list of strings to a single string.
  string encode(vector<string>& strs) {
      string encode = "";
      if(strs.size()==0)
          return encode;
      for(int i=0;i<strs.size();i++){
          int len = strs[i].size();
          encode+=to_string(len)+'@'+strs[i];
          
      }
      return encode;
  }

  // Decodes a single string to a list of strings.
  vector<string> decode(string s) {
      vector<string> ret;
      if(s.size()==0)
          return ret;
      int start = 0;
      int len = s.size();
      while(start<len){
          int len = 0;
          while(s[start]!='@'){
              len = len*10+s[start]-'0';
              start++;
          }
          start++;
          ret.push_back(s.substr(start,len));
          start = start+len;

      }
      
      return ret;
  }
};
