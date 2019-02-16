#pragma once
#ifndef __DISPLAYMESSAGE_H
#define __DISPLAYMESSAGE_H

#include "..\Modules\CalibrationPlate\include\CalibrationPlateCommon.hpp"


class DisplayMessage
{
public:
	DisplayMessage();
	~DisplayMessage();

	static
		void
		DisplayWindowMessage(
			_In_ CMat image,
			_In_ CPCHAR message, 
			_In_  INT index = 0
		);

	static
		void
		DisplayFilteredConcentricImage(
			_In_ CMat frame,
			_In_ SerialCycleInfo cycleInfos,
			_In_ INT index = 0
		);

	template<typename Center, typename IndexType>
	static
		void
		PutTextToImageCycle(_Out_ CMat& image, _In_ Center center,
							_In_ IndexType str, _In_opt_ FLOAT radius=8.0);
private:

};



template<typename Center, typename IndexType>
inline void 
DisplayMessage::PutTextToImageCycle(
	_Out_ CMat& image, _In_ Center center,
	_In_ IndexType str, _In_opt_ FLOAT radius)
{
	_StrStm_ msg;
	if(str == '\0')msg << "(" << center.x << ", " << center.y << ", " << radius << ")";
	else msg <</* "(" << center.x << ", " << center.y << ", " <<*/ str /*<< ", " << radius << ")"*/;
	CvFont font;
	cvInitFont(&font, CV_FONT_HERSHEY_SIMPLEX, 0.05, 0.05, 0, 1, CV_AA);///³õÊ¼»¯×ÖÌå
	putText(image, msg.str(), center, 0.6, 0.4, cv::Scalar(255, 255, 0));
}

using DM = DisplayMessage;

#endif // !__DISPLAYMESSAGE_H

