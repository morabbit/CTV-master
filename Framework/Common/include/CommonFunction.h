#pragma once
#ifndef __COMMONFUNCTION_H
#define __COMMONFUNCTION_H
#include "FrameworkType.h"

enum StripType
{
	BOTHSTRIP,
	LEFTSTRIP,
	RIGHTSTRIP
};
class DOC
{
public:
	DOC();
	~DOC();

	static
		_String
		do_strip(
			const _String &str,
			const _String&chars,
			INT striptype
			);
	static
		void 
		deleteAllMark(
			_String &src,
			const _String &mark
		);
private:

};

_String replace(_String& str, const _String& src_str, const _String& tar_str,UINT cout=0);
_String strip(_String& src, const _String& chars=" ");
_String lrstrip(_String& src, const _String& chars=" ");
_String lstrip(_String& src, const _String& chars=" ");
_String rstrip(_String& src, const _String& chars=" ");

#endif // !__COMMONFUNCTION_H
