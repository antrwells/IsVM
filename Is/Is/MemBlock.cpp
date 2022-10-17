#include "pch.h"
#include "MemBlock.h"
#include <malloc.h>
MemBlock::MemBlock(size_t bsize) {

	ptr = (void*)malloc(size);
	size = bsize;

}