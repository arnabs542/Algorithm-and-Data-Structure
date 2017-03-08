//https://leetcode.com/problems/missing-ranges/
/*
 Given a sorted integer array where the range of elements are [lower, upper] inclusive, return its missing ranges.
For example, given [0, 1, 3, 50, 75], lower = 0 and upper = 99, return ["2", "4->49", "51->74", "76->99"]. 
*/
class Solution {
public:
    vector<string> findMissingRanges(vector<int>& nums, int lower, int upper) {
        vector<string> ret;
        int pre = lower-1;//notice lower and upper are inclusive, other numbers should be exclusive
        for(int i=0;i<nums.size();i++){
            //not continous if distance >1
            if(nums[i]-pre>1 ){
                ret.push_back(help(pre+1,nums[i]-1));
            }
            pre = nums[i];
        }
        if(pre<upper)//inclusive
            ret.push_back(help(pre+1,upper));
        return ret;
    }
    
    string help(int start, int end){
        if(start==end)
            return to_string(start);
        
        return to_string(start) +"->" + to_string(end);
    }
};
