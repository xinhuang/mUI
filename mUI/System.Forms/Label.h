#ifndef __MUI_SYSTEM_FORMS_LABEL_H__
#define __MUI_SYSTEM_FORMS_LABEL_H__

#include "Control.h"

#include <System/System.h>

namespace mUI{ namespace System{  namespace Forms{

class FORMS_ENTRY Label : public Control
{
	typedef Control base;

public:
	Label();
	virtual ~Label();

	virtual void set_Text(const String& text);


protected:
	virtual void OnPaint( PaintEventArgs* e );

	void AdjustSize();

private:
	struct Data;
	Data* _d;
};

}}}

#endif
