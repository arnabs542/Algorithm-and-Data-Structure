//http://www.lintcode.com/en/problem/subarray-sum/
/*
Given an integer array, 
find a subarray where the sum of numbers is zero. 
Your code should return the index of the first number and the index of the last number.

Example
Given [-3, 1, 2, -3, 4], return [0, 2] or [1, 3].
*/
class Solution {
public:
    /**
     * @param nums: A list of integers
     * @return: A list of integers includes the index of the first number 
     *          and the index of the last number
     */
    vector<int> subarraySum(vector<int> nums){
        int sum = 0;
        vector<int> ret;
        //key is added up sum, val is index ;
        unordered_map<int,int> m; 
        m[0]=-1;
        /*
        added up sum 
        */
        for(int i=0;i<nums.size();i++){
            sum+=nums[i];
            /*
            if subarray=0; so sum value before sub array starts and at end 
            of sub array should be the same;
            */
            if(m.find(sum)!=m.end()){
                ret.push_back(m[sum]+1);
                ret.push_back(i);
                return ret;
            }
            m[sum]=i;
        }

        return ret;
    }
};
