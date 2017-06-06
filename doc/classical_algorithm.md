## KMP

Used to check whether str2 is a substring of str1

Idea is to get the next array, next array is largest number i in substring m, where prefix(0->i-1) and postfix(m-i,m) is same


```CPP
//get start index of string m inside string s, if not found, return -1
int getIndexOf(String s, String m) {
  if (s == null || m == null || m.size() < 1 || s.size() < m.size()) {
    return -1;
  }
  int si = 0;
  int mi = 0;
  vector<int> next = getNextArray(ms);
  while (si < s.size() && mi < m.size()) {
    if (s[si] == m[mi]) {
      si++;
      mi++;
    } else if (next[mi] == -1) {
      si++;
    } else {
      mi = next[mi];
    }
  }
  return mi == ms.size() ? si - mi : -1;
}

vector<int> getNextArray(vector<int> ms) {
  vector<int> next;
  if (ms.size() == 1) {
    next.push_back(-1);
    return next;
  }
  next[0] = -1;
  next[1] = 0;
  int pos = 2;
  int cn = 0;
  while (pos < next.size()) {
    if (ms[pos - 1] == ms[cn]) {
      next[pos++] = ++cn;
    } else if (cn > 0) {
      cn = next[cn];
    } else {
      next[pos++] = 0;
    }
  }
  return next;
}


```

## BFPRT
In an unordered array, find the k'th smallest or largest value

first method is recursive:
1. select a pivot number
2. partition the collection into <,=,> 3 collections compared with pivot
3. check k's smallest location, then recursive

The issue is pivot choice could be random and worst case is O(N^2)




## Check if one string is Rotation of another string

the easy way is to append the s1+s1, and check whether s2 is substring of s1.

How do we achieve O(N). s1+s1 exhaustive list all substring



## reverse string


## Implement a basic calculator to evaluate a simple expression string.
https://leetcode.com/problems/basic-calculator/#/description
Implement a basic calculator to evaluate a simple expression string.

The expression string may contain open ( and closing parentheses ), the plus + or minus sign -, non-negative integers and empty


```CPP
int calculate(string s) {
  int len = s.size();
  int sign = 1;
  int ret = 0;
  int num = 0;
  stack<int> nums,ops;
  for(int i=0;i<len;i++){
      if(isdigit(s[i])){
        num = num*10+(s[i]-'0');
      }else{
        //not number anymore, so we would need to get the current calculation num and accumulated ret
        ret+=sign*num;
        num = 0;
        if(s[i]=='+') sign = 1;
        if(s[i]=='-') sign = -1;
        if(s[i]=='('){
            nums.push(ret);  //cache the results before bracket
            ops.push(sign);  //cache the sign before bracket
            ret = 0;
            sign = 1;
        }
        if (s[i] == ')' && ops.size()) {
            ret = ops.top() * ret + nums.top(); //finish the calculation of current bracket, so get cached
            ops.pop();
            nums.pop();
        }
      }
  }
  ret += sign * num;
  return ret;
}

```


## Longest Substring Without Repeating Characters
https://leetcode.com/problems/longest-substring-without-repeating-characters/#/description

> substring problems: (if ending at certain position. sub problem:)

In this problem, it is longest substring without duplicate ending at i

```CPP
//method 1: use a map to record position
int lengthOfLongestSubstring(string s) {
    int start = 0;
    int end = 0;
    int counter = 0; //how many char has more than once
    vector<int> map(128,0);
    int ret = 0;
    while(end<s.size()){
        //for unique char
        if(map[s[end]]==1){
            counter++;
        }
        map[s[end]]++;
        end++;
        //not unique so counter>0
        while(counter>0){
            if(--map[s[start]]==1){
                counter--;
            }
            start++;
        }
        ret = max(ret,end-start);
    }
    return ret;
}

//Method 2: DP
//dp[i] = longest substring ending at position i
//pos[i] is i'th char last occur position

int lengthOfLongestSubstring(string s) {
    int ret = 0;
    int len = s.size();
    map<char,int>pos; //each char's last occur position
    vector<int> dp(len,1); //lengthOfLongestSubstring at position i;

    for(int i=0;i<len;i++){
        int last;
        if(pos.find(s[i])!=pos.end())
            last= pos[s[i]]; //last occur position of s[i]
        else
            last = -1;//never occur
        if(i>0){
            dp[i] = i-dp[i-1]>last?dp[i-1]+1:i-last;  
        }
        //update position
        pos[s[i]] = i;
        ret = max(ret,dp[i]);
    }

    return ret;
}

```

## Minimum windows substring
https://leetcode.com/problems/minimum-window-substring/#/description
Given a string S and a string T, find the minimum window in S which will contain all the characters in T in complexity O(n).

For example,
S = "ADOBECODEBANC"
T = "ABC"
Minimum window is "BANC".

```CPP
class Solution {
public:
  string minWindow(string s, string t) {
      string ret="";
      int start = 0;
      int end = 0;
      int d = INT_MAX;  //length of window size
      int head = 0; //start of sub string
      vector<int> m(128,0);

      for(int i=0;i<t.size();i++){
          m[t[i]]++;
      }
      int counter = t.size();    
      while(end<s.size()){
          if(m[s[end]]-->0)  //find it is in t
              counter--;
          end++;
          //found all in t,
          while(counter==0){
             if(end-start<d){
                 d = end-start;
                 head = start;
             }
             //we move start pointer to try to find another instance, we need to add back the hash table and counter.
             if(m[s[start]]++==0)
                  counter++;
             start++;
          }
      }

      return d==INT_MAX?"":s.substr(head,d);

  }
};
```

## Longest substring length to make sure whole string is sorted
https://leetcode.com/problems/shortest-unsorted-continuous-subarray/#/description

[1,2,3,6,4,5,7], need to sort[6,4,5] to ensure sorted

> Common techniques: Pre process the array


```CPP
//O(n) in time, O(1) extra memory
//from left->right, record max. from right->left, record min
/*
[1,5,3,4,2,6,7]
left->right: [1,5,R,R,R,6,7], right value which is smaller than max is 2
right->left:[1,L,L,L,L,2,6,7], left value which is larger than min is 5

re sort L->R
*/

int findUnsortedSubarray(vector<int>& nums) {
    int len = nums.size();
    if (len==0 || len == 1) {
        return 0;
    }
    //from right to left, record value not descending. find left most
    int min_v = nums[len - 1];
    int l = -1;
    for (int i = len - 2; i >=0; i--) {
        if (nums[i] > min_v) {
          l = i;
        } else {
          min_v = min(min_v, nums[i]);
        }
    }
    if (l == -1) {
        return 0;
    }
    //from left to rightm record value not ascending, find right most
    int max_v = nums[0];
    int r = -1;
    for (int i = 1; i <len; i++) {
        if (nums[i] < max_v) {
          r = i;
        } else {
          max_v = max(max_v, nums[i]);
        }
    }
    return r - l + 1;        
}

```

## Half Majority
https://leetcode.com/problems/majority-element/#/description
Given an array of size n, find the majority element. The majority element is the element that appears more than ⌊ n/2 ⌋ times.

```CPP
int majorityElement(vector<int>& nums) {
  int cand = 0;
  int times = 0;
  int len = nums.size();
  for (int i = 0; i < len; i++) {
    if (times == 0) {
      cand = nums[i];
      times = 1;
    } else if (nums[i] == cand) {
      times++;
    } else {
      times--;
    }
  }
  times = 0;
  for (int i = 0; i < len; i++) {
    if (nums[i] == cand) {
      times++;
    }
  }
  if (times > len / 2)
      return cand;
}

```

Extend. [K/N], then we just need to prepare K candidates


## Search a 2D matrix
https://leetcode.com/problems/search-a-2d-matrix-ii/#/description
Write an efficient algorithm that searches for a value in an m x n matrix. This matrix has the following properties:

Integers in each row are sorted in ascending from left to right.
Integers in each column are sorted in ascending from top to bottom.

```CPP
bool searchMatrix(vector<vector<int>>& matrix, int target) {
    int row = matrix.size();
    if(row==0) return false;
    int col = matrix[0].size();

    int x = 0;
    int y = col-1;
    while(x<row && y>=0){
        if(matrix[x][y]>target){
            y = y-1;
        }else if(matrix[x][y]<target){
            x = x + 1;
        }else{
            return true;
        }

    }
    return false;
}

```

## Sub Array problem
> Common techniques
* two pointer problem to get these longest/smallest problem
* preprocess to get the sum of array
* Hash table to record value, index/occur number

> __*Tips*__:
  * process before record to hash table, otherwise may over calculate
  * insert special case for hash set/map, like index -1, value 0. etc, so sum calculation including sum from beging to current or sum of current item


### Two sum
https://leetcode.com/problems/two-sum/#/description
Given an array of integers, return indices of the two numbers such that they add up to a specific target.

You may assume that each input would have exactly one solution, and you may not use the same element twice.

```CPP
vector<int> twoSum(vector<int>& nums, int target) {
    //O(nlog(n)) is easy, sort and use pointer head and tail
    //O(n)
    int len = nums.size();
    vector<int> ret;
    unordered_map<int,int> m; //key is val, val is index
    for(int i=0;i<len;i++){
        if(m.find(target-nums[i])!=m.end()){
            ret.push_back(i);
            ret.push_back(m[target-nums[i]]);
            return ret;
        }
        m[nums[i]] = i;    
    }
}
```



### Longest Sum SubArray Length: Subarray sum equal to target

```CPP
int LongestSumSubArrayLength(vector<int> nums, int k){
  int len = nums.size();
  int l = 0; //left index
  int r = 0;//right index
  int sum=0;
  int ret = 0;
  while(r<len){
    sum+=nums[r];
    if(sum==k){
      ret = max(r-l+1,ret);
      sum -=nums[l++];
    }else if(sum<k){
      r++;
    }else{
      sum-=nums[l++];
    }
  }

  return ret;

}

```

### Follow up
https://leetcode.com/problems/continuous-subarray-sum/#/description

Given a list of non-negative numbers and a target integer k, write a function to check if the array has a continuous subarray of size at least 2 that sums up to the multiple of k, that is, sums up to n*k where n is also an integer.

```CPP
bool checkSubarraySum(vector<int>& nums, int k) {
    //easy way is O(N^2)
    //proprocess. first get a sum array, then use hash map to
    int len = nums.size();
    int sum = 0;
    unordered_map<int,int> m; //key is sum, val is index
    m[0] = -1;
    for(int i=0;i<len;i++){
        sum += nums[i];
        if(k!=0)
            sum = sum%k;
        if(m.find(sum)!=m.end()){
            if(i-m[sum]>1)
                return true;
        }else{
            m[sum]=i;
        }
    }
    return false;
}


//Or we can use select    bool checkSubarraySum(vector<int>& nums, int k) {
bool checkSubarraySum(vector<int>& nums, int k) {
    int n = nums.size(), sum = 0, pre = 0;
    unordered_set<int> modk;
    for (int i = 0; i < n; ++i) {
        sum += nums[i];
        int mod = k == 0 ? sum : sum % k;
        if (modk.count(mod)) return true;
        modk.insert(pre);
        pre = mod;
    }
    return false;

}
```

### Subarray sum
https://leetcode.com/problems/subarray-sum-equals-k/#/description
Given an array of integers and an integer k, you need to find the total number of continuous subarrays whose sum equals to k.

```CPP
int subarraySum(vector<int>& nums, int k) {
    //notice if the array is all positive, it is different
    //easy way is to do O(N^2), calculate all subarry starting from 0->len-1, to end
    //if we want to do O(N), need a map to record
    int len = nums.size();
    int sum = 0;
    int ret = 0;
    map<int,int> m; //key is sum value, val is how many times it appears
    m[0] = 1;
    for(int i=0;i<len;i++){
        sum+=nums[i];
        if(m.find(sum-k)!=m.end())
            ret+=m[sum-k];
        m[sum]++;
    }
    return ret;    
}

```

### Max subarray sum
https://leetcode.com/problems/maximum-subarray/
Find the contiguous subarray within an array (containing at least one number) which has the largest sum.
For example, given the array [-2,1,-3,4,-1,2,1,-5,4],
the contiguous subarray [4,-1,2,1] has the largest sum = 6.
```CPP
int maxSubArray(vector<int>& nums) {
    int len = nums.size();
    int ret = INT_MIN;
    int sum = 0;
    for(int i=0;i<len;i++){
        sum+=nums[i];
        ret = max(ret,sum);
        //if sum<0. subarray should start from next item
        if(sum<0)
            sum = 0;
    }
    return ret;
}
```
### Count of range sum
https://leetcode.com/problems/count-of-range-sum/#/description
Given an integer array nums, return the number of range sums that lie in [lower, upper] inclusive.

Range sum S(i, j) is defined as the sum of the elements in nums between indices i and j (i ≤ j), inclusive.

```CPP
int countRangeSum(vector<int>& nums, int lower, int upper) {
    int len = nums.size();
    int ret = 0;
    long long sum = 0;
    // lower<=sum[i]-sum[j]<=upper
    //j (0=< j< i) satisfy sum[i]-upper=< sum[j]<=-sum[i]-lower.
    multiset<long long> s; //multi set allow same item
    s.insert(0); //since one number itself can be see as range, insert 0 to collect one number case
    for(int i=0;i<len;i++){
        sum+=nums[i];
        //count how many in that range
        ret+=std::distance(s.lower_bound(sum-upper),s.upper_bound(sum-lower));
        s.insert(sum);
    }
    return ret;
}
```


## 3Sum problems: Typical three pointers problems
> Common techniques
* Sort the array
* Fix the first pointer, and move the second and third
* define the condition properly

```CPP
vector<vector<int>> threeSum(vector<int>& nums) {
    sort(nums.begin(),nums.end());
    vector<vector<int>> ret;
    for(int i=0;i<nums.size();i++){
        int target = -nums[i];
        int start = i+1;
        int end = nums.size()-1;
        while(start<end){
            if(nums[start]+nums[end]>target){
                end--;
            }else if(nums[start]+nums[end]<target){
                start++;
            }else{
                vector<int> one;
                one.push_back(nums[i]);
                one.push_back(nums[start]);
                one.push_back(nums[end]);
                ret.push_back(one);
                int begin = nums[start];
                int finish = nums[end];

                while(start<end && nums[start]==begin)
                    start++;
                while(start<end && nums[end]==finish)
                    end--;
            }
            if(start>=end)
                break;
        }
                // Processing duplicates of Number 1
        while (i + 1 < nums.size() && nums[i + 1] == nums[i])
            i++;
    }

    return ret;
}

```

### Follow up: Number of triangles
There are lots of problem can be soled by similar idea

http://www.geeksforgeeks.org/find-number-of-triangles-possible/
Given an unsorted array of positive integers. Find the number of triangles that can be formed with three different array elements as three sides of triangles.

```CPP
int NumOfTriangles(vector<int> arr)
{
    int len = arr.size();
    sort(arr.begin(),arr.end());
    int ret = 0;

    for (int i = 0; i < len-2; i++)
    {
        //right most index
        int k = i+2;

        // Fix the second element
        for (int j = i+1; j < len; j++)
        {
            while (k < len && arr[i] + arr[j] > arr[k])
               ++k;

            ret += k - j - 1;
        }
    }

    return ret;
}

```
