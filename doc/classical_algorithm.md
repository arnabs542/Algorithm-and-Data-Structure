<!-- START doctoc generated TOC please keep comment here to allow auto update -->
<!-- DON'T EDIT THIS SECTION, INSTEAD RE-RUN doctoc TO UPDATE -->
**Table of Contents**  *generated with [DocToc](https://github.com/thlorenz/doctoc)*

- [Sort](#sort)
  - [Quick Sort](#quick-sort)
  - [Select Sort Common](#select-sort-common)
    - [Partial Selection: Find K-th smallest](#partial-selection-find-k-th-smallest)
  - [Bucket Sort:](#bucket-sort)
  - [Merge Sort](#merge-sort)
    - [Find kth element in two sorted arrays](#find-kth-element-in-two-sorted-arrays)
- [BackTracking/Recurisve](#backtrackingrecurisve)
  - [Common logic](#common-logic)
  - [Permutation](#permutation)
  - [SubSet](#subset)
    - [Subset with Duplicate](#subset-with-duplicate)
  - [Generalized Abbreviation](#generalized-abbreviation)
  - [Different Ways to Add Parentheses](#different-ways-to-add-parentheses)
  - [Combination](#combination)
  - [Application](#application)
    - [Letter Combinations of a Phone Number](#letter-combinations-of-a-phone-number)
    - [Generate parentheses](#generate-parentheses)
    - [Robot Room Cleaner](#robot-room-cleaner)
- [Others](#others)
  - [BFPRT](#bfprt)
  - [Half Majority](#half-majority)
  - [Search a 2D matrix](#search-a-2d-matrix)
  - [First missing positive](#first-missing-positive)
- [Random/Probablity](#randomprobablity)
  - [Random sampling: Generate random k numbers in range n](#random-sampling-generate-random-k-numbers-in-range-n)
  - [Reject sampling](#reject-sampling)
  - [Suffle](#suffle)
  - [Revisor sampling](#revisor-sampling)

<!-- END doctoc generated TOC please keep comment here to allow auto update -->





# Sort

## Quick Sort
```CPP
void qSort(int a[], int start, int end){
	if(start>=end)
		return;
	int i = start;
	int j = end-1;
	int pivot = a[start];

	while(i<j){
		do{
			i++;
		}while(i<end&&x[i]<pivot);

		do{
			j--;
		}while(j>=start&&x[j]>pivot);

		swap(a[i],a[j]);
	}
	swap(a,pivot,a[j]);
	qSort(x, start, j-1);
       qSort(x, j + 1, end);

}
```

## Select Sort Common 

The basic idea is to use Quick Select algorithm to partition the array with pivot:

```
Put numbers < pivot to pivot's left
Put numbers > pivot to pivot's right
Then

if indexOfPivot == k, return A[k]
else if indexOfPivot < k, keep checking left part to pivot
else if indexOfPivot > k, keep checking right part to pivot
```

### Partial Selection: Find K-th smallest
```CPP
int selectsort(vector<int> num, int k){
	int len = num.size();
	for(int i=0;i<k;i++){
		for(int j=i+1;j<len;j++){
			if(num[j]<num[i]){
				swap(num[j],num[i]);
			}
		}

	}
	return nums[k-1];
}

```

https://leetcode.com/problems/kth-largest-element-in-an-array/

Find the kth largest element in an unsorted array. Note that it is the kth largest element in the sorted order, not the kth distinct element.

```
Example 1:

Input: [3,2,1,5,6,4] and k = 2
Output: 5
Example 2:

Input: [3,2,3,1,2,4,5,5,6] and k = 4
Output: 4
```

```CPP
int findKthLargest(vector<int>& nums, int k) {
        return quickSelect(nums, 0, nums.size()-1, k);
    }
    
    int quickSelect(vector<int>& nums, int low, int high, int k) {
      int pivot = low;

      // use quick sort's idea
      // put nums that are <= pivot to the left
      // put nums that are  > pivot to the right
      for (int j = low; j < high; j++) {
        if (nums[j] <= nums[high]) {
          swap(nums, pivot++, j);
        }
      }
      swap(nums, pivot, high);

      // count the nums that are > pivot from high
      int count = high - pivot + 1;
      // pivot is the one!
      if (count == k) 
          return nums[pivot];
      // pivot is too small, so it must be on the right
      if (count > k) {
          return quickSelect(nums, pivot + 1, high, k);
      }else {
          return quickSelect(nums, low, pivot - 1, k - count);
      }
          
      // pivot is too big, so it must be on the left
      
    }
```



## Bucket Sort:
Used heavily when values are bounded into certain range
```CPP
void bucketSort(vector<int> in) {
	vector<int> bucket(120, 0);
	for (int i = 0; i < in.size(); i++) {
		bucket[i]++;
	}
	int index = 0;
	for (int i = 0; i < 120;i++) {
		while (bucket[i] > 0) {
			in[index] = i;
			index++;
			bucket[i]--;
		}
	}
}

```

Example will be:
https://leetcode.com/problems/maximum-gap/

Given an unsorted array, find the maximum difference between the successive elements in its sorted form.
Try to solve it in linear time/space.
Return 0 if the array contains less than 2 elements.
You may assume all elements in the array are non-negative integers and fit in the 32-bit signed integer range

```CPP
int maximumGap(vector<int>& nums) {
		int max_g = INT_MIN;
		int min_g = INT_MAX;
		int len = nums.size();
		if (len <= 1)
			return 0;

		for (int i = 0; i<len; i++) {
			max_g = max(max_g, nums[i]);
			min_g = min(min_g, nums[i]);
		}
		int bucket_size = max(1, (max_g - min_g) / (len - 1));
		int bucket_num = (max_g - min_g) / bucket_size + 1;

		if (bucket_num <= 1)
			return (max_g - min_g);
		vector<int> bucket_max(bucket_num, INT_MIN);
		vector<int> bucket_min(bucket_num, INT_MAX);
		vector<int> bucket_count(bucket_num, 0);
		int index;
		//using bucket, we basic sort this array
		for (int i = 0; i<len; i++) {

			index = (nums[i] - min_g) / bucket_size;
			bucket_count[index]++;
			bucket_min[index] = min(bucket_min[index], nums[i]);
			bucket_max[index] = max(bucket_max[index], nums[i]);
		}

		int maxGap = INT_MIN;
		int last_max = min_g;//max number in last bucket
		for (int i = 0; i<bucket_num; i++) {
			if (bucket_count[i]>0) {
				maxGap = max(maxGap, bucket_min[i] - last_max);
				last_max = bucket_max[i];
			}
		}
		return maxGap;

	}

```

## Merge Sort

### Find kth element in two sorted arrays
General idea:

* If A[k/2] < B[k/2], kth element is within A[k/2...k]+B[1...k/2]
* If A[k/2] > B[k/2]，kth element is within A[1...k/2]+B[k/2...k]

https://leetcode.com/problems/median-of-two-sorted-arrays/

There are two sorted arrays nums1 and nums2 of size m and n respectively.
Find the median of the two sorted arrays. The overall run time complexity should be O(log (m+n)).
Example 1:
nums1 = [1, 3]
nums2 = [2]
The median is 2.0
Example 2:
nums1 = [1, 2]
nums2 = [3, 4]
The median is (2 + 3)/2 = 2.5

```CPP
double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
		int m = nums1.size(), n = nums2.size();
		int k = (m + n) / 2;
		int num1 = findKth(nums1, 0, m, nums2, 0, n, k + 1);
		if ((n + m) % 2 == 0)
		{
			int num2 = findKth(nums1, 0, m, nums2, 0, n, k);
			return (num1 + num2) / 2.0;
		}
		else return num1;
	}
	int findKth(vector<int> & nums1, int nums1_left, int nums1_right, vector<int>& nums2, int nums2_left, int nums2_right, int k)
	{
		int m = nums1_right - nums1_left;
		int n = nums2_right - nums2_left;
		if (m > n) return findKth(nums2, nums2_left, nums2_right, nums1, nums1_left, nums1_right, k);
		else if (m == 0)
			return nums2[nums2_left + k - 1];
		else if (k == 1)
			return min(nums1[nums1_left], nums2[nums2_left]);
		else {
			int s1LeftCount = min(k / 2, m);
			int s2LeftCount = k - s1LeftCount;
			if (nums1[nums1_left + s1LeftCount - 1] == nums2[nums2_left + s2LeftCount - 1])
				return nums1[nums1_left + s1LeftCount - 1];
			else if (nums1[nums1_left + s1LeftCount - 1] < nums2[nums2_left + s2LeftCount - 1])
				return findKth(nums1, nums1_left + s1LeftCount, nums1_right, nums2, nums2_left, nums2_right, k - s1LeftCount);
			else
				return findKth(nums1, nums1_left, nums1_right, nums2, nums2_left + s2LeftCount, nums2_right, k - s2LeftCount);
		}
	}

```

# BackTracking/Recurisve

## Common logic

> DFS+Recursive

1.	DFS/recursive logical key is call back and each level just do one thing and every level do the same thing repeat
2.	Interface definition. For most problem, use reference in C++(&) so some data structure needs to be in every level and modified. Otherwise each level should be in tact
3.	Push_back() and pop_back() is key thing to go over all items, they should be balance (push should be paired with pop), when thinking the problem, every level(in DFS or recursive) should consider its own level, do not go into recursive logic next level. Same for set item true/false (visited in two dimensional array. etc)
4.	If not push/pop. Use local variable
5.	Put core recursive logic tact, judgement/return/error case should be outside the recursive loop.

```CPP
//Core Logic Code
//Core Recursive logic can be seens as
void help(int &ret, int start, void * param) {
	if (certain condition) {
		// process ret logic
		return;
	}

	for (i = start; i < param;i++) {
		one_res.push_back();  //make a choice
    ret = f(); //some ret logic
		help(ret, i+1/i, param);
		one_res.pop_back(); //retrieve the choice
	}
}



```
## Permutation

Get all permutation of array

```CPP
vector<vector<int>> permuteUnique(vector<int>& nums) {
		vector<vector<int>> ret;
		vector<int> cur;
		vector<bool> visit(nums.size(), false);
		std::sort(nums.begin(), nums.end());
		permute_helper(ret, cur, nums, visit, nums.size());

		return ret;

	}

	void permute_helper(vector<vector<int>>& ret, vector<int>& cur, vector<int>& nums, vector<bool> visit, int len) {
		if (cur.size() == len) {
			ret.push_back(cur);
			return;
		}
		int prev = INT_MAX;
		for (int i = 0; i<len; i++) {
			if (visit[i] == false && nums[i] != prev) {
				cur.push_back(nums[i]);
				visit[i] = true;
				prev = nums[i];
				permute_helper(ret, cur, nums, visit, len);
				cur.pop_back();
				visit[i] = false;
			}
		}
	}

```

## SubSet

https://leetcode.com/problems/subsets/

Given a set of distinct integers, nums, return all possible subsets (the power set).

Note: The solution set must not contain duplicate subsets.

```
Example:

Input: nums = [1,2,3]
Output:
[
  [3],
  [1],
  [2],
  [1,2,3],
  [1,3],
  [2,3],
  [1,2],
  []
]
```

```CPP
class Solution {
public:
    vector<vector<int>> res;
    vector<vector<int>> subsets(vector<int>& nums) {
        vector<int> track;
        //record all path
        backtrack(nums, 0, track);
        return res;
    }
        
    void backtrack(vector<int>& nums, int start, vector<int>& track) {
        res.push_back(track);
        for (int i = start; i < nums.size(); i++) {
            // make choice
            track.push_back(nums[i]);
            // backtrack
            backtrack(nums, i + 1, track);
            // retreive choice
            track.pop_back();
        }
    }

};
```

### Subset with Duplicate

https://www.educative.io/courses/grokking-the-coding-interview/7npk3V3JQNr

https://leetcode.com/problems/subsets-ii/

Given a collection of integers that might contain duplicates, nums, return all possible subsets (the power set).

Note: The solution set must not contain duplicate subsets.

```CPP
vector<vector<int>> subsetsWithDup(vector<int>& nums) {
        vector<vector<int>> ret;
        vector<int> cur;
        
        if(nums.empty())
            return ret;
        
        ret.push_back(vector<int>());
        //each iteration return subsets with same number of items
        std::sort(nums.begin(),nums.end());
        for(int i=1;i<=nums.size();i++){
            subsets_helper(nums,ret,cur,i,0);
        }
        
        return ret;
        
    }
    //width is the size of subsets with same len
    void subsets_helper(vector<int>& nums,vector<vector<int>> &ret, vector<int> &cur,int width, int start){
        if(cur.size()==width){
            ret.push_back(cur);
            return;
        }
        int prev = INT_MAX;
        //duplicate can only happen in one level.
        for(int i=start;i<nums.size();i++){
            if(prev!=nums[i]){
                prev = nums[i];
                cur.push_back(nums[i]);
                subsets_helper(nums,ret,cur,width,i+1);
                cur.pop_back(); 
            }
        }
    }
```

## Generalized Abbreviation

https://leetcode.com/problems/generalized-abbreviation/

Write a function to generate the generalized abbreviations of a word. 

Note: The order of the output does not matter.

```
Example:

Input: "word"
Output:
["word", "1ord", "w1rd", "wo1d", "wor1", "2rd", "w2d", "wo2", "1o1d", "1or1", "w1r1", "1o2", "2r1", "3d", "w3", "4"]
```

```CPP
vector<string> generateAbbreviations(string word) {
    /*
    this is a combination problem:
    for each char in word, either we keep it or abbreviate it
    */
    vector<string> ret;
    string one = "";
    help(ret,word,0,one,0);
    return ret;
}

/*
current char can be either keep itself, or abbreviated by len. 
//pos is the current char's position in word. len is abbrevaite len
*/
void help(vector<string> &ret, string& word, int pos, string cur, int len){
    if(pos==word.size()){
        if(len>0){
            cur+=to_string(len);
        }
        ret.push_back(cur);
        return;
    }
    
    help(ret,word,pos+1,cur,len+1);  //current char is abbreviated.
    //current char is kept. get the len for last abbreviation, reset len to 0 since abbreviation is done 
    help(ret,word,pos+1,cur+(len>0?to_string(len):"")+word[pos],0);
}
```

## Different Ways to Add Parentheses

https://leetcode.com/problems/different-ways-to-add-parentheses/

https://www.educative.io/courses/grokking-the-coding-interview/N0Q3PKRKMPz

Given an expression containing digits and operations (+, -, *), find all possible ways in which the expression can be evaluated by grouping the numbers and operators using parentheses.

```
Example 1:

Input: "1+2*3"
Output: 7, 9
Explanation: 1+(2*3) => 7 and (1+2)*3 => 9
Example 2:

Input: "2*3-4-5"
Output: 8, -12, 7, -7, -3 
Explanation: 2*(3-(4-5)) => 8, 2*(3-4-5) => -12, 2*3-(4-5) => 7, 2*(3-4)-5 => -7, (2*3)-4-5 => -3
```

```CPP
vector<int> diffWaysToCompute(string input) {
    vector<int> ret;   
    for(int i = 0;i<input.length();i++){
        if(input[i]=='+'|| input[i]=='-'||input[i]=='*'){
            string str1 = input.substr(0,i);
            string str2 = input.substr(i+1);
            vector<int> part1 = diffWaysToCompute(str1);
            vector<int> part2 = diffWaysToCompute(str2);
            for (int l : part1) {
                for (int r : part2) {
                    switch (input[i]) {
                        case '+':
                            ret.push_back(l + r);
                            break;
                        case '-':
                            ret.push_back(l - r);
                            break;
                        default:
                            ret.push_back(l * r);
                    }
                } 
            }
        }
    }
    
    if (ret.empty())
        ret.push_back(stoi(input));
    return ret;
}
```

## Combination

https://leetcode.com/problems/combinations/

Given two integers n and k, return all possible combinations of k numbers out of 1 ... n.

```
Example:

Input: n = 4, k = 2
Output:
[
  [2,4],
  [3,4],
  [2,3],
  [1,2],
  [1,3],
  [1,4],
]
```

```CPP
class Solution {
public:
    vector<vector<int>>res;
    vector<vector<int>> combine(int n, int k) {
        if (k <= 0 || n <= 0) 
            return res;
        vector<int> track;
        backtrack(n, k, 1, track);
        return res;
    }
    
    void backtrack(int n, int k, int start, vector<int>& track) {
        // to the bottom of tree(backtrack tree)
        if (k == track.size()) {
            res.push_back(track);
            return;
        }
        // i from current start
        for (int i = start; i <= n; i++) {
            // make choice
            track.push_back(i);
            backtrack(n, k, i + 1, track);
            // retreieve choice
            track.pop_back();
        }
    }
};
```

## Application

### Letter Combinations of a Phone Number

https://leetcode.com/problems/letter-combinations-of-a-phone-number/ 

Given a string containing digits from 2-9 inclusive, return all possible letter combinations that the number could represent.

A mapping of digit to letters (just like on the telephone buttons) is given below. Note that 1 does not map to any letters.


```
Example:

Input: "23"
Output: ["ad", "ae", "af", "bd", "be", "bf", "cd", "ce", "cf"].
```

```CPP
class Solution {
private:
    map<int,string> dic;
public:
    void init(){

        dic[2] = "abc";  
        dic[3] = "def";
        dic[4] = "ghi";
        dic[5] = "jkl";
        dic[6] = "mno";
        dic[7] = "pqrs";
        dic[8] = "tuv";
        dic[9] = "wxyz";
    }
    
    vector<string> letterCombinations(string digits) {
        vector<string> ret;
        /* for this question, we need to create a look-up dictionary */
       
        if(digits.empty())
            return ret;
        
        
        init();
        
        string one = "";
        help(ret,one,digits,0);
        return ret;        
    }
    
    void help(vector<string> &ret, string one, string& digits,int idx){
        if(idx==digits.size()){
            ret.push_back(one);
            return;
        }
        //DO not over counts.
        string letter = dic[digits[idx]-'0'];
        for(int i=0;i<letter.size();i++){
            
            help(ret,one+letter[i],digits,idx+1);
        }

    }
```



### Generate parentheses

https://leetcode.com/problems/generate-parentheses/

```
Given n pairs of parentheses, write a function to generate all combinations of well-formed parentheses.

For example, given n = 3, a solution set is:

[
  "((()))",
  "(()())",
  "(())()",
  "()(())",
  "()()()"
]
```

```CPP
class Solution {
public:
    vector<string> generateParenthesis(int n) {
        vector<string> ret;
        help(ret,"",n,n);
        
        return ret;
    }
    //left is number of "(", and right is number of ")"
    void help(vector<string> &ret,string str, int left, int right){
        if(left==0 && right==0){
            ret.push_back(str);
            return;
        }
        if(left>0)
            help(ret,str+"(",left-1,right);
        if(left<right) //valid Parentheses starts with "("
            help(ret,str+")",left,right-1);
    }
};
```

### Robot Room Cleaner

https://leetcode.com/problems/robot-room-cleaner/

Given a robot cleaner in a room modeled as a grid.Each cell in the grid can be empty or blocked.The robot cleaner with 4 given APIs can move forward, turn left or turn right. Each turn it made is 90 degrees.When it tries to move into a blocked cell, its bumper sensor detects the obstacle and it stays on the current cell.Design an algorithm to clean the entire room using only the 4 given APIs shown below.

```
interface Robot {
  // returns true if next cell is open and robot moves into the cell.
  // returns false if next cell is obstacle and robot stays on the current cell.
  boolean move();

  // Robot will stay on the same cell after calling turnLeft/turnRight.
  // Each turn will be 90 degrees.
  void turnLeft();
  void turnRight();

  // Clean the current cell.
  void clean();
}
```

```JAVA
class Solution {
// going clockwise : 0: 'up', 1: 'right', 2: 'down', 3: 'left'
  int[][] directions = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};
  Set<Pair<Integer, Integer>> visited = new HashSet();
  Robot robot;

  public void goBack() {
    robot.turnRight();
    robot.turnRight();
    robot.move();
    robot.turnRight();
    robot.turnRight();
  }

  public void backtrack(int row, int col, int d) {
    visited.add(new Pair(row, col));
    robot.clean();
    // going clockwise : 0: 'up', 1: 'right', 2: 'down', 3: 'left'
    for (int i = 0; i < 4; ++i) {
      int newD = (d + i) % 4;
      int newRow = row + directions[newD][0];
      int newCol = col + directions[newD][1];

      if (!visited.contains(new Pair(newRow, newCol)) && robot.move()) {
        backtrack(newRow, newCol, newD);
        goBack();
      }
      // turn the robot following chosen direction : clockwise
      robot.turnRight();
    }
  }

  public void cleanRoom(Robot robot) {
    this.robot = robot;
    backtrack(0, 0, 0);
  }
}
```


# Others

## BFPRT
In an unordered array, find the k'th smallest or largest value

first method is recursive:
1. select a pivot number
2. partition the collection into <,=,> 3 collections compared with pivot
3. check k's smallest location, then recursive

The issue is pivot choice could be random and worst case is O(N^2)

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

## First missing positive
ideally we should have vector as 1,2,3,...n. so nums[i-1]=i

Just go through the array sequentially and for every index write the value at the index to the index specified by value, recursively placing any value at that location to its place and throwing away values > N. Then go again through the array looking for the spot where value doesn't match the index - that's the smallest value not in the array.

```CPP
int firstMissingPositive(vector<int>& nums) {
  int len = nums.size();
  int ret = 0;
  for(int i=0;i<len;i++){
      int target = nums[i];
      //recursively placing any value to location to its place, until find or no more place
      while(target>0 && target<=len && target!=nums[target-1]){
          swap(target,nums[target-1]);
      }
  }

  for(int i=0;i<len;i++){
      if(nums[i]!=i+1){
          ret = i+1;
          return ret;
      }
  }
  return len+1;
}
```

# Random/Probablity

To get random probablity p=1/N

```CPP
p = (rand()*N)%N
if(p==0) //this will give 1/N probability
  {...}
```

## Random sampling: Generate random k numbers in range n

Example to draw 3 random from 0-9:

* First draw (n1), a random number between 1 and 7
* Second draw (n2), a random number between 1 and 8, with 8 having TWO chances to be drawn:
  * if 8 is drawn
  * if n1 is drawn
* Third draw (n3), a random number between 1 and 9, with 9 having THREE chances to be drawn:
  * if 9 is drawn
  * if n1 is drawn
  * if n2 is drawn

* So, each number has 3(k) chances to be drawn:
  * The numbers at or below 7 have a chance to be drawn each of the 3 draws
  * The number 8 has two chances to be drawn on the second draw, and one draw thereafter
  * The number 9 has three chances to be drawn on the third draw,

```CPP
set<int> randomSample(int k, int n){
  set<int> ret;
  for(int i=n-k;i<n;i++){
    int t = rand()%i;
    if(ret.find(t)==ret.end()){
      ret.insert(t);
    }else{
      ret.insert(i);
    }
  }
  return ret;
}
```


## Reject sampling
Given a function which generates a random integer in the range 1 to 7, write a function which generates a random integer in the range 1 to 10 uniformly.
The main idea is when you generate a number in the desired range, output that number immediately. If the number is out of the desired range,
reject it and re-sample again. As each number in the desired range has the same probability of being chosen, a uniform distribution is produced.

```CPP
int rand10() {
  int row, col, idx;
  do {
    row = rand7();
    col = rand7();
    idx = col + (row-1) * 7;
  } while (idx > 40);
  return 1 + (idx-1)%10;
}


```

## Suffle
Shuffle a Deck

```CPP
void KnuthShuffle(int* pArr)
{
    int val;
    for(int i=51;i>=0;i--)
    {
        val=(rand() * 52)%i;
        swap(pArr[i], pArr[val]);
    }
}
```

https://leetcode.com/problems/shuffle-an-array/#/
```CPP
vector<int> shuffle(vector<int> nums) {
    vector<int> ret(nums);
    //shuffle each position with another one after that
    for (int i = 0;i < ret.size();i++) {
        int pos = rand()%(ret.size()-i);
        swap(ret[i+pos], ret[i]);
    }
    return ret;
}

```

## Revisor sampling
Reservoir sampling is a family of randomized algorithms for randomly choosing a sample of k items from a list S containing n items, where n is either a very large or unknown number. Typically n is large enough that the list doesn't fit into main memory.

* Keep the first item(or first k items) in memory.
* When i-th item comes
  * With 1/i probability, replace the first item with new item
  * With (1-1/i) probability, keep item


```CPP
// A function to randomly select k items from stream[0..n-1].
vector<int> selectKItems(vector<int> stream, int n, int k){
  vector<int> ret;
  int i;
  for(i=0;i<k;i++){
    ret[i] = stream[i];
  }
  for(;i<n;i++){
    int pos = rand()%(i+1);
    if(pos<k)
      ret[pos] = stream[i];
  }
  return ret;
}

```

Revisor sampling can also be used to some other random sample issues

> Given an array of integers with possible duplicates, randomly output the index of a given target number.

Example:
https://leetcode.com/problems/random-pick-index/#/description
int[] nums = new int[] {1,2,3,3,3};
Solution solution = new Solution(nums);

// pick(3) should return either index 2, 3, or 4 randomly. Each index should have equal probability of returning.
solution.pick(3);

// pick(1) should return 0. Since in the array only nums[0] is equal to 1.
solution.pick(1);

```CPP
int pick(int target,vector<int> n) {
    int ret = -1;
    int size = 0;
    for(int i=0;i<n.size();i++){
        if(n[i]==target){
            size++;
            if(size==1)
                ret = i; //init
            else{
                if(rand()%size==0)
                    ret = i;//revisor sampling with probability p=1/size
            }
        }
    }
    return ret;
}

```