//https://leetcode.com/problems/insert-interval/
/*
Given a set of non-overlapping intervals, insert a new interval into the intervals (merge if necessary).
You may assume that the intervals were initially sorted according to their start times.

Example 1:
Given intervals [1,3],[6,9], insert and merge [2,5] in as [1,5],[6,9].

Example 2:
Given [1,2],[3,5],[6,7],[8,10],[12,16], insert and merge [4,9] in as [1,2],[3,10],[12,16].

This is because the new interval [4,9] overlaps with [3,5],[6,7],[8,10].
*/
class Solution {
private:
    static bool mycompare(Interval s1, Interval s2){
        return s1.start<s2.start;
    }
public:
    vector<Interval> insert(vector<Interval>& intervals, Interval newInterval) {
        vector<Interval> ret;
        sort(intervals.begin(),intervals.end(),mycompare);
        int i=0;
        int len = intervals.size();
        if(len==0){
            ret.push_back(newInterval);
            return ret;
        }

        while(i<len && intervals[i].end<newInterval.start){
            ret.push_back(intervals[i]);
            i++;
        }
        //insert the interval
        while(i<len&&intervals[i].start<=newInterval.end){
            
            newInterval.start = min(newInterval.start,intervals[i].start);
            newInterval.end = max(newInterval.end,intervals[i].end);
            i++;
        }
        ret.push_back(newInterval);
        
        //check the remaining after insert
        while(i < len){
            ret.push_back(intervals[i]);
            i++;
        }
        
        return ret;
        
    }
};
