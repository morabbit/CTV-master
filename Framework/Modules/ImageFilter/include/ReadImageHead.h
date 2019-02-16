#pragma once
#ifndef __READIMAGEHEAD_H
#define __READIMAGEHEAD_H
#include "LoadImageHead.h"


class ReadImageHead
{
public:
	ReadImageHead();
	~ReadImageHead();

public :
	static DciomObject LoadImageHead(CPCHAR);
};

#endif // !__READIMAGEHEAD_H
