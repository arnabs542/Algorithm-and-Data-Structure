/*
https://leetcode.com/problems/task-scheduler/#/description
Given a char array representing tasks CPU need to do. It contains capital letters A to Z where different letters represent different tasks.Tasks could be done without original order. Each task could be done in one interval. For each interval, CPU could finish one task or just be idle.

However, there is a non-negative cooling interval n that means between two same tasks, there must be at least n intervals that CPU are doing different tasks or just be idle.

You need to return the least number of intervals the CPU will take to finish all the given tasks.

Example 1:
Input: tasks = ['A','A','A','B','B','B'], n = 2
Output: 8
Explanation: A -> B -> idle -> A -> B -> idle -> A -> B.
*/

int leastInterval(vector<char>& tasks, int n) {
    map<char,int> m;
    for(int i=0;i<tasks.size();i++){
        m[tasks[i]]++;
    }
    priority_queue<int> pq; //heap for task's count
    for(auto i:m){
        pq.push(i.second);
    }
    int ret = 0;
    int cycle = n+1;
    while(!pq.empty()){
        int t = 0;
        vector<int> tmp;
        for(int i=0;i<cycle;i++){
            if(!pq.empty()){
                tmp.push_back(pq.top());
                pq.pop();
                t++;
            }
        }
        for (int i=0;i<tmp.size();i++) {
            if (--tmp[i]>0) {
                pq.push(tmp[i]);
            }
        }
        ret += !pq.empty() ? cycle : t;
    }

    return ret;
}
