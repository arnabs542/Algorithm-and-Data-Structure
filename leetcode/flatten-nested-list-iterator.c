//https://leetcode.com/problems/flatten-nested-list-iterator/
/*
Given a nested list of integers, implement an iterator to flatten it.
Each element is either an integer, or a list -- whose elements may also be integers or other lists.
Example 1:
Given the list [[1,1],2,[1,1]],

By calling next repeatedly until hasNext returns false, the order of elements returned by next should be: [1,1,2,1,1].
Example 2:
Given the list [1,[4,[6]]],
By calling next repeatedly until hasNext returns false, the order of elements returned by next should be: [1,4,6].
*/
/**
 * // This is the interface that allows for creating nested lists.
 * // You should not implement it, or speculate about its implementation
 * class NestedInteger {
 *   public:
 *     // Return true if this NestedInteger holds a single integer, rather than a nested list.
 *     bool isInteger() const;
 *
 *     // Return the single integer that this NestedInteger holds, if it holds a single integer
 *     // The result is undefined if this NestedInteger holds a nested list
 *     int getInteger() const;
 *
 *     // Return the nested list that this NestedInteger holds, if it holds a nested list
 *     // The result is undefined if this NestedInteger holds a single integer
 *     const vector<NestedInteger> &getList() const;
 * };
 */
class NestedIterator {
    stack<NestedInteger> s;
public:
    NestedIterator(vector<NestedInteger> &nestedList) {
        int len = nestedList.size();
        //need to push from back of list in stack so stack top is front of list
        for(int i=len-1;i>=0;i--){
            s.push(nestedList[i]);
        }
    }

    int next() {
        if(hasNext()){
            int ret = s.top().getInteger();
            s.pop();
            return ret;
        }
        return 0;
    }

    bool hasNext() {
        while(!s.empty()){
            NestedInteger cur = s.top();
            if(cur.isInteger()){
                return true;
            }else{
                s.pop();
                vector<NestedInteger>& nextone = cur.getList();
                int len = nextone.size();
                for(int i=len-1;i>=0;i--){
                    s.push(nextone[i]);
                }
                
            }
            
        }
        return false;
    }
};

/**
 * Your NestedIterator object will be instantiated and called as such:
 * NestedIterator i(nestedList);
 * while (i.hasNext()) cout << i.next();
 */
