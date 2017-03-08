//https://leetcode.com/problems/shortest-word-distance/
/*
Given a list of words and two words word1 and word2, return the shortest distance between these two words in the list.

For example,
Assume that words = ["practice", "makes", "perfect", "coding", "makes"].

Given word1 = “coding”, word2 = “practice”, return 3.
Given word1 = "makes", word2 = "coding", return 1. 
*/
class Solution {
public:
    int shortestDistance(vector<string>& words, string word1, string word2) {
        int index1 = -1; //word1 happens index
        int index2 = -1; //word2 happens index
        int ret = INT_MAX;
        for(int i=0;i<words.size();i++){
            if(words[i]==word1){
                index1 = i;
                if(index2!=-1){
                    ret = min(ret,abs(i-index2));
                }
            }
            if(words[i]==word2){
                index2 = i;
                if(index1!=-1){
                    ret = min(ret,abs(i-index1));
                }
            }
        }
        return ret;
    }
};
