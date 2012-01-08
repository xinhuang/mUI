#include "String.h"

#include <Pal.h>

namespace mUI{ namespace System{ 

const String String::Empty;

String::String( const wchar_t* value )
{
	if (value == null)
		return;

	*this = value;
}

String& String::operator=( const wchar_t* value )
{
	clear();

	if (value == null)
		return *this;

	for (const wchar_t* p = value; *p != 0; ++p)
	{
		*this += *p;
	}
	return *this;
}

String::String( const char* value )
{
	if (value == null)
		return;

// warning C4996: 'mUI::System::String::String': was declared deprecated
#pragma warning(push)
#pragma warning(disable: 4996)
	*this = value;
#pragma warning(pop)
}

String::String( const std::string& value )
{
#pragma warning(push)
#pragma warning(disable: 4996)
	*this = value.c_str();
#pragma warning(pop)
}

String::String( const std::wstring& value )
{
	*this = value.c_str();
}

String& String::operator=( const char* value )
{
	clear();

	if (value == null)
		return *this;

	wchar_t* buffer = Pal::Utf8ToUtf16(value);
	*this = buffer;
	Pal::ReleaseBuffer(reinterpret_cast<void*>(buffer));

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

	char* buffer = Pal::Utf16ToAnsi(this->c_str());
	ret = buffer;
	Pal::ReleaseBuffer(reinterpret_cast<void*>(buffer));

	return ret;
}

}}