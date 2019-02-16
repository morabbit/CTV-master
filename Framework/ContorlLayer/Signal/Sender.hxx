#pragma once
#ifndef __SENDER_HXX
#define __SENDER_HXX

#include "SignalBaseObject.hxx"

template<class ...__ParameterType>
class Sender
{
public:
	Sender() {};
	~Sender() {};

	auto  Excute(__ParameterType... __parm) -> void;

private:
	SignalBaseObject<__ParameterType...> __signal__;
	 
};


template<class ...__ParameterType>
inline void Sender<__ParameterType...>::Excute(__ParameterType... __parm)
{
	__signal__(__parm...);
}

#endif // !__SENDER_HXX
