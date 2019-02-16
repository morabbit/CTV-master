#pragma once
#ifndef __USERTOOLS_H
#define __USERTOOLS_H

#include <Windows.h>

#define _System_1MB  1024.0*1024.0
#define _System_1GB  1024.0*1024.0*1024.0

struct CPUInfo
{
public:
	CPUInfo();
	~CPUInfo();
	CPUInfo(const CPUInfo& obj);
	CPUInfo& operator=(const CPUInfo& obj);

public:
	ULONG numaNodeCount;
	ULONG processorPackageCount;
	ULONG processorCoreCount;
	ULONG logicalProcessorCount;
	ULONG processorL1CacheCount;
	ULONG processorL2CacheCount;
	ULONG processorL3CacheCount;
};

class UserTool
{
protected:
	typedef BOOL(WINAPI *LPFN_GLPI)(
		PSYSTEM_LOGICAL_PROCESSOR_INFORMATION,
		PDWORD);
	
public:
	UserTool();
	~UserTool();
	UserTool(const UserTool& obj);
	UserTool& operator=(const UserTool& obj);

public:
	static DOUBLE GetTotalPhysicalMemeoryAsMB();
	static DOUBLE GetTotalPhysicalMemeoryAsGB();
	static DOUBLE GetAvailablePhysicalMemeoryAsMB();
	static DOUBLE GetAvailablePhysicalMemeoryAsGB();
	/// just support logic core less than 64 per node and only 1 group
	/// Get logic Cores
	static ULONG GetNumberOfCPUCores();
	/// here use GetLogicalProcessorInformation , 
	/// but this function can only support 2 node 
	/// and each node's logic cores number must 
	/// less than 64, if any one node's logic 
	/// number is more than 64 , here shold be
	/// use GetLogicalProcessorInformationEx , 
	/// and the structer use PSYSTEM_LOGICAL_PROCESSOR_INFORMATION_EX
	/// however , in  domestic market ,
	/// the are less and less PC witch one node's
	/// logic core can over . so we just use current function
	void InitializeCpuInfo();
	ULONG GetCPULogicCores();
	ULONG GetCPUPhysicalCores();
	ULONG GetNumaNodeNumber();
	ULONG GetPhysicalProcessorPackages();
	ULONG GetProcessorL1Cache();
	ULONG GetProcessorL2Cache();
	ULONG GetProcessorL3Cache();

private:
	void __GetCPUInfoo();
	void __GetCacheInfo(PCACHE_DESCRIPTOR& cache);

	DWORD __GetLocalProcessorInfoBuffer();
	DWORD __CountSetBits(ULONG_PTR bitMask);
	

private:
	CPUInfo* __cpu_info__;
	PSYSTEM_LOGICAL_PROCESSOR_INFORMATION __buffer__;
};

#endif // !USERTOOLS_H
