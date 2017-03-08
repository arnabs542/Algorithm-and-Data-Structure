//https://leetcode.com/problems/maximal-rectangle/
/*
 Given a 2D binary matrix filled with 0's and 1's, find the largest rectangle containing only 1's and return its area.
For example, given the following matrix:

1 0 1 0 0
1 0 1 1 1
1 1 1 1 1
1 0 0 1 0
Return 6. 
*/
//method 1: traverse all nodes, if node==1, go through all adjcent ones
class Solution {
public:
    int maximalRectangle(vector<vector<char>>& matrix) {
        /*
        check max rectangle starting for (i,j) and extending to row below
        O(n^3)
        */
        int row=matrix.size();
        if(row==0)
            return 0;
        int col=matrix[0].size();
        vector<int> r(row,0);
        int maxarea = 0;
        for(int i=0;i<row;i++){
            for(int j=0;j<col;j++){
                if(matrix[i][j]=='1'){
                    //check largest area starting from current row and extends until reach 0
                    int area = maxRectangle(matrix,i,j);
                    maxarea = maxarea>area?maxarea:area;
                }
            }
        }
        return maxarea;
    }
    
    int maxRectangle(vector<vector<char>>& matrix, int x, int y){
        int area = 0;
        int min_width = INT_MAX;
        int maxarea = 0;
        for(int i=x;i<matrix.size() && matrix[i][y]=='1';i++){
            int width = 0;
            //check how far the current row can extend via col
            while((y+width)<matrix[x].size()&&(matrix[i][y+width]=='1')){
                width++;
            }
            //check whether the extending row has less width
            min_width = min_width<width?min_width:width;
            area = min_width * (i- x + 1);
            maxarea = maxarea>area?maxarea:area;
        }
        return maxarea;
    }
};

//method 2: DP. O(n^2)
class Solution {
public:
    int maximalRectangle(vector<vector<char>>& matrix) {
        /*
        DP: any rectangle space is determined by left, right of row and high
        left(i,j) = max(left(i-1,j), cur_left), cur_left can be determined from the current row
        right(i,j) = min(right(i-1,j), cur_right), cur_right can be determined from the current row
        height(i,j) = height(i-1,j) + 1, if matrix[i][j]=='1';
        height(i,j) = 0, if matrix[i][j]=='0'
        */
        int row=matrix.size();
        if(!row) return 0;
        int col=matrix[0].size();
        //three dp vector, left, right and high
        //size of row+1 since we need to init row 0 and do not break
        vector<vector<int>> l(row+1,vector<int>(col,0));
        vector<vector<int>> r(row+1,vector<int>(col,col));
        vector<vector<int>> h(row+1,vector<int>(col,0));
        int maxarea = 0;
        int cur_left = 0;//cur row, left most 1 in current strench
        int cur_right = col-1; //cur row, right most 1 in current strench

        //start to go through remainning row
        for(int i=1;i<=row;i++){
            cur_left = 0;
            cur_right = col-1;
            for(int j=0;j<col;j++){
                if(matrix[i-1][j]=='1'){
                    l[i][j] = max(l[i-1][j],cur_left);
                    h[i][j] = h[i-1][j]+1;
                }else{
                    cur_left = j+1;
                    l[i][j] = 0;
                    h[i][j] = 0;
                }
            }
            for(int j=col-1;j>=0;j--){
                if(matrix[i-1][j]=='1'){
                    r[i][j] = min(r[i-1][j],cur_right);
                }else{
                    cur_right = j-1;
                    r[i][j] = col-1;
                }                
            }
            
            // compute the area of rectangle (can do this from either side)
            for(int j=0; j<col; j++)
                maxarea = max(maxarea,(r[i][j]-l[i][j]+1)*h[i][j]);
        }
        return maxarea;
    }
};

//method 2 can be optimized as
class Solution {
public:
    int maximalRectangle(vector<vector<char>>& matrix) {
        int row=matrix.size();
        if(!row) return 0;
        int col=matrix[0].size();
        //three dp vector, left, right and high
        //size of row+1 since we need to init row 0 and do not break
        vector<vector<int>> l(row+1,vector<int>(col,0));
        vector<vector<int>> r(row+1,vector<int>(col,col));
        vector<vector<int>> h(row+1,vector<int>(col,0));
        int maxarea = 0;
        int cur_left = 0;//cur row, left most 1 in current strench
        int cur_right = col-1; //cur row, right most 1 in current strench

        //start to go through remainning row
        for(int i=1;i<=row;i++){
            cur_left = 0;
            cur_right = col-1;
            for(int j=0;j<col;j++){
                if(matrix[i-1][j]=='1'){
                    l[i][j] = max(l[i-1][j],cur_left);
                    h[i][j] = h[i-1][j]+1;
                }else{
                    cur_left = j+1;
                    l[i][j] = 0;
                    h[i][j] = 0;
                }
            }
            for(int j=col-1;j>=0;j--){
                if(matrix[i-1][j]=='1'){
                    r[i][j] = min(r[i-1][j],cur_right);
                }else{
                    cur_right = j-1;
                    r[i][j] = col-1;
                }                
            }
            
            // compute the area of rectangle (can do this from either side)
            for(int j=0; j<col; j++)
                maxarea = max(maxarea,(r[i][j]-l[i][j]+1)*h[i][j]);
        }
        return maxarea;
    }
};
