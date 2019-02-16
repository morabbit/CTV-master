#pragma once
#ifndef __MEMORYPOOL_H
#define __MEMORYPOOL_H

#include "StaticMemory.h"
/** @class ObjectManager
 * 实现利用内存池创建对象
 * 要求对象具有缺省构造函数
 */

using _Pool = StaticMemory;

template<typename _Type>
class MemoryPool
{
public:
	static _Type* Malloc(_Pool* pool, unsigned int count);

	static void Free(_Pool* pool, _Type** pobject);

};

template<typename _Type>
inline _Type * MemoryPool<_Type>::Malloc(_Pool * pool, unsigned int count)
{
	void* pobject = pool->Malloc(sizeof(_Type) * count);
	new(pobject) _Type();
	return static_cast<_Type*>(pobject);
}

template<typename _Type>
inline void MemoryPool<_Type>::Free(_Pool * pool, _Type ** pobject)
{
	if(*pobject == nullptr) return;

	(*pobject)->~T();
	pool->Free(pobject);
}


void* FWAPI HeapMalloc(_Pool * pool, unsigned int count);
void FWAPI HeapFree(_Pool * pool, void ** pobject);


#endif // !__MEMORYPOOL_H