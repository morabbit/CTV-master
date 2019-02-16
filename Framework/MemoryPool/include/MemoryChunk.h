#pragma once
#ifndef __MEMORYCHUNK_H
#define __MEMORYCHUNK_H

#include "MemoryPrivateHeader.h"


class MemoryChunk;

/** @struct MemoryBlock
 *
 */
typedef struct BlockHeader
{
	MemoryChunk* pChunk;
	size_t length;
}_Header;

struct _block;

typedef struct BlockData
{
	union {
		_block* pNext;
		char pBuffer;
	};
}_Data;

struct _block
{
	_Header header;
	_Data data;
};

/** @class MemoryChunk
 *
 */

class MemoryChunk
{
public:
	MemoryChunk(size_t size, unsigned int count = 1000);

	~MemoryChunk();

	void* malloc();

	static void free(void** pMem);

	void free(_block* pBlock);

	MemoryChunk* Next() { return __next__; }
	///debug
	unsigned int linkListLength();

protected:
	_block* _CreateBlock();
	void _DeleteBlock(_block* pBlock);

private:
	//!Block number
	int __count__;
	//!Block size
	size_t __size__;
	MUTEXTYPE __mutex__;
	MemoryChunk* __next__;
	_block* __free_list__;
};

#endif // !__MEMORYCHUNK_H

