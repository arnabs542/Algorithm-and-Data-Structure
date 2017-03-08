//https://leetcode.com/problems/top-k-frequent-elements/
/*
Given a non-empty array of integers, return the k most frequent elements.

For example,
Given [1,1,1,2,2,3] and k = 2, return [1,2].
*/

//classic problem solved by map and heap sort
class comparePair {
    public:
    bool operator() (const pair<int,int>& lhs, const pair<int,int>& rhs) const
    {
        return lhs.second > rhs.second;
    }
};

class Solution {
public:
    vector<int> topKFrequent(vector<int>& nums, int k) {
        //use heap sort to achieven o(log(n)) time complexity 
        unordered_map<int,int> m;
        
        vector<int> ret;
        for(int i=0;i<nums.size();i++){
            m[nums[i]] ++;
        }
        
        priority_queue<pair<int, int>, vector<pair<int, int>>, comparePair> heap;
        
        for(unordered_map<int, int>::iterator it=m.begin();it!=m.end();it++){
            
            if(heap.size()<k){
                heap.push(*it);
            }else{
                if(heap.top().second<it->second){
                    heap.pop();
                    heap.push(*it);
                }
            }
        }
        
        for(int i=0;i<k;i++){
            ret.push_back(heap.top().first);
            heap.pop();
        }
        reverse(ret.begin(), ret.end());
        
        return ret;
    }
};
