/*
Longest Common Prefix

Given k strings, find the longest common prefix (LCP).
Have you met this question in a real interview?
Example

For strings "ABCD", "ABEF" and "ACEF", the LCP is "A"

For strings "ABCDEFG", "ABCEFG" and "ABCEFA", the LCP is "ABC"

*/

class Solution {
public:
	/**
	* @param strs: A list of strings
	* @return: The longest common prefix
	*/
	string longestCommonPrefix(vector<string> &strs) {
		string ret;
		int index = 0;
		if (strs.size() == 0) {
			return "";
		}
		while (true) {
			if (index >= strs[0].size())
				return ret;
			char cur = strs[0][index];
			for (int i = 1; i<strs.size(); i++) {
				if (index >= strs[i].size())
					return ret;
				if (strs[i][index] != cur)
					return ret;
			}
			index++;
			ret += cur;
		}

		return ret;
	}
};


//solution 2
string longestCommonPrefix(vector<string> &strs) {
    string ret;
    int index = 0;
    if (strs.size() == 0) {
        return ret;
    }
    
    for(int i=0;i<strs[0].size();i++){
        for(int j=0;j<strs.size();j++){
            if(i>=strs[j].size())//current string to end
                return ret;
            if (strs[j][i] != strs[0][i]) {
                return ret;
            }
        }
        ret+=strs[0][i];
    }
    
    return ret;
}
