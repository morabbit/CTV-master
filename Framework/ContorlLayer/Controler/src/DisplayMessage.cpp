#include "pch.h"
#include "TraceLogExporter.h"
#include "..\include\DisplayMessage.h"


DisplayMessage::DisplayMessage()
{
}

DisplayMessage::~DisplayMessage()
{
}

void 
DisplayMessage::DisplayWindowMessage(
	_In_ CMat image, _In_ CPCHAR message, _In_  INT index)
{
	_StrStm_ msg;
	msg << message << " " << index;
	cv::namedWindow(msg.str());
	cv::imshow(msg.str(), image);
}

void 
DisplayMessage::DisplayFilteredConcentricImage(
	_In_ CMat frame,_In_ SerialCycleInfo cycleInfos, _In_ INT index)
{
	CMat cooImage = frame.clone();
	CMat cycleImage(frame.size(), CV_8U, cv::Scalar(0, 0, 0));
	for(int j = 0; j < cycleInfos.size(); j++) 
	{
		PutTextToImageCycle<P2F, INT>(
			cooImage, cycleInfos[j].center, 
			j,  cycleInfos[j].radius);

		cv::circle(cooImage, cycleInfos[j].center,
				   cycleInfos[j].radius, 
				   cv::Scalar(255, 255, 0), 1, 8);

		cv::circle(cycleImage, cycleInfos[j].center,
				   cycleInfos[j].radius,
				   cv::Scalar(255, 255, 0), 1, 8);

		TraceLog << "  Cycle [" << std::left << std::setw(2) << j << "],\tcenter: ("
			<< std::setw(8) << cycleInfos[j].center.x << ", "
			<< std::setw(8) << cycleInfos[j].center.y << "), \tRadius = ["
			<< std::setw(8) << cycleInfos[j].radius << "]";
	}
	DisplayWindowMessage(cycleImage, "Black Point Mask", index);
	DisplayWindowMessage(cooImage, "Src Image Cycled", index);
}

