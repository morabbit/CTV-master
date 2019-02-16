#pragma once
#ifndef __VOLUMMATHCOMMONDEFINE_HPP
#define __VOLUMMATHCOMMONDEFINE_HPP
#include "FrameWorkType.h"
#include "CommonImageFilterCtl.hxx"
#include "MathGeometryLine.h"

typedef struct LineObject
{
public:
	LineObject()
	{
		id = -1;
		headId = -1;
		tailId = -1;
		__math__obj__ = nullptr;
	}

	~LineObject()
	{
		if(nullptr != __math__obj__)
		{
			delete __math__obj__;
		}
	}

	LineObject(const LineObject& obj)
	{
		*this = obj;
	}

	LineObject& operator=(const LineObject& obj)
	{
		this->id = obj.id;
		this->headId = obj.headId;
		this->tailId = obj.tailId;
		this->__math__obj__ = obj.__math__obj__;
	}

public:
	INT id;
	INT headId;
	INT tailId;
	MathematicalGeometry* __math__obj__;

}LineObj, *pLineObj;


typedef enum GeometryObjectType
{
	GeometryObjectTypeDefault      = 0     ,
	GeometryObjectTypeLine         = 1 << 0,
	GeometryObjectTypeHeadPoint    = 1 << 1,
	GeometryObjectTypetailPoint    = 1 << 2,
}GOT;

#define SetColorMacro(ColorType)  \
virtual void SetColor(ColorType color[3], INT line_id,\
                      GOT gotp=GOT::GeometryObjectTypeDefault)\
{\
    if (this->__lines__.size() == 0)\
	{\
		return;\
	}\
	pLineObj __obj = nullptr;\
	if(-1 == line_id)\
	{\
		__obj = this->__lines__.end()->second;\
	}\
	else\
	{\
		__obj = this->__lines__[line_id];\
	}\
	if(__obj == nullptr)\
	{\
		return;\
	}\
	if(gotp == GOT::GeometryObjectTypeDefault)\
	{\
		__obj->__math__obj__->SetColor(color, PaintType::PaintTypeLine);\
		__obj->__math__obj__->SetColor(color, PaintType::PaintTypeHeadPoint);\
		__obj->__math__obj__->SetColor(color, PaintType::PaintTypeTailPoint);\
	}\
	else\
	{\
		if(gotp & GOT::GeometryObjectTypeLine)\
		{\
			__obj->__math__obj__->SetColor(color, PaintType::PaintTypeLine);\
		}\
		if(gotp & GOT::GeometryObjectTypeHeadPoint)\
		{\
			__obj->__math__obj__->SetColor(color, PaintType::PaintTypeHeadPoint);\
		}\
		if(gotp & GOT::GeometryObjectTypetailPoint)\
		{\
			__obj->__math__obj__->SetColor(color, PaintType::PaintTypeTailPoint);\
		}\
	}\
}\
virtual void SetColor(ColorType r, ColorType g, ColorType b,\
                      INT line_id, GOT gotp=GOT::GeometryObjectTypeDefault)\
{\
    if (this->__lines__.size() == 0)\
	{\
		return;\
	}\
	pLineObj __obj = nullptr;\
	if(-1 == line_id)\
	{\
		__obj = this->__lines__.end()->second;\
	}\
	else\
	{\
		__obj = this->__lines__[line_id];\
	}\
	if(__obj == nullptr)\
	{\
		return;\
	}\
	if(gotp == GOT::GeometryObjectTypeDefault)\
	{\
		__obj->__math__obj__->SetColor(r, g, b, PaintType::PaintTypeLine);\
		__obj->__math__obj__->SetColor(r, g, b, PaintType::PaintTypeHeadPoint);\
		__obj->__math__obj__->SetColor(r, g, b, PaintType::PaintTypeTailPoint);\
	}\
	else\
	{\
		if(gotp & GOT::GeometryObjectTypeLine)\
		{\
			__obj->__math__obj__->SetColor(r, g, b, PaintType::PaintTypeLine);\
		}\
		if(gotp & GOT::GeometryObjectTypeHeadPoint)\
		{\
			__obj->__math__obj__->SetColor(r, g, b, PaintType::PaintTypeHeadPoint);\
		}\
		if(gotp & GOT::GeometryObjectTypetailPoint)\
		{\
			__obj->__math__obj__->SetColor(r, g, b, PaintType::PaintTypeTailPoint);\
		}\
	}\
}


#define GetColorMacro(ColorType)  \
void GetColor(ColorType color[3], INT line_id, GOT gotp=GOT::GeometryObjectTypeDefault)\
{\
    if (this->__lines__.size() == 0)\
	{\
		return;\
	}\
	pLineObj __obj = nullptr;\
	if(-1 == line_id)\
	{\
		__obj = __lines__.end()->second;\
	}\
	else\
	{\
		__obj = __lines__[line_id];\
	}\
	if(__obj == nullptr)\
	{\
		return;\
	}\
	if(gotp == GOT::GeometryObjectTypeDefault)\
	{\
		__obj->__math__obj__->SetColor(color, PaintType::PaintTypeLine);\
		__obj->__math__obj__->SetColor(color, PaintType::PaintTypeHeadPoint);\
		__obj->__math__obj__->SetColor(color, PaintType::PaintTypeTailPoint);\
	}\
	else\
	{\
		if(gotp & GOT::GeometryObjectTypeLine)\
		{\
			__obj->__math__obj__->SetColor(color, PaintType::PaintTypeLine);\
		}\
		if(gotp & GOT::GeometryObjectTypeHeadPoint)\
		{\
			__obj->__math__obj__->SetColor(color, PaintType::PaintTypeHeadPoint);\
		}\
		if(gotp & GOT::GeometryObjectTypetailPoint)\
		{\
			__obj->__math__obj__->SetColor(color, PaintType::PaintTypeTailPoint);\
		}\
	}\
}\
void GetColor(ColorType& r, ColorType& g, ColorType& b,\
			  INT line_id, GOT gotp=GOT::GeometryObjectTypeDefault)\
{\
    if (this->__lines__.size() == 0)\
	{\
		return;\
	}\
	pLineObj __obj = nullptr;\
	if(-1 == line_id)\
	{\
		__obj = __lines__.end()->second;\
	}\
	else\
	{\
		__obj = __lines__[line_id];\
	}\
	if(__obj == nullptr)\
	{\
		return;\
	}\
	if(gotp == GOT::GeometryObjectTypeDefault)\
	{\
		__obj->__math__obj__->SetColor(r, g, b, PaintType::PaintTypeLine);\
		__obj->__math__obj__->SetColor(r, g, b, PaintType::PaintTypeHeadPoint);\
		__obj->__math__obj__->SetColor(r, g, b, PaintType::PaintTypeTailPoint);\
	}\
	else\
	{\
		if(gotp & GOT::GeometryObjectTypeLine)\
		{\
			__obj->__math__obj__->SetColor(r, g, b, PaintType::PaintTypeLine);\
		}\
		if(gotp & GOT::GeometryObjectTypeHeadPoint)\
		{\
			__obj->__math__obj__->SetColor(r, g, b, PaintType::PaintTypeHeadPoint);\
		}\
		if(gotp & GOT::GeometryObjectTypetailPoint)\
		{\
			__obj->__math__obj__->SetColor(r, g, b, PaintType::PaintTypeTailPoint);\
		}\
	}\
}


#endif // !__VOLUMMATHCOMMONDEFINE_HPP
