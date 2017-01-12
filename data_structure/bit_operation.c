/************
Bit Manipulation and low level stuff
**************/
/*
Swap odd and even bit
*/
int SwapOddEvenbits(int x){
  return ((x&0xaaaaaaaa)>>1) | (x&0x55555555)<<1))
}

/*
Detect whether a number is 2's power
*/
bool Istwopower(int n)
{
	if((n&(n-1)) == 0)
		return true;
	else
		return false
}

return (num != 0) && ((num & (num - 1)) == 0);

/*
Detect how many "1" in one int
*/
//method 1, shift and &
int Numofone(int x){
	int count = 0;
	for(i=0;i<sizeof(int)*8;i++){
		if(x&0x00000001) count++;
		x = x>>1;
	}
	
	return count;
}

//method 2, using a array or hash table to search

//method 3
int Numofone(int x){
	x = (x & 0x55555555) + ((x>>1) & 0x55555555);
	x = (x & 0x33333333) + ((x>>2) & 0x33333333);
	x = (x & 0x0f0f0f0f) + ((x>>4) & 0x0f0f0f0f);
	x += (x>>8);
	x += (x>>16);
	return (x & 0x00ff);
}

//method 4:
int Numofone(int x){
	int count = 0;
	if(x == 0) count = 0;

	do{
		count++;
	}while(x&=(x-1));
	
	return count;
}

int Numofone(int x){

    int counter =0;
    for(;x!=0;x&=(x-1)){
        count++;
    }
    
    return counter;

}

//Swapping values with XOR 
#define SWAP(a, b) (((a) ^= (b)), ((b) ^= (a)), ((a) ^= (b)))

/*
Reverse bits of an unsigned integer.
We only need to perform the swap when the ith bit and the jth bit are different. To test if two bits are different, we could use the XOR operation. Then, we need to toggle both ith and jth bits. We could apply the XOR operation again. By XOR-ing the ith and jth bit with 1, both bits are toggled.
typedef unsigned int uint;
*/

//method 1
uint swapBits(uint x, uint i, uint j) {
  uint lo = ((x >> i) & 1);
  uint hi = ((x >> j) & 1);
  if (lo ^ hi) {
    x ^= ((1U << i) | (1U << j));
  }
  return x;
}
 
uint reverseXor(uint x) {
  uint n = sizeof(x) * 8;
  for (uint i = 0; i < n/2; i++) {
    x = swapBits(x, i, n-i-1);
  }
  return x;
}

//Method 2
unsigned int v; // 32 bit word to reverse bit order
 
// swap odd and even bits
v = ((v >> 1) & 0x55555555) | ((v & 0x55555555) << 1);
// swap consecutive pairs
v = ((v >> 2) & 0x33333333) | ((v & 0x33333333) << 2);
// swap nibbles ... 
v = ((v >> 4) & 0x0F0F0F0F) | ((v & 0x0F0F0F0F) << 4);
// swap bytes
v = ((v >> 8) & 0x00FF00FF) | ((v & 0x00FF00FF) << 8);
// swap 2-byte long pairs
v = ( v >> 16             ) | ( v               << 16);

//method 3
int reverseBits(int num)
{
    int count = sizeof(num) * 8 - 1;
    int reverse_num = 0    
    
    while(count>=0){
    	
    	reverse_num |= (num&1)<<count;
    	count--;
    	num>>=1;
    	
    }
    
    
    return reverse_num;
}


unsigned int v;     // input bits to be reversed
unsigned int r = v; // r will be reversed bits of v; first get LSB of v
int s = sizeof(v) * CHAR_BIT - 1; // extra shift needed at end

for (v >>= 1; v; v >>= 1)
{   
  r <<= 1;
  r |= v & 1;
  s--;
}
r <<= s; // shift when v's highest bits are zero


unsigned int v;     // input bits to be reversed
unsigned int r = 0; // r will be reversed bits of v; first get LSB of v
int s = sizeof(v) * CHAR_BIT ; // extra shift needed at end

for (; v; v >>= 1)
{   
  r |= v & 1;
  r<<=1;
  s--;
}
r <<= s; // shift when v's highest bits are zero
