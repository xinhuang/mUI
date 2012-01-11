#ifndef __MUI_SYSTEM_FORMS_TEXTBOX_H__
#define __MUI_SYSTEM_FORMS_TEXTBOX_H__

#include "Control.h"

#include <System/System.h>
#include "FormBorderStyle.h"

namespace mUI{ namespace System{ namespace Drawing{
	class Rectangle;
}}}

namespace mUI{ namespace System{  namespace Forms{

class FORMS_ENTRY TextBox : public Control
{
	typedef Control base;

public:
	TextBox();
	virtual ~TextBox();

	virtual void set_AutoSize(bool value);
	void set_BorderStyle( FormBorderStyle::Enum borderStyle );
	FormBorderStyle::Enum get_BorderStyle() const;

protected:
	virtual void OnPaint( PaintEventArgs* e );
	virtual void OnKeyPress( KeyPressEventArgs* e );
	virtual void OnTextChanged( EventArgs* e );

	void AdjustSize();
	void DrawBorder( Graphics& g, Drawing::Rectangle& clipRectangle );

private:
	struct Data;
	Data *_d;
};

}}}

#endif
