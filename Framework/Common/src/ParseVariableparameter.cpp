#include "pch.h"
#include "ParseVariableparameter.h"


ParseVariables::ParseVariables()
{
}

ParseVariables::~ParseVariables()
{
}


_StrStm_ ParseVariables::var_param(_CPCH_ fmt, va_list __args)
{
	_StrStm_ __mes;

	while(*fmt) {
		if(*fmt == '%' && *(++fmt) != '%')
			__mes << __parse_vars__(*fmt++, __args).str();
		else __mes << *fmt++;
	}

	return __mes;
}

_StrStm_ ParseVariables::__parse_dec__(_Int_ dec)
{
	_StrStm_ __mes;
	if(dec == 0)
		return __mes;

	__mes << __parse_dec__(dec / 10).str();
	__mes << (char)(dec % 10 + '0');
	return __mes;
}

_StrStm_ ParseVariables::__parse_flt__(_dbl_ flt)
{
	_StrStm_ __mes;
	int __tp = 0;

	__tp = (_Int_)flt;
	__mes << __parse_dec__(__tp).str() << ".";

	flt = flt - __tp;

	__tp = (_Int_)(flt * 10000000000);
	__mes << __parse_dec__(__tp).str();

	return __mes;
}

_StrStm_ ParseVariables::__parse_bin__(_Int_ bin)
{
	_StrStm_ __mes;

	if(bin == 0) {
		__mes << "0b";
		return __mes;
	}
	__mes << __parse_bin__(bin / 2).str();
	__mes << (_CH_)(bin % 2 + '0');

	return __mes;
}

_StrStm_ ParseVariables::__parse_hex__(_Int_ hex)
{
	_StrStm_ __mes;
	if(hex == 0) {
		__mes << "0x";
		return __mes;
	}
	__mes << __parse_hex__(hex / 16).str();
	hex = hex % 16;

	if(hex < 10)
		__mes << (char)(hex + '0');
	else
		__mes << (char)(hex - 10 + 'A');

	return __mes;
}

_StrStm_ ParseVariables::__parse_oct__(_Int_ oct)
{
	_StrStm_ __mes;

	if(oct == 0) {
		__mes << "0";
		return __mes;
	}
	__mes << __parse_oct__(oct / 8).str();
	oct = oct % 8;
	__mes << oct;

	return __mes;
}

_StrStm_ ParseVariables::__parse_vars__(_CH_ c, va_list & args)
{
	_StrStm_ __mes;

	switch(c)
	{
		case 'i':
		case 'd':
			__mes << va_arg(args, _Int_);
			break;
		case 'h':
		case 'x':
			__mes << __parse_hex__(va_arg(args, int)).str();
			break;
		case 'b':
			__mes << __parse_bin__(va_arg(args, int)).str();
			break;
		case 'c':
			__mes << va_arg(args, char);
			break;
		case 'f':
			__mes << std::fixed << va_arg(args, double);
			break;
		case 's':
			__mes << va_arg(args, char*);
			break;
		case 'o':
			__mes << __parse_oct__(va_arg(args, int)).str();
			break;
		default:
			__mes << "Input control character error !";
			break;
	}
	return __mes;
}
