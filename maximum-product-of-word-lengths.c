//https://leetcode.com/problems/maximum-product-of-word-lengths/
/*
Given a string array words, find the maximum value of length(word[i]) * length(word[j]) where the two words do not share common letters. You may assume that each word will contain only lower case letters. If no such two words exist, return 0.

Example 1:
Given ["abcw", "baz", "foo", "bar", "xtfn", "abcdef"]
Return 16
The two words can be "abcw", "xtfn".

Example 2:
Given ["a", "ab", "abc", "d", "cd", "bcd", "abcd"]
Return 4
The two words can be "ab", "cd".

Example 3:
Given ["a", "aa", "aaa", "aaaa"]
Return 0
No such pair of words.
*/

class Solution {
public:
    int maxProduct(vector<string>& words) {
        int ret = 0;
        //first, translate each string into int, as bit vector
        int len = words.size();
        vector<int> word_int(len,0); //highest shift is 1<<26, smaller than 1<<31 for max int
        for(int i=0;i<len;i++){
            string cur = words[i];
            int cur_int = 0;
            for(int j=0;j<cur.size();j++){
                cur_int|=(1<<(cur[j]-'a'));
            }
            word_int[i] = cur_int;
        }
        for(int i=0;i<len;i++){
            for(int j=i+1;j<len;j++){
                //no same letter
                if((word_int[i]&word_int[j])==0){
                    int product = words[i].size()*words[j].size();
                    ret = ret>product?ret:product;
                }
            }
        }
        
        return ret;
    }
};
