//https://leetcode.com/problems/exclusive-time-of-functions/#/description
/*
Given the running logs of n functions that are executed in a nonpreemptive single threaded CPU, find the exclusive time of these functions.
Each function has a unique id, start from 0 to n-1. A function may be called recursively or by another function.
A log is a string has this format : function_id:start_or_end:timestamp. For example, "0:start:0" means function 0 starts from the very beginning of time 0. "0:end:0" means function 0 ends to the very end of time 0.
Exclusive time of a function is defined as the time spent within this function, the time spent by calling other functions should not be considered as this function's exclusive time. You should return the exclusive time of each function sorted by their function id.

Example 1:
Input:
n = 2
logs =
["0:start:0",
 "1:start:2",
 "1:end:5",
 "0:end:6"]
Output:[3, 4]
Explanation:
Function 0 starts at time 0, then it executes 2 units of time and reaches the end of time 1.
Now function 0 calls function 1, function 1 starts at time 2, executes 4 units of time and end at time 5.
Function 0 is running again at time 6, and also end at the time 6, thus executes 1 unit of time.
So function 0 totally execute 2 + 1 = 3 units of time, and function 1 totally execute 4 units of time.
*/

vector<int> exclusiveTime(int n, vector<string>& logs) {
    vector<int> ret(n,0); //func id as index, time is value
    stack<pair<int,int>> s; //func id, current execution time, when start, push, when end, pop

    for(int i=0;i<logs.size();i++){
        int index = 0;
        int id = checkid(logs[i],index);
        int label = checklabel(logs[i],index);
        int t = checktime(logs[i],index);
        if(label==0){
            s.push(make_pair(id,t));
        }else{
            pair<int,int> cur = s.top();
            int last = t-cur.second+1;
            ret[cur.first]+=last;
            s.pop();
            if (!s.empty()) {
              //to remove over count, not time for s.top().first id 
                ret[s.top().first] -= last;
            }
        }
    }


    return ret;
}

int checkid(string s, int &index){
    int ret = 0;
    while(index<s.size()){
        if(s[index]==':'){
            index++;
            break;
        }
        ret = ret*10+s[index]-'0';
        index++;
    }
    return ret;
}

int checklabel(string s,int &index){
    int ret = 0;

    if(s[index]=='s'){
        index = index + 6;
        ret = 0;
    }else{
        index = index + 4;
        ret = 1;
    }
    return ret;
}

int checktime(string s, int &index){
    int ret = 0;
    while(index<s.size()){
        ret = ret*10+s[index]-'0';
        index++;
    }
    return ret;
}
