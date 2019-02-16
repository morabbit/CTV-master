#pragma once
#ifndef __PARSEVARIABLEPARAMETER_H
#define __PARSEVARIABLEPARAMETER_H
#include "FrameWorkType.h"

class ParseVariables
{
public:
	ParseVariables();
	~ParseVariables();

private:
	using _Int_    = int;
	using _CH_     = char;
	using _PCH_    = char*;
	using _dbl_    = double;
	using _CPCH_   = const char * ;

public:
	static _StrStm_ var_param(_CPCH_ fmt, va_list __args);

private:
	static _StrStm_ __parse_dec__(_Int_ dec);  // decimalism integer
	static _StrStm_ __parse_flt__(_dbl_ flt);  // decimals
	static _StrStm_ __parse_bin__(_Int_ bin);  // binary
	static _StrStm_ __parse_hex__(_Int_ hex);  // hexadecimal
	static _StrStm_ __parse_oct__(_Int_ oct);  // octonary
	static _StrStm_ __parse_vars__(_CH_ c, va_list& args);

};


#endif // !__PARSEVARIABLEPARAMETER_H
