/*
	Copyright 2011 hello.patz@gmail.com

	Licensed under the Apache License, Version 2.0 (the "License");
	you may not use this file except in compliance with the License.
	You may obtain a copy of the License at

	http://www.apache.org/licenses/LICENSE-2.0

	Unless required by applicable law or agreed to in writing, software
	distributed under the License is distributed on an "AS IS" BASIS,
	WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
	See the License for the specific language governing permissions and
	limitations under the License.
*/

#ifndef __MUI_SYSTEM_STRING_H__
#define __MUI_SYSTEM_STRING_H__

#include "Export.h"
#include <string>
#include "BasicType.h"


#if defined(_MSC_VER)
#	pragma warning(push)
#	pragma warning(disable : 4251)
#endif

namespace mUI{ namespace System{ 

class SYSTEM_ENTRY String : public std::wstring
{
public:
	String() {}

	String(const wchar_t* value);
	String& operator=(const wchar_t* value);

	DEPRECATED String(const char* value);
	DEPRECATED String& operator=(const char* value);


	std::string ToANSI() const;

	static const String Empty;
};

}}

#if defined(_MSC_VER)
#	pragma warning(pop)
#endif

#endif // __MUI_SYSTEM_STRING_H__
