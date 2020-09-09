<!-- START doctoc generated TOC please keep comment here to allow auto update -->
<!-- DON'T EDIT THIS SECTION, INSTEAD RE-RUN doctoc TO UPDATE -->
**Table of Contents**  *generated with [DocToc](https://github.com/thlorenz/doctoc)*

- [Trie](#trie)
  - [Data Structure](#data-structure)
  - [Example:](#example)
    - [Add and Search Word](#add-and-search-word)
    - [Search Suggestions System](#search-suggestions-system)
    - [Map Sum Pairs](#map-sum-pairs)

<!-- END doctoc generated TOC please keep comment here to allow auto update -->

# Trie

In computer science, a trie, also called digital tree and sometimes radix tree or prefix tree (as they can be searched by prefixes), is a kind of search tree—an ordered tree data structure that is used to store a dynamic set or associative array where the keys are usually strings.

## Data Structure 


## Example: 

### Add and Search Word

https://leetcode.com/problems/add-and-search-word-data-structure-design/

Design a data structure that supports the following two operations:

void addWord(word)
bool search(word)
search(word) can search a literal word or a regular expression string containing only letters a-z or .. A . means it can represent any one letter.

```

Example:

addWord("bad")
addWord("dad")
addWord("mad")
search("pad") -> false
search("bad") -> true
search(".ad") -> true
search("b..") -> true
```


```CPP
class WordDictionary {
public:
    struct TrieNode{
        bool end = false;
        struct TrieNode * child[26];
    };

    TrieNode * root = new TrieNode();
    // Adds a word into the data structure.
    void addWord(string word) {
        TrieNode * p = root;
        int len= word.size();
        for(int i=0;i<len;i++){
            int pos = word[i]-'a';
            if(p->child[pos] == NULL){
                p->child[pos] = new TrieNode();
            }

            p = p->child[pos];
        }
        p->end = true;//mark the end of tree

    }

    // Returns if the word is in the data structure. A word could
    // contain the dot character '.' to represent any one letter.
    bool search(string word) {
        return searchvalid(word,root);
    }

    bool searchvalid(string word, TrieNode * p){

        if(p==NULL)
            return false;
        int len = word.size();
        if(len == 0)
            return p->end;

        for(int i=0;i<len;i++){
            if(word[i]=='.'){
                //check all possible solution

                for(int j=0;j<26;j++){
                    if(p->child[j]!=NULL){
                         //check all possible solutions
                         if(searchvalid(word.substr(i+1,len-i),p->child[j]))
                            return true;
                    }
                }
                return false;

            }else{
                int pos=word[i]-'a';
                if(p->child[pos] == NULL)
                    return false;

                p=p->child[pos];
            }
        }

        return p->end;
    }
};

```


### Search Suggestions System

https://leetcode.com/problems/search-suggestions-system/

Given an array of strings products and a string searchWord. We want to design a system that suggests at most three product names from products after each character of searchWord is typed. Suggested products should have common prefix with the searchWord. If there are more than three products with a common prefix return the three lexicographically minimums products.

Return list of lists of the suggested products after each character of searchWord is typed. 

```
Example 1:

Input: products = ["mobile","mouse","moneypot","monitor","mousepad"], searchWord = "mouse"
Output: [
["mobile","moneypot","monitor"],
["mobile","moneypot","monitor"],
["mouse","mousepad"],
["mouse","mousepad"],
["mouse","mousepad"]
]
Explanation: products sorted lexicographically = ["mobile","moneypot","monitor","mouse","mousepad"]
After typing m and mo all products match and we show user ["mobile","moneypot","monitor"]
After typing mou, mous and mouse the system suggests ["mouse","mousepad"]
Example 2:

Input: products = ["havana"], searchWord = "havana"
Output: [["havana"],["havana"],["havana"],["havana"],["havana"],["havana"]]
Example 3:

Input: products = ["bags","baggage","banner","box","cloths"], searchWord = "bags"
Output: [["baggage","bags","banner"],["baggage","bags","banner"],["baggage","bags"],["bags"]]
Example 4:

Input: products = ["havana"], searchWord = "tatiana"
Output: [[],[],[],[],[],[],[]]
```


```CPP
class Solution {
public:
    //Create Trie
    struct Trie {
        struct Trie* child[26];
        //for each Trie node, put all suggested items starting with prefix
        vector<string> suggest = {};
    };
    
    vector<vector<string>> suggestedProducts(vector<string>& products, string searchWord) {

        //build Trie Tree
        Trie* root = new Trie();
        for(auto word: products){
            Trie *p = root;
            for (auto c: word){
                //char is not in map
                int pos = c-'a';
                if (p->child[pos]==NULL){
                    p->child[pos] = new Trie();
                }
                p = p->child[pos];
                p->suggest.push_back(word);
            }

        }
        
        vector<vector<string>> result(searchWord.length());
        for (int i=0; i<searchWord.length() && root->child[searchWord[i]-'a']!=NULL; i++ ){
            root = root->child[searchWord[i]-'a'];
            sort(root->suggest.begin(), root->suggest.end());
            root->suggest.resize(min(3, (int)root->suggest.size()));
            result[i] = root->suggest;

        }
        return result;
    }
};
```

### Map Sum Pairs

https://leetcode.com/problems/map-sum-pairs/

Implement a MapSum class with insert, and sum methods.

For the method insert, you'll be given a pair of (string, integer). The string represents the key and the integer represents the value. If the key already existed, then the original key-value pair will be overridden to the new one.

For the method sum, you'll be given a string representing the prefix, and you need to return the sum of all the pairs' value whose key starts with the prefix.

```
Example 1:
Input: insert("apple", 3), Output: Null
Input: sum("ap"), Output: 3
Input: insert("app", 2), Output: Null
Input: sum("ap"), Output: 5
```

```CPP
class MapSum {
private:
    struct TrieNode{
        int val = 0;
        struct TrieNode * child[26];
    };
    
public:
    /** Initialize your data structure here. */
    TrieNode* root;
    
    MapSum() {
        root = new TrieNode();
    }
    
    void insert(string key, int val) {
        TrieNode* p = root;
        for(int i=0;i<key.size();i++){
            int pos = key[i]-'a';
            if(p->child[pos]==NULL){
                p->child[pos] = new TrieNode();
            }
            p=p->child[pos];
        }
        p->val = val;
    }
    
    int sum(string prefix) {
        int ret = 0;
        
        TrieNode* p = root;
        for(int i=0;i<prefix.size();i++){
            int pos = prefix[i]-'a';
            if(p->child[pos]==NULL)
                return ret;
            p=p->child[pos];
        }
        //contine to all leaf
        help(p, ret);
        return ret;
    }
    
    void help(TrieNode* cur, int& sum){

        sum+=cur->val;
        
        for(int i=0;i<26;i++){
            if(cur->child[i]!=NULL){
                help(cur->child[i], sum);
            }
        }
    }
};
```
