//https://leetcode.com/problems/line-reflection/
/*
Given n points on a 2D plane, find if there is such a line parallel to y-axis that reflect the given points.

Example 1:
Given points = [[1,1],[-1,1]], return true.

Example 2:
Given points = [[1,1],[-1,-1]], return false.

Follow up:
Could you do better than O(n2)? 
*/
class Solution {
public:
  bool isReflected(vector<pair<int, int>>& points) {
      //two conditions to meet the reflect
      //1: points with same y axis have a reflect line
      //2: points with different y axis has same reflect line
      
      map<int,pair<int,int>> m_edge; //key is y axis, val is min/max of x in that y axis
      map<int,set<int>> m;  //key is y axis, val is all x axises in set(so to remove duplicate ones)
      for(int i=0;i<points.size();i++){
          if(m.find(points[i].second)==m.end()){
              m[points[i].second].insert(points[i].first);
              m_edge[points[i].second].first = points[i].first;
              m_edge[points[i].second].second = points[i].first;
          }else{
              //important to filter out duplicate points
              m[points[i].second].insert(points[i].first);
              //update min
              if(points[i].first<m_edge[points[i].second].first){
                  m_edge[points[i].second].first = points[i].first;
              }
              //update max
              if(points[i].first>m_edge[points[i].second].second){
                  m_edge[points[i].second].second = points[i].first;
              }
          }
      }
      double middle = 0;
      std::map<int,pair<int,int>>::iterator it = m_edge.begin();
      middle = (it->second.first + it->second.second)/2.0;
      
      for (auto n:m){
          set<int> cur = n.second;
          int cur_middle = 0;
          
          for(auto i:cur){
              cur_middle += i;
          }
          if((double)cur_middle/cur.size()!=middle)
              return false;
      }
      
      return true;

  }
};
