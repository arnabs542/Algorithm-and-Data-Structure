//https://leetcode.com/problems/moving-average-from-data-stream/
/*
Given a stream of integers and a window size, calculate the moving average of all integers in the sliding window.

For example,

MovingAverage m = new MovingAverage(3);
m.next(1) = 1
m.next(10) = (1 + 10) / 2
m.next(3) = (1 + 10 + 3) / 3
m.next(5) = (10 + 3 + 5) / 3
*/

class MovingAverage {
private:
  queue<int> q;
  int len;
  int sum;
public:
  /** Initialize your data structure here. */
  MovingAverage(int size) {
      len = size;
      sum = 0;
  }
  
  double next(int val) {
      if(q.size()<len){
          q.push(val);
          sum+=val;
          return (double) sum/q.size();
      }else{
         sum = sum-q.front()+val;
         q.pop();
         q.push(val);
         return (double) sum/len;
      }
      
  }
};
