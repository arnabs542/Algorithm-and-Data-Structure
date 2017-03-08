//https://leetcode.com/problems/paint-fence/
/*
There is a fence with n posts, each post can be painted with one of the k colors.
You have to paint all the posts such that no more than two adjacent fence posts have the same color.
Return the total number of ways you can paint the fence.
*/
class Solution {
public:
    int numWays(int n, int k) {
        /*
        If n == 1, there would be k-ways to paint.

        if n == 2, there would be two situations:
        
        2.1 You paint same color with the previous post: k*1 ways to paint, named it as same
        2.2 You paint differently with the previous post: k*(k-1) ways to paint this way, named it as dif

        
        */
        if(n == 0) return 0;
        if(n == 1) return k;
        vector<int>same(n+1,0);  //same[i] means i's post has same color as last post i-1
        vector<int>diff(n+1,0); //diff[i] means i's post has different color as last post i-1
        same[2] = k;
        diff[2] = k*(k-1);
        
        for (int i = 3; i <= n; i++) {
            //paint i different as i-1, so k-1 choices if i-1 is same as i-2, k-1 choice if i-1 is diff from i-2
            //paint i same as i-1, only if i-1 is different as i-2 
            same[i] = diff[i-1];
            diff[i] = same[i-1]*(k-1) + diff[i-1]*(k-1);
        }
        
        return  same[n]+diff[n];
    }
};
