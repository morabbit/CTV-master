#pragma once
#ifndef __FRAMEPRIVATEDEFINE_H
#define __FRAMEPRIVATEDEFINE_H
#include "MemoryManager.h"


#define MallocMemroy(count)  HeapMalloc(gPool, count);
#define FreeMemory(pointer)  HeapFree(gPool, (void**)pointer);

#endif // !__FRAMEPRIVATEDEFINE_H
