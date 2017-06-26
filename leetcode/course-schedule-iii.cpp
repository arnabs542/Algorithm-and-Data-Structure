/*
https://leetcode.com/problems/course-schedule-iii/#/description

There are n different online courses numbered from 1 to n. Each course has some duration(course length) t and closed on dth day. A course should be taken continuously for t days and must be finished before or on the dth day. You will start at the 1st day.
Given n online courses represented by pairs (t,d), your task is to find the maximal number of courses that can be taken.

Example:
Input: [[100, 200], [200, 1300], [1000, 1250], [2000, 3200]]
Output: 3
Explanation:
There're totally 4 courses, but you can take 3 courses at most:
First, take the 1st course, it costs 100 days so you will finish it on the 100th day, and ready to take the next course on the 101st day.
Second, take the 3rd course, it costs 1000 days so you will finish it on the 1100th day, and ready to take the next course on the 1101st day.
Third, take the 2nd course, it costs 200 days so you will finish it on the 1300th day.
The 4th course cannot be taken now, since you will finish it on the 3300th day, which exceeds the closed date.
*/

struct mycompare{
    bool operator()(vector<int> a, vector<int> b){
        return a.back()<b.back();
    }
};
int scheduleCourse(vector<vector<int>>& courses) {
    sort(courses.begin(),courses.end(),mycompare()); //sort via course ending time
    multiset<int> cls;
    int start = 0;
    for(int i=0;i<courses.size();i++){
        if(start+courses[i].front()<=courses[i].back()){
            cls.insert(courses[i].front());
            start+=courses[i].front();
        }else if(*cls.rbegin()>courses[i].front()){
            // if we don't have enough time, we switch out a longer course and try again
            if(start+courses[i].front()-*cls.rbegin()<=courses[i].back()){
                start+=courses[i].front()-*cls.rbegin();
                cls.erase(--cls.end());
                cls.insert(courses[i].front());
            }

        }// if we don't have enough time for course[i],
          //and it's longer than any courses taken, then we ignore it
    }
    return cls.size();
}
