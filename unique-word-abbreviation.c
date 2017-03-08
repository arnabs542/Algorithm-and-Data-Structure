//https://leetcode.com/problems/unique-word-abbreviation/
/*
An abbreviation of a word follows the form <first letter><number><last letter>. Below are some examples of word abbreviations:
a) it                      --> it    (no abbreviation)
b) d|o|g                   --> d1g
c) i|nternationalizatio|n  --> i18n
d) l|ocalizatio|n          --> l10n

Assume you have a dictionary and given a word, find whether its abbreviation is unique in the dictionary. A word's abbreviation is unique if no other word from the dictionary has the same abbreviation.
Example:
Given dictionary = [ "deer", "door", "cake", "card" ]

isUnique("dear") -> false
isUnique("cart") -> true
isUnique("cane") -> false
isUnique("make") -> true
*/

class ValidWordAbbr {
private:
  map<string,unordered_set<string>> m;
public:
  ValidWordAbbr(vector<string> &dictionary) {
      for(int i=0;i<dictionary.size();i++){
          string cur = dictionary[i];
          m[abbr(cur)].insert(cur);
      }
  }

  bool isUnique(string word) {
      string encode = abbr(word);
      if(m[encode].count(word)==m[encode].size())
          return true;
      else{
          return false;
      }
  }
  
  string abbr(string s){
      int len = s.size();
      string ret;
      if(len<=2){
          ret = s;
      }else{
          ret = s[0]+to_string(len-2)+s[len-1];
      }
      return ret;
  }
};
