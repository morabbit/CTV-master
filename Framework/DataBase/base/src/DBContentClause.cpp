#include "pch.h"
#include "DBContentClause.h"
#include "ParseVariableparameter.h"


ContentCaluse::ContentCaluse()
{
	__used_cls__ = 0;
	__caluse__ << " where ";
}

ContentCaluse::~ContentCaluse()
{
}

ContentCaluse::ContentCaluse(const ContentCaluse & obj)
{
	*this = obj;
}

ContentCaluse & ContentCaluse::operator=(const ContentCaluse & obj)
{
	this->__caluse__ = _StrStm_();
	this->__caluse__ << obj.__caluse__.str();

	this->__used_cls__ = obj.__used_cls__;
	return *this;
}

auto ContentCaluse::like(_String _key_, int _value_) -> ContentCaluse &
{
	return __like<int>(_key_, _value_);
}

auto ContentCaluse::like(_String _key_, bool _value_) -> ContentCaluse &
{
	return __like<bool>(_key_, _value_);
}

auto ContentCaluse::like(_String _key_, long _value_) -> ContentCaluse &
{
	return __like<long>(_key_, _value_);
}

auto ContentCaluse::like(_String _key_, char _value_) -> ContentCaluse &
{
	return __like<char>(_key_, _value_);
}

auto ContentCaluse::like(_String _key_, short _value_) -> ContentCaluse &
{
	return __like<short>(_key_, _value_);
}

auto ContentCaluse::like(_String _key_, float _value_) -> ContentCaluse &
{
	return __like<float>(_key_, _value_);
}

auto ContentCaluse::like(_String _key_, double _value_) -> ContentCaluse &
{
	return __like<double>(_key_, _value_);
}

auto ContentCaluse::like(_String _key_, char * _value_) -> ContentCaluse &
{
	_StrStm_ msg;
	msg << "\"" << _value_ << "\"";
	return __like<const char*>(_key_, msg.str().c_str());
}

auto ContentCaluse::like(_String _key_, _String _value_) -> ContentCaluse &
{

	_StrStm_ msg;
	msg << "\"" << _value_ << "\"";
	return __like<_String>(_key_, msg.str());
}

auto ContentCaluse::like(_String _key_, long long _value_) -> ContentCaluse &
{
	return __like<long long>(_key_, _value_);
}

auto ContentCaluse::like(_String _key_, long double _value_) -> ContentCaluse &
{
	return __like<long double>(_key_, _value_);
}

auto ContentCaluse::like(_String _key_, unsigned int _value_) -> ContentCaluse &
{
	return __like<unsigned int>(_key_, _value_);
}

auto ContentCaluse::like(_String _key_, unsigned short _value_) -> ContentCaluse &
{
	return __like<unsigned short>(_key_, _value_);
}

auto ContentCaluse::like(_String _key_, unsigned char _value_) -> ContentCaluse &
{
	return __like<unsigned char>(_key_, _value_);
}

auto ContentCaluse::like(_String _key_, unsigned long _value_) -> ContentCaluse &
{
	return __like<unsigned long>(_key_, _value_);
}

auto ContentCaluse::like(_String _key_, unsigned long long _value_) -> ContentCaluse &
{
	return __like<unsigned long long>(_key_, _value_);
}

ContentCaluse& ContentCaluse::equal(_String _key_, int _value_)
{	
	return __equal<int>(_key_, _value_);
}

auto ContentCaluse::equal(_String _key_, bool _value_) -> ContentCaluse &
{
	return __equal<bool>(_key_, _value_);
}

auto ContentCaluse::equal(_String _key_, long _value_) -> ContentCaluse &
{
	return __equal<long>(_key_, _value_);
}

auto ContentCaluse::equal(_String _key_, char _value_) -> ContentCaluse &
{
	return __equal<char>(_key_, _value_);
}

auto ContentCaluse::equal(_String _key_, short _value_) -> ContentCaluse &
{
	return __equal<short>(_key_, _value_);
}

auto ContentCaluse::equal(_String _key_, float _value_) -> ContentCaluse &
{
	return __equal<float>(_key_, _value_);
}

auto ContentCaluse::equal(_String _key_, double _value_) -> ContentCaluse &
{
	return __equal<double>(_key_, _value_);
}

auto ContentCaluse::equal(_String _key_, char * _value_) -> ContentCaluse &
{
	_StrStm_ msg;
	msg << "\"" << _value_ << "\"";
	return __equal<const char*>(_key_, msg.str().c_str());
}

auto ContentCaluse::equal(_String _key_, _String _value_) -> ContentCaluse &
{

	_StrStm_ msg;
	msg << "\"" << _value_ << "\"";
	return __equal<_String>(_key_, msg.str());
}

auto ContentCaluse::equal(_String _key_, long long _value_) -> ContentCaluse &
{
	return __equal<long long>(_key_, _value_);
}

auto ContentCaluse::equal(_String _key_, long double _value_) -> ContentCaluse &
{
	return __equal<long double>(_key_, _value_);
}

auto ContentCaluse::equal(_String _key_, unsigned int _value_) -> ContentCaluse &
{
	return __equal<unsigned int>(_key_, _value_);
}

auto ContentCaluse::equal(_String _key_, unsigned short _value_) -> ContentCaluse &
{
	return __equal<unsigned short>(_key_, _value_);
}

auto ContentCaluse::equal(_String _key_, unsigned char _value_) -> ContentCaluse &
{
	return __equal<unsigned char>(_key_, _value_);
}

auto ContentCaluse::equal(_String _key_, unsigned long _value_) -> ContentCaluse &
{
	return __equal<unsigned long>(_key_, _value_);
}

auto ContentCaluse::equal(_String _key_, unsigned long long _value_) -> ContentCaluse &
{
	return __equal<unsigned long long>(_key_, _value_);
}

auto ContentCaluse::neq(_String _key_, int _value_) -> ContentCaluse &
{
	return __neq<int>(_key_, _value_);
}

auto ContentCaluse::neq(_String _key_, bool _value_) -> ContentCaluse &
{
	return __neq<bool>(_key_, _value_);
}

auto ContentCaluse::neq(_String _key_, long _value_) -> ContentCaluse &
{
	return __neq<long>(_key_, _value_);
}

auto ContentCaluse::neq(_String _key_, char _value_) -> ContentCaluse &
{
	return __neq<char>(_key_, _value_);
}

auto ContentCaluse::neq(_String _key_, short _value_) -> ContentCaluse &
{
	return __neq<short>(_key_, _value_);
}

auto ContentCaluse::neq(_String _key_, float _value_) -> ContentCaluse &
{
	return __neq<float>(_key_, _value_);
}

auto ContentCaluse::neq(_String _key_, double _value_) -> ContentCaluse &
{
	return __neq<double>(_key_, _value_);
}

auto ContentCaluse::neq(_String _key_, char * _value_) -> ContentCaluse &
{
	_StrStm_ msg;
	msg << "\"" << _value_ << "\"";
	return __neq<const char*>(_key_, msg.str().c_str());
}

auto ContentCaluse::neq(_String _key_, _String _value_) -> ContentCaluse &
{
	_StrStm_ msg;
	msg << "\"" << _value_ << "\"";
	return __neq<_String>(_key_, msg.str());
}

auto ContentCaluse::neq(_String _key_, long long _value_) -> ContentCaluse &
{
	return __neq<long long>(_key_, _value_);
}

auto ContentCaluse::neq(_String _key_, long double _value_) -> ContentCaluse &
{
	return __neq<long double>(_key_, _value_);
}

auto ContentCaluse::neq(_String _key_, unsigned int _value_) -> ContentCaluse &
{
	return __neq<unsigned int>(_key_, _value_);
}

auto ContentCaluse::neq(_String _key_, unsigned short _value_) -> ContentCaluse &
{
	return __neq<unsigned short>(_key_, _value_);
}

auto ContentCaluse::neq(_String _key_, unsigned char _value_) -> ContentCaluse &
{
	return __neq<unsigned char>(_key_, _value_);
}

auto ContentCaluse::neq(_String _key_, unsigned long _value_) -> ContentCaluse &
{
	return __neq<unsigned long>(_key_, _value_);
}

auto ContentCaluse::neq(_String _key_, unsigned long long _value_) -> ContentCaluse &
{
	return __neq<unsigned long long>(_key_, _value_);
}

auto ContentCaluse::gtr(_String _key_, int _value_) -> ContentCaluse &
{
	return __gtr<int>(_key_, _value_);
}

auto ContentCaluse::gtr(_String _key_, long _value_) -> ContentCaluse &
{
	return __gtr<long>(_key_, _value_);
}

auto ContentCaluse::gtr(_String _key_, char _value_) -> ContentCaluse &
{
	return __gtr<char>(_key_, _value_);
}

auto ContentCaluse::gtr(_String _key_, short _value_) -> ContentCaluse &
{
	return __gtr<short>(_key_, _value_);
}

auto ContentCaluse::gtr(_String _key_, float _value_) -> ContentCaluse &
{
	return __gtr<float>(_key_, _value_);
}

auto ContentCaluse::gtr(_String _key_, double _value_) -> ContentCaluse &
{
	return __gtr<double>(_key_, _value_);
}

auto ContentCaluse::gtr(_String _key_, long long _value_) -> ContentCaluse &
{
	return __gtr<long long>(_key_, _value_);
}

auto ContentCaluse::gtr(_String _key_, long double _value_) -> ContentCaluse &
{
	return __gtr<long double>(_key_, _value_);
}

auto ContentCaluse::gtr(_String _key_, unsigned int _value_) -> ContentCaluse &
{
	return __gtr<unsigned int>(_key_, _value_);
}

auto ContentCaluse::gtr(_String _key_, unsigned short _value_) -> ContentCaluse &
{
	return __gtr<unsigned short>(_key_, _value_);
}

auto ContentCaluse::gtr(_String _key_, unsigned char _value_) -> ContentCaluse &
{
	return __gtr<unsigned char>(_key_, _value_);
}

auto ContentCaluse::gtr(_String _key_, unsigned long _value_) -> ContentCaluse &
{
	return __gtr<unsigned long>(_key_, _value_);
}

auto ContentCaluse::gtr(_String _key_, unsigned long long _value_) -> ContentCaluse &
{
	return __gtr<unsigned long long>(_key_, _value_);
}

auto ContentCaluse::geq(_String _key_, int _value_) -> ContentCaluse &
{
	return __geq<int>(_key_, _value_);
}

auto ContentCaluse::geq(_String _key_, long _value_) -> ContentCaluse &
{
	return __geq<long>(_key_, _value_);
}

auto ContentCaluse::geq(_String _key_, char _value_) -> ContentCaluse &
{
	return __geq<char>(_key_, _value_);
}

auto ContentCaluse::geq(_String _key_, short _value_) -> ContentCaluse &
{
	return __geq<short>(_key_, _value_);
}

auto ContentCaluse::geq(_String _key_, float _value_) -> ContentCaluse &
{
	return __geq<float>(_key_, _value_);
}

auto ContentCaluse::geq(_String _key_, double _value_) -> ContentCaluse &
{
	return __geq<double>(_key_, _value_);
}

auto ContentCaluse::geq(_String _key_, long long _value_) -> ContentCaluse &
{
	return __geq<long long>(_key_, _value_);
}

auto ContentCaluse::geq(_String _key_, long double _value_) -> ContentCaluse &
{
	return __geq<long double>(_key_, _value_);
}

auto ContentCaluse::geq(_String _key_, unsigned int _value_) -> ContentCaluse &
{
	return __geq<unsigned int>(_key_, _value_);
}

auto ContentCaluse::geq(_String _key_, unsigned short _value_) -> ContentCaluse &
{
	return __geq<unsigned short>(_key_, _value_);
}

auto ContentCaluse::geq(_String _key_, unsigned char _value_) -> ContentCaluse &
{
	return __geq<unsigned char>(_key_, _value_);
}

auto ContentCaluse::geq(_String _key_, unsigned long _value_) -> ContentCaluse &
{
	return __geq<unsigned long>(_key_, _value_);
}

auto ContentCaluse::geq(_String _key_, unsigned long long _value_) -> ContentCaluse &
{
	return __geq<unsigned long long>(_key_, _value_);
}

auto ContentCaluse::ltr(_String _key_, int _value_) -> ContentCaluse &
{
	return __ltr<int>(_key_, _value_);
}

auto ContentCaluse::ltr(_String _key_, long _value_) -> ContentCaluse &
{
	return __ltr<long>(_key_, _value_);
}

auto ContentCaluse::ltr(_String _key_, char _value_) -> ContentCaluse &
{
	return __ltr<char>(_key_, _value_);
}

auto ContentCaluse::ltr(_String _key_, short _value_) -> ContentCaluse &
{
	return __ltr<short>(_key_, _value_);
}

auto ContentCaluse::ltr(_String _key_, float _value_) -> ContentCaluse &
{
	return __ltr<float>(_key_, _value_);
}

auto ContentCaluse::ltr(_String _key_, double _value_) -> ContentCaluse &
{
	return __ltr<double>(_key_, _value_);
}

auto ContentCaluse::ltr(_String _key_, long long _value_) -> ContentCaluse &
{
	return __ltr<long long>(_key_, _value_);
}

auto ContentCaluse::ltr(_String _key_, long double _value_) -> ContentCaluse &
{
	return __ltr<long double>(_key_, _value_);
}

auto ContentCaluse::ltr(_String _key_, unsigned int _value_) -> ContentCaluse &
{
	return __ltr<unsigned int>(_key_, _value_);
}

auto ContentCaluse::ltr(_String _key_, unsigned short _value_) -> ContentCaluse &
{
	return __ltr<unsigned short>(_key_, _value_);
}

auto ContentCaluse::ltr(_String _key_, unsigned char _value_) -> ContentCaluse &
{
	return __ltr<unsigned char>(_key_, _value_);
}

auto ContentCaluse::ltr(_String _key_, unsigned long _value_) -> ContentCaluse &
{
	return __ltr<unsigned long>(_key_, _value_);
}

auto ContentCaluse::ltr(_String _key_, unsigned long long _value_) -> ContentCaluse &
{
	return __ltr<unsigned long long>(_key_, _value_);
}

auto ContentCaluse::leq(_String _key_, int _value_) -> ContentCaluse &
{
	return __leq<int>(_key_, _value_);
}

auto ContentCaluse::leq(_String _key_, long _value_) -> ContentCaluse &
{
	return __leq<long>(_key_, _value_);
}

auto ContentCaluse::leq(_String _key_, char _value_) -> ContentCaluse &
{
	return __leq<char>(_key_, _value_);
}

auto ContentCaluse::leq(_String _key_, short _value_) -> ContentCaluse &
{
	return __leq<short>(_key_, _value_);
}

auto ContentCaluse::leq(_String _key_, float _value_) -> ContentCaluse &
{
	return __leq<float>(_key_, _value_);
}

auto ContentCaluse::leq(_String _key_, double _value_) -> ContentCaluse &
{
	return __leq<double>(_key_, _value_);
}

auto ContentCaluse::leq(_String _key_, long long _value_) -> ContentCaluse &
{
	return __leq<long long>(_key_, _value_);
}

auto ContentCaluse::leq(_String _key_, long double _value_) -> ContentCaluse &
{
	return __leq<long double>(_key_, _value_);
}

auto ContentCaluse::leq(_String _key_, unsigned int _value_) -> ContentCaluse &
{
	return __leq<unsigned int>(_key_, _value_);
}

auto ContentCaluse::leq(_String _key_, unsigned short _value_) -> ContentCaluse &
{
	return __leq<unsigned short>(_key_, _value_);
}

auto ContentCaluse::leq(_String _key_, unsigned char _value_) -> ContentCaluse &
{
	return __leq<unsigned char>(_key_, _value_);
}

auto ContentCaluse::leq(_String _key_, unsigned long _value_) -> ContentCaluse &
{
	return __leq<unsigned long>(_key_, _value_);
}

auto ContentCaluse::leq(_String _key_, unsigned long long _value_) -> ContentCaluse &
{
	return __leq<unsigned long long>(_key_, _value_);
}

auto ContentCaluse::between(_String _key_, int _val1_, int _val2_) -> ContentCaluse &
{
	return __between<int>(_key_, _val1_, _val2_);
}

auto ContentCaluse::between(_String _key_, bool _val1_, bool _val2_) -> ContentCaluse &
{
	return __between<bool>(_key_, _val1_, _val2_);
}

auto ContentCaluse::between(_String _key_, long _val1_, long _val2_) -> ContentCaluse &
{
	return __between<long>(_key_, _val1_, _val2_);
}

auto ContentCaluse::between(_String _key_, char _val1_, char _val2_) -> ContentCaluse &
{
	return __between<char>(_key_, _val1_, _val2_);
}

auto ContentCaluse::between(_String _key_, short _val1_, short _val2_) -> ContentCaluse &
{
	return __between<short>(_key_, _val1_, _val2_);
}

auto ContentCaluse::between(_String _key_, float _val1_, float _val2_) -> ContentCaluse &
{
	return __between<float>(_key_, _val1_, _val2_);
}

auto ContentCaluse::between(_String _key_, double _val1_, double _val2_) -> ContentCaluse &
{
	return __between<double>(_key_, _val1_, _val2_);
}

auto ContentCaluse::between(_String _key_, long long _val1_, long long _val2_) -> ContentCaluse &
{
	return __between<long long>(_key_, _val1_, _val2_);
}

auto ContentCaluse::between(_String _key_, long double _val1_, long double _val2_) -> ContentCaluse &
{
	return __between<long double>(_key_, _val1_, _val2_);
}

auto ContentCaluse::between(_String _key_, unsigned int _val1_, unsigned int _val2_) -> ContentCaluse &
{
	return __between<unsigned int>(_key_, _val1_, _val2_);
}

auto ContentCaluse::between(_String _key_, unsigned short _val1_, unsigned short _val2_) -> ContentCaluse &
{
	return __between<unsigned short>(_key_, _val1_, _val2_);
}

auto ContentCaluse::between(_String _key_, unsigned char _val1_, unsigned char _val2_) -> ContentCaluse &
{
	return __between<unsigned char>(_key_, _val1_, _val2_);
}

auto ContentCaluse::between(_String _key_, unsigned long _val1_, unsigned long _val2_) -> ContentCaluse &
{
	return __between<unsigned long>(_key_, _val1_, _val2_);
}

auto ContentCaluse::between(_String _key_, unsigned long long _val1_, unsigned long long _val2_) -> ContentCaluse &
{
	return __between<unsigned long long>(_key_, _val1_, _val2_);
}

auto ContentCaluse::And() -> ContentCaluse &
{
	this->__caluse__ << " and ";

	return *this;
}

auto ContentCaluse::And(_String _cdt_) -> ContentCaluse &
{
	ContentCaluse __obj;
	__obj.__caluse__ << "(" << this->__caluse__.str() << ") and (" << _cdt_ << " )";

	this->__caluse__ = _StrStm_();

	this->__caluse__ << __obj.__caluse__.str();

	return *this;
}

auto ContentCaluse::And(_String _cdt1_, _String _cdt2_) -> ContentCaluse &
{
	this->__caluse__ << "(" << _cdt1_ << ") and (" << _cdt2_ << " )";

	return *this;
}

auto ContentCaluse::and_all() -> ContentCaluse &
{
	ContentCaluse __obj;
	__obj.__caluse__ << "(" << this->__caluse__.str() << ") and ";

	this->__caluse__ = _StrStm_();

	this->__caluse__ << __obj.__caluse__.str();

	return *this;
}

auto ContentCaluse::Or() -> ContentCaluse &
{
	__used_cls__++;
	this->__caluse__ << " or ";

	return *this;
}

auto ContentCaluse::Or(_String _cdt_) -> ContentCaluse &
{
	__used_cls__++;
	ContentCaluse __obj;
	__obj.__caluse__ << "(" << this->__caluse__.str() << ") or (" << _cdt_ << " )";

	this->__caluse__ = _StrStm_();

	this->__caluse__ << __obj.__caluse__.str();

	return *this;
}

auto ContentCaluse::Or(_String _cdt1_, _String _cdt2_) -> ContentCaluse &
{
	__used_cls__++;
	this->__caluse__ << "(" << _cdt1_ << ") or (" << _cdt2_ << " )";

	return *this;
}

auto ContentCaluse::in(_String _column_, _String _vals_) -> ContentCaluse &
{
	__used_cls__++;
	this->__caluse__ << _column_ << " in " << _vals_;

	return *this;
}

auto ContentCaluse::not_in(_String _column_, _String _vals_) -> ContentCaluse &
{
	__used_cls__++;
	this->__caluse__ << _column_ << " not in " << _vals_;

	return *this;
}

auto ContentCaluse::limited(const char * fmt, ...) -> _String
{
	__used_cls__++;
	_StrStm_ __mess;
	__mess << " (";

	va_list __args;
	va_start(__args, fmt);
	__mess = ParseVariables::var_param(fmt, __args);
	va_end(__args);
	__mess << ") ";

	return __mess.str();
}

auto ContentCaluse::str() -> _String
{
	return __caluse__.str();
}

auto ContentCaluse::get_count() -> int
{
	return __used_cls__;
}

auto ContentCaluse::or_all() -> ContentCaluse &
{
	ContentCaluse __obj;
	__obj.__caluse__ << "(" << this->__caluse__.str() << ") or ";

	this->__caluse__ = _StrStm_();

	this->__caluse__ << __obj.__caluse__.str();

	return *this;
}

auto ContentCaluse::__condition(_String _key_, _String _cdt, _String _value_) -> ContentCaluse &
{
	__used_cls__++;
	_String __str = __caluse__.str(); 
	if(__str.size() > 8)
	{
		_String __sub_str = __str.substr(__str.size() - 5);
		if( (0 == strstr(__sub_str.c_str(), "and")) && 
			(0 == strstr(__sub_str.c_str(), "or" )) )
		{
#ifdef _DEBUG
			RaiseException(-54, -1, 2, nullptr);
#endif // _DEBUG
			__caluse__ << "and";		
		}
	}	
	__caluse__ << _key_ << _cdt.c_str() << _value_.c_str();

	return *this;
}
