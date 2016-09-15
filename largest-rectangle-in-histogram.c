//https://leetcode.com/problems/largest-rectangle-in-histogram/
/*
 Given n non-negative integers representing the histogram's bar height where the width of each bar is 1, find the area of largest rectangle in the histogram.
Above is a histogram where width of each bar is 1, given height = [2,1,5,6,2,3].
The largest rectangle is shown in the shaded area, which has area = 10 unit.
For example,
Given heights = [2,1,5,6,2,3],
return 10. 
*/
class Solution {
public:
    int largestRectangleArea(vector<int>& heights) {
        //use a stack to track the index
        //only push index if height[index] > height[back of vector],
        //stack only has increasing height's index
        
        int ret = 0;
        heights.push_back(0); //no run time error.
        stack<int> index;
        for(int i=0;i<heights.size();i++){
            //we are not in continous height increase anymore, need to cal back all area  
            while(index.size()>0 && heights[index.top()] >= heights[i]){
                int h = heights[index.top()];
                index.pop();
                int left = index.size() > 0 ? index.top() : -1;
                int area = (i-left-1)*h;
                ret = ret>area?ret:area;
            }
            index.push(i);
        }
        return ret;
    }
};
