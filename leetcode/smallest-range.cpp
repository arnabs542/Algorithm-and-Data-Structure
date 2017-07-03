//https://leetcode.com/problems/smallest-range/#/description
/*
You have k lists of sorted integers in ascending order. Find the smallest range that includes at least one number from each of the k lists.

We define the range [a,b] is smaller than range [c,d] if b-a < d-c or a < c if b-a == d-c.

Example 1:
Input:[[4,10,15,24,26], [0,9,12,20], [5,18,22,30]]
Output: [20,24]
Explanation:
List 1: [4, 10, 15, 24,26], 24 is in range [20,24].
List 2: [0, 9, 12, 20], 20 is in range [20,24].
List 3: [5, 18, 22, 30], 22 is in range [20,24].
*/

vector<int> smallestRange(vector<vector<int>>& nums) {
    typedef vector<int>::iterator vi;
    struct comp {
        bool operator()(pair<vi, vi> p1, pair<vi, vi> p2) {
            return *p1.first > *p2.first;
        }
    };

    int l = INT_MAX, h = INT_MIN;
    priority_queue<pair<vi, vi>, vector<pair<vi, vi>>, comp> pq;
    for(int i=0;i<nums.size();i++){
        l = min(l, nums[i][0]);
        h = max(h, nums[i][0]);
        pq.push(make_pair(nums[i].begin(), nums[i].end())); //min heap

    }
    vector<int> ret = {l,h};

    while(true){
        auto cur =pq.top();
        pq.pop();
        ++cur.first;
        if (cur.first == cur.second)   //reach one list's end
            break;
        pq.push(cur);  //push cur min's next item in vector
        l = *pq.top().first;
        h = max(h, *cur.first);
        if (h - l < ret[1] - ret[0])
            ret = {l, h};
    }
    return ret;
}
