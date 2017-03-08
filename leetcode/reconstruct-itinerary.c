//https://leetcode.com/problems/reconstruct-itinerary/
/*
Given a list of airline tickets represented by pairs of departure and arrival airports [from, to], reconstruct the itinerary in order. All of the tickets belong to a man who departs from JFK. Thus, the itinerary must begin with JFK.

Note:
    If there are multiple valid itineraries, you should return the itinerary that has the smallest lexical order when read as a single string. For example, the itinerary ["JFK", "LGA"] has a smaller lexical order than ["JFK", "LGB"].
    All airports are represented by three capital letters (IATA code).
    You may assume all tickets form at least one valid itinerary.

Example 1:
tickets = [["MUC", "LHR"], ["JFK", "MUC"], ["SFO", "SJC"], ["LHR", "SFO"]]
Return ["JFK", "MUC", "LHR", "SFO", "SJC"].

Example 2:
tickets = [["JFK","SFO"],["JFK","ATL"],["SFO","ATL"],["ATL","JFK"],["ATL","SFO"]]
Return ["JFK","ATL","JFK","SFO","ATL","SFO"].
Another possible reconstruction is ["JFK","SFO","ATL","JFK","ATL","SFO"]. But it is larger in lexical order. 
*/

class Solution {
public:
    vector<string> findItinerary(vector<pair<string, string>> tickets) {
        vector<string> ret;
        //graph: key is airport and val is set of destination from its airport
        //use set to ensure the lexical order
        //need to use multiset in order to keep mutiple cases for airport
        unordered_map<string,multiset<string>> g;
        for(int i=0;i<tickets.size();i++){
            pair<string, string> cur=tickets[i];
            string src=cur.first;
            string dest = cur.second;
            g[src].insert(dest);
        }
        dfs(ret,g,"JFK");
        reverse(ret.begin(),ret.end());
        return ret;
    }
    
    void dfs(vector<string> &ret,unordered_map<string,multiset<string>> &g,string src){
        while(!g[src].empty()){
            set<string>::iterator it = g[src].begin(); //lexical order: we only interested in first
            string dest = *it;
            g[src].erase(it);//visited, remove
            dfs(ret,g,dest);
        }
        ret.push_back(src);
    }
};
