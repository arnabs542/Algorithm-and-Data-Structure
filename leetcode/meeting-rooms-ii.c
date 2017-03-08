//https://leetcode.com/problems/meeting-rooms-ii/
/*
Given an array of meeting time intervals consisting of start and end times [[s1,e1],[s2,e2],...] (si < ei), find the minimum number of conference rooms required.

For example,
Given [[0, 30],[5, 10],[15, 20]],
return 2.
*/
class Solution {
private:
  static bool mycompare(Interval s1, Interval s2){
      return s1.start<s2.start;
  }
  
  struct pq_compare{
      bool operator()(Interval& a, Interval& b){
          return a.end>b.end;
      }
  };
public:
  int minMeetingRooms(vector<Interval>& intervals) {
      if(intervals.size()==0)
          return 0;
      sort(intervals.begin(),intervals.end(),mycompare);
      priority_queue<Interval, vector<Interval>, pq_compare> pq;//maintain the earliest ends time, min queue
      int len = intervals.size();
      pq.push(intervals[0]);
      for(int i=1;i<len;i++){
          int cur_end = pq.top().end;
          if(intervals[i].start<cur_end){
              pq.push(intervals[i]); //if start time eariler, need a new room.
          }else{
              pq.pop();           //if start later than cur earilest end time, extend current room end time
              pq.push(intervals[i]);
          }
      }
      
      return pq.size();
  }
};
