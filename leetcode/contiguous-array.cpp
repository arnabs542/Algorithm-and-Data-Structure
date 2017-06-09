//https://leetcode.com/problems/contiguous-array
//Given a binary array, find the maximum length of a contiguous subarray with equal number of 0 and 1.


int findMaxLength(vector<int>& nums) {
    int len=nums.size();
    int ret = 0;
    int shift = 0; //shift: num of 0 - num of 1
    map<int,int> m; //key is shift, val is index. find two index that has same shift, len in between has same 0 and 1
    m[0]=-1;
    for(int i=0;i<len;i++){
        if(nums[i]==1){
            shift++;
        }else{
            shift--;
        }
        if(m.find(shift)!=m.end()){
            ret = max(ret,i-m[shift]);
        }else{
            m[shift]=i;
        }
    }
    return ret;
}
