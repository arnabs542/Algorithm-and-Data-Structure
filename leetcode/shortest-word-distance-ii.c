//https://leetcode.com/problems/shortest-word-distance-ii/
/*
This is a follow up of Shortest Word Distance. The only difference is now you are given the list of words and your method will be called repeatedly many times with different parameters. How would you optimize it?
Design a class which receives a list of words in the constructor, and implements a method that takes two words word1 and word2 and return the shortest distance between these two words in the list.

For example,
Assume that words = ["practice", "makes", "perfect", "coding", "makes"].

Given word1 = “coding”, word2 = “practice”, return 3.
Given word1 = "makes", word2 = "coding", return 1. 
*/
class WordDistance {
    //string is key, index vector is val
    unordered_map<string,vector<int>> m;
public:
    WordDistance(vector<string>& words) {
        for(int i=0;i<words.size();i++){
            m[words[i]].push_back(i);
        }

    }

    int shortest(string word1, string word2) {
        int i = 0;
        int j = 0;
        vector<int> index1 = m[word1];
        vector<int> index2 = m[word2];
        int dist = INT_MAX;
        while(i<index1.size() && j<index2.size()){
            dist = min(dist, abs(index1[i]-index2[j]));
            index1[i]<index2[j]?i++:j++;
        }
        
        return dist;
    }
};
