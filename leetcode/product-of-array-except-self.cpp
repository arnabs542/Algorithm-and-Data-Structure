
//https://leetcode.com/problems/product-of-array-except-self/
/*
Given an array of n integers where n > 1, nums, return an array output such that output[i] is equal to the product of all the elements of nums except nums[i].
Solve it without division and in O(n).

For example, given [1,2,3,4], return [24,12,8,6].
*/
vector<int> productExceptSelf(vector<int>& nums) {
    int len=nums.size();
    vector<int> begin(len,0);  //product value vector from begin until index i(exclusive)
    vector<int> end(len,0);    //product value vector from end until index i(exclusive)
    vector<int> ret(len,0);
    begin[0]=1;
    end[len-1]=1;
    for(int i=1;i<len;i++){
        begin[i] = begin[i-1]*nums[i-1];
    }
    for(int i=len-2;i>=0;i--){
        end[i]=end[i+1]*nums[i+1];
    }
    for(int i=0;i<len;i++){
        ret[i]=begin[i]*end[i];
    }
    return ret;
}

//method 2: it can be optimized to O(1) memory
vector<int> productExceptSelf(vector<int>& nums) {
    int len=nums.size();
    int begin = 1;
    int end = 1;
    vector<int> ret(len,1);
    for(int i=0;i<len;i++){
        ret[i]*=begin;
        begin *=nums[i];
        ret[len-1-i]*=end;
        end *=nums[len-1-i];
    }
    return ret;
}
