//https://leetcode.com/problems/walls-and-gates/
/*
You are given a m x n 2D grid initialized with these three possible values.

-1 - A wall or an obstacle.
0 - A gate.
INF - Infinity means an empty room. We use the value 231 - 1 = 2147483647 to represent INF as you may assume that the distance to a gate is less than 2147483647.
Fill each empty room with the distance to its nearest gate. If it is impossible to reach a gate, it should be filled with INF.

For example, given the 2D grid:
INF  -1  0  INF
INF INF INF  -1
INF  -1 INF  -1
  0  -1 INF INF
After running your function, the 2D grid should be:
  3  -1   0   1
  2   2   1  -1
  1  -1   2  -1
  0  -1   3   4
*/
class Solution {
    int row = 0;
    int col = 0;
public:
    void wallsAndGates(vector<vector<int>>& rooms) {
        row=rooms.size();
        if(!row) return;
        col=rooms[0].size();
        if(!col) return;
        
        for(int i=0;i<row;i++){
            for(int j=0;j<col;j++){
                if(rooms[i][j]==0){
                    DFS(rooms,i,j,0);
                }
            }
        }
    }
    
    void DFS(vector<vector<int>>& rooms, int i, int j, int path){
        //if new path>than current, we do not need to update
        if(path>rooms[i][j]){
            return;
        }else{
            
           rooms[i][j] = path;
            if(i-1>=0)
                DFS(rooms,i-1,j,path+1);
            if(i+1<row)
                DFS(rooms,i+1,j,path+1);
            if(j-1>=0)
                DFS(rooms,i,j-1,path+1);
            if(j+1<col)
                DFS(rooms,i,j+1,path+1);
           
        }
    }
};

//we also notice the DFS function could be slightly optimized as below to avoid unnessesary re visit
void DFS(vector<vector<int>>& rooms, int i, int j, int path){
    //For DFS, need to check the boudary case first
    //if new path>than current, we do not need to update
    if(i<0 || i>=row || j<0 || j>=col || path>rooms[i][j]){
        return;
    }else{
        
       rooms[i][j] = path;
       DFS(rooms,i-1,j,path+1);
       DFS(rooms,i+1,j,path+1);
       DFS(rooms,i,j-1,path+1);
       DFS(rooms,i,j+1,path+1);
       
    }
    
}


//BFS way
class Solution {
public:
    void wallsAndGates(vector<vector<int>>& rooms) {
        int row = 0;
        int col = 0;
        row=rooms.size();
        if(!row) return;
        col=rooms[0].size();
        if(!col) return;
        
        queue<pair<int,int>> q; //queue for points
        for(int i=0;i<row;i++){
            for(int j=0;j<col;j++){
                if(rooms[i][j]==0){
                    q.push(make_pair(i,j));
                }
            }
        }
        //BFS
        while(!q.empty()){
            int x=q.front().first;
            int y=q.front().second;
            q.pop();
            //only update when inside boudary and new move could lead to smaller number to gate
            if(x-1>=0 && rooms[x-1][y]>rooms[x][y]+1){
                rooms[x-1][y] = rooms[x][y]+1;
                q.push(make_pair(x-1,y));
            }
            if(x+1<row && rooms[x+1][y]>rooms[x][y]+1){
                rooms[x+1][y] = rooms[x][y]+1;
                q.push(make_pair(x+1,y));
            }
            if(y-1>=0 && rooms[x][y-1]>rooms[x][y]+1){
                rooms[x][y-1] = rooms[x][y]+1;
                q.push(make_pair(x,y-1));
            }
            if(y+1<col && rooms[x][y+1]>rooms[x][y]+1){
                rooms[x][y+1] = rooms[x][y]+1;
                q.push(make_pair(x,y+1));
            }
        }
    }
};
