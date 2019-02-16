#pragma once
#ifndef __UICOMMUNICATIONDATA_H
#define __UICOMMUNICATIONDATA_H
#include <iostream>

typedef 
struct DicomReadWriteParameter{
	///<@ is dir or file 
	bool           bDir;
	///<@ full path / dir
	std::string   strPath;	
	void*  ptr;

}DicomReadWrite;
#endif // !__UICOMMUNICATIONDATA_H
