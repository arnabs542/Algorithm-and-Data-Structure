//https://leetcode.com/problems/word-search-ii/#/description

#include <iostream>
#include<cstring>
#include<vector>
using namespace std;



#define M 3
#define N 3

string dictionary[] = {"cat", "dog", "pig", "goat"};
int n = sizeof(dictionary)/sizeof(dictionary[0]);

bool is_word(string &str)
{

    for (int i=0; i<n; i++)
        if (str.compare(dictionary[i]) == 0)
          return true;
    return false;
}

void DFS(vector<string> &ret, vector<vector<char>> &word_matrix, vector<vector<bool>> visited, int i,
                   int j, string str){

    visited[i][j] = true;
    str = str + word_matrix[i][j];

    if (is_word(str)==true){
        ret.push_back(str);
    }

    for (int row=i-1; row<=i+1 && row<M; row++)
      for (int col=j-1; col<=j+1 && col<N; col++)
        if (row>=0 && col>=0 && !visited[row][col])
          DFS(ret,word_matrix,visited, row, col, str);


    visited[i][j] = false;
}

vector<string> find_words(vector<vector<char>> &word_matrix){

    vector<string> ret;

    for (int i=0; i<M; i++){
       for (int j=0; j<N; j++){
           string str = "";
           vector<vector<bool>> visited(M,vector<bool>(N,false));
           DFS(ret,word_matrix, visited, i, j, str);
       }
    }
    return ret;

}

//   c a t
//   p d o
//   i g t

int main() {
    vector<vector<char>> word_matrix = {{'c','a','t'},
                         {'p','d','o'},
                         {'i','g','t'}};
    vector<string> res;
    res = find_words(word_matrix);
    for(int i=0;i<res.size();i++){
        cout << res[i];
        cout<<"\n";
    }

    return 0;
}
