#ifndef __NUMBERLABEL_H__
#define __NUMBERLABEL_H__

#include <mUI.h>
using namespace mUI::System::Forms;

class NumberLabel : public Control
{
public:
	NumberLabel();

protected:
	void InitializeComponents();

	virtual void OnPaint( PaintEventArgs* e );

private:
	struct Data;
	Data* _d;
};

#endif // __NUMBERLABEL_H__
