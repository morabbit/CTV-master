#include "pch.h"
#include "FrameworkErrorCode.h"
#include "FrameCommonFunctionMacro.h"
#include "TraceLogExporter.h"

#include "..\include\MathematicalGeometryCTL.h"


MathematicalCTL::MathematicalCTL()
{
}

MathematicalCTL::~MathematicalCTL()
{
}

MathematicalCTL::MathematicalCTL(const MathematicalCTL& __obj)
{
	*this = __obj;
}

MathematicalCTL& MathematicalCTL::operator=(const MathematicalCTL& __obj)
{
	this->__status__ = __obj.__status__;
	this->__err_msg__ = _StrStm_();
	this->__err_msg__ << __obj.__err_msg__.str();

	this->__math__obj__ = __obj.__math__obj__;
	return *this;
}

NTSTATUS MathematicalCTL::GetStatus()
{
	return __status__;
}

_String MathematicalCTL::GetErrorMessage()
{
	return __err_msg__.str();
}
