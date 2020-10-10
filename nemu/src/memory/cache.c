#include "common.h"
#include "burst.h"
#include "memory/cache.h"
#include <stdlib.h>

void ddr3read(hwaddr_t addr,void *data);
void cache_init() {
	int i;
	for(i=0;i<CACHE_WAY_SIZE*CACHE_SET_SIZE;i++) {
		cache[i].valid = false;	
	}
}

