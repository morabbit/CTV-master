#pragma once
#ifndef __MEMORYPRIVATEHEAD_H
#define __MEMORYPRIVATEHEAD_H


#include "FrameworkType.h"
#include "FrameworkCommon.h"

typedef CRITICAL_SECTION MUTEXTYPE;
#define INITMUTEX(hMutex) InitializeCriticalSection(&hMutex)
#define DELMUTEX(hMutex) DeleteCriticalSection(&hMutex)
#define LOCK(hMutex) EnterCriticalSection(&hMutex)
#define UNLOCK(hMutex) LeaveCriticalSection(&hMutex)


#define Byte_1          unsigned long long(1)
#define KB          unsigned long long(1024 *   Byte_1)
#define B_16        unsigned long long(16   *   Byte_1)
#define B_32        unsigned long long(32   *   Byte_1)
#define B_64        unsigned long long(64   *   Byte_1)
#define B_128       unsigned long long(128  *   Byte_1)
#define B_256       unsigned long long(256  *   Byte_1)
#define B_512       unsigned long long(512  *   Byte_1)
#define KB_1        unsigned long long(1    *   KB)
#define KB_2        unsigned long long(2    *   KB)
#define KB_4        unsigned long long(4    *   KB)
#define KB_8        unsigned long long(8    *   KB)
#define KB_16       unsigned long long(16   *   KB)
#define KB_32       unsigned long long(32   *   KB)
#define KB_64       unsigned long long(64   *   KB)
#define MB          unsigned long long(1024 *   KB)
#define MB_1        unsigned long long(1    *   MB)
#define MB_100      unsigned long long(100  *   MB)
#define MB_800      unsigned long long(800  *   MB)
#define GB          unsigned long long(1024 *   MB)
#define GB_1        unsigned long long(1    *   GB)

const unsigned long long cMemorySizeList[] = {
	B_16  , B_32 , B_64  , B_128 , B_256, B_512 ,
	KB_1  , KB_2 , KB_4  , KB_8  , KB_16, KB_32 ,
	KB_64 , MB_1 , MB_100, MB_800, GB_1  };


#endif // !__MEMORYPRIVATEHEAD_H
