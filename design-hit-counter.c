//https://leetcode.com/problems/design-hit-counter/
/*
Design a hit counter which counts the number of hits received in the past 5 minutes.
Each function accepts a timestamp parameter (in seconds granularity) and you may assume that calls are being made to the system in chronological order (ie, the timestamp is monotonically increasing). 
You may assume that the earliest timestamp starts at 1.
It is possible that several hits arrive roughly at the same time.

Example:
HitCounter counter = new HitCounter();

// hit at timestamp 1.
counter.hit(1);
// hit at timestamp 2.
counter.hit(2);
// hit at timestamp 3.
counter.hit(3);
// get hits at timestamp 4, should return 3.
counter.getHits(4);
// hit at timestamp 300.
counter.hit(300);
// get hits at timestamp 300, should return 4.
counter.getHits(300);
// get hits at timestamp 301, should return 3.
counter.getHits(301); 
*/

//method 1: use queue, cons is queue size could be increased in large
class HitCounter {
private:
  queue<int> q;//timestamp.
  int cnt;
public:
  /** Initialize your data structure here. */
  HitCounter() {
      cnt = 0;
  }
  
  /** Record a hit.
      @param timestamp - The current timestamp (in seconds granularity). */
  void hit(int timestamp) {
      q.push(timestamp);
  }
  
  /** Return the number of hits in the past 5 minutes.
      @param timestamp - The current timestamp (in seconds granularity). */
  int getHits(int timestamp) {
      //check whether queue is empty
      if(q.empty()){
              return 0;
      }
      int firsttime = q.front();
      while(firsttime<=timestamp-300){
          q.pop();
          if(q.empty()){
              return 0;
          }
          firsttime = q.front();
      }
      return q.size();
  }
};

//method 2: use circular buffer, fix size 300
class HitCounter {
private:
  vector<int> times;//timestamp.
  vector<int> hits;
public:
  /** Initialize your data structure here. */
  HitCounter() {
      times.resize(300);
      hits.resize(300);
  }
  
  /** Record a hit.
      @param timestamp - The current timestamp (in seconds granularity). */
  void hit(int timestamp) {
      int index = (timestamp)%300;
      if(times[index] != timestamp){
          times[index] = timestamp;
          hits[index] = 1;
      }else{
          hits[index]++;
      }
  }
  
  /** Return the number of hits in the past 5 minutes.
      @param timestamp - The current timestamp (in seconds granularity). */
  int getHits(int timestamp) {
      //check whether queue is empty
      int ret = 0;
      for(int i=0;i<300;i++){
          if(timestamp-times[i]<300)
              ret+=hits[i];
      }
      return ret;
  }
};
