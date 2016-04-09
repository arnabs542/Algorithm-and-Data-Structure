//http://www.lintcode.com/en/problem/topological-sorting/
//DFS
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
        for(int i=0;i<graph.size();i++){
            if(visit.find(graph[i])==visit.end()){
                Toposort_DFS(visit,graph[i],ret,graph);
            }
        }
        std::reverse(ret.begin(),ret.end());
        return ret;
    }
    
    void Toposort_DFS(set<DirectedGraphNode*> &visit,DirectedGraphNode* node, vector<DirectedGraphNode*> &ret,vector<DirectedGraphNode*> graph){
        visit.insert(node);
        for(int i=0;i<node->neighbors.size();i++){
            if(visit.find(node->neighbors[i])==visit.end()){
                Toposort_DFS(visit,node->neighbors[i],ret,graph);
            }
        }
        //go to end, no direct child node, sink
        ret.push_back(node);
    }
};
