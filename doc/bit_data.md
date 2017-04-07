# Calculate whether a input is included large dataset

* 10B black list URL, each URL is 64B or less, design a system to detect whether a URL is in black list.

* requirements: 1: 0.01% error rate is allowed, 2: 30G extra space

## Hash Function

* same input -> same out
* different inputs could have same out
* Input range could be much larger than out, output should be roughly distributed equally in all out space

> If we solve this using hash Function

Hash(URL) %M -> file: next step is to find whether the URL is in file

* Use hash to filter out
* simple and easy, but needs at least 640G space(64B * 10B)

## Bloom Filter

### Idea:

1. A large bit array:

2. length is m, suppose we have input, set bit to 1 in position __*hash(input)%m*__

3. when a new input comes, run the same __*hash(input)%m*__ to find bit position,
 * if it is not set to 1, then it is definitely not in set
 * if it is set to 1, not sure whether it is in set

### Bloom filter design


1. Same idea as before: but we could have multiple hash functions to Calculate mutiple bit positions
2. when new input comes, run all hash functions.
  * if one of the bit position is not set, then input is not in set
  * if all bit positions are set, it is still possible input may not be in set

### Math

how many hash functions we need, how large is bit vector

* Given:

> n: how many items you expect to have in your filter (e.g. 20B)

> p: your acceptable false positive rate {0..1} (e.g. 0.0001 → 0.01%)

* we want to calculate:

> m: the number of bits needed in the bloom filter

> k: the number of hash functions we should apply

* The formulas:

> m = -n*ln(p) / (ln(2)^2) the number of bits

> k = m/n * ln(2) the number of hash functions


### Pros

* No missed detection, if it is in set, definitely being detected
* only false alarm, miss detected even if it is not in set
* size of input(64B or 640B) dose not matter, only number of input matters

# Hash Parse: put input with same hash value into same small file

* Resource constrained,
* use (hash + mod) to parse the large input into small files in case memory is not enough to store all input.
* Hash parse to ensure that same input should be in same file(Because hashed value )

## Calculate highest frequency in large dataset, 2G memory, calculate highest frequency number in 2B int input (int is 32 bits)

if we use hash, one record is 4 bytes key and 4 bytes value. 2B*8 = 16B memory

* Hash to parse, split the large file into small files (64 files)
* in each file run, calculate highest frequent in each file, then among these 64 largest value, get the largest

# Bitmap

> requirements

* Calculate missing number
* input is 4B 32bits int
* constrain: maximum 1G memory

> Hash

only need key, space is 4B*4 = 16G bits memory, can not use hash

> Solution

use bitmap: 4B/8 = 500M bytes memory

```CPP
len = 2^32/8;
vector<int> bitvector(len,0);
```

> Followup, only 10M memory, but can only detect one missing one: range counter

* split the 2^32 number into m different input ranges.
* every range has counters, counter ++ when a number appears
* there is at least one range, in which counter is smaller than range size. missing number is inside
* use same bitmap technique. 10M*8 = 80M bits, so we can split 4B/80M = 50 ranges

# Duplicate and Top K problems

* A big file with 10B URL, find all duplicate URLs and top K URLs

* Hash parse, __*hash(url)*__, then write into different files, calculate each files' URL occurence: Noticing through hash parse, same URLs will be categorized in same small file

* for each small file. get the highest URL occurence, then build up a min heap of size K, put each file's highest URL occurence into heap.

## 40B positive 32 bits int, find int that appears twice.

use two bits to represent how many times a int appears.
00-> 0 times. 01 -> 1 times, 10-> 2 times, 11 -> more than 2 times

* find median value in 40B int via 10M memory

1. parse the 40B into m ranges, counts occurence in each range.
2. accumulate all occurence, locate the 20B-th int appears in which range

```CPP
//suppose num = 40B

int findMedian(vector<int> num){
//since memory is 10M, we need to split into
  int ret = 0;
  int len = 2^10 //(40*2^30)/(10*2^20*4)
  vector<int> occur(len,0);
  for(int i=0;i<num.size();i++){
    int index = num[i]/len;
    occur[index]++;
  }
  int target = 20*2^30; //medium value
  int cnts = 0;
  int i;
  for(i=0;i<len;i++){
    cnts+=occur[i];
    if(cnts>=taregt)
      break;
  }

  len = 10*2^20*4//range size
  int begin = len*i; //range begin number
  int end = begin + len; //range end number
  cnts -= occur[i]; //how many numbers before i's range
  occur.resize(len,0);
  for(int i=0;i<len;i++){
    if(nums[i]>=begin && nums[i]<end){
      cnts++;
      if(cnts==target){
        ret = nums[i];
        break;
      }

    }
  }
  return ret;
}
```

# Consistent Hash

* in distributed system, need to locate which machine locate which information
* drawback of hash: input % m to 0->m-1 machine, but if machine increase or decrease, all input needs to be re hashed

## Basic

* Every machine has a hashed value
* for a input, calculate which machine it needs to be put via binary  search. all machines hashed values can be considered as array

* How to distribute equally
> Use virtual node

```
T1: V1,V2...V100
T2: V101, V102...V200
```
The front end maintain a physical node -> virtual node mapping. and also all the hashed value for virtual nodes(routing)

if new node added, all virtual nodes are added, and virtual nodes get data from nearby virtual nodes(from virtual find physical node)


### Design UUID

* only one machine generating UUID. and then assign to later sub nodes based on country, then sub-sub nodes based on region. etc.
* The root machine has a base and range.
* country machine ask UUID from root, root give the base + range. then region ask UUID base + range from country



# Bit Operation

* Swap without extra memory
```CPP
void swapNoextra(int a, int b){
  //idea is to know difference between a and b, use XOR to find difference
  a = a^b;  // a becomes difference between a and b
  b = b^a;  // b becomes a, a is still difference between a and b
  a = a^b;  //
}
```

* return larger between a and b(32 bits), without comparison
```CPP
int flip(int n){
  return n^1;
}

int sign(int n){
  //positive: 1. negative: 0
  return flip((n>>31)&1);
}

int getmax(int a, int b){
  //map overflow
  int c = a-b;
  int sA = sign(c);
  int sB = flip(sA);
  return return a * sA + b * sB;
}
```

* Calculate number of 1

```CPP
int numofOnes(int n){
  int res = 0;
  while (n != 0) {
    res += n & 1;
    n >>= 1;
  }
  return res;
}
```

* Odd and Even
```CPP
//in array, only one appears odd, others are even
int findOdd(vector<int> in){
  int ret = 0;
  for(auto i:in){
    ret = ret^i;
  }
  return ret;
}

//if two numbers appear odd, others are even
pair<int,int> findOdd2(vector<int> in){
  int e = 0;
  for(auto i:in){
    e = e^i;
  }
  //e is a^b;
  int rightone = e &(~e+1); //get the right most 1, suppose k
  //XOR, for number that k position is 1.
  for (auto cur : in) {
    if ((cur & rightOne) != 0) {
      ehasOne ^= cur;
    }
  }

  return make_pair(ehasOne,e^ehasOne);
}
```

* Followup: one number appear 1 time, others k times.
```CPP

```
