#ifndef __MUI_SYSTEM_FORMS_TEXTBOX_H__
#define __MUI_SYSTEM_FORMS_TEXTBOX_H__

#include "Control.h"

#include <System/System.h>
#include "FormBoarderStyle.h"

namespace mUI{ namespace System{  namespace Forms{

class FORMS_ENTRY TextBox : public Control
{
	typedef Control base;

public:
	TextBox();
	virtual ~TextBox();

	virtual void set_Text(const String& text);
	virtual void set_AutoSize(bool value);
	void set_BorderStyle( FormBorderStyle borderStyle );

protected:
	virtual void OnPaint( PaintEventArgs* e );
	virtual void OnKeyPress( KeyPressEventArgs* e );

	void AdjustSize();

private:
	struct Data;
	Data *_d;
};

}}}

#endif
