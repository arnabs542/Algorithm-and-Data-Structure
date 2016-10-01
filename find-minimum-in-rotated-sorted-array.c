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
		int end = len - 1;
		int ret = INT_MAX;

		while (begin<end) {
			int mid = begin + (end - begin) / 2;
			if (num[mid]>num[end]) {
				begin = mid + 1;
			}
			else if (num[mid]<num[end]) {
				end = mid;
			}
		}

		return num[begin];
	}
};

//follow up, what if there could be equal.
//https://leetcode.com/problems/find-minimum-in-rotated-sorted-array-ii/
class Solution {
public:
	int findMin(vector<int>& nums) {
		int begin = 0;
		int len = nums.size();
		int end = len - 1;

		while (begin<end) {
			int mid = begin + (end - begin) / 2;
			if (nums[mid]>nums[end]) {
				begin = mid + 1;
			}
			else if (nums[mid]<nums[end]) {
				end = mid;
			}
			else {
				//num[mid] == num[hi], we couldn't sure the position of minimum in mid's left or right, so reduce one high
				end--;
			}
		}

		return nums[begin];
	}
};
