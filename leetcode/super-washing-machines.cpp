/*
https://leetcode.com/problems/super-washing-machines/#/description

ou have n super washing machines on a line. Initially, each washing machine has some dresses or is empty.
For each move, you could choose any m (1 ≤ m ≤ n) washing machines, and pass one dress of each washing machine to one of its adjacent washing machines at the same time .
Given an integer array representing the number of dresses in each washing machine from left to right on the line, you should find the minimum number of moves to make all the washing machines have the same number of dresses. If it is not possible to do it, return -1.

Example1
Input: [1,0,5]
Output: 3
Explanation:
1st move:    1     0 <-- 5    =>    1     1     4
2nd move:    1 <-- 1 <-- 4    =>    2     1     3
3rd move:    2     1 <-- 3    =>    2     2     2

Example2
Input: [0,3,0]
Output: 2
Explanation:
1st move:    0 <-- 3     0    =>    1     2     0
2nd move:    1     2 --> 0    =>    1     1     1

Example3
Input: [0,2,0]
Output: -1
Explanation:
It's impossible to make all the three washing machines have the same number of dresses.
*/

int findMinMoves(vector<int>& machines) {
        int ret = -1;
        int len = machines.size();
        vector<int> sum(len+1,0);
        for(int i=0;i<machines.size();i++){
            sum[i+1]= sum[i] + machines[i];
        }
        if(sum[len]%machines.size()!=0)
            return ret; //not able to evenly distribute

        int average = sum[len]/len;

        /*For a single machine, necessary operations is to transfer dresses from one side to another until sum of both sides and itself reaches the average number. We can calculate (required dresses) - (contained dresses) of each side as L and
        L > 0 && R > 0: both sides lacks dresses, and we can only export one dress from current machines at a time, so result is abs(L) + abs(R)
        L < 0 && R < 0: both sides contains too many dresses, and we can import dresses from both sides at the same time, so result is max(abs(L), abs(R))
        L < 0 && R > 0 or L >0 && R < 0: the side with a larger absolute value will import/export its extra dresses from/to current machine or other side, so result is max(abs(L), abs(R))
        */

        int l = 0;  //all dress left of current
        int r = 0;  //all dress right of current
        for(int i=0;i<len;i++){
            l = i*average-sum[i]; //0 until i-1;
            r = (len-i-1)*average - (sum[len]-sum[i+1]);  //i+1 until end
            if(l>0 && r>0)
                ret = max(ret, abs(l)+abs(r));
            else
                ret = max(ret,max(abs(l),abs(r)));
        }
        return ret;

}
