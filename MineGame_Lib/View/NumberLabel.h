#ifndef __NUMBERLABEL_H__
#define __NUMBERLABEL_H__

#include <mUI.h>
using namespace mUI::System::Forms;

class NumberLabel : public Control
{
public:
	NumberLabel();
	virtual ~NumberLabel();

	void set_Value( int value );

protected:
	void InitializeComponents();

private:
	struct Data;
	Data* _d;
};

#endif // __NUMBERLABEL_H__
