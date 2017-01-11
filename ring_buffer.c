//implement ringbuffer in c
/*
From Wiki:
A circular buffer, circular queue, cyclic buffer or ring buffer is a data structure that uses a single, fixed-size buffer as if it were connected end-to-end. This structure lends itself easily to buffering data streams.
Ring buffer is widely used in DMA
*/

/*
Ring buffer
*/
#define buffer_size C_SIZE
typedef ringbuffer_t{
	item[C_SZIE];
	int read;
	int write;
}ringBuffer;

ringBuffer *RB;

uint buffer_init(){
	RB = (ringBuffer*)malloc(sizeof(ringBuffer));
	if(RB==NULL)
		return -1;
}

uint free_buffer(ringBuffer *rb){
	if(rb==NULL)
		return -1;
	free(rb);
}

uint push(item in){
	if(read==(write+1)%C_SIZE){
		//buffer full, can not write any more
		return -1;
	}
	RB->item[write]=in;
	write = (write+1)%C_SIZE;
}

uint pop(item &out){
	if(read==write){
		//buffer is empty
		return -2;
	}
	out = RB->item[read];
	read = (read+1)%C_SIZE;
}

