#include "pch.h"
#include "MemoryPool.h"


void* FWAPI HeapMalloc(_Pool * pool, unsigned int count)
{
	return pool->Malloc(count);
}

void FWAPI HeapFree(_Pool * pool, void ** pobject)
{
	if(*pobject == nullptr) return;
	pool->Free(pobject);
}
