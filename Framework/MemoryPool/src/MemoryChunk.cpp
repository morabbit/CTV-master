#include "pch.h"
#include "MemoryChunk.h"
#include <cassert>

MemoryChunk::MemoryChunk(size_t size, unsigned int count)
{
	INITMUTEX(__mutex__);
	this->__free_list__ = NULL;
	this->__size__ = size;
	this->__count__ = 0;

	_block* __block;
	while(count--)
	{
		__block = _CreateBlock();
		if(!__block)break;
		__block->data.pNext = __free_list__;
		__free_list__ = __block;
	}
}

MemoryChunk::~MemoryChunk()
{
	int __tempcount = 0;
	_block* __block;
	while(__block = __free_list__)
	{
		__free_list__ = __block->data.pNext;
		_DeleteBlock(__block);
		++__tempcount;
	}
	//make sure all the memory  was released
#ifdef _DEBUG
	assert(__tempcount == __count__);
#else
	printf("there are [%d] block memory not release", __count__ - __tempcount);
#endif // _DEBUG	
	DELMUTEX(__mutex__);
}

void * MemoryChunk::malloc()
{
	_block* __block;
	LOCK(__mutex__);
	if(__free_list__)
	{
		__block = __free_list__;
		__free_list__ = __block->data.pNext;
	}
	else
	{
		if(!(__block = _CreateBlock()))
		{
			UNLOCK(__mutex__);
			return NULL;
		}
	}
	UNLOCK(__mutex__);
	return &__block->data.pBuffer;
}

void MemoryChunk::free(void ** pMem)
{
	_block* __block = (_block*)((char*)(*pMem) - sizeof(_Header));
	__block->header.pChunk->free(__block);
	*pMem = nullptr;
}

void MemoryChunk::free(_block * pBlock)
{
	LOCK(__mutex__);
	pBlock->data.pNext = __free_list__;
	__free_list__ = pBlock;
	UNLOCK(__mutex__);
}

_block * MemoryChunk::_CreateBlock()
{
	_block* __block = (_block*)::malloc(sizeof(_Header) + __size__);

	if(__block)
	{
		__block->header.pChunk = this;
		__block->header.length = __size__;
		++__count__;
	}

	return __block;
}

void MemoryChunk::_DeleteBlock(_block * pBlock)
{
	::free(pBlock);
}

unsigned int MemoryChunk::linkListLength()
{
	unsigned int __length = 0;
	_block* ptr = __free_list__;
	while(nullptr != ptr)
	{
		__length++;
		ptr = ptr->data.pNext;
	}

	return __length;
}
