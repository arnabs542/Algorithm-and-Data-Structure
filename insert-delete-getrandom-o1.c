//https://leetcode.com/problems/insert-delete-getrandom-o1/
/*
Design a data structure that supports all following operations in average O(1) time.

    insert(val): Inserts an item val to the set if not already present.
    remove(val): Removes an item val from the set if present.
    getRandom: Returns a random element from current set of elements. Each element must have the same probability of being returned.

Example:

// Init an empty set.
RandomizedSet randomSet = new RandomizedSet();
// Inserts 1 to the set. Returns true as 1 was inserted successfully.
randomSet.insert(1);
// Returns false as 2 does not exist in the set.
randomSet.remove(2);
// Inserts 2 to the set, returns true. Set now contains [1,2].
randomSet.insert(2);
// getRandom should return either 1 or 2 randomly.
randomSet.getRandom();
// Removes 1 from the set, returns true. Set now contains [2].
randomSet.remove(1);
// 2 was already in the set, so return false.
randomSet.insert(2);
// Since 1 is the only number in the set, getRandom always return 1.
randomSet.getRandom();
*/

class RandomizedSet {
private:
  vector<int> num;
  //int total;
  map<int,int> m; //key is val, val is index in vector<int> num
public:
  /** Initialize your data structure here. */
  RandomizedSet() {
      
  }
  
  /** Inserts a value to the set. Returns true if the set did not already contain the specified element. */
  bool insert(int val) {
      if(m.find(val)==m.end()){
          num.push_back(val);
          m[val] = num.size()-1;
          return true;
      }
      return false;
  }
  
  /** Removes a value from the set. Returns true if the set contained the specified element. */
  bool remove(int val) {
      if(m.find(val)!=m.end()){
          int last = num.back();
          int idx = m[val];
          m[last] = m[val];  //move map's map: last's position to be position of val to be removed.
          num[idx] = last; //move the val to replace value to be removed in vector.
          num.pop_back();
          m.erase(val);
          return true;
      }
      return false;
  }
  
  /** Get a random element from the set. */
  int getRandom() {
      int idx = rand()%num.size();
      return num[idx];
  }
};
