/*
https://leetcode.com/problems/expression-add-operators/#/description
Given a string that contains only digits 0-9 and a target value, return all possibilities to add binary operators (not unary) +, -, or * between the digits so they evaluate to the target value.

Examples:
"123", 6 -> ["1+2+3", "1*2*3"]
"232", 8 -> ["2*3+2", "2+3*2"]
"105", 5 -> ["1*0+5","10-5"]
"00", 0 -> ["0+0", "0-0", "0*0"]
"3456237490", 9191 -> []
*/

vector<string> addOperators(string num, int target) {
    vector<string> ret;
    string one = "";
    if(num.size()==0)
        return ret;

    help(num,0,one,0,0,ret,target);
    return ret;

}

void help(string num, int i, string one, long val, long save, vector<string> &ret, int target){

    if(i==num.size()){
        if(val==target)
            ret.push_back(one);
        return;
    }
    for(int j=i;j<num.size();j++){
        string t = num.substr(i, j-i+1);
        long cur = stol(t);
        if (to_string(cur).size() != t.size()) continue;  //remove some 0
        if(i==0){//first one, no operator
            help(num,j+1,one+to_string(cur),cur,cur,ret,target);
        }else{
            //add '+' before current num
            help(num,j+1,one+"+"+to_string(cur),val+cur,cur,ret,target);
            //add '-' before current num
            help(num,j+1,one+"-"+to_string(cur),val-cur,-cur,ret,target);
            //add '*' before current num, for mutiple, like 2+3*5, need to save 3 otherwise it will be 2+3=5*5
            help(num,j+1,one+"*"+to_string(cur), val-save + save*cur,save*cur ,ret,target);
        }
    }
}
