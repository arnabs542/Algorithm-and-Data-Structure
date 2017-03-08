//https://leetcode.com/problems/number-of-boomerangs/
/*
Given n points in the plane that are all pairwise distinct, a "boomerang" is a tuple of points (i, j, k) such that the distance between i and j equals the distance between i and k (the order of the tuple matters).

Find the number of boomerangs. You may assume that n will be at most 500 and coordinates of points are all in the range [-10000, 10000] (inclusive).

Example:
Input:
[[0,0],[1,0],[2,0]]

Output:
2

Explanation:
The two boomerangs are [[1,0],[0,0],[2,0]] and [[1,0],[2,0],[0,0]]
*/

class Solution {
public:
    int numberOfBoomerangs(vector<pair<int, int>>& points) {
        
        int len = points.size();
        int distance = 0;
        map<int,int> m;//key is distance, val is cnts
        int ret = 0;
        for(int i=0;i<len;i++){
            for(int j=0;j<len;j++){
                if(i!=j){
                    distance = getdis(points[i],points[j]);
                    m[distance]++;
                }
            }
            //for each anchor points, calcualte all other's distance to it. 
            for(auto k:m){
                ret+=k.second*(k.second-1);
            }
            m.clear();
        }

        return ret;
    }
    
    int getdis(pair<int, int> a, pair<int, int> b){
        return (a.first-b.first)*(a.first-b.first)+(a.second-b.second)*(a.second-b.second);
    }
};
