#include "pch.h"
#include "..\include\CommonTools.h"
#include "TraceLogExporter.h"
#include "FrameworkDefine.h"

CommonTools::CommonTools()
{
}

CommonTools::~CommonTools()
{
}

LONGLONG CommonTools::sampleCodeTimestamp(void)
{
	LARGE_INTEGER li = { 0 };
	if(!QueryPerformanceCounter(&li))
	{
		PRINT_ERR("QueryPerformanceCounter failed, GetLastError() returned %d",
				  GetLastError());
		return 0;
	}

	return li.QuadPart;
}

void CommonTools::sampleCodeSleep(DWORD seconds)
{
	sampleCodeSleepMilliSec(seconds * 1000);
}

void CommonTools::sampleCodeSleepMilliSec(DWORD milliseconds)
{
	Sleep(milliseconds);
}

DWORD CommonTools::sampleCodeGetCpuFreq(void)
{
	LARGE_INTEGER lpFrequency;

	if(!QueryPerformanceFrequency(&lpFrequency))
	{
		PRINT_ERR("QueryPerformanceFrequency failed, GetLastError() returned %d",
				  GetLastError());
		return 0;
	}

	return lpFrequency.LowPart;
}

NTSTATUS
CommonTools::sampleCodeThreadBind(
	sample_code_thread_t * thread, DWORD logicalCore)
{
	DWORD_PTR mask = (DWORD_PTR)1 << logicalCore;
	DWORD_PTR retVal = SetThreadAffinityMask(*thread, mask);

	 CHECK_EXPRESSION_AND_RETURN_FAIL((0 != retVal),
        "SetThreadAffinityMask failed(), GetLastError() returned: %d",
        GetLastError());

	return SUCCESSED;
}

DWORD CommonTools::SnapshotPhyMemInUseInMB(void)
{
	MEMORYSTATUSEX memStatus = { 0 };
	memStatus.dwLength = sizeof(MEMORYSTATUSEX);
	GlobalMemoryStatusEx(&memStatus);

	return (DWORD)((memStatus.ullTotalPhys - memStatus.ullAvailPhys) / ONE_MB);
}

DWORD CommonTools::sampleCodeGetNumberOfCpus(void)
{
	SYSTEM_INFO si = { 0 };
	GetSystemInfo(&si);

	return si.dwNumberOfProcessors;
}

