#include "pch.h"
#include <iostream>
#include "StaticMemory.h"


/// define a static area varlable to recycle
///memory pool memory while those app finished 
StaticMemory::GC StaticMemory::GC::gc;
/////init memory poor
//StaticMemory* StaticMemory::m_memory__ = new StaticMemory;

StaticMemory::StaticMemory()
{
	__chunk_count__ = 0;
	for(size_t i = 0; i < ARRAYSIZE(cMemorySizeList); i++)++__chunk_count__;
	__chunk_List__ = new _Chunk*[__chunk_count__];

	int __index = 0;
	unsigned int __count = 1000;
	for(size_t i = 0; i < ARRAYSIZE(cMemorySizeList); i++)
	{
		if(cMemorySizeList[i] <= KB_1) __count = 600;
		else if(cMemorySizeList[i] <= KB_8) __count = 400;
		else if(cMemorySizeList[i] <= MB_1) __count = 200;
		else if(cMemorySizeList[i] == MB_100) __count = 8;
		else if(cMemorySizeList[i] == MB_800) __count = 4;
		else __count = 2;

#ifdef _DEBUG
		__m_blocksMap__.insert(std::make_pair(__index, __count));/// Debug
#endif // _DEBUG		
		__chunk_List__[__index++] = new _Chunk(cMemorySizeList[i], __count);
	}
}

StaticMemory::~StaticMemory()
{
#ifdef _DEBUG
	__BlockCheck();
#endif // _DEBUG

	for(unsigned int index = 0; index < __chunk_count__; ++index)
	{
		delete __chunk_List__[index];
	}
	delete[] __chunk_List__;
}

void * StaticMemory::Malloc(size_t size)
{
	if(size > GB) {
		return malloc(size);
	}
	int index = 0;
	for(size_t i = 0; i < ARRAYSIZE(cMemorySizeList); i++) 
	{
		if(cMemorySizeList[i] >= size)break;
		++index;
	}
	return __chunk_List__[index]->malloc();
}

void StaticMemory::Free(void ** pMem)
{
	if(!_free(pMem))_Chunk::free(pMem);
}

StaticMemory * StaticMemory::GetInstance()
{
	return __m_memory__;
}

/// Debug
void StaticMemory::__BlockCheck()
{
	std::cout << "0  chunk memory size: [ 16 ] \n";
	std::cout << "1  chunk memory size: [ 32 ] \n";
	std::cout << "2  chunk memory size: [ 64 ] \n";
	std::cout << "3  chunk memory size: [ 128 ] \n";
	std::cout << "4  chunk memory size: [ 256 ] \n";
	std::cout << "5  chunk memory size: [ 512 ] \n";
	std::cout << "6  chunk memory size: [ 1024 ] \n";
	std::cout << "7  chunk memory size: [ 2048 ] \n";
	std::cout << "8  chunk memory size: [ 4096 ] \n";
	std::cout << "9  chunk memory size: [ 8192 ] \n";
	std::cout << "10 chunk memory size: [ 16384 ] \n";
	std::cout << "11 chunk memory size: [ 32768 ] \n";
	std::cout << "12 chunk memory size: [ 65536 ] \n";
	std::cout << "13 chunk memory size: [ 1048576 ] \n";
	std::cout << "14 chunk memory size: [ 104857600 ] \n";
	std::cout << "15 chunk memory size: [ 838860800 ] \n";
	std::cout << "16 chunk memory size: [ 1073741824 ] \n";

	using Iter = UintMap::iterator;
	for(Iter _it_ = __m_blocksMap__.begin(); _it_ != __m_blocksMap__.end(); _it_++)
	{
		long length = __chunk_List__[_it_->first]->linkListLength();
		if(length != _it_->second)
		{
			std::cout << _it_->first << " chunk memory has: " << abs((long)_it_->second - length)
				<< " block(s) memory not released. total number: "
				<< _it_->second << ", but actural number: " << length << " \n";
		}
	}
}

void * StaticMemory::_malloc(size_t size)
{
	_Memory* __heap = (_Memory*)::malloc(sizeof(_Hheap) + size);
	if(__heap) 
	{
		__heap->header.size = size;
		return &__heap->pBuffer;
	}
	return nullptr;
}

bool StaticMemory::_free(void ** pMem)
{
	_Memory* __heap = (_Memory*)((char*)(*pMem) - sizeof(_Hheap));
	if(__heap->header.size > GB_1)
	{
		::free(__heap);
		return true;
	}
	return false;
}

