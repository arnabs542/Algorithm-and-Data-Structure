//https://leetcode.com/problems/count-and-say/
/*
The count-and-say sequence is the sequence of integers beginning as follows:
1, 11, 21, 1211, 111221, ...

1 is read off as "one 1" or 11.
11 is read off as "two 1s" or 21.
21 is read off as "one 2, then one 1" or 1211.
Given an integer n, generate the nth sequence.
*/
class Solution {
public:
  std::string countAndSay(int n) {
  	if (0 == n) return "";  
  	if (1 == n) return "1";
  	
  	string res="1"; //start point
  	for (int i = 1; i < n; i++){    // run from starting to generate second string
  		int len = res.size();
  		string s="";
          //cheack all digits in the string
  		for (int j = 0; j < len; j++){  
  		    int count=1; // we have at least 1 occourence of each digit
              // get the number of times same digit occurred (be carefull with the end of the string)
			while ((j + 1 < len) && (res[j] == res[j + 1])){
				count++;    
				j++;        // we need to keep increasing the index inside of the string
			}
              // add to new string "count"+"digit itself"
  			s += to_string(count) + res[j];
  		}
  		res = s;
  	}
  	return res;
  }
};
