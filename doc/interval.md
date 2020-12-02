<!-- START doctoc generated TOC please keep comment here to allow auto update -->
<!-- DON'T EDIT THIS SECTION, INSTEAD RE-RUN doctoc TO UPDATE -->
**Table of Contents**  *generated with [DocToc](https://github.com/thlorenz/doctoc)*

- [Interval](#interval)
  - [Merge intervals](#merge-intervals)
  - [Insert interval](#insert-interval)
  - [Remove intervals so that no overlap happen](#remove-intervals-so-that-no-overlap-happen)
  - [Interval Intersection](#interval-intersection)
  - [Minimum Meeting room](#minimum-meeting-room)
  - [Max CPU time](#max-cpu-time)
  - [Course schedule with deadline](#course-schedule-with-deadline)
  - [Meeting Scheduler](#meeting-scheduler)
  - [Employee Free time](#employee-free-time)
  - [Ballon Burst](#ballon-burst)
  - [Skyline](#skyline)

<!-- END doctoc generated TOC please keep comment here to allow auto update -->

# Interval


## Merge intervals
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

## Insert interval

https://leetcode.com/problems/insert-interval/

https://www.educative.io/courses/grokking-the-coding-interview/3jKlyNMJPEM

Given a set of non-overlapping intervals, insert a new interval into the intervals (merge if necessary).
You may assume that the intervals were initially sorted according to their start times.


```CPP
vector<Interval> insert(vector<Interval>& intervals, Interval newInterval) {
    vector<Interval> res;
    int index = 0;
    //insert interval in left, no overlap
    while(index < intervals.size() && intervals[index].end < newInterval.start){
        res.push_back(intervals[index++]);
    }
    //begin merge, until newInterval's end< start
    while(index < intervals.size() && intervals[index].start <= newInterval.end){
        newInterval.start = min(newInterval.start, intervals[index].start);
        newInterval.end = max(newInterval.end, intervals[index].end);
        index++;
    }
    res.push_back(newInterval);
    while(index < intervals.size()){
        res.push_back(intervals[index++]);
    }
    return res;
}
```



## Remove intervals so that no overlap happen

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

## Interval Intersection

https://leetcode.com/problems/interval-list-intersections/

https://www.educative.io/courses/grokking-the-coding-interview/JExVVqRAN9D

Given two lists of intervals, find the intersection of these two lists. Each list consists of disjoint intervals sorted on their start time.
```
Example 1:

Input: arr1=[[1, 3], [5, 6], [7, 9]], arr2=[[2, 3], [5, 7]]
Output: [2, 3], [5, 6], [7, 7]
Explanation: The output list contains the common intervals between the two lists.
```

```CPP
vector<vector<int>> intervalIntersection(vector<vector<int>>& A, vector<vector<int>>& B) {
    vector<vector<int>> ret;
    
    int i=0;
    int j=0;
    while(i<A.size() && j<B.size()){
        /*
        start = max(a.start, b.start)
        end = min(a.end, b.end) 
        */

        int l=max(A[i][0], B[j][0]);
        int u=min(A[i][1], B[j][1]);
        if(l<=u) 
            ret.push_back({l,u});
        if(A[i][1] < B[j][1])   
            i++;
        else 
            j++;
    }
    
    return ret;
}
```


## Minimum Meeting room

https://leetcode.com/problems/meeting-rooms-ii/#/description

https://www.educative.io/courses/grokking-the-coding-interview/JQMAmrVPL7l

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
    //min heap, top is earilest ending time
    priority_queue<Interval, vector<Interval>, pq_compare> pq;//maintain the earliest ends time, min queue
    pq.push(intervals[0]);
    for(int i=1;i<intervals.size();i++){
        Interval tmp = pq.top();
        //no additional room needed, pop current(current meeting end), push new, so meeting room is same
        if(intervals[i].start>=tmp.end){
            pq.pop(); 
        }
        pq.push(intervals[i]);
    }
    return pq.size();
}

```

## Max CPU time

https://www.educative.io/courses/grokking-the-coding-interview/xVlyyv3rR93


We are given a list of Jobs. Each job has a Start time, an End time, and a CPU load when it is running. Our goal is to find the maximum CPU load at any time if all the jobs are running on the same machine.
```
Example 1:

Jobs: [[1,4,3], [2,5,4], [7,9,6]]
Output: 7
Explanation: Since [1,4,3] and [2,5,4] overlap, their maximum CPU load (3+4=7) will be when both the 
jobs are running at the same time i.e., during the time interval (2,4)
```

The problem follows the Merge Intervals pattern and can easily be converted to Minimum Meeting Rooms. Similar to ‘Minimum Meeting Rooms’ where we were trying to find the maximum number of meetings happening at any time, for ‘Maximum CPU Load’ we need to find the maximum number of jobs running at any time.


```CPP
static bool startcomp(Interval s1, Interval s2){
    return s1.start<s2.start;
}

struct endCompare {
    bool operator()(const Job &x, const Job &y) { return x.end > y.end; }
  };

  static int findMaxCPULoad(vector<Job> &jobs) {
    if (jobs.empty()) {
      return 0;
    }

    // sort the jobs by start time
    sort(jobs.begin(), jobs.end(), startcomp);

    int maxCPULoad = 0;
    int currentCPULoad = 0;
    //minheap, top is earilest ending job
    priority_queue<Job, vector<Job>, endCompare> minHeap;
    for (auto job : jobs) {
      // remove all jobs that have ended
      while (!minHeap.empty() && job.start > minHeap.top().end) {
        currentCPULoad -= minHeap.top().cpuLoad;
        minHeap.pop();
      }

      // add the current job into the minHeap
      minHeap.push(job);
      currentCPULoad += job.cpuLoad;
      maxCPULoad = max(maxCPULoad, currentCPULoad);
    }

    return maxCPULoad;
  }
```

## Course schedule with deadline

https://leetcode.com/problems/course-schedule-iii/

There are n different online courses numbered from 1 to n. Each course has some duration(course length) t and closed on dth day. A course should be taken continuously for t days and must be finished before or on the dth day. You will start at the 1st day.

Given n online courses represented by pairs (t,d), your task is to find the maximal number of courses that can be taken.

```
Example:

Input: [[100, 200], [200, 1300], [1000, 1250], [2000, 3200]]
Output: 3
Explanation: 
There're totally 4 courses, but you can take 3 courses at most:
First, take the 1st course, it costs 100 days so you will finish it on the 100th day, and ready to take the next course on the 101st day.
Second, take the 3rd course, it costs 1000 days so you will finish it on the 1100th day, and ready to take the next course on the 1101st day. 
Third, take the 2nd course, it costs 200 days so you will finish it on the 1300th day. 
The 4th course cannot be taken now, since you will finish it on the 3300th day, which exceeds the closed date.
```

```CPP
struct comp{
      bool operator()(const vector<int>& v1, const vector<int>& v2) {
          return v1[1] < v2[1];
      } 
    };
    

    int scheduleCourse(vector<vector<int>>& courses) 
    {
        //sort by ending time of course
        sort(courses.begin(), courses.end(), comp());
        
        // max heap, so top is longest time taken course
        priority_queue<int> q;
        
        int sum = 0;
        for (auto& c : courses)
        {
            int t = c[0]; //Course time
            int d = c[1]; //Max day before which course has to be completed
            
            q.push(t);
            sum += t;
            
            //can not finish before deadline, pop most time taken course
            while (sum > d)
            {
                sum -= q.top(); //This can be some other long course
                q.pop();
            }

        }
        return q.size();
    }
```

## Meeting Scheduler

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



## Employee Free time

https://leetcode.com/problems/employee-free-time/

https://www.educative.io/courses/grokking-the-coding-interview/YQykDmBnvB0

For ‘K’ employees, we are given a list of intervals representing the working hours of each employee. Our goal is to find out if there is a free interval that is common to all employees. You can assume that each list of employee working hours is sorted on the start time.

```
Example 1:

Input: Employee Working Hours=[[[1,3], [5,6]], [[2,3], [6,8]]]
Output: [3,5]
Explanation: Both the employees are free between [3,5].
Example 2:

Input: Employee Working Hours=[[[1,3], [9,12]], [[2,4]], [[6,8]]]
Output: [4,6], [8,9]
Explanation: All employees are free between [4,6] and [8,9].
```

```CPP
struct startCompare {
        bool operator()(pair<Interval, pair<int, int>> &x,
                        pair<Interval, pair<int, int>> &y) {
          return x.first.start > y.first.start;
        }
    };
    
    vector<Interval> employeeFreeTime(vector<vector<Interval>>& schedule) {
        vector<Interval> ret;
        if (schedule.empty()) {
          return ret;
        }

        // min Heap 
        priority_queue<pair<Interval, pair<int, int>>, vector<pair<Interval, pair<int, int>>>,
                       startCompare>
            minHeap;

        // insert the first interval of each employee to the queue
        for (int i = 0; i < schedule.size(); i++) {
          minHeap.push(make_pair(schedule[i][0], make_pair(i, 0)));
        }
        
        /*
        Once we have the smallest start-time interval, we can then compare it with the next smallest start-time interval (again from the Heap) to find the gap
        */
        
        Interval prev = minHeap.top().first; 
        while(!minHeap.empty()){
            auto next = minHeap.top();
            minHeap.pop();
            //no overlap
            if (prev.end < next.first.start) {
                ret.push_back({prev.end, next.first.start});
                prev = next.first;
              } else {  
                // overlapping intervals, update the prev if needed
                if (prev.end < next.first.end) {
                  prev = next.first;
                }
            }
            
    
            vector<Interval> cur_employee = schedule[next.second.first];
            //index of current employee's next schedule
            int next_index = next.second.second + 1;
            if (cur_employee.size() > next_index) {
                minHeap.push(make_pair(cur_employee[next_index],
                                   make_pair(next.second.first, next_index)));
            }
        }
        
        return ret;
    }
```

* Another simple way, flat out the interval

```CPP
vector<Interval> employeeFreeTime(vector<vector<Interval>>& schedule) {
    vector<Interval> res, v;
    for (auto a : schedule) {
        v.insert(v.end(), a.begin(), a.end());
    }
    sort(v.begin(), v.end(), mycompare);
    Interval t = v[0];
    for (Interval i : v) {
        if (t.end < i.start) {
            res.push_back(Interval(t.end, i.start));
            t = i;
        } else {
            t = (t.end < i.end) ? i : t;
        }
    }
    return res;
}
```


## Ballon Burst


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

## Skyline

A city's skyline is the outer contour of the silhouette formed by all the buildings in that city when viewed from a distance. Now suppose you are given the locations and height of all the buildings as shown on a cityscape photo (Figure A), write a program to output the skyline formed by these buildings collectively (Figure B).

```CPP
vector<pair<int, int>> getSkyline(vector<vector<int>>& buildings) {
        vector<pair<int, int>> res;
        int cur=0, cur_X, cur_H =-1,  len = buildings.size();
        priority_queue< pair<int, int>> liveBlg; // first: height, second, end time
        while(cur<len || !liveBlg.empty())
        { // if either some new building is not processed or live building queue is not empty
            cur_X = liveBlg.empty()? buildings[cur][0]:liveBlg.top().second; // next timing point to process

            if(cur>=len || buildings[cur][0] > cur_X)
            { //first check if the current tallest building will end before the next timing point
                  // pop up the processed buildings, i.e. those  have height no larger than cur_H and end before the top one
                while(!liveBlg.empty() && ( liveBlg.top().second <= cur_X) ) liveBlg.pop();
            }
            else
            { // if the next new building starts before the top one ends, process the new building in the vector
                cur_X = buildings[cur][0];
                while(cur<len && buildings[cur][0]== cur_X)  // go through all the new buildings that starts at the same point
                {  // just push them in the queue
                    liveBlg.push(make_pair(buildings[cur][2], buildings[cur][1]));
                    cur++;
                }
            }
            cur_H = liveBlg.empty()?0:liveBlg.top().first; // outut the top one
            if(res.empty() || (res.back().second != cur_H) ) res.push_back(make_pair(cur_X, cur_H));
        }
        return res;
    }
```