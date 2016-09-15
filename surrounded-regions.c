//https://leetcode.com/problems/surrounded-regions/
/*
 Given a 2D board containing 'X' and 'O' (the letter O), capture all regions surrounded by 'X'.

A region is captured by flipping all 'O's into 'X's in that surrounded region.

For example,
X X X X
X O O X
X X O X
X O X X

After running your function, the board should be:
X X X X
X X X X
X X X X
X O X X
*/

//Method 1: DFS
class Solution {
    int row = 0;
    int col = 0;
public:
    void solve(vector<vector<char>>& board) {
        int i,j;
        row=board.size();
        if(!row) return;
        col=board[0].size();
        if(!col) return;
		for(j=0;j<col;j++){
			DFS(board,0,j);
			DFS(board,row-1,j);
		}
		for(i=0;i<row;i++){
			DFS(board,i,0);
			DFS(board,i,col-1);
		}

		for(i=0;i<row;i++)
			for(j=0;j<col;j++)
				if(board[i][j]=='O')
					board[i][j]='X';
				else if(board[i][j]=='1')
					board[i][j]='O';
    }
    
    void DFS(vector<vector<char>>& board, int x, int y){
		if(board[x][y]=='O'){
			board[x][y]='1';
			if(x>1)
				DFS(board,x-1,y);
			if(y>1)
				DFS(board,x,y-1);
			if(x+1<row)
				DFS(board,x+1,y);
			if(y+1<col)
				DFS(board,x,y+1);
        }
    }
};

//Method 2: BFS
class Solution {
public:
  void solve(vector<vector<char>>& board) {
      /*
      The algorithm is quite simple: Use BFS starting from 'O's on the boundary and mark them as 'V', then iterate over the whole board and mark 'O' as 'X' and 'V' as 'O'.
      */
      int row = board.size();
      if (row == 0) //Add this to prevent run-time error!
          return;
      int col = board[0].size();
      if  (col == 0) // Add this to prevent run-time error!
          return;
      for (int i = 0; i < col; ++i)
      {
          if (board[0][i] == 'O')
              BFS(board, 0, i);
  
          if (board[row-1][i] == 'O')
              BFS(board, row-1, i);
      }
  
      for (int i = 0; i < row; ++i)
      {
          if (board[i][0] == 'O')
              BFS(board, i, 0);
          if (board[i][col-1] == 'O')
              BFS(board, i, col-1);
      }
  
      for (int i = 0; i < row; ++i)
      {
          for (int j = 0; j < col; ++j)
          {
              if (board[i][j] == 'O')
                  board[i][j] = 'X';
              else if (board[i][j] == 'V')
                  board[i][j] = 'O';
          }
      }
      
      
  }
  
  void BFS(vector<vector<char>>& board, int x, int y){
      int row = board.size();
      int col = board[0].size();
      queue<pair<int,int>> q;
      q.push(make_pair(x,y));
      board[x][y]= 'V';
      while(!q.empty()){
          pair<int,int> cur = q.front();
          q.pop();
          vector<pair<int,int>> adj;
          adj.push_back(make_pair(cur.first+1,cur.second));
          adj.push_back(make_pair(cur.first-1,cur.second));
          adj.push_back(make_pair(cur.first,cur.second+1));
          adj.push_back(make_pair(cur.first,cur.second-1));
          for(int i=0;i<adj.size();i++){
              int adj_x = adj[i].first;
              int adj_y = adj[i].second;
              if((adj_x>=0)&&(adj_x<row)&&(adj_y<col)&&(adj_y>=0)){
                  if(board[adj_x][adj_y]=='O'){
                      q.push(make_pair(adj_x,adj_y));
                      board[adj_x][adj_y]= 'V';
                  }
              }
          }
      }
  }
};
