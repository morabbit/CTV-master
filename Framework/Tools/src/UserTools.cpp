#include "pch.h"
#include "TraceLogExporter.h"
#include "..\include\UserTools.h"

#if !defined (_WIN32) && !defined (_WIN64)
#define LINUX
#include <sysconf.h>
#else
#define WINDOWS
#include <windows.h>
#endif


CPUInfo::CPUInfo()
{
	this->numaNodeCount = 0;
	this->processorPackageCount = 0;
	this->processorCoreCount = 0;
	this->logicalProcessorCount = 0;
	this->processorL1CacheCount = 0;
	this->processorL2CacheCount = 0;
	this->processorL3CacheCount = 0;
}

CPUInfo::~CPUInfo()
{
}

CPUInfo::CPUInfo(const CPUInfo & obj)
{
	*this = obj;
}

CPUInfo & CPUInfo::operator=(const CPUInfo & obj)
{
	this->numaNodeCount = obj.numaNodeCount;
	this->processorPackageCount = obj.processorPackageCount;
	this->processorCoreCount = obj.processorCoreCount;
	this->logicalProcessorCount = obj.logicalProcessorCount;
	this->processorL1CacheCount = obj.processorL1CacheCount;
	this->processorL2CacheCount = obj.processorL2CacheCount;
	this->processorL3CacheCount = obj.processorL3CacheCount;

	return *this;
}


UserTool::UserTool()
{
	__buffer__ = nullptr;
	__cpu_info__ = new CPUInfo;
}

UserTool::~UserTool()
{
	delete __cpu_info__;
}

UserTool::UserTool(const UserTool & obj)
{
	*this = obj;
}

UserTool & UserTool::operator=(const UserTool & obj)
{
	this->__buffer__ = obj.__buffer__;
	this->__cpu_info__= obj.__cpu_info__;

	return *this;
}

DOUBLE UserTool::GetTotalPhysicalMemeoryAsMB()
{
	MEMORYSTATUS ms;
	::GlobalMemoryStatus(&ms);
	return ((DOUBLE)ms.dwTotalPhys / _System_1MB);
}

DOUBLE UserTool::GetTotalPhysicalMemeoryAsGB()
{
	MEMORYSTATUS ms;
	::GlobalMemoryStatus(&ms);
	return ((DOUBLE)ms.dwTotalPhys / _System_1GB);
}

DOUBLE UserTool::GetAvailablePhysicalMemeoryAsMB()
{
	MEMORYSTATUS ms;
	::GlobalMemoryStatus(&ms);
	return ((DOUBLE)ms.dwAvailPhys / _System_1MB);
}

DOUBLE UserTool::GetAvailablePhysicalMemeoryAsGB()
{
	MEMORYSTATUS ms;
	::GlobalMemoryStatus(&ms);
	return ((DOUBLE)ms.dwAvailPhys / _System_1GB);
}

ULONG UserTool::GetNumberOfCPUCores()
{
	ULONG cores = 1;
#if defined (LINUX)
	cores = sysconf(_SC_NPROCESSORS_CONF);
#elif defined (WINDOWS)
	SYSTEM_INFO si;
	GetSystemInfo(&si);
	cores = si.dwNumberOfProcessors;
#endif
	return cores;
}

void UserTool::InitializeCpuInfo()
{
	__GetCPUInfoo();
}

ULONG UserTool::GetCPULogicCores()
{
	return __cpu_info__->logicalProcessorCount;
}

ULONG UserTool::GetCPUPhysicalCores()
{
	return __cpu_info__->processorCoreCount;
}

ULONG UserTool::GetNumaNodeNumber()
{
	return __cpu_info__->numaNodeCount;
}

ULONG UserTool::GetPhysicalProcessorPackages()
{
	return __cpu_info__->processorPackageCount;
}

ULONG UserTool::GetProcessorL1Cache()
{
	return __cpu_info__->processorL1CacheCount;
}

ULONG UserTool::GetProcessorL2Cache()
{
	return __cpu_info__->processorL2CacheCount;
}

ULONG UserTool::GetProcessorL3Cache()
{
	return __cpu_info__->processorL3CacheCount;
}

void UserTool::__GetCPUInfoo()
{
	DWORD byteOffset = 0;
	PCACHE_DESCRIPTOR Cache;
	DWORD len = __GetLocalProcessorInfoBuffer();
	PSYSTEM_LOGICAL_PROCESSOR_INFORMATION ptr = __buffer__;
	while(byteOffset + sizeof(SYSTEM_LOGICAL_PROCESSOR_INFORMATION) <= len)
	{
		switch(ptr->Relationship)
		{
			case RelationNumaNode:
				__cpu_info__->numaNodeCount++;
				break;
			case RelationProcessorCore:
				__cpu_info__->processorCoreCount++;
				__cpu_info__->logicalProcessorCount +=
					__CountSetBits(ptr->ProcessorMask);
				break;
			case RelationCache:
				Cache = &ptr->Cache;
				__GetCacheInfo(Cache);
				break;
			case RelationProcessorPackage:
				__cpu_info__->processorPackageCount++;
				break;
			default:
				TraceLog << "\nError: Unsupported LOGICAL_PROCESSOR_RELATIONSHIP value.\n";
				break;
		}
		byteOffset += sizeof(SYSTEM_LOGICAL_PROCESSOR_INFORMATION);
		ptr++;
	}
	free(__buffer__);
}

DWORD UserTool::__GetLocalProcessorInfoBuffer()
{
	LPFN_GLPI glpi;
	DWORD length = 0;
	glpi = (LPFN_GLPI)GetProcAddress(GetModuleHandle(TEXT("kernel32")),
									 "GetLogicalProcessorInformation");
	if(NULL == glpi)
	{
		TraceLog << "\nGetLogicalProcessorInformation is not supported.\n";
		return 0;
	}

	while(1)
	{
		DWORD rc = glpi(__buffer__, &length);
		if(TRUE == rc)
		{
			break;
		}
		if(GetLastError() != ERROR_INSUFFICIENT_BUFFER)
		{
			TraceLog << "\nError = " << GetLastError();
			return length;
		}

		if(__buffer__)
		{
			free(__buffer__);
		}

		__buffer__ = (PSYSTEM_LOGICAL_PROCESSOR_INFORMATION)malloc(length);

		if(NULL == __buffer__)
		{
			TraceLog << "\nError: Allocation failure\n";
			return length;
		}
	}

	return length;
}

DWORD UserTool::__CountSetBits(ULONG_PTR bitMask)
{
	DWORD bitSetCount = 0;
	DWORD LSHIFT = sizeof(ULONG_PTR) * 8 - 1;	
	ULONG_PTR bitTest = (ULONG_PTR)1 << LSHIFT;
	DWORD i;

	for(i = 0; i <= LSHIFT; ++i)
	{
		bitSetCount += ((bitMask & bitTest) ? 1 : 0);
		bitTest /= 2;
	}

	return bitSetCount;
}

void UserTool::__GetCacheInfo(PCACHE_DESCRIPTOR& Cache)
{
	if(Cache->Level == 1)
	{
		__cpu_info__->processorL1CacheCount++;
	}
	else if(Cache->Level == 2)
	{
		__cpu_info__->processorL2CacheCount++;
	}
	else if(Cache->Level == 3)
	{
		__cpu_info__->processorL3CacheCount++;
	}
}
