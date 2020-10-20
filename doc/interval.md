<!-- START doctoc generated TOC please keep comment here to allow auto update -->
<!-- DON'T EDIT THIS SECTION, INSTEAD RE-RUN doctoc TO UPDATE -->
**Table of Contents**  *generated with [DocToc](https://github.com/thlorenz/doctoc)*

- [Interval](#interval)
  - [Interval overlap](#interval-overlap)
    - [Merge intervals](#merge-intervals)
    - [Remove intervals so that no overlap happen](#remove-intervals-so-that-no-overlap-happen)
    - [Interval Overlap](#interval-overlap)
      - [Meeting room](#meeting-room)
      - [Meeting Scheduler](#meeting-scheduler)

<!-- END doctoc generated TOC please keep comment here to allow auto update -->

# Interval

## Interval overlap

### Merge intervals
https://leetcode.com/problems/merge-intervals/#/description
Given a collection of intervals, merge all overlapping intervals.

For example,
Given [1,3],[2,6],[8,10],[15,18],
return [1,6],[8,10],[15,18].

```CPP
static bool mycompare(Interval s1, Interval s2){
    return s1.start<s2.start;
}

vector<Interval> merge(vector<Interval>& intervals) {
    vector<Interval> ret;
    if(intervals.size()==0)
        return ret;
    sort(intervals.begin(),intervals.end(),mycompare);
    //direct compare with current one in vector, and push/modify the end
    ret.push_back(intervals[0]);
    for (int i = 1; i < intervals.size(); i++) {
        if(intervals[i].start>ret.back().end)
            ret.push_back(intervals[i]);
        else
            ret.back().end = max(ret.back().end,intervals[i].end);
    }

    return ret;
}
```

### Remove intervals so that no overlap happen

https://leetcode.com/problems/non-overlapping-intervals/#/description
Given a collection of intervals, find the minimum number of intervals you need to remove to make the rest of the intervals non-overlapping.

Note:
You may assume the interval's end point is always bigger than its start point.
Intervals like [1,2] and [2,3] have borders "touching" but they don't overlap each other.
Example 1:
Input: [ [1,2], [2,3], [3,4], [1,3] ]
Output: 1
Explanation: [1,3] can be removed and the rest of intervals are non-overlapping.

Example 2:
Input: [ [1,2], [1,2], [1,2] ]
Output: 2
Explanation: You need to remove two [1,2] to make the rest of intervals non-overlapping.

Example 3:
Input: [ [1,2], [2,3] ]
Output: 0
Explanation: You don't need to remove any of the intervals since they're already non-overlapping.

```CPP
static bool mycompare(Interval s1, Interval s2){
    return s1.start<s2.start;
}
int eraseOverlapIntervals(vector<Interval>& intervals) {

    if(intervals.size()==0)
        return 0;
    sort(intervals.begin(),intervals.end(),mycompare);
    int prev = 0;
    int ret = 0;
    for (int i = 1; i < intervals.size(); i++) {
        if (intervals[i].start < intervals[prev].end) {
            ret++; //need to remove
            if (intervals[i].end < intervals[prev].end) //remove one with largest area, max end coordinate
                prev = i;
        }
        else
            prev = i;

    }

    return ret;
}

```

### Interval Overlap

* usually these questions looks like get some min/max for interval list considering intervals could overlap

#### Meeting room

https://leetcode.com/problems/meeting-rooms-ii/#/description
Given an array of meeting time intervals consisting of start and end times [[s1,e1],[s2,e2],...] (si < ei), find the minimum number of conference rooms required.

For example,
Given [[0, 30],[5, 10],[15, 20]],
return 2.

```CPP
static bool sortcomp(Interval s1, Interval s2){
    return s1.start<s2.start;
}

struct pq_compare{
    bool operator()(Interval& a, Interval& b){
        return a.end>b.end;
    }
};

int minMeetingRooms(vector<Interval>& intervals) {
    if(intervals.size()==0)
        return 0;
    sort(intervals.begin(),intervals.end(),sortcomp);
    priority_queue<Interval, vector<Interval>, pq_compare> pq;//maintain the earliest ends time, min queue
    pq.push(intervals[0]);
    for(int i=1;i<intervals.size();i++){
        Interval tmp = pq.top();

        if(intervals[i].start>=tmp.end){
            pq.pop(); //extend current room
        }
        pq.push(intervals[i]);
    }
    return pq.size();
}

```

#### Meeting Scheduler

https://leetcode.com/problems/meeting-scheduler/

Given the availability time slots arrays slots1 and slots2 of two people and a meeting duration duration, return the earliest time slot that works for both of them and is of duration duration.If there is no common time slot that satisfies the requirements, return an empty array.

The format of a time slot is an array of two elements [start, end] representing an inclusive time range from start to end.  It is guaranteed that no two availability slots of the same person intersect with each other. That is, for any two time slots [start1, end1] and [start2, end2] of the same person, either start1 > end2 or start2 > end1.

 
```
Example 1:

Input: slots1 = [[10,50],[60,120],[140,210]], slots2 = [[0,15],[60,70]], duration = 8
Output: [60,68]
Example 2:

Input: slots1 = [[10,50],[60,120],[140,210]], slots2 = [[0,15],[60,70]], duration = 12
Output: []
```

* Solution 1: 2 pointers

```CPP
 vector<int> minAvailableDuration(vector<vector<int>>& slots1, vector<vector<int>>& slots2, int duration) {
        sort(slots1.begin(), slots1.end()); // sort  by start time 
        sort(slots2.begin(), slots2.end()); //
        
        int i = 0, j = 0;
        int n1 = slots1.size(), n2 = slots2.size();
        while(i<n1 && j<n2){
            
            int start = max(slots1[i][0],slots2[j][0]);
            int end = min(slots1[i][1],slots2[j][1]);
            
            if(start+duration<=end){
                return {start, start + duration};
            }else if(slots1[i][1]<slots2[j][1]){
                i++;
            }else{
                j++;
            }
            
        }
        
        return {};
    }
```

* Solution 2: Priority Queue

```CPP
vector<int> minAvailableDuration(vector<vector<int>>& slots1, vector<vector<int>>& slots2, int duration) {
    //min queue by start time
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> q;
    for (auto s : slots1) {
        if (s[1] - s[0] >= duration) q.push({ s[0], s[1] });
    }
    for (auto s : slots2) {
        if (s[1] - s[0] >= duration) q.push({ s[0], s[1] });
    }
    
    while (q.size()>1) {
        
        int end1 = q.top().second;
        q.pop();
        //since min queue by start time, so start1 is always < start2
        int start2 = q.top().first;
        if (end1 >= start2 + duration)
            return { start2, start2 + duration };
    }
    return {};
}
```



https://leetcode.com/problems/minimum-number-of-arrows-to-burst-balloons/#/description
There are a number of spherical balloons spread in two-dimensional space. For each balloon, provided input is the start and end coordinates of the horizontal diameter. Since it's horizontal, y-coordinates don't matter and hence the x-coordinates of start and end of the diameter suffice. Start is always smaller than end. There will be at most 104 balloons.

An arrow can be shot up exactly vertically from different points along the x-axis. A balloon with xstart and xend bursts by an arrow shot at x if xstart ≤ x ≤ xend. There is no limit to the number of arrows that can be shot. An arrow once shot keeps travelling up infinitely. The problem is to find the minimum number of arrows that must be shot to burst all balloons.

Example:

Input:
[[10,16], [2,8], [1,6], [7,12]]

Output:
2

Explanation:
One way is to shoot one arrow for example at x = 6 (bursting the balloons [2,8] and [1,6]) and another arrow at x = 11 (bursting the other two balloons).

```CPP
static bool mycompare(pair<int, int> s1, pair<int, int> s2){
    return s1.first<s2.first;
}

int findMinArrowShots(vector<pair<int, int>>& points) {
    if(points.size()==0)
        return 0;
    sort(points.begin(),points.end(),mycompare);
    //idea is to get overlap area among ballons
    vector<pair<int, int>> overlap;
    overlap.push_back(points[0]);
    for(int i=1;i<points.size();i++){
        if(points[i].first<=overlap.back().second){
            overlap.back().first = max(points[i].first,overlap.back().first);  //calculate possible overlap and update
            overlap.back().second = min(points[i].second,overlap.back().second);
        }else{
            overlap.push_back(points[i]);
        }

    }
    return overlap.size();
}
```