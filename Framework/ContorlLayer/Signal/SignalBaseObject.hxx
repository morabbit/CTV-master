#pragma once
#ifndef __SIGNALBASEOBJECT_HXX
#define __SIGNALBASEOBJECT_HXX

#include <vector>
#include "..\Slot\Receiver.hxx"


template<typename ..._FunctionPtrType>
class SignalBaseObject
{
public:
	SignalBaseObject() {};
	~SignalBaseObject();

public:
	template<class __ObjectType>
	void Bind(__ObjectType* pObj, void(__ObjectType::*func)(_FunctionPtrType...));
	void operator()(_FunctionPtrType... param1);

private:
	std::vector<SlotBasicObject<_FunctionPtrType...>*> __m_slot_set__;
};

template<typename ..._FunctionPtrType>
inline SignalBaseObject<_FunctionPtrType...>::~SignalBaseObject()
{
	for(uint32_t i = 0 ; i < __m_slot_set__.size(); i++)
	{
		delete __m_slot_set__[i];
	}
}

template<typename ..._FunctionPtrType>
inline void
SignalBaseObject<_FunctionPtrType...>::operator()(_FunctionPtrType... __param)
{
	for(size_t i = 0; i < __m_slot_set__.size(); i++)
	{
		__m_slot_set__[i]->Excute(__param...);
	}
}

template<typename ..._FunctionPtrType>
template<class __ObjectType>
inline void
SignalBaseObject<_FunctionPtrType...>::Bind(
	__ObjectType * pObj, void(__ObjectType::* func)(_FunctionPtrType...))
{
	__m_slot_set__.push_back(
		new Receiver<__ObjectType, _FunctionPtrType...>(pObj, func)
	);
}

#endif // !__SIGNALBASEOBJECT_HXX


