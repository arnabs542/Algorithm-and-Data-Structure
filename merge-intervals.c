//https://leetcode.com/problems/merge-intervals/
/*
Given a collection of intervals, merge all overlapping intervals.

For example,
Given [1,3],[2,6],[8,10],[15,18],
return [1,6],[8,10],[15,18]. 
*/
//method 1:
class Solution {
private:
    static bool mycompare(Interval s1, Interval s2){
        return s1.start<s2.start;
    }
public:
    vector<Interval> merge(vector<Interval>& intervals) {
        vector<Interval> ret;
        if(intervals.size()==0)
            return ret;
        sort(intervals.begin(),intervals.end(),mycompare);
        int start = intervals[0].start;
        int end = intervals[0].end;
        int len = intervals.size();
        for(int i=1;i<len;i++){
            if(intervals[i].start<=end){
                //merge
                end = intervals[i].end>end?intervals[i].end:end;
            }else{
                Interval cur;
                cur.start = start;
                cur.end = end;
                ret.push_back(cur);
                start = intervals[i].start;
                end = intervals[i].end;
            }
        }
        //we need to merge the final one
        Interval cur;
        cur.start = start;
        cur.end = end;
        ret.push_back(cur);

        return ret;
    }
};

//method 2:
class Solution {
private:
    static bool mycompare(Interval s1, Interval s2){
        return s1.start<s2.start;
    }
public:
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
};
