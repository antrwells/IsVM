#pragma once
class MemBlock
{
public:
	MemBlock(size_t size);
	void* ptr;
	size_t size;
};

