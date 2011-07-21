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

#ifndef __COLOR_H__
#define __COLOR_H__

#ifdef ARGB
#	undef ARGB
#endif // ARGB

#include "../Export.h"
#include "../System.h"

namespace mUI{ namespace System{  namespace Drawing{

class MUI_ENTRY Color
{
public:
	static const unsigned int Black = 0xFF000000;
	static const unsigned int White = 0xFFFFFFFF;
	static const unsigned int Silver = 0xFFC0C0C0;
	static const unsigned int Grey = 0xFF545454;
	static const unsigned int Red = 0xFFFF0000;


	Color() { FromARGB(Black); }

	Color(unsigned int value)
	{
		FromARGB(value);
	}

	Color(unsigned char A, unsigned char R, unsigned char G, unsigned char B)
	{
		FromARGB((A << 24) | (R << 16) | (G << 8) | B);
	}

	bool operator==(const Color& rhs) const
	{
		if (this == &rhs)
			return true;
		else if (get_ARGB() == rhs.get_ARGB())
			return true;
		else
			return false;
	}

	bool operator!= (const Color& rhs) const
	{
		return !(*this == rhs);
	}

	unsigned int get_ARGB() const
	{
		return (A << 24) | (R << 16) | (G << 8) | B;
	}

	void FromARGB(unsigned int value)
	{
		A = static_cast<unsigned char>(value >> 24);
		R = static_cast<unsigned char>(value >> 16);
		G = static_cast<unsigned char>(value >> 8);
		B = static_cast<unsigned char>(value);
	}

	union{
		argb_t ARGB;
		struct{
			unsigned char A, R, G, B;
		};
	};
};

}}}

#endif // __COLOR_H__