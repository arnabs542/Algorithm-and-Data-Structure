class Solution {
public:
    bool wordBreak(string s, unordered_set<string>& wordDict) {
        /*
        state f[i] can first i characters be broken successfully?
        Function: f[i] = or{f[j], j < i, letter in [j+1, i] can be found in dict}
        */
        
        if (s.empty()) return true;
        if (wordDict.empty()) return false;
        
        int max_word_len = 0;
        for(unordered_set<string>::iterator it=wordDict.begin(); it!=wordDict.end();it++){
            if((*it).size()>max_word_len)
                max_word_len = (*it).size();
        }
        
        vector<bool> word_break(s.size() + 1, false);
        word_break[0] = true;
        for(int i=1;i<=s.size();i++){
            for(int j=i-1;j>=0;j--){
                if(i-j>max_word_len)
                    break;
                //notice the word_break[j] corresponding to s[j-1]
                if(word_break[j]==true && wordDict.find(s.substr(j,i-j))!=wordDict.end()){
                    word_break[i] = true;
                     break;
                }
                
               
            }
        }
        
        return word_break[s.size()];
    }
};
