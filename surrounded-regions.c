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
    int row = 0;
    int col = 0;
public:
	void solve(vector<vector<char>>& board) {
      /*
      The algorithm is quite simple: Use BFS starting from 'O's on the boundary and mark them as 'V', then iterate over the whole board and mark 'O' as 'X' and 'V' as 'O'.
      */
      int row = board.size();
      if (row == 0) return;
      int col = board[0].size();
        queue<pair<int,int>> q;

      for (int i = 0; i < col; ++i){
          if (board[0][i] == 'O'){
              q.push(make_pair(0,i));
              board[0][i] ='V';
          }
          if (board[row-1][i] == 'O'){
              q.push(make_pair(row-1,i));
              board[row-1][i] ='V';
          }
      }
  
      for (int i = 0; i < row; ++i){
          if (board[i][0] == 'O'){
              q.push(make_pair(i,0));
              board[i][0] ='V';
          }
          if (board[i][col-1] == 'O'){
              q.push(make_pair(i,col-1));
              board[i][col-1] ='V';
          }
      }
      
      while(!q.empty()){
          int x=q.front().first;
          int y=q.front().second;
          q.pop();
          if(x-1>=0 && board[x-1][y]=='O'){
              board[x-1][y]='V';
              q.push(make_pair(x-1,y));
          }
          if(x+1<row && board[x+1][y]=='O'){
              board[x+1][y]='V';
              q.push(make_pair(x+1,y));
          }
          if(y-1>=0 && board[x][y-1]=='O'){
              board[x][y-1]='V';
              q.push(make_pair(x,y-1));
          }
          if(y+1<col && board[x][y+1]=='O'){
              board[x][y+1]='V';
              q.push(make_pair(x,y+1));
          }
      }
  
      for (int i = 0; i < row; ++i){
          for (int j = 0; j < col; ++j){
              if (board[i][j] == 'O')
                  board[i][j] = 'X';
              else if (board[i][j] == 'V')
                  board[i][j] = 'O';
          }
      }
    }
};
