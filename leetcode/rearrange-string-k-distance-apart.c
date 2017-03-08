//https://leetcode.com/problems/rearrange-string-k-distance-apart/
/*
Given a non-empty string str and an integer k, rearrange the string such that the same characters are at least distance k from each other.
All input strings are given in lowercase letters. If it is not possible to rearrange the string, return an empty string "".

Example 1:
str = "aabbcc", k = 3
Result: "abcabc"

The same letters are at least distance 3 from each other.
Example 2:
str = "aaabc", k = 3 
Answer: ""

It is not possible to rearrange the string.
Example 3:
str = "aaadbbcc", k = 2
Answer: "abacabcd"

Another possible answer is: "abcabcda"
The same letters are at least distance 2 from each other.
*/
class Solution {
public:
  string rearrangeString(string str, int k) {
      if(k==0)
          return str;
      int len = str.size();
      map<char,int> m;
      priority_queue<pair<int,char>> pq;
      string ret;
      
      for(int i=0;i<len;i++){
          m[str[i]]++;
      }
      //insert in pq so that char with largest number of occurance will be top
      for(std::map<char,int>::iterator it=m.begin(); it!=m.end(); ++it){
          pq.push(make_pair(it->second,it->first));
      }
      
      while(!pq.empty()){
          vector<pair<int,char>> tmp;
          int cnt = min(k,len);
          for(int i=0;i<cnt;i++){
              /*check in case after len--, len<k, so there are still items in pq that can be not separated in k
              if cnt = len, like aabbc, after one rounds it will be ret = abc and 
              remaining is bc.so in this case using k will result to pq.pop() 3 times, which could lead to wrong answer
              */
              if(pq.empty()) 
                  return "";
              pair<int,char> cur = pq.top();
              ret.push_back(cur.second);
              cur.first--;
              if(cur.first>0) //if particular char has been used out, do not push to vector
                  tmp.push_back(cur);
              pq.pop();
              len--;
          }
          //push back all in tmp vetor again
          for(int i=0;i<tmp.size();i++){
              pq.push(tmp[i]);
          }
      }
      
      return ret;
  }
};
