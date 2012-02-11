#ifndef __MUI_EXTRA_CONTEXT_H__
#define __MUI_EXTRA_CONTEXT_H__

#include "Export.h"

#include <System/System.h>
using mUI::System::String;

#include <System.Drawing/Drawing.h>
using mUI::System::Drawing::Size;
using mUI::System::Drawing::Color;

namespace mUI{ namespace Extra{

class EXTRA_ENTRY HgeContext
{
public:
	const String& get_LogFile() const
	{
		return String::Empty;
	}

	bool get_Windowed() const
	{
		return true;
	}

	int get_ScreenBpp() const { return 32; }
	int get_Fps() const { return 60; }
	bool get_DontSuspent() const { return true; }
	bool get_HideMouse() const { return false; }
	const String& get_Title() const { return String::Empty; }
	const Size get_Size() const { return Size(400, 300); }
    bool get_ClearBack() const { return true; }
    Color get_BackColor() const { return Color::Black; }
};

}}

#endif // __MUI_EXTRA_CONTEXT_H__
