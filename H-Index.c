//https://leetcode.com/problems/h-index/
//https://leetcode.com/problems/h-index-ii/

/*
Given an array of citations (each citation is a non-negative integer) of a researcher, 
write a function to compute the researcher's h-index.

According to the definition of h-index on Wikipedia: "A scientist has index h if h of his/her N papers have at least h citations each, 
and the other N − h papers have no more than h citations each."
For example, given citations = [3, 0, 6, 1, 5], 
which means the researcher has 5 papers in total and each of them had received 3, 0, 6, 1, 5 citations respectively. Since the 
researcher has 3 papers with at least 3 citations each and the remaining two with no more than 3 citations each, his h-index is 3.
Note: If there are several possible values for h, the maximum one is taken as the h-index.
*/
class Solution {
public:
    int hIndex(vector<int>& citations) {
        int ret = 0;
        std::sort(citations.begin(),citations.end());
        for(int i=citations.size()-1;i>=0;i--){
            if(citations[i]>=citations.size()-i)
                ret = citations.size()-i>ret?citations.size()-i:ret;
                if(citations[i]<citations.size()-i)
                    break;
        }
            
        
        return ret;
    }
};

//Follow up, if it is already sorted, can we make it O(log(n))
class Solution {
public:
    int hIndex(vector<int>& citations) {
        //if sorted, binary search
        int ret=0;
        int start=0;
        int len = citations.size();
        int end=len-1;

        while(start<=end){
            int mid=(start+end)/2;
            if(citations[mid]>=len-mid){
                ret = len-mid;
                end = mid-1;
            }else{
                start=mid+1;
            }

        }
        return ret;
    }
};

