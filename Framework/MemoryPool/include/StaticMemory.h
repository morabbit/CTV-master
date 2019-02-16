#pragma once
#ifndef __STATICMEMORY_H
#define __STATICMEMORY_H

#include "MemoryChunk.h"
/** @ StaticMemory.h
 * 定义实现内存池
 * 采用固定大小策略进行内存管理与分配
 * 减少因大量小内存分配导致的内存碎片增加
 */



typedef struct HeapHeader
{
	size_t size;
}_Hheap;

typedef struct MemoryHeap
{
	_Hheap header;
	char pBuffer;
}_Memory;

class StaticMemory
{
public:
	void* Malloc(size_t size);

	void Free(void** pMem);

	static StaticMemory* GetInstance();

protected:
	StaticMemory();

	~StaticMemory();

protected:
	void* _malloc(size_t size);

	bool _free(void** pMem);

private:
	static StaticMemory* __m_memory__;
	/// recycle memory 
	class GC
	{
	public:
		~GC() {
			if(__m_memory__ != nullptr)
			{
				delete __m_memory__;
				__m_memory__ = nullptr;
			}
		}
		static GC gc;
	};

	/// Debug
	void __BlockCheck();

private:
	using _Chunk = MemoryChunk;
	
private:
	_Chunk** __chunk_List__;
	unsigned int __chunk_count__;	
	
	///Debug
	UintMap __m_blocksMap__;
};

#endif // !__STATICMEMORY_H

