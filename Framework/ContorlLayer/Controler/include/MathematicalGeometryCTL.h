#pragma once
#ifndef __MATHEMATICALGEOMETRYCTL_H
#define __MATHEMATICALGEOMETRYCTL_H
#include "FrameWorkType.h"
#include "CommonImageFilterCtl.hxx"

class MathematicalCTL
{
public:
	MathematicalCTL();
	~MathematicalCTL();
	MathematicalCTL(const MathematicalCTL&);
	MathematicalCTL& operator=(const MathematicalCTL&);

public:

	NTSTATUS GetStatus();
	_String GetErrorMessage();

private:
	_StrStm_ __err_msg__;
	NTSTATUS __status__;
	MathematicalGeometry* __math__obj__;
};


#endif // !__MATHEMATICALGEOMETRYCTL_H

