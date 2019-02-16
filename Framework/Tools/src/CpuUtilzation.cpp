#include "pch.h"
#include "..\include\CpuUtilzation.h"
#include "FrameworkDefine.h"
#include "TraceLogExporter.h"

#pragma comment(lib,"pdh.lib")


CpuUtilzation::CpuUtilzation()
{
}

CpuUtilzation::~CpuUtilzation()
{
}


NTSTATUS
CpuUtilzation::InitCpuUtilCounters(
	PUitlContours pCpuUtilCounters, DWORD dwLogicalCore)
{
	NTSTATUS status = SUCCESSED;
	char      szProcCoreQry[200] = { 0 };

	CHECK_POINTER_AND_RETURN_FAIL_IF_NULL(pCpuUtilCounters);
	status = PdhOpenQuery(NULL, 0, &pCpuUtilCounters->hQuery);
	CHECK_EXPRESSION_AND_GOTO_EXIT((SUCCESSED == status),
		"PdhOpenQuery failed, status = 0x%x", status);

	status = PdhAddCounterA(pCpuUtilCounters->hQuery,
		"\\Processor(_Total)\\% Processor Time", 0,
		&pCpuUtilCounters->hOverallCpuUtil);
	CHECK_EXPRESSION_AND_GOTO_EXIT((SUCCESSED == status),
        "PdhAddCounter [Processor(_Total)] failed, status = 0x%x", status);

	sprintf_s(szProcCoreQry, sizeof(szProcCoreQry), 
        "\\Processor(%d)\\%% Processor Time", dwLogicalCore);

	status = PdhAddCounterA(pCpuUtilCounters->hQuery, szProcCoreQry, 0,
        &pCpuUtilCounters->hCoreCpuUtil);
    CHECK_EXPRESSION_AND_GOTO_EXIT((SUCCESSED == status),
        "PdhAddCounter [%s] failed, status = 0x%x", szProcCoreQry, status);
Exit:
	if((SUCCESSED != status) && (NULL != pCpuUtilCounters->hQuery))
	{
		PdhCloseQuery(pCpuUtilCounters->hQuery);
	}
	return status;
}

NTSTATUS 
CpuUtilzation::SnapshotCpuUtilCounters(PUitlContours pCpuUtilCounters)
{
	CHECK_POINTER_AND_RETURN_FAIL_IF_NULL(pCpuUtilCounters);
	NTSTATUS status = PdhCollectQueryData(pCpuUtilCounters->hQuery);
    CHECK_EXPRESSION_AND_RETURN_CODE((SUCCESSED == status), status,
        "PdhAddCounter failed, status = 0x%x", status);

	return SUCCESSED;
}

DWORD
CpuUtilzation::GetOverallCpuUtilCounterValue(PUitlContours pCpuUtilCounters)
{
	 PDH_FMT_COUNTERVALUE counterValcpu = { 0 };

    CHECK_EXPRESSION_AND_GOTO_EXIT(NULL != pCpuUtilCounters, 
        "GetOverallCpuUtilCounterValue: NULL pCpuUtilCounters");

    NTSTATUS status = PdhGetFormattedCounterValue(
		pCpuUtilCounters->hOverallCpuUtil, 
        PDH_FMT_LONG, 0, &counterValcpu);
    CHECK_EXPRESSION_AND_GOTO_EXIT((SUCCESSED == status),
        "PdhGetFormattedCounterValue failed, status = 0x%x", status);

Exit:
    return counterValcpu.longValue;
}

DWORD 
CpuUtilzation::GetCoreCpuUtilCounterValue(PUitlContours pCpuUtilCounters)
{
	PDH_FMT_COUNTERVALUE counterValcpu = { 0 };

    CHECK_EXPRESSION_AND_GOTO_EXIT(NULL != pCpuUtilCounters,
        "GetCoreCpuUtilCounterValue: NULL pCpuUtilCounters");

    NTSTATUS status = PdhGetFormattedCounterValue(pCpuUtilCounters->hCoreCpuUtil,
        PDH_FMT_LONG, 0, &counterValcpu);
    CHECK_EXPRESSION_AND_GOTO_EXIT((SUCCESSED == status),
        "PdhGetFormattedCounterValue failed, status = 0x%x", status);

Exit:
    return counterValcpu.longValue;
}

void CpuUtilzation::CleanupCpuUtilCounters(PUitlContours pCpuUtilCounters)
{
	if(nullptr != pCpuUtilCounters->hQuery)
	{
		PdhCloseQuery(pCpuUtilCounters->hQuery);
	}
}
