//https://leetcode.com/problems/flip-game-ii/
/*
 You are playing the following Flip Game with your friend: Given a string that contains only these two characters: + and -,
 you and your friend take turns to flip two consecutive "++" into "--". 
 The game ends when a person can no longer make a move and therefore the other person will be the winner.
Write a function to determine if the starting player can guarantee a win.
For example, given s = "++++", return true. 
The starting player can guarantee a win by flipping the middle "++" to become "+--+". 
*/
class Solution {
public:
/*
The idea is try to replace every "++" in the current string s to "--" and see if the opponent can win or not, if the opponent cannot win, great, we win!
*/
  bool canWin(string s) {
      if(s.empty()||s.size()<2)
          return false;
      
      for(int i=0;i<s.size()-1;i++){
          if((s[i]=='+')&&(s[i+1]=='+')){
              s[i] = '-'; 
              s[i+1] = '-';
              bool win = !canWin(s);  //oponent can win or not. if oponent win, we will lose
              s[i] = '+'; 
              s[i+1] = '+';
              if (win == true) 
                  return true;
          }    
      }     
      return false;
  }
};
