//https://leetcode.com/problems/find-median-from-data-stream/
/*
Median is the middle value in an ordered integer list. If the size of the list is even, there is no middle value. So the median is the mean of the two middle value.

Examples: 
[2,3,4] , the median is 3

[2,3], the median is (2 + 3) / 2 = 2.5

Design a data structure that supports the following two operations:

void addNum(int num) - Add a integer number from the data stream to the data structure.
double findMedian() - Return the median of all elements so far.
For example:

add(1)
add(2)
findMedian() -> 1.5
add(3) 
findMedian() -> 2
*/

class MedianFinder {
private:
  struct mycompare{
      bool operator()(int a, int b){
          return a>b;
      }
  };

public:
  //two heaps: max_half has max half nums, min_half has small half nums
  priority_queue<int> min_half;  //top of min_half heap is max value in min heap
  priority_queue<int, vector<int>, mycompare> max_half; // top of max_half heap is min value of max heap

  // Adds a number into the data structure.
  void addNum(int num) {
      //need to make sure push into both heap, otherwise if two heaps are equal and one new item input, this new item could be mistakely choosen as median since later balance function is not called
      max_half.push(num);
      min_half.push(max_half.top());
      max_half.pop();
      
      //balance both heap, make sure max_half is either equal size of min_half or has one more item
      while(min_half.size()>max_half.size()+1){
          max_half.push(min_half.top());
          min_half.pop();
      }
          
  }

  // Returns the median of current data stream
  double findMedian() {
      if(max_half.size()==min_half.size()){
          return (min_half.top()+max_half.top())/2.0;
      }else{
          return (double) min_half.top();
      }
  }
};
