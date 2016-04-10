//https://leetcode.com/problems/course-schedule/
//Method 1: DFS

class Solution {
public:
    /*for DFS of Topological sort. we have 3 states:
    visited: 1, unvisited: 0, temporary visit: -1
    temp visit means that current DFS run is visiting
    visit=1 means is explored */ 
    bool canFinish(int numCourses, vector<pair<int, int>>& prerequisites) {
        vector<vector<int>> matrix(numCourses);//convert to adjcent list based graph
        for (int i = 0; i < prerequisites.size(); ++i)
            matrix[prerequisites[i].second].push_back(prerequisites[i].first);

        vector<int> flag(numCourses);
        for (int i = 0; i < numCourses; ++i)
            if (flag[i]!=1)
                if (hasCycle(matrix, i, flag))
                    return false;
        return true;
    }
    
    bool hasCycle(vector<vector<int>>& matrix, int i, vector<int>& flag) {
        if (flag[i] == -1)
            return true;
        flag[i] = -1;  //mark temporary visit. 
        for (int j=0; j< matrix[i].size();j++) {//explore i's neighbors recursively 
            if (hasCycle(matrix, matrix[i][j], flag))
                return true;
        }
        flag[i] = 1;  //explore current node and all its link, no cycle found
        return false;
    }
};
