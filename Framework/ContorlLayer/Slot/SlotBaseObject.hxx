#pragma once
#ifndef __BASICSLOTOBJECT_H
#define __BASICSLOTOBJECT_H

template<class ..._BasicType>
class SlotBasicObject
{
public:
	~SlotBasicObject() {};

public:
	virtual auto Excute(_BasicType... parm) -> void = 0 ;

private:

};

#endif // !__BASICSLOTOBJECT_H
