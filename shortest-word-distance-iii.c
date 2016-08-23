//https://leetcode.com/problems/shortest-word-distance-iii/
/*
This is a follow up of Shortest Word Distance. The only difference is now word1 could be the same as word2.
Given a list of words and two words word1 and word2, return the shortest distance between these two words in the list.
word1 and word2 may be the same and they represent two individual words in the list.

For example,
Assume that words = ["practice", "makes", "perfect", "coding", "makes"].
Given word1 = “makes”, word2 = “coding”, return 1.
Given word1 = "makes", word2 = "makes", return 3. 
*/
class Solution {
public:
    int shortestWordDistance(vector<string>& words, string word1, string word2) {

        long long ret = INT_MAX;
        long long index1 = ret;//to avoid init case when index 1 and index2 could be 0;
        long long index2 = -ret;
        bool same = false;
        if(word1==word2)
            same = true;
        for(int i=0;i<words.size();i++){
            if(words[i]==word1){
                if(same){
                    ret = min(ret,abs(i-index1));
                    index1 = i;
                    continue;
                }
                index1 = i;
                    
            }
            if(words[i]==word2){
                index2 = i;
            }
            ret = min(ret,abs(index1-index2));
        }
        
        return ret;
    }
};
