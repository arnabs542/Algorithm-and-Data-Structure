//https://leetcode.com/problems/find-minimum-in-rotated-sorted-array/
/*
Suppose a sorted array is rotated at some pivot unknown to you beforehand.
(i.e., 0 1 2 4 5 6 7 might become 4 5 6 7 0 1 2).
Find the minimum element.
*/

//it is clearly a binary search
class Solution {
public:
    int findMin(vector<int> &num) {
        int begin = 0;
        int len = num.size();
        int end = len-1;
        int ret = INT_MAX;
        
        while(begin<=end){
            int mid = begin + (end-begin)/2;
            if(num[mid]>num[end]){
                begin = mid+1;
                ret = num[end]<ret?num[end]:ret;
            }else if(num[mid]<num[end]){
                end = mid-1;
                ret = num[mid]<ret?num[mid]:ret;
            }else{
                ret = num[mid]<ret?num[mid]:ret;
                break;
            }
        }
        
        return ret;
    }
};

//follow up, what if there could be equal.
//https://leetcode.com/problems/find-minimum-in-rotated-sorted-array-ii/
class Solution {
public:
    int findMin(vector<int> &num) {

        int begin = 0;
        int end = num.size()-1;
        int ret = num[0];
        
        while(begin<=end){
            
            int mid = begin + (end-begin)/2;
            if(begin < mid && mid < end && num[begin] == num[mid] && num[end] == num[mid]){
                begin++;
                end--;
            }else if(num[mid]<=num[end]){
                end = mid-1;
                ret = num[mid]<ret?num[mid]:ret;
            }else if(num[mid]>num[end]){
                begin = mid+1;
                ret = num[end]<ret?num[end]:ret;
            }
        }
            
        return ret;
    }
};
