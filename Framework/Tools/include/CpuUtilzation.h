#pragma once
#ifndef __CPUUTILZATION_H
#define __CPUUTILZATION_H
#include <pdh.h>
#include <pdhmsg.h>
#include "FrameworkType.h"

typedef struct _CPU_UTIL_COUNTERS
{
	DWORD dwLogicalCore;
	HANDLE hQuery;
	HANDLE hOverallCpuUtil;
	HANDLE hCoreCpuUtil;

}UitlContours, *PUitlContours ;

class CpuUtilzation
{
public:
	CpuUtilzation();
	~CpuUtilzation();

public:
	
	static 
		NTSTATUS
		InitCpuUtilCounters(
			PUitlContours pCpuUtilCounters,
			DWORD dwLogicalCore
	);

	static
		NTSTATUS 
		SnapshotCpuUtilCounters(
			PUitlContours pCpuUtilCounters
	);

	static 
		DWORD
		GetOverallCpuUtilCounterValue(
			PUitlContours pCpuUtilCounters
	);

	static
		DWORD
		GetCoreCpuUtilCounterValue(
			PUitlContours pCpuUtilCounters
	);

	static
		void 
		CleanupCpuUtilCounters(
			PUitlContours pCpuUtilCounters
	);

private:

};


#endif // !__CPUUTILZATION_H
