#pragma once
#ifndef __CPIINFORMATIONTOOLS_H
#define __CPIINFORMATIONTOOLS_H
#include "FrameworkType.h"

#define ONE_MB (1024 * 1024)
#define sample_code_thread_t   HANDLE

class CommonTools
{
public:
	CommonTools();
	~CommonTools();

	static
		LONGLONG
		sampleCodeTimestamp(void);

	static
		void
		sampleCodeSleep(DWORD seconds);

	static
		void
		sampleCodeSleepMilliSec(DWORD milliseconds);

	static
		DWORD
		sampleCodeGetCpuFreq(void);

	static
		NTSTATUS
		sampleCodeThreadBind(
			sample_code_thread_t *thread,
			DWORD logicalCore
		);

	static
		DWORD
		SnapshotPhyMemInUseInMB(void);

	static
		DWORD
		sampleCodeGetNumberOfCpus(void);

private:

};

#endif // !__CPIINFORMATIONTOOLS_H
