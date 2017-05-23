https://leetcode.com/problems/majority-element/#/description
//Given an array of size n, find the majority element. The majority element is the element that appears more than ⌊ n/2 ⌋ times.

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
