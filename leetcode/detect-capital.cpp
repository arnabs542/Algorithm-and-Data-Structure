/*
https://leetcode.com/problems/detect-capital/#/description

Total Accepted: 25737
Total Submissions: 49316
Difficulty: Easy
Contributors:
love_Fawn
Given a word, you need to judge whether the usage of capitals in it is right or not.

We define the usage of capitals in a word to be right when one of the following cases holds:

All letters in this word are capitals, like "USA".
All letters in this word are not capitals, like "leetcode".
Only the first letter in this word is capital if it has more than one letter, like "Google".
Otherwise, we define that this word doesn't use capitals in a right way.
Example 1:
Input: "USA"
Output: True
Example 2:
Input: "FlaG"
Output: False
*/

bool detectCapitalUse(string word) {
    int cnt = 0;
    for(int i=0;i<word.size();i++){
        if('Z'-word[i]>=0)
            cnt++;
    }
    if(cnt==0 || cnt==word.size() || cnt==1&& 'Z'-word[0]>=0)
        return true;
    return false;
}
