#pragma once
#ifndef __RECEIVER_H
#define __RECEIVER_H
#include "SlotBaseObject.hxx"


template<class _ObjectType, class ..._FunctionPtrType>
class Receiver : public SlotBasicObject<_FunctionPtrType...>
{
public:
	Receiver(_ObjectType* pObj, void(_ObjectType::*func)(_FunctionPtrType...));
	~Receiver();

	auto Excute(_FunctionPtrType... parm) -> void;
private:
	_ObjectType* __p_slot__ = nullptr;
	void (_ObjectType::*__p_func__)(_FunctionPtrType...);
};

template<class _ObjectType, class ..._FunctionPtrType>
inline Receiver<_ObjectType, _FunctionPtrType...>::Receiver(
	_ObjectType * pObj, void(_ObjectType::* func)(_FunctionPtrType...))
{
	__p_slot__ = pObj;
	__p_func__ = func;
}

template<class _ObjectType, class ..._FunctionPtrType>
inline Receiver<_ObjectType, _FunctionPtrType...>::~Receiver()
{
}

template<class _ObjectType, class ..._FunctionPtrType>
inline void 
Receiver<_ObjectType, _FunctionPtrType...>::Excute(_FunctionPtrType... parm)
{
	(__p_slot__->__p_func__)(parm...);
}


#endif // !__RECEIVER_H
