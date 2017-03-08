//https://leetcode.com/problems/gas-station/
/*
 There are N gas stations along a circular route, where the amount of gas at station i is gas[i].
You have a car with an unlimited gas tank and it costs cost[i] of gas to travel from station i to its next station (i+1). 
You begin the journey with an empty tank at one of the gas stations.
Return the starting gas station's index if you can travel around the circuit once, otherwise return -1. 
*/

//Greedy
//brute force, starting from each station and check ahead to see if it reaches back to itself
//TLE in leetcode
class Solution {
public:
    int canCompleteCircuit(vector<int>& gas, vector<int>& cost) {
        int ret = -1;

        for(int i=0;i<gas.size();i++){
            int sum = 0;
            bool found = true;
            for(int j=i;j<cost.size()+i;j++){//start from gas station i, notice it is circular 
                int index = j%cost.size();
                sum += gas[index]-cost[index];
                if(sum<0){
                    found = false;
                    break;  //break the inner loop
                }
                
            }
            if(found){
                ret = i;
                break;  //found it, break outside loop
            }
        }
        
        return ret;
    }
};

//O(n^2)
/*
if we can not reach from A to B, then we do not need to check any new starting point in between A->B
*/
class Solution {
public:
    int canCompleteCircuit(vector<int>& gas, vector<int>& cost) {
        int ret = -1;

        int k = 0;
        int i =0;
        while(i<gas.size()){
            int sum = 0;
            bool found = true;
            //start from gas station i, notice it is circular so until end and back to 0-> i-1
            for(int j=i;j<cost.size()+i;j++){
                int index = j%cost.size();
                sum += gas[index]-cost[index];
                if(sum<0){
                    k = j + 1;
                    found = false;
                    break;  //break the inner loop
                }
                
            }
            if(found){
                ret = i;
                break;  //found it, break outside loop
            }
            i = k;
        }
        
        return ret;
    }
};
//O(n)
/*
O(n) solution, assume first check adjacent two stations, 0 and size-1;
if we can go from start to end, then we extend end to next and check
if we can not go from start to end, then we know starting from current start lack of gas, 
we need to go back to former one to see if former gas station can give us more remaning gas
*/

class Solution {
public:
    int canCompleteCircuit(vector<int>& gas, vector<int>& cost) {

        int start = gas.size()-1;
        int end = 0;
        int sum = gas[start]-cost[start]; //starting point is from last to first station(in loop)
        while(start>end){
            if(sum<0){
                start--;
                sum += gas[start]-cost[start];
            }else{
                //can drive to current end, then extend end to next
                sum+=gas[end]-cost[end];
                end++;
            }
        }
        
        if(sum>=0)
            return end;
        else
            return -1;

    }
};
