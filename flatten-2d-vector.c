//https://leetcode.com/problems/flatten-2d-vector/
/*
Implement an iterator to flatten a 2d vector.

For example,
Given 2d vector =
[
  [1,2],
  [3],
  [4,5,6]
]
By calling next repeatedly until hasNext returns false, the order of elements returned by next should be: [1,2,3,4,5,6].
*/
class Vector2D {
    queue<int> q;
public:
    Vector2D(vector<vector<int>>& vec2d) {
        for(int i=0;i<vec2d.size();i++){
            for(int j=0;j<vec2d[i].size();j++){
                q.push(vec2d[i][j]);
            }
        }
    }

    int next() {
        int ret=q.front();
        q.pop();
        return ret;
    }

    bool hasNext() {
        return !q.empty();
    }
};

/**
 * Your Vector2D object will be instantiated and called as such:
 * Vector2D i(vec2d);
 * while (i.hasNext()) cout << i.next();
 */
