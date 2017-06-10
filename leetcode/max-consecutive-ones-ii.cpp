//https://leetcode.com/problems/max-consecutive-ones-ii
/*
Given a binary array, find the maximum number of consecutive 1s in this array if you can flip at most one 0.

Example 1:
Input: [1,0,1,1,0]
Output: 4
Explanation: Flip the first zero will get the the maximum number of consecutive 1s.
    After flipping, the maximum number of consecutive 1s is 4.

What if the input numbers come in one by one as an infinite stream?
*/

//method 1: two pointer
int findMaxConsecutiveOnes(vector<int>& nums) {
    int len = nums.size();
    int first = -1;
    int second = -1;
    int ret = 0;
    for(int i=0;i<len;i++){
        if(nums[i]==0){
            if(first!=second){
                ret = max(ret,i-first-1);
                //move forward both
                first = second;
                second = i;
            }else{
                second = i; //first time meet 0, move second only
            }
        }
    }
    //calculate final len by flip second 0
    ret = max(ret,len-1-first);
    return ret;
}

//Method 2: change k zeros, so more general

int findMaxConsecutiveOnes(vector<int>& nums, int k) {
    int len = nums.size();
    //The idea is to keep a window [l, h] that contains at most k zero
    int zero = 0;
    int ret=0;
    for(int l=0,h=0;h<len;h++){
        if(nums[h]==0)
            zero++;
        while(zero>k){
            if(nums[l++]==0){
                zero--;
            }
        }
        ret = max(ret,h-l+1);
    }

    return ret;
}

//follow up, change k zeros and infinite stream
int findMaxConsecutiveOnes(vector<int>& nums) {
    int len = nums.size();
    //The idea is to keep a window [l, h] that contains at most k zero
    int ret=0;
    queue<int> q;
    int k=1;
    for(int l=0,h=0;h<len;h++){
        if(nums[h]==0){
            q.push(h);
        }
        if(q.size()>k){
            l=q.front()+1;
            q.pop();
        }
        ret = max(ret,h-l+1);
    }
    return ret;
}
