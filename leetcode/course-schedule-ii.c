//https://leetcode.com/problems/course-schedule-ii/
//Method 1: DFS

class Solution {
public:
    vector<int> findOrder(int numCourses, vector<pair<int, int>>& prerequisites) {
        vector<int> ret;
        vector<vector<int>> map(numCourses);
        for(int i=0;i<prerequisites.size();i++){
            map[prerequisites[i].second].push_back(prerequisites[i].first);
        }
        vector<int> visit(numCourses,0);

        for (int i = 0; i < numCourses; ++i){
            if(DFSloop(map, visit, i,ret)){
                return vector<int>();
            }
        }
                    
        reverse(ret.begin(),ret.end());
        return ret;
    }
    bool DFSloop(vector<vector<int>> &map, vector<int> &visit, int v, vector<int> &ret)
    {
        if (visit[v] == -1) 
            return true;
        if (visit[v] == 1)  
            return false;

        visit[v] = -1;

        for (int j=0; j<map[v].size();j++)//explore v's neighbors in DFS recursive way
        {
            if (DFSloop(map, visit, map[v][j], ret))
                return true;
        }
        ret.push_back(v);
        visit[v] = 1;
        return false;
    }
};
