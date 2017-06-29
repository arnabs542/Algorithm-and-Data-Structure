/*
//https://leetcode.com/contest/leetcode-weekly-contest-18a/problems/ipo/
Suppose LeetCode will start its IPO soon. In order to sell a good price of its shares to Venture Capital, LeetCode would like to work on some projects to increase its capital before the IPO. Since it has limited resources, it can only finish at most k distinct projects before the IPO. Help LeetCode design the best way to maximize its total capital after finishing at most k distinct projects.

You are given several projects. For each project i, it has a pure profit Pi and a minimum capital of Ci is needed to start the corresponding project. Initially, you have W capital. When you finish a project, you will obtain its pure profit and the profit will be added to your total capital.

To sum up, pick a list of at most k distinct projects from given projects to maximize your final capital, and output your final maximized capital.

Example 1:
Input: k=2, W=0, Profits=[1,2,3], Capital=[0,1,1].

Output: 4

Explanation: Since your initial capital is 0, you can only start the project indexed 0.
             After finishing it you will obtain profit 1 and your capital becomes 1.
             With capital 1, you can either start the project indexed 1 or the project indexed 2.
             Since you can choose at most 2 projects, you need to finish the project indexed 2 to get the maximum capital.
             Therefore, output the final maximized capital, which is 0 + 1 + 3 = 4.
*/

struct cost_compare{
    bool operator()(pair<int,int> a, pair<int,int> b){
        return a.first>b.first;
    }
};

struct profit_compare{
    bool operator()(pair<int,int> a, pair<int,int> b){
        return a.second<b.second;
    }
};
int findMaximizedCapital(int k, int W, vector<int>& Profits, vector<int>& Capital) {
    priority_queue<pair<int,int>,vector<pair<int,int>>,cost_compare> cost; //min heap for cost
    priority_queue<pair<int,int>,vector<pair<int,int>>,profit_compare> profit; //max heap for profit

    int len = Capital.size();
    pair<int,int> cur;
    for(int i=0;i<len;i++){
        cur = make_pair(Capital[i],Profits[i]);
        cost.push(cur);
    }
    int picks = 0;
    while(k>0){

     while(!cost.empty() && W>=cost.top().first){
        //only pick possible project, do not trade yet
        profit.push(cost.top());
        cost.pop();
     }
     if(profit.empty())
        break;
    //deal the real transaction here
      cur = profit.top();
      W = W + cur.second;
      profit.pop();
      k--;
    }
    return W;
}
