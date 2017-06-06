//https://leetcode.com/problems/two-sum/#/description

vector<int> twoSum(vector<int>& nums, int target) {
    //O(nlog(n)) is easy, sort and use pointer head and tail
    //O(n)
    int len = nums.size();
    vector<int> ret;
    unordered_map<int,int> m; //key is val, val is index
    for(int i=0;i<len;i++){
        if(m.find(target-nums[i])!=m.end()){
            ret.push_back(i);
            ret.push_back(m[target-nums[i]]);
            return ret;
        }
        m[nums[i]] = i;
    }
}
