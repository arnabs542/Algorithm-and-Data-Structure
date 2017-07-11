//https://leetcode.com/problems/hamming-distance/#/description
/*
The Hamming distance between two integers is the number of positions at which the corresponding bits are different.
Given two integers x and y, calculate the Hamming distance.
*/

int hammingDistance(int x, int y) {
    int ret = 0;
    while(x>0 || y>0){
        if((x&0x01) != (y&0x01)){
            ret++;
        }
        x= x>>1;
        y=y>>1;
    }    
    return ret;
}
