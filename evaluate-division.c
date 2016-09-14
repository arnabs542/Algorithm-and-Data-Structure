//https://leetcode.com/problems/evaluate-division/
/*
 Equations are given in the format A / B = k, where A and B are variables represented as strings, and k is a real number (floating point number). Given some queries, return the answers. If the answer does not exist, return -1.0.

Example:
Given a / b = 2.0, b / c = 3.0.
queries are: a / c = ?, b / a = ?, a / e = ?, a / a = ?, x / x = ? .
return [6.0, 0.5, -1.0, 1.0, -1.0 ].

The input is: vector<pair<string, string>> equations, vector<double>& values, vector<pair<string, string>> queries , where equations.size() == values.size(), and the values are positive. This represents the equations. Return vector<double>.

According to the example above:

equations = [ ["a", "b"], ["b", "c"] ],
values = [2.0, 3.0],
queries = [ ["a", "c"], ["b", "a"], ["a", "e"], ["a", "a"], ["x", "x"] ]. 
*/

//method 1:
class Solution {
public:
    vector<double> calcEquation(vector<pair<string, string>> equations, vector<double>& values, vector<pair<string, string>> queries) {
        //map: key is string, and value is vector of pair <string,float>
        //key: string
        //value: vector<string,val> string is , value is division along path
        int len = equations.size();
        vector<string> root(len);

        unordered_map<string,vector<pair<string,double>>> m;
        for(int i=0;i<len;i++){
            string s1=equations[i].first;
            string s2=equations[i].second;
            
            pair<string,double> tmp;

            tmp.first = s2;
            tmp.second=values[i];
            m[s1].push_back(tmp);
            //reverse way
            tmp.first = s1;
            tmp.second=1/values[i];
            m[s2].push_back(tmp);

        }
        vector<double> ret;
        for(int i=0;i<queries.size();i++){
			unordered_set<string> visited;
			visited.insert(queries[i].first);
			double res = 1;
			if(dfs(m, visited, queries[i].first, queries[i].second, res))
				ret.push_back(res);
			else
				ret.push_back(-1);
        }
        
        return ret;
    }
    
    
    bool dfs(unordered_map<string, vector<pair<string, double>>>& m, unordered_set<string>& visited, string& s, string& e, double& res) {
		if (m.find(s) == m.end()) return false;
		if (s == e) return true;

		for (int i = 0; i < m[s].size(); i++) {
			if (visited.find(m[s][i].first) == visited.end()) {
				visited.insert(m[s][i].first);
				double old = res;
				res *= m[s][i].second;
				if (dfs(m, visited, m[s][i].first, e, res))
					return true;
				res = old;
				visited.erase(m[s][i].first);
			}
		}

		return false;
	}
};


//method 2:
class Solution {
public:
    vector<double> calcEquation(vector<pair<string, string>> equations, vector<double>& values, vector<pair<string, string>> queries) {
        //map: key is string, and value is vector of pair <string,float>
        //key: string
        //value: unordered_map<string,val> string is , value is dinomination
        int len = equations.size();
        vector<string> root(len);

        unordered_map<string,unordered_map<string,double>> m;
        for(int i=0;i<len;i++){
            string s1=equations[i].first;
            string s2=equations[i].second;
            
            pair<string,double> tmp;

            tmp.first = s2;
            tmp.second=values[i];
            m[s1].insert(tmp);
            //reverse way
            tmp.first = s1;
            tmp.second=1/values[i];
            m[s2].insert(tmp);

        }
        vector<double> ret;
        for(int i=0;i<queries.size();i++){
			unordered_set<string> visited;
			//need to have a visited mark to record visited and avoid loop.
			double res = dfs(m, visited, queries[i].first, queries[i].second);
			if(res)
				ret.push_back(res);
			else
				ret.push_back(-1);
        }
        
        return ret;
    }
    
    
    double dfs(unordered_map<string,unordered_map<string,double>> &m, unordered_set<string>& visited, string s, string e) {
		if(m.find(s) == m.end()) 
		    return -1.0;
		if(s == e) 
		    return 1.0;
		    //found the direct 
		if(m[s].find(e)!=m[s].end()){
		    return m[s][e];
		}

		for (auto i:m[s]) {
            if(visited.find(i.first)==visited.end()){
                visited.insert(i.first);
                double res = dfs(m,visited,i.first,e);
                if(res)
                    return i.second*res;
            }
		}

		return 0;
	}
};
