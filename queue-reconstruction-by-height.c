//https://leetcode.com/problems/queue-reconstruction-by-height/
/*
Suppose you have a random list of people standing in a queue. Each person is described by a pair of integers (h, k), where h is the height of the person and k is the number of people in front of this person who have a height greater than or equal to h. Write an algorithm to reconstruct the queue.

Note:
The number of people is less than 1,100.

Example
Input:
[[7,0], [4,4], [7,1], [5,0], [6,1], [5,2]]

Output:
[[5,0], [7,0], [5,2], [6,1], [4,4], [7,1]]
*/
class Solution {
    
public:
    vector<pair<int, int>> reconstructQueue(vector<pair<int, int>>& people) {
        /*
        Pick out tallest group of people and sort them in a subarray (S). Since there's no other groups of people taller than them, 
        therefore each guy's index will be just as same as his k value.
        For 2nd tallest group (and the rest), insert each one of them into (S) by k value. So on and so forth.
        */
        auto comp = [](pair<int, int> a, pair<int, int> b){
            return a.first>b.first || (a.first==b.first)&&(a.second<b.second);
        };
        sort(people.begin(),people.end(),comp);
        vector<pair<int, int>> ret;
        for(auto p:people){
            ret.insert(ret.begin()+p.second,p);
        }
        return ret;
    }
};
