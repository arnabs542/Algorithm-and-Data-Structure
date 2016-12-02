//https://leetcode.com/problems/third-maximum-number/
/*
Given a non-empty array of integers, return the third maximum number in this array. If it does not exist, return the maximum number. The time complexity must be in O(n).

Example 1:
Input: [3, 2, 1]

Output: 1

Explanation: The third maximum is 1.
Example 2:
Input: [1, 2]

Output: 2

Explanation: The third maximum does not exist, so the maximum (2) is returned instead.
Example 3:
Input: [2, 2, 3, 1]

Output: 1

Explanation: Note that the third maximum here means the third maximum distinct number.
Both numbers with value 2 are both considered as second maximum.
*/

//method 1: heap sort
class Solution {
public:
    struct mycompare{
        bool operator()(int a, int b){
            return a>b;
        }
    };
    int thirdMax(vector<int>& nums) {
        //heap sort, min heap, top is minimum
        //hash table to eliminate duplicate
        unordered_set<int> s;
        priority_queue<int,vector<int>,mycompare> pq;
        for(int i=0;i<nums.size();i++){
            if(s.find(nums[i])==s.end()){
                s.insert(nums[i]);
                pq.push(nums[i]);
                if(pq.size()>3)
                    pq.pop();
            }
        }
        if(pq.size()==3)
            return pq.top();
        else{
            pq.pop();
            return pq.top();
        }
    }
};

//method 2: much simple, use the default set sort
class Solution {
public:
    int thirdMax(vector<int>& nums) {
        //using set, Olog(3)
        set<int> s;
        for(int i=0;i<nums.size();i++){
            s.insert(nums[i]);
            if(s.size()>3)
                s.erase(s.begin());
        }
        
        return s.size()==3 ? *s.begin():*s.rbegin();
    }
};
