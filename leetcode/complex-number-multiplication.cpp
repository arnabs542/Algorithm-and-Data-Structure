/*
https://leetcode.com/problems/complex-number-multiplication/#/description

Given two strings representing two complex numbers.
You need to return a string representing their multiplication. Note i2 = -1 according to the definition.

Example 1:
Input: "1+1i", "1+1i"
Output: "0+2i"
Explanation: (1 + i) * (1 + i) = 1 + i2 + 2 * i = 2i, and you need convert it to the form of 0+2i.
Example 2:
Input: "1+-1i", "1+-1i"
Output: "0+-2i"
Explanation: (1 - i) * (1 - i) = 1 + i2 - 2 * i = -2i, and you need convert it to the form of 0+-2i.
*/

string complexNumberMultiply(string a, string b) {
    pair<int, int> av = parse(a);
    pair<int, int> bv = parse(b);
    int ra = av.first * bv.first - av.second * bv.second;
    int rb = av.first * bv.second + av.second * bv.first;
    return to_string(ra) + "+" + to_string(rb) + "i";
}

pair<int, int> parse(const string& a) {
    int plus = find(a.begin(), a.end(), '+') - a.begin();
    int i = find(a.begin(), a.end(), 'i') - a.begin();
    int ra = stoi(a.substr(0, plus));
    int rb = stoi(a.substr(plus + 1, i - plus));
    return {ra, rb};
}
