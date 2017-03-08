//http://www.lintcode.com/en/problem/strstr/
/*
For a given source string and a target string, you should output the first index(from 0) of target string in source string.
If target does not exist in source, just return -1.
Example
If source = "source" and target = "target", return -1.
If source = "abcdabcdefg" and target = "bcd", return 1.
*/
class Solution {
public:
    /**
     * Returns a index to the first occurrence of target in source,
     * or -1  if target is not part of source.
     * @param source string to be scanned.
     * @param target string containing the sequence of characters to match.
     */
    int strStr(const char *source, const char *target) {
        int index = 0;
        if(source==NULL || target==NULL)
            return -1;
        
        if(*target=='\0')
            return 0;

        
        while(*source!='\0'){
            const char *s = source;
            const char *t = target;
            
            while(*s++==*t++){
                if(*s=='\0' && *t!='\0') 
                    return -1;
                
                if(*t=='\0')
                    return index;
            }
            index++;
            source++;
        }
        
        return -1;
    }
};

