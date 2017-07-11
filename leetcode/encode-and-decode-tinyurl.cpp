//https://leetcode.com/problems/encode-and-decode-tinyurl/#/description
/*
TinyURL is a URL shortening service where you enter a URL such as https://leetcode.com/problems/design-tinyurl and it returns a short URL such as http://tinyurl.com/4e9iAk.
Design the encode and decode methods for the TinyURL service. There is no restriction on how your encode/decode algorithm should work. You just need to ensure that a URL can be encoded to a tiny URL and the tiny URL can be decoded to the original URL.
*/

class Solution {
public:
    string dict = "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
    unordered_map<string,string> m;  //key is longURL, value is shortURL
    unordered_map<int, string> idm;  //key is id in DB, value is longURL
    int id = 0;
    // Encodes a URL to a shortened URL.
    string encode(string longUrl) {
        if(m.find(longUrl)!=m.end()){
            return m[longUrl];
        }
        string res = "";
        id++;
        int count = id;
        while(count > 0)
        {
            res = dict[count%62] + res;
            count /= 62;
        }

        m[longUrl] = res;
        idm[id] = longUrl;
        return res;

    }

    // Decodes a shortened URL to its original URL.
    string decode(string shortUrl) {
        int id = 0;
        for(int i = 0; i < shortUrl.size(); i++)
        {
            id = 62*id + (int)(dict.find(shortUrl[i]));
        }
        if(idm.find(id) != idm.end())return idm[id];
        return "";
    }
};
