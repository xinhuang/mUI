#include "String.h"

#include "PAL/Pal.h"

namespace mUI{ namespace System{ 

const String String::Empty;

String::String( const wchar_t* value )
{
	if (value == NULL)
		return;

	for (const wchar_t* p = value; *p != 0; ++p)
	{
		*this += *p;
	}
}

String& String::operator=( const wchar_t* value )
{
	clear();

	if (value == NULL)
		return *this;

	for (const wchar_t* p = value; *p != 0; ++p)
	{
		*this += *p;
	}
	return *this;
}

String::String( const char* value )
{
	if (value == NULL)
		return;

	*this = value;
}

String& String::operator=( const char* value )
{
	clear();

	if (value == NULL)
		return *this;

	wchar_t* buffer = PAL::Utf8ToUtf16(value);
	*this = buffer;
	PAL::ReleaseBuffer(reinterpret_cast<void*>(buffer));

	return *this;
}

std::string String::ToANSI() const
{
	std::string ret;
	//for (const_iterator iter = begin(); iter != end(); ++iter)
	//{
	//	wchar_t c = *iter;
	//	if (c > 0)
	//	{
	//		ret += static_cast<char>(c);
	//	}
	//	else
	//	{
	//		ret += c >> 8;
	//		ret += static_cast<char>(c);
	//	}
	//}

	char* buffer = PAL::Utf16ToAnsi(this->c_str());
	ret = buffer;
	PAL::ReleaseBuffer(reinterpret_cast<void*>(buffer));

	return ret;
}

}}