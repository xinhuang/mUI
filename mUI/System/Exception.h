﻿/*
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

#ifndef __MUI_EXCEPTION_H__
#define __MUI_EXCEPTION_H__

#include "Export.h"
#include "String.h"

namespace mUI{ namespace System{

class SYSTEM_ENTRY Exception
{
public:
	Exception() {}
	Exception(const String& message)
		: Message(message)
	{
	}

	const String Message;
};

class SYSTEM_ENTRY SystemException : public Exception
{
	typedef Exception base;
public:
	SystemException() {}
	SystemException(const String& message)
		: base(message)
	{
	}
};

class SYSTEM_ENTRY ArgumentException : public SystemException
{
	typedef SystemException base;
public:
	ArgumentException() {}
	ArgumentException(const String& message)
		: base(message)
	{
	}
};

class SYSTEM_ENTRY NotImplementedException : public SystemException
{
	typedef SystemException base;
public:
	NotImplementedException() {}
	NotImplementedException(const String& message)
		: base(message)
	{
	}
};

}}

#endif	// __MUI_EXCEPTION_H__
