//https://leetcode.com/problems/add-binary/#/description
/*
Given two binary strings, return their sum (also a binary string).

For example,
a = "11"
b = "1"
Return "100".
*/

string addBinary(string a, string b) {
    string ret = "";
    int c = 0;
    int i = a.size()-1;
    int j = b.size()-1;
    while(i>=0 || j>=0 ||c==1){
        c += i>=0? a[i--]-'0': 0;
        c += j>=0? b[j--]-'0': 0;
        ret = char(c%2+'0') + ret;
        c = c/2;
    }
    return ret;
}
