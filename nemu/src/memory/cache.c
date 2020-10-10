#include "common.h"
#include "burst.h"
#include "memory/cache.h"
#include <stdlib.h>

void ddr3read(hwaddr_t addr,void *data);
void ddr3write(hwaddr_t addr, void *data, uint8_t *mask);
void dram_write(hwaddr_t addr, size_t len, uint32_t data);
void cache_init() {
	int i;
	for(i=0;i<CACHE_WAY_SIZE*CACHE_SET_SIZE;i++) {
		cache[i].valid = false;	
	}
}
uint32_t cache_read(hwaddr_t addr) {
	uint32_t tag = addr>>(CACHE_SET_SIZE_B+CACHE_BLOCK_SIZE_B);
	uint32_t set = addr>>(CACHE_BLOCK_SIZE_B);
	set &= (CACHE_SET_SIZE-1);
	//uint32_t block = (addr>>CACHE_BLOCK_SIZE_B)<<CACHE_BLOCK_SIZE_B;
	int i;
	for(i=set*CACHE_WAY_SIZE;i<(set+1)*CACHE_WAY_SIZE;i++) {
		if(cache[i].valid&&cache[i].tag==tag) {
			return i;
		}
	}

	return 0;
}

