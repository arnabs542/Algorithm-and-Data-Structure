//https://leetcode.com/problems/insert-delete-getrandom-o1-duplicates-allowed/
/*
Design a data structure that supports all following operations in average O(1) time.
Note: Duplicate elements are allowed.

    insert(val): Inserts an item val to the collection.
    remove(val): Removes an item val from the collection if present.
    getRandom: Returns a random element from current collection of elements. The probability of each element being returned is linearly related to the number of same value the collection contains.

Example:

// Init an empty collection.
RandomizedCollection collection = new RandomizedCollection();
// Inserts 1 to the collection. Returns true as the collection did not contain 1.
collection.insert(1);
// Inserts another 1 to the collection. Returns false as the collection contained 1. Collection now contains [1,1].
collection.insert(1);
// Inserts 2 to the collection, returns true. Collection now contains [1,1,2].
collection.insert(2);
// getRandom should return 1 with the probability 2/3, and returns 2 with the probability 1/3.
collection.getRandom();
// Removes 1 from the collection, returns true. Collection now contains [1,2].
collection.remove(1);
// getRandom should return 1 and 2 both equally likely.
collection.getRandom();
*/

class RandomizedCollection {
private:
  vector<int> num;
  map<int,queue<int>> m; //map of val->idx in num as queue 

public:
  /** Initialize your data structure here. */
  RandomizedCollection() {
      
  }
  
  /** Inserts a value to the collection. Returns true if the collection did not already contain the specified element. */
  bool insert(int val) {
      num.push_back(val);
      m[val].push(num.size()-1);  //map to each val -> indx;
      if(m.find(val)==m.end()){
          return true;
      }
      return false;
  }
  
  /** Removes a value from the collection. Returns true if the collection contained the specified element. */
  bool remove(int val) {
      if(m.find(val)!=m.end()){
          
          queue<int> index = m[val]; //check all index of removed val.
          int last = num.back();
          num[index.front()] = last;
          m[last].push(index.front());  //add new index for last
          m[last].pop(); //remove old index for last;
          m[val].pop();   //remove old index for val
          num.pop_back();
          if(m[val].empty())
              m.erase(val);
          return true;
      }
      return false;
  }
  
  /** Get a random element from the collection. */
  int getRandom() {
      if(num.size()!=0){
          int pos = rand()%num.size();
          return num[pos];
      }else{
          return 0;
      }
  }
};
