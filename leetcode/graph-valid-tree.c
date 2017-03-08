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
        vector<int> root(n,0);
        for(int i=0;i<n;i++){
            root[i] = i;
        }
        int len = edges.size();
        for(int i=0;i<len;i++){
            int v1 = edges[i].first;
            int v2 = edges[i].second;
            while(root[v1]!=v1){
                root[v1] = root[root[v1]]; //search for deepest root.
                v1 = root[v1];
            }
            while(root[v2]!=v2){
                root[v2] = root[root[v2]]; //search for deepest root.
                v2 = root[v2];
            }
            if(root[v1]==root[v2])
                return false;
            root[v1] = v2;
        }
        
        return len==n-1;
    }
};
