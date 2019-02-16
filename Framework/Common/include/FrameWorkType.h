#pragma once
#ifndef __FRAMEWORKTYPE_H
#define __FRAMEWORKTYPE_H

//#include "FrameworkLibrary.h"

#include <sstream>
#include <windows.h>
#include <vector>
#include <map>
#include <bcrypt.h>

using  CPCHAR = const char*;
using _String = std::string;
using PDOUBLE = double* ;

using _StrStm_  = std::stringstream;
using StrVector = std::vector<_String>;
using UintMap = std::map<UINT, UINT>;
using StrMap = std::map<_String, _String>;
using DataMap = std::map<UINT, StrVector>;
using ObjNameMap = std::map<UINT, _String>;

typedef std::vector<int>             SerialInt;
typedef std::vector<float>           SerialFloat;
typedef std::vector<double>          SerialDouble;
typedef std::vector<_String>         SerialString;

#endif // !__FRAMEWORKTYPE_H

