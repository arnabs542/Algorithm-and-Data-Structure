//https://leetcode.com/problems/design-phone-directory/
/*
Design a Phone Directory which supports the following operations:

    get: Provide a number which is not assigned to anyone.
    check: Check if a number is available or not.
    release: Recycle or release a number.

Example:

// Init a phone directory containing a total of 3 numbers: 0, 1, and 2.
PhoneDirectory directory = new PhoneDirectory(3);
// It can return any available phone number. Here we assume it returns 0.
directory.get();
// Assume it returns 1.
directory.get();
// The number 2 is available, so return true.
directory.check(2);
// It returns 2, the only number that is left.
directory.get();
// The number 2 is no longer available, so return false.
directory.check(2);
// Release number 2 back to the pool.
directory.release(2);
// Number 2 is available again, return true.
directory.check(2);
*/

//easy way is to use two sets, but time cost is high

//use vector instead.
class PhoneDirectory {
public:
    /** Initialize your data structure here
        @param maxNumbers - The maximum numbers that can be stored in the phone directory. */
    vector<int> unused;
    vector<int>available;
    int index;
    PhoneDirectory(int maxNumbers) {
        available.resize(maxNumbers);
        unused.resize(maxNumbers,1);
        for(int i=0;i<maxNumbers;i++){
            available[i] = i;
        }
        index = maxNumbers-1;
    }
    
    /** Provide a number which is not assigned to anyone.
        @return - Return an available number. Return -1 if none is available. */
    int get() {
        if(index<0)
            return -1;
        else{
            //use index to simulate last available number. when one is used, index --.
            int num = available[index--];  
            unused[num] = 0;
            return num;
        }

    }
    
    /** Check if a number is available or not. */
    bool check(int number) {
        return unused[number];

    }
    
    /** Recycle or release a number. */
    void release(int number) {
        if(unused[number]==0){
            //need to ++ first since last index is -- in get 
            available[++index] = number;
            unused[number] =1;
        }        
    }
};
