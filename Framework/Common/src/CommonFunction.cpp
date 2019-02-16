#include "pch.h"
#include "CommonFunction.h"


DOC::DOC()
{
}

DOC::~DOC()
{
}

_String 
DOC::do_strip(const _String& str,
			  const _String& chars, 
			  INT striptype)
{
	_String::size_type strlen = str.size();
	_String::size_type charslen = chars.size();
	_String::size_type i, j;

	if(0 == charslen)
	{
		i = 0;
		if(striptype != RIGHTSTRIP)
		{
			while(i < strlen &&::isspace(str[i]))
			{
				i++;
			}
		}
		j = strlen;
		if(striptype != LEFTSTRIP)
		{
			j--;
			while(j >= i && ::isspace(str[j]))
			{
				j--;
			}
			j++;
		}
	}
	else
	{
		CPCHAR sep = chars.c_str();
		i = 0;
		if(striptype != RIGHTSTRIP)
		{
			while(i < strlen && memchr(sep, str[i], charslen))
			{
				i++;
			}
		}
		j = strlen;
		if(striptype != LEFTSTRIP)
		{
			j--;
			while(j >= i && memchr(sep, str[j], charslen))
			{
				j--;
			}
			j++;
		}		
	}
	if(0 == i && j == strlen)
	{
		return str;
	}
	else
	{
		return str.substr(i, j - i);
	}
}

void DOC::deleteAllMark(_String & src, const _String & mark)
{
	size_t nSize = mark.size();
	while(1)
	{
		size_t pos = src.find(mark);
		if(pos == _String::npos)
		{
			return;
		}
		src.erase(pos, nSize);
	}
}

_String 
replace(
	_String & str, const _String& src_str,
	const _String & tar_str, UINT cout)
{
	UINT  time = 0;
	_String::size_type pos = 0;
	_String::size_type srclen = src_str.size();
	_String::size_type dstlen = tar_str.size();

	while((pos = str.find(src_str, pos)) != _String::npos)
	{
		if((cout != 0)&&(time == cout))
		{
			break;
		}
		time++;
		str.replace(pos, srclen, tar_str);
		pos += dstlen;
	}

	return str;
}

_String strip(_String& src, const _String & chars)
{
	DOC::deleteAllMark(src, chars);

	return src;
}

_String lrstrip(_String& src, const _String& chars)
{
	return DOC::do_strip(src, chars, StripType::BOTHSTRIP);
}

_String lstrip(_String & src, const _String & chars)
{
	return DOC::do_strip(src, chars, StripType::LEFTSTRIP);
}

_String rstrip(_String & src, const _String & chars)
{
	return DOC::do_strip(src, chars, StripType::RIGHTSTRIP);
}
