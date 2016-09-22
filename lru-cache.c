//https://leetcode.com/problems/lru-cache/
/*
Design and implement a data structure for Least Recently Used (LRU) cache. It should support the following operations: get and set.

get(key) - Get the value (will always be positive) of the key if the key exists in the cache, otherwise return -1.
set(key, value) - Set or insert the value if the key is not already present. When the cache reached its capacity, it should invalidate the least recently used item before inserting a new item. 
*/

class LRUCache{
    /*
    Linked list to update cache time. put the hit item into front
    hash table to record key, and value is linked list position
    */
    
private:    
    int len = 0;
    typedef list<pair<int,int>> pList; //pair is key value
    pList l;
    unordered_map<int,pList::iterator> m;  //key value 
    //update function to update the list, 
    void update(pList::iterator it){
        int key = it->first;
        int val = it->second;
        l.erase(it);
        l.push_front(make_pair(key,val));
        m[key] = l.begin();
    }
public:
    LRUCache(int capacity) {
        len = capacity;
    }
    
    int get(int key) {
        if(m.find(key)==m.end())
            return -1;
        update(m[key]);
        return m[key]->second;
    }
    
    void set(int key, int value) {
        if(m.find(key)!=m.end()){
            update(m[key]);
            m[key]->second = value;
        }else{
            l.push_front(make_pair(key,value));
            m[key] = l.begin();
            if(m.size()>len){
                m.erase(l.back().first);
                l.pop_back();
            }
        }
    }
};
