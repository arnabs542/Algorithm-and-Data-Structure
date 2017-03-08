//https://leetcode.com/problems/binary-watch/
/*A binary watch has 4 LEDs on the top which represent the hours (0-11), and the 6 LEDs on the bottom represent the minutes (0-59).
Each LED represents a zero or one, with the least significant bit on the right.
For example, the above binary watch reads "3:25".
Given a non-negative integer n which represents the number of LEDs that are currently on, return all possible times the watch could represent.

Example:
Input: n = 1
Return: ["1:00", "2:00", "4:00", "8:00", "0:01", "0:02", "0:04", "0:08", "0:16", "0:32"]
*/

class Solution {
public:
    vector<string> readBinaryWatch(int num) {
        vector<string> ret;
        for(int h=0;h<12;h++){
            for(int m=0;m<60;m++){
                int cur = (h<<6|m);
                if(numofbits(cur)==num){
                    string times = to_string(h) + (m<10?":0":":") + to_string(m);
                    ret.push_back(times);
                }
            }
        }
        return ret;
    }
    
    int numofbits(int x){
    	int count = 0;
    	if(x == 0) 
    	    return 0;
    
    	do{
    		count++;
    	}while(x&=(x-1));
    	
    	return count;
    }
};
