/*
https://leetcode.com/problems/beautiful-arrangement/#/description

Suppose you have N integers from 1 to N. We define a beautiful arrangement as an array that is constructed by these N numbers successfully if one of the following is true for the ith position (1 ≤ i ≤ N) in this array:

The number at the ith position is divisible by i.
i is divisible by the number at the ith position.
Now given N, how many beautiful arrangements can you construct?

Example 1:
Input: 2
Output: 2
Explanation:

The first beautiful arrangement is [1, 2]:

Number at the 1st position (i=1) is 1, and 1 is divisible by i (i=1).

Number at the 2nd position (i=2) is 2, and 2 is divisible by i (i=2).

The second beautiful arrangement is [2, 1]:

Number at the 1st position (i=1) is 2, and 2 is divisible by i (i=1).

Number at the 2nd position (i=2) is 1, and i (i=2) is divisible by 1.
*/

int countArrangement(int N) {
    int ret = 0;
    vector<int> used(N+1,0);
    if(N==0)
        return 0;

    help(N,1,used,ret);
    return ret;
}

void help(int N, int index, vector<int> &used, int &cnt){
    if(index>N){
        //finish construction until end, and conditions all meet
        cnt++;
        return;
    }
    //every possible number at each position
    for(int i=1;i<=N;i++){
        if(used[i] == 0 && (index%i==0 || i%index==0)){
            used[i]=1;  //push.pop way
            help(N,index+1,used,cnt);
            used[i]=0;
        }
    }

}
