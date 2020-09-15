<!-- START doctoc generated TOC please keep comment here to allow auto update -->
<!-- DON'T EDIT THIS SECTION, INSTEAD RE-RUN doctoc TO UPDATE -->
**Table of Contents**  *generated with [DocToc](https://github.com/thlorenz/doctoc)*

- [Data structure](#data-structure)
  - [Edge List](#edge-list)
  - [Adjacency list](#adjacency-list)
  - [Matrix](#matrix)
  - [Access complexity](#access-complexity)
- [Traversal](#traversal)
  - [Build Graph: from edge list to adjacent List](#build-graph-from-edge-list-to-adjacent-list)
  - [DFS](#dfs)
    - [Check Graph Connection](#check-graph-connection)
    - [evaluate-division](#evaluate-division)
    - [reconstruct-itinerary](#reconstruct-itinerary)
    - [Check Valid Path](#check-valid-path)
  - [BFS](#bfs)
    - [Shortest path](#shortest-path)
      - [Path with Obstable](#path-with-obstable)
    - [Minimum Height Tree](#minimum-height-tree)
- [Connected components via Union Find/DFS/BFS](#connected-components-via-union-finddfsbfs)
  - [Basic idea](#basic-idea)
    - [Number of island](#number-of-island)
    - [Number of connected component](#number-of-connected-component)
    - [Number of component with some step count](#number-of-component-with-some-step-count)
      - [Rotting Oranges](#rotting-oranges)
    - [Number of island](#number-of-island-1)
    - [Friends Circle](#friends-circle)
    - [Graph Valid Tree](#graph-valid-tree)
- [Topological Sort](#topological-sort)
    - [Detect Circle via Topo Sort](#detect-circle-via-topo-sort)
  - [DFS](#dfs-1)
  - [BFS](#bfs-1)
  - [Example](#example)
    - [Sequence Reconstruction](#sequence-reconstruction)
    - [Course Schedule](#course-schedule)

<!-- END doctoc generated TOC please keep comment here to allow auto update -->

# Data structure
There are three basic ways to represent a graph in memory (objects and pointers, matrix, and adjacency list.

## Edge List
One simple way to represent a graph is just a list, or array, of |E| edges, which we call an edge list.

It looks like
```
[ [0,1], [0,6], [0,8], [1,4], [1,6], [1,9], [2,4], [2,6], [3,4], [3,5],
[3,8], [4,5], [4,9], [7,8], [7,9] ]
```

## Adjacency list

Example is
```
[ [1, 6, 8],
  [0, 4, 6, 9],
  [4, 6],
  [4, 5, 8],
  [1, 2, 3, 5, 9],
  [3, 4],
  [0, 1, 2],
  [8, 9],
  [0, 3, 7],
  [1, 4, 7] ]
```
Vertex numbers in an adjacency list are not required to appear in any particular order, though it is often convenient to list them in increasing order, as in this example.
We can get to each vertex's adjacency list in constant time, because we just have to index into an array. To find out whether an edge (i,j) is present in the graph, we go to i's adjacency list in constant time and then look for j in i's adjacency list.

Code to visit each node and do some stuff
```CPP
for(int i=0;i<graph.size();i++){
  for(int j=0;j<graph[i].size();j++){
    do_stuff(graph[i][j])
  }
}

```

## Matrix

Entire matrix to represent it


## Access complexity
* Edge list
1.	Adding an edge – O(1);
2.	Deleting an edge – O(1);
3.	Answering the question “is there an edge between i and j” – O(1);
4.	Finding the successors of a given vertex – O(n);
5.	Finding (if exists) a path between two vertices – O(n2);

* Adjacent List

1.	Adding an edge – O(log(n));
2.	Deleting an edge – O(log(n));
3.	Answering the question “is there an edge between i and j” – O(log(n));
4.	Finding the successors of a given vertex – O(k), where “k” is the length of the lists containing the successors of i;
5.	Finding (if exists) a path between two vertices – O(n+m) – where m <= n;


# Traversal

## Build Graph: from edge list to adjacent List
```CPP
/*
Edge list to Graph
*/
//two commonly used data structure to build graph
//if no associated path is needed, key is some vertex, value is all vertexes linked to key
unordered_map<vertex, unordered_set<vertex>> m;
//key is some vertex, value is a map, with which vertex is vertex linked to key's vertex, and val is some parameter associated with path
unordered_map<vertex, unordered_map<vertex, val>> m;

for (int i = 0; i < edge.size(); i++) {
	//for first case
	m[edge[i].first].insert(edge[i].second);
	m[edge[i].second].insert(edge[i].first);
	//for second case
	m[edge[i].first].insert(make_pair(edge[i].second,val[i]));
	m[edge[i].second].insert(make_pair(edge[i].firsr, 1/val[i]));
}
```

## DFS

```CPP
void Graph::DFSUtil(int v, bool visited[])
{
    // Mark the current node as visited and print it
    visited[v] = true;
    cout << v << " ";

    // Recur for all the vertices adjacent to this vertex
    list<int>::iterator i;
    for (i = adj[v].begin(); i != adj[v].end(); ++i)
        if (!visited[*i])
            DFSUtil(*i, visited);
}

// DFS traversal of the vertices reachable from v.
// It uses recursive DFSUtil()
void Graph::DFS(int v)
{
    // Mark all the vertices as not visited
    bool *visited = new bool[V];
    for (int i = 0; i < V; i++)
        visited[i] = false;

    // Call the recursive helper function to print DFS traversal
    DFSUtil(v, visited);
}
```

### Check Graph Connection

https://leetcode.com/problems/critical-connections-in-a-network/

There are n servers numbered from 0 to n-1 connected by undirected server-to-server connections forming a network where connections[i] = [a, b] represents a connection between servers a and b. Any server can reach any other server directly or indirectly through the network.

A critical connection is a connection that, if removed, will make some server unable to reach some other server.

Return all critical connections in the network in any order.

```

Example 1:

Input: n = 4, connections = [[0,1],[1,2],[2,0],[1,3]]
Output: [[1,3]]
Explanation: [[3,1]] is also accepted.
```

```CPP
//Key idea is to find cycle, if node is in cycle then it is not in critical path


```


### evaluate-division
```CPP
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
		//value: unordered_map<string,val> string is , value is dinomination
		int len = equations.size();
		vector<string> root(len);

		unordered_map<string, unordered_map<string, double>> m;
		for (int i = 0; i<len; i++) {
			string s1 = equations[i].first;
			string s2 = equations[i].second;

			pair<string, double> tmp;

			tmp.first = s2;
			tmp.second = values[i];
			m[s1].insert(tmp);
			//reverse way
			tmp.first = s1;
			tmp.second = 1 / values[i];
			m[s2].insert(tmp);

		}
		vector<double> ret;
		for (int i = 0; i<queries.size(); i++) {
			unordered_set<string> visited;
			//need to have a visited mark to record visited and avoid loop.
			double res = dfs(m, visited, queries[i].first, queries[i].second);
			if (res)
				ret.push_back(res);
			else
				ret.push_back(-1);
		}

		return ret;
	}


	double dfs(unordered_map<string, unordered_map<string, double>> &m, unordered_set<string>& visited, string s, string e) {
		if (m.find(s) == m.end())
			return -1.0;
		if (s == e)
			return 1.0;
		//found the direct
		if (m[s].find(e) != m[s].end()) {
			return m[s][e];
		}

		for (auto i : m[s]) {
			if (visited.find(i.first) == visited.end()) {
				visited.insert(i.first);
				double res = dfs(m, visited, i.first, e);
				if (res)
					return i.second*res;
			}
		}

		return 0;
	}
};

```

### reconstruct-itinerary


```CPP
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
		unordered_map<string, multiset<string>> g;
		for (int i = 0; i<tickets.size(); i++) {
			pair<string, string> cur = tickets[i];
			string src = cur.first;
			string dest = cur.second;
			g[src].insert(dest);
		}
		dfs(ret, g, "JFK");
		reverse(ret.begin(), ret.end());
		return ret;
	}

	void dfs(vector<string> &ret, unordered_map<string, multiset<string>> &g, string src) {
		while (!g[src].empty()) {
			set<string>::iterator it = g[src].begin(); //lexical order: we only interested in first
			string dest = * it;
			g[src].erase(it);//visited, remove
			dfs(ret, g, dest);
		}
		ret.push_back(src);
	}
};
```

### Check Valid Path



## BFS

```CPP
void Graph::BFS(int s)
{
    // Mark all the vertices as not visited
    bool *visited = new bool[V];
    for(int i = 0; i < V; i++)
        visited[i] = false;

    // Create a queue for BFS
    list<int> queue;

    // Mark the current node as visited and enqueue it
    visited[s] = true;
    queue.push_back(s);

    // 'i' will be used to get all adjacent vertices of a vertex
    list<int>::iterator i;

    while(!queue.empty())
    {
        // Dequeue a vertex from queue and print it
        s = queue.front();
        cout << s << " ";
        queue.pop_front();

        // Get all adjacent vertices of the dequeued vertex s
        // If a adjacent has not been visited, then mark it visited
        // and enqueue it
        for(i = adj[s].begin(); i != adj[s].end(); ++i)
        {
            if(!visited[*i])
            {
                visited[*i] = true;
                queue.push_back(*i);
            }
        }
    }
}
```

### Shortest path

https://leetcode.com/problems/shortest-path-in-binary-matrix/

In an N by N square grid, each cell is either empty (0) or blocked (1).

A clear path from top-left to bottom-right has length k if and only if it is composed of cells C_1, C_2, ..., C_k such that:

```

Adjacent cells C_i and C_{i+1} are connected 8-directionally (ie., they are different and share an edge or corner)
C_1 is at location (0, 0) (ie. has value grid[0][0])
C_k is at location (N-1, N-1) (ie. has value grid[N-1][N-1])
If C_i is located at (r, c), then grid[r][c] is empty (ie. grid[r][c] == 0).
Return the length of the shortest such clear path from top-left to bottom-right.  If such a path does not exist, return -1.
```

```CPP
int shortestPathBinaryMatrix(vector<vector<int>>& grid) {
    int row = grid.size();
    int col = grid[0].size();
    if (grid[0][0]==1 || grid[row-1][col-1]==1)
        return -1;
    //possible to visit all 8 directions
    vector<vector<int>> directions = {{1,1}, {0,1},{1,0},{0,-1},{-1,0},{-1, -1},{1, -1},{-1, 1}};
    queue<pair<int,int>> q;
    //start count
    grid[0][0] =1;
    q.push(make_pair(0,0));
    
    while(!q.empty()){
        auto cur = q.front();
        int x = cur.first, y = cur.second;
        if( x == row -1 && y == col -1) 
            return grid[x][y];

        for(auto direction : directions){
            int nx = x + direction[0];
            int ny = y + direction[1];
            if(nx >= 0 && nx < row && ny >= 0 && ny < col && grid[nx][ny] == 0){
                q.push(make_pair(nx,ny));
                grid[nx][ny] = grid[x][y] + 1;
            }
        }
        q.pop();
    }
    
    return -1;
    
}
```

#### Path with Obstable

https://leetcode.com/problems/shortest-path-in-a-grid-with-obstacles-elimination/

Given a m * n grid, where each cell is either 0 (empty) or 1 (obstacle). In one step, you can move up, down, left or right from and to an empty cell.

Return the minimum number of steps to walk from the upper left corner (0, 0) to the lower right corner (m-1, n-1) given that you can eliminate at most k obstacles. If it is not possible to find such walk return -1.

 
```
Example 1:

Input: 
grid = 
[[0,0,0],
 [1,1,0],
 [0,0,0],
 [0,1,1],
 [0,0,0]], 
k = 1
Output: 6
Explanation: 
The shortest path without eliminating any obstacle is 10. 
The shortest path with one obstacle elimination at position (3,2) is 6. Such path is (0,0) -> (0,1) -> (0,2) -> (1,2) -> (2,2) -> (3,2) -> (4,2).
 

Example 2:

Input: 
grid = 
[[0,1,1],
 [1,1,1],
 [1,0,0]], 
k = 1
Output: -1
Explanation: 
We need to eliminate at least two obstacles to find such a walk.
```

```CPP
int shortestPath(vector<vector<int>>& grid, int k) {
        //set to keep track of already visited paths
        int ret =0;
        int m = grid.size();
        int n = grid[0].size();
        vector<vector<int>> dirs= {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
        // min obstacles elimination from (0,0) to (x, y)
        vector<vector<int>> obs(m, vector<int>(n,INT_MAX));

        //x,y, and how many obstable moved
        queue<vector<int>> q;
        q.push({0,0,0});
        obs[0][0]=0;
        
        while(!q.empty()){
            int size = q.size();
            //level by level
            while(size-->0){
                vector<int> cur = q.front();
                q.pop();
                //to end
                if(cur[0]==m-1 && cur[1]==n-1){
                    return ret;
                }
                for(auto dir: dirs){
                    int x = dir[0] + cur[0];
                    int y = dir[1] + cur[1];
                    if (x < 0 || x >= m || y < 0 || y >= n) {
                        continue;
                    }
                    //either +1 for obstable or same as previous
                    int o = grid[x][y] + cur[2];
                    //
                    if (o >= obs[x][y] || o > k) {
                        continue;
                    }
                    obs[x][y] = o;
                    q.push({x,y,o});
                }
            }
            //for all this level in queue, only +1 for step
            ++ret;
        }
        
        return -1;
    }
```

### Minimum Height Tree
```CPP
//https://leetcode.com/problems/minimum-height-trees/
/*
For a undirected graph with tree characteristics, we can choose any node as the root. The result graph is then a rooted tree. Among all possible rooted trees, those with minimum height are called minimum height trees (MHTs). Given such a graph, write a function to find all the MHTs and return a list of their root labels.
Format
The graph contains n nodes which are labeled from 0 to n - 1. You will be given the number n and a list of undirected edges (each edge is a pair of labels).
You can assume that no duplicate edges will appear in edges. Since all edges are undirected, [0, 1] is the same as [1, 0] and thus will not appear together in edges.
Example 1:
Given n = 4, edges = [[1, 0], [1, 2], [1, 3]]
return [1]
Example 2:
Given n = 6, edges = [[0, 3], [1, 3], [2, 3], [4, 3], [5, 4]]
return [3, 4]
*/

class Solution {
public:
	vector<int> findMinHeightTrees(int n, vector<pair<int, int>>& edges) {
		vector<int> ret;
		//key is int and value is its direct linked node
		unordered_map<int, unordered_set<int>> g;
		for (int i = 0; i<edges.size(); i++) {
			g[edges[i].first].insert(edges[i].second);
			g[edges[i].second].insert(edges[i].first);
		}
		vector<int> cur;
		//corner case
		if (n == 1) {
			cur.push_back(0);
			return cur;
		}

		// Create first leaf layer
		for (int i = 0; i < g.size(); ++i) {
			if (g[i].size() == 1) {
				cur.push_back(i);
			}
		}
		// BFS the graph
		while (true) {
			vector<int> next;
			for (int node : cur) {
				for (int neighbor : g[node]) {
					g[neighbor].erase(node);
					if (g[neighbor].size() == 1)
						next.push_back(neighbor);
				}
			}
			if (next.empty())
				return cur;
			cur = next;
		}
	}
};


```

# Connected components via Union Find/DFS/BFS

## Basic idea
1. via Union find: Basic idea is to find root/parents of certain node, and union if same parents
2. DFS/BFS:  from one item(item in vector or point in 2-D matrix)
	* search all surrounding via DFS/BFS
	* mark visited(through either some visited mark, or change original value)

### Number of island

https://leetcode.com/problems/number-of-islands/

Given a 2d grid map of '1's (land) and '0's (water), count the number of islands. An island is surrounded by water and is formed by connecting adjacent lands horizontally or vertically. You may assume all four edges of the grid are all surrounded by water.

 
```
Example 1:

Input: grid = [
  ["1","1","1","1","0"],
  ["1","1","0","1","0"],
  ["1","1","0","0","0"],
  ["0","0","0","0","0"]
]
Output: 1
Example 2:

Input: grid = [
  ["1","1","0","0","0"],
  ["1","1","0","0","0"],
  ["0","0","1","0","0"],
  ["0","0","0","1","1"]
]
Output: 3
```

```CPP
int numIslands(vector<vector<char>>& grid) {
        int m = grid.size(), n = m ? grid[0].size() : 0, islands = 0;
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (grid[i][j] == '1') {
                    islands++;
                    eraseIslands(grid, i, j);
                }
            }
        }
        return islands;
    }
    
    void eraseIslands(vector<vector<char>>& grid, int i, int j){
         int m = grid.size(), n = grid[0].size();
        if (i < 0 || i == m || j < 0 || j == n || grid[i][j] == '0') {
            return;
        }
        grid[i][j] = '0';
        eraseIslands(grid, i - 1, j);
        eraseIslands(grid, i + 1, j);
        eraseIslands(grid, i, j - 1);
        eraseIslands(grid, i, j + 1);
    }
```

### Number of connected component

https://leetcode.com/problems/number-of-connected-components-in-an-undirected-graph/

```CPP

/*
Given n nodes labeled from 0 to n - 1 and a list of undirected edges (each edge is a pair of nodes), write a function to find the number of connected components in an undirected graph.
Example 1:

0          3
|          |
1 --- 2    4
Given n = 5 and edges = [[0, 1], [1, 2], [3, 4]], return 2.

Example 2:
0           4
|           |
1 --- 2 --- 3
Given n = 5 and edges = [[0, 1], [1, 2], [2, 3], [3, 4]], return 1.
*/

class Solution {
public:
	int countComponents(int n, vector<pair<int, int>>& edges) {

		//find root for each node, if same root, link together by union find

		vector<int> root(n, 0);
		for (int i = 0; i<n; i++) {
			root[i] = i;
		}

		for (int i = 0; i<edges.size(); i++) {
			int v1 = edges[i].first;
			int v2 = edges[i].second;
			int root1 = find(root, v1);
			int root2 = find(root, v2);
			if (root1 != root2) {//union two parts into one
				root[root1] = root2;
			}

		}

		int cnt = 0;
		for (int i = 0; i<root.size(); i++) {
			if (root[i] == i)
				cnt++;
		}

		return cnt;
	}

	int find(vector<int> root, int v) {
		while (root[v] != v) {//until find root is itself, not more parent node/root.
			root[v] = root[root[v]]; //path compression, directly find the final root
			v = root[v];
		}
		return v;
	}
};

```

> DFS soltution

```CPP
int countComponents(int n, vector<vector<int>>& edges) {

    int ret =0;
    vector<vector<int>> g(n);
    //convert the edge into graph 
    for(int i=0;i<edges.size();i++){
        g[edges[i][0]].push_back(edges[i][1]);
        g[edges[i][1]].push_back(edges[i][0]);
    }
    
    vector<int> visited(n,0);
    
    for(int i=0;i<n;i++){
        if(visited[i]==0){
            visited[i] =1;
            dfs(g,visited, i);
            ret++;
        }
    }
    
    return ret;
}

void dfs(vector<vector<int>>& g, vector<int>& visited, int cur){
    for(auto j: g[cur]){
        if(visited[j]==0){
            visited[j] =1;
            dfs(g,visited, j);
        }
    }
}
```

> BFS

```CPP
int countComponents(int n, vector<vector<int>>& edges) {
    
        int ret =0;
        vector<vector<int>> g(n);
        //convert the edge into graph 
        for(int i=0;i<edges.size();i++){
            g[edges[i][0]].push_back(edges[i][1]);
            g[edges[i][1]].push_back(edges[i][0]);
        }
        
        vector<int> visited(n,0);
        queue<int> q;
        
        for (int i = 0; i < n; i++) {
            if (visited[i]) continue;
            visited[i] = 1;
            q.push(i);

            while (!q.empty()) {
                int cur = q.front(); 
                q.pop();
                for (auto node : g[cur]) {
                    if (visited[node] ==0) {
                        visited[node] = 1;
                        q.push(node);
                    }
                }
            }
            ret++;
        }
        
        return ret;
    }

```

### Number of component with some step count

#### Rotting Oranges

https://leetcode.com/problems/rotting-oranges/

In a given grid, each cell can have one of three values:

the value 0 representing an empty cell;
the value 1 representing a fresh orange;
the value 2 representing a rotten orange.
Every minute, any fresh orange that is adjacent (4-directionally) to a rotten orange becomes rotten.

Return the minimum number of minutes that must elapse until no cell has a fresh orange.  If this is impossible, return -1 instead.

 
```
Example 1:

Input: [[2,1,1],[1,1,0],[0,1,1]]
Output: 4
Example 2:

Input: [[2,1,1],[0,1,1],[1,0,1]]
Output: -1
Explanation:  The orange in the bottom left corner (row 2, column 0) is never rotten, because rotting only happens 4-directionally.
Example 3:

Input: [[0,2]]
Output: 0
Explanation:  Since there are already no fresh oranges at minute 0, the answer is just 0.
```

```CPP
int orangesRotting(vector<vector<int>>& grid) {
    int fresh=0, res=-1;
    queue<pair<int,int>> q;
    vector<vector<int>> dir={{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
    for(int i=0;i<grid.size();i++) {
        for(int j=0;j<grid[0].size();j++) {
            if(grid[i][j]==1) 
                fresh++;
            if(grid[i][j]==2) 
                q.push({i, j});
        }
    }
    while(!q.empty()) {
        res++;
        int size = q.size();
        //each layer we have some count/res
        for(int k=0;k<size;k++) {
            pair<int,int> cur=q.front();
            
            q.pop();
            for(int i=0;i<4;i++) {
                int x=cur.first+dir[i][0], y=cur.second+dir[i][1];
                if(x>=grid.size()||x<0||y>=grid[0].size()||y<0||grid[x][y]!=1) 
                    continue;
                grid[x][y]=2;
                q.push({x, y});
                fresh--;
            }
        }
    }
    if(fresh==0) 
        return max(0, res);
    return -1;
    
}
```


### Number of island

https://leetcode.com/problems/number-of-islands/

Given a 2d grid map of '1's (land) and '0's (water), count the number of islands. An island is surrounded by water and is formed by connecting adjacent lands horizontally or vertically. You may assume all four edges of the grid are all surrounded by water.

 
```
Example 1:

Input: grid = [
  ["1","1","1","1","0"],
  ["1","1","0","1","0"],
  ["1","1","0","0","0"],
  ["0","0","0","0","0"]
]
Output: 1
Example 2:

Input: grid = [
  ["1","1","0","0","0"],
  ["1","1","0","0","0"],
  ["0","0","1","0","0"],
  ["0","0","0","1","1"]
]
Output: 3
```

```CPP
//DFS, key idea is to remove 1->0 if visited
    int numIslands(vector<vector<char>>& grid) {
        if(grid.size() == 0 || grid[0].size() == 0)
            return 0;
        int ret = 0;
        for(int i = 0; i < grid.size(); ++ i)
            for(int j = 0; j < grid[0].size(); ++ j)
                if(grid[i][j] == '1'){
                    ++ ret;
                    DFS(grid, i, j);
                }
        return ret;
    }
    
    void DFS(vector<vector<char>> &grid, int x, int y){
        
        grid[x][y] = '0';
        if(x<grid.size()-1 && grid[x+1][y]=='1') DFS(grid, x+1,y);
        if(x>0 && grid[x-1][y]=='1') DFS(grid, x-1,y);
        if(y<grid[0].size()-1 && grid[x][y+1]=='1') DFS(grid, x,y+1);
        if(y>0 && grid[x][y-1]=='1') DFS(grid, x,y-1);
    }
```

### Friends Circle

https://leetcode.com/problems/friend-circles/

There are N students in a class. Some of them are friends, while some are not. Their friendship is transitive in nature. For example, if A is a direct friend of B, and B is a direct friend of C, then A is an indirect friend of C. And we defined a friend circle is a group of students who are direct or indirect friends.

Given a N*N matrix M representing the friend relationship between students in the class. If M[i][j] = 1, then the ith and jth students are direct friends with each other, otherwise not. And you have to output the total number of friend circles among all the students.
```
Example 1:
Input: 
[[1,1,0],
 [1,1,0],
 [0,0,1]]
Output: 2
Explanation:The 0th and 1st students are direct friends, so they are in a friend circle. 
The 2nd student himself is in a friend circle. So return 2.
Example 2:
Input: 
[[1,1,0],
 [1,1,1],
 [0,1,1]]
Output: 1
Explanation:The 0th and 1st students are direct friends, the 1st and 2nd students are direct friends, 
so the 0th and 2nd students are indirect friends. All of them are in the same friend circle, so return 1.
```


```CPP
//DFS
int findCircleNum(vector<vector<int>>& M) {
    //visited[i] means i-th node is visited and undergoing DFS
    vector<int> visited(len,0);
    int ret=0;
    
    for(int i=0;i<len;i++){
        //if visited[i] == 1. means it has been visited by last DFS
        if(visited[i]==0){
            dfs(M,visited,i,len);
            ret++;
        }
    }
    
    return ret;
}

void dfs(vector<vector<int>>& M, vector<int> &visited, int i, int len){
    //dfs for a particular node index i only
    for(int j=0;j<len;j++){
        if(M[i][j]==1 && visited[j]==0){
            visited[j]=1;
            dfs(M,visited,j,len);
        }
    }
}
```


```CPP
//BFS
int findCircleNum(vector<vector<int>>& M) {
        //visited[i] means i-th node is visited and undergoing DFS
        int len = M.size();
        vector<int> visited(len,0);
        int ret=0;
        queue<int> q;
        for(int i=0;i<len;i++){
            if(visited[i]==0){
                q.push(i);
                while(!q.empty()){
                    int cur = q.front();
                    visited[cur] = 1;
                    q.pop();
                    //only push those not visited, start from current index
                    for(int j=0;j<len;j++){
                        if(M[cur][j]==1 && visited[j] == 0){
                            q.push(j);
                        }
                    }
                }
                ret++;
            }
        }
        
        
        return ret;
    }

```



### Graph Valid Tree

```CPP
//https://leetcode.com/problems/graph-valid-tree/
/*
Given n nodes labeled from 0 to n - 1 and a list of undirected edges (each edge is a pair of nodes), write a function to check whether these edges make up a valid tree.

For example:

Given n = 5 and edges = [[0, 1], [0, 2], [0, 3], [1, 4]], return true.
Given n = 5 and edges = [[0, 1], [1, 2], [2, 3], [1, 3], [1, 4]], return false.
*/
class Solution {
public:
	bool validTree(int n, vector<pair<int, int>>& edges) {
		/*
		Make sure there is no cycle in the graph - this has to be a none-cyclic graph;
		Make sure every node is reached - this has to be a connected graph;

		To test cyclic, we can make an array for each node (as array index), and the array will store the parent of the node (as array index). Every time we fetch a new pair of nodes, we trace the root node (the deepest parent node) of these two nodes, if it has the same root, then is will be a cycle; otherwise, we set the parent of second node to be the first node;
		After we make sure there is node cycle in the graph, we simple test if there is enough edges to make this graph connected.
		*/
		vector<int> root(n, 0);
		for (int i = 0; i<n; i++) {
			root[i] = i;
		}
		int len = edges.size();
		for (int i = 0; i<len; i++) {
			int v1 = edges[i].first;
			int v2 = edges[i].second;
			while (root[v1] != v1) {
				root[v1] = root[root[v1]]; //search for deepest root.
				v1 = root[v1];
			}
			while (root[v2] != v2) {
				root[v2] = root[root[v2]]; //search for deepest root.
				v2 = root[v2];
			}
			if (root[v1] == root[v2])
				return false;
			root[v1] = v2;
		}

		return len == n - 1;
	}
};

```

# Topological Sort

In the field of computer science, a topological sort (sometimes abbreviated toposort[1]) or topological ordering of a directed graph is a linear ordering of its vertices such that for every directed edge uv from vertex u to vertex v, u comes before v in the ordering. A topological ordering is possible if and only if the graph has no directed cycles, that is, if it is a directed acyclic graph (DAG). Any DAG has at least one topological ordering, and algorithms are known for constructing a topological ordering of any DAG in linear time.
Given an directed graph, a topological order of the graph nodes is defined as follow:
* For each directed edge A -> B in graph, A must before B in the order list.
* The first node in the order can be any node in the graph with no nodes direct to it.
Find any topological order for the given graph.

### Detect Circle via Topo Sort

```
L = Empty list that will contain the sorted elements
S = Set of all nodes with no incoming edge

while S is non-empty do
    remove a node n from S
    add n to tail of L
    for each node m with an edge e from n to m do
        remove edge e from the graph
        if m has no other incoming edges then
            insert m into S

if graph has edges then
    return error   (graph has at least one cycle)
else 
    return L   (a topologically sorted order)
```

To better understand the above algorithm, we summarize a few points here:

* In order to find a global order, we can start from those nodes  indegree of node is zero, we then incrementally add new nodes to the global order, following the dependencies (edges).
* Once we follow an edge, we then remove it from the graph.
* With the removal of edges, there would more nodes appearing with indegree 0, in addition to the initial list in the first step.
* The algorithm would terminate when we can no longer remove edges from the graph. There are two possible outcomes:
-- If there are still some edges left in the graph, then these edges must have formed certain cycles, which is similar to the deadlock situation. It is due to these cyclic dependencies that we cannot remove them during the above processes.
-- Otherwise, i.e. we have removed all the edges from the graph, and we got ourselves a topological order of the graph.


## DFS
https://www.youtube.com/watch?v=ddTC4Zovtbc

https://www.cs.usfca.edu/~galles/visualization/TopoSortDFS.html

The idea is to explore nodes and its neighbors recursively, using a set to check whether node has been visited

```CPP
/**
* Definition for Directed graph.
* struct DirectedGraphNode {
*     int label;
*     vector<DirectedGraphNode *> neighbors;
*     DirectedGraphNode(int x) : label(x) {};
* };
*/
class Solution {
public:
	/**
	* @param graph: A list of Directed graph node
	* @return: Any topological order for the given graph.
	*/
	vector<DirectedGraphNode*> topSort(vector<DirectedGraphNode*> graph) {
		// write your code here
		set<DirectedGraphNode*> visit;
		vector<DirectedGraphNode*> ret;
		for (int i = 0; i<graph.size(); i++) {
			if (visit.find(graph[i]) == visit.end()) {
				Toposort_DFS(visit, graph[i], ret, graph);
			}
		}
		std::reverse(ret.begin(), ret.end());
		return ret;
	}

	void Toposort_DFS(set<DirectedGraphNode*> &visit, DirectedGraphNode* node, vector<DirectedGraphNode*> &ret, vector<DirectedGraphNode*> graph) {
		visit.insert(node);
		for (int i = 0; i<node->neighbors.size(); i++) {
			if (visit.find(node->neighbors[i]) == visit.end()) {
				Toposort_DFS(visit, node->neighbors[i], ret, graph);
			}
		}
		//go to end, no direct child node, sink
		ret.push_back(node);
	}
};

```



## BFS
The idea is come from wiki: https://en.wikipedia.org/wiki/Topological_sorting#Algorithms
Two key point of Topological sorting using BFS is:
1.	Build the map and relationship of each node (incoming and outgoing edges of each node).
2.	BFS uses the indegrees of each node. We will first try to find a node with 0 indegree. If we fail to do so, there must be a cycle in the graph and we return false. Otherwise we have found one. We set its indegree to be -1 to prevent from visiting it again and reduce the indegrees of all its neighbors by 1. This process will be repeated for n (number of nodes) times. If we have not returned false, we will return true.
Each time remove a node that with no incoming edges and at same time remove this node's outgoing edges.

```CPP
vector<DirectedGraphNode*> topSort(vector<DirectedGraphNode*> graph) {
        vector<DirectedGraphNode*> ret;
        map<DirectedGraphNode*,int> indegree;
        queue<DirectedGraphNode*> q;
        //generate map
        for(int i=0;i<graph.size();i++){
            for(int j=0;j<graph[i]->neighbors.size();j++){
                if(indegree.find(graph[i]->neighbors[j])==indegree.end())
                    indegree[graph[i]->neighbors[j]] = 1;
                else
                    indegree[graph[i]->neighbors[j]] ++;
            }
        }

        //put all nodes with no in-degree into queue and ret
        for (int i = 0; i < graph.size(); ++i) {
            if (indegree[graph[i]] == 0) {
                ret.push_back(graph[i]);
                q.push(graph[i]);
            }
        }

        while (!q.empty()) {
            DirectedGraphNode * cur = q.front();
            q.pop();
            for(int j = 0; j < cur->neighbors.size(); ++j) {
                indegree[cur->neighbors[j]]--;
                if (indegree[cur->neighbors[j]] == 0) {
                    ret.push_back(cur->neighbors[j]);
                    q.push(cur->neighbors[j]);
                }
            }
        }

        return ret;
    }

```



## Example

### Sequence Reconstruction

https://leetcode.com/problems/sequence-reconstruction/

Check whether the original sequence org can be uniquely reconstructed from the sequences in seqs. The org sequence is a permutation of the integers from 1 to n, with 1 ≤ n ≤ 104. Reconstruction means building a shortest common supersequence of the sequences in seqs (i.e., a shortest sequence so that all sequences in seqs are subsequences of it). Determine whether there is only one sequence that can be reconstructed from seqs and it is the org sequence.

 
```
Example 1:

Input: org = [1,2,3], seqs = [[1,2],[1,3]]
Output: false
Explanation: [1,2,3] is not the only one sequence that can be reconstructed, because [1,3,2] is also a valid sequence that can be reconstructed.
Example 2:

Input: org = [1,2,3], seqs = [[1,2]]
Output: false
Explanation: The reconstructed sequence can only be [1,2].
Example 3:

Input: org = [1,2,3], seqs = [[1,2],[1,3],[2,3]]
Output: true
Explanation: The sequences [1,2], [1,3], and [2,3] can uniquely reconstruct the original sequence [1,2,3].
Example 4:

Input: org = [4,1,5,2,6,3], seqs = [[5,2,6,3],[4,1,5,2]]
Output: true
```


```CPP
    bool sequenceReconstruction(vector<int>& org, vector<vector<int>>& seqs) {
        if (seqs.size() == 0) return false;
        int n = org.size(), count = 0;
        unordered_map<int, unordered_set<int>> graph;   // record parents
        vector<int> degree(n+1, 0); // record out degree
        for (auto s : seqs) {   // build graph
            for (int i = s.size()-1; i >= 0; --i) {
                if (s[i] > n or s[i] < 0) 
                    return false; // in case number in seqs is out of range 1-n
                if (i > 0 and graph[s[i]].find(s[i-1])==graph[s[i]].end()) {
                    graph[s[i]].insert(s[i-1]);
                    if (degree[s[i-1]]++ == 0) count ++;
                }
            }
        }
        if (count != n-1) 
            return false; // all nodes should have degree larger than 0 except the last one
        for (int i = n-1; i >= 0; --i) {    // topological sort
            if (degree[org[i]] > 0) return false;   // the last node should have 0 degree
            for (auto p : graph[org[i]]) 
                if (--degree[p] == 0 and p != org[i-1]) // found a node that is not supposed to have 0 degree
                    return false;
        }
        return true;        
    }
```

### Course Schedule

https://leetcode.com/problems/course-schedule/

There are a total of numCourses courses you have to take, labeled from 0 to numCourses-1.

Some courses may have prerequisites, for example to take course 0 you have to first take course 1, which is expressed as a pair: [0,1]

Given the total number of courses and a list of prerequisite pairs, is it possible for you to finish all courses?

 
```
Example 1:

Input: numCourses = 2, prerequisites = [[1,0]]
Output: true
Explanation: There are a total of 2 courses to take. 
             To take course 1 you should have finished course 0. So it is possible.
Example 2:

Input: numCourses = 2, prerequisites = [[1,0],[0,1]]
Output: false
Explanation: There are a total of 2 courses to take. 
             To take course 1 you should have finished course 0, and to take course 0 you should
             also have finished course 1. So it is impossible.
```

```CPP
    bool sequenceReconstruction(vector<int>& org, vector<vector<int>>& seqs) {
        if (seqs.size() == 0) return false;
        int n = org.size(), count = 0;
        unordered_map<int, unordered_set<int>> graph;   // record parents
        vector<int> degree(n+1, 0); // record out degree
        for (auto s : seqs) {   // build graph
            for (int i = s.size()-1; i >= 0; --i) {
                if (s[i] > n or s[i] < 0) 
                    return false; // in case number in seqs is out of range 1-n
                if (i > 0 and graph[s[i]].find(s[i-1])==graph[s[i]].end()) {
                    graph[s[i]].insert(s[i-1]);
                    if (degree[s[i-1]]++ == 0) count ++;
                }
            }
        }
        if (count != n-1) 
            return false; // all nodes should have degree larger than 0 except the last one
        for (int i = n-1; i >= 0; --i) {    // topological sort
            if (degree[org[i]] > 0) return false;   // the last node should have 0 degree
            for (auto p : graph[org[i]]) 
                if (--degree[p] == 0 and p != org[i-1]) // found a node that is not supposed to have 0 degree
                    return false;
        }
        return true;        
    }
```



