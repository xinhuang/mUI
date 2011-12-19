#ifndef __MINEFIELDVIEW_H__
#define __MINEFIELDVIEW_H__

#include <vector>
using std::vector;

#include <mUI.h>
using namespace mUI::System::Forms;

#include "View.h"

class MineFieldView : public Control
{
public:
	MineFieldView();
	virtual ~MineFieldView();

	void CreateSquares(const Size& fieldSize);
	vector<ISquareView*> get_SquareViews() const;

	SquareEventHandler Uncover;
	SquareEventHandler ToggleFlag;

protected:
	virtual void OnUncover(SquareEventArgs* e);
	virtual void OnToggleFlag(SquareEventArgs* e);

	void OnSquareMouseClick(void* sender, MouseEventArgs* e);

	void Resize(const Size& fieldSize);

private:
	struct Data;
	Data* _d;
};

#endif // __MINEFIELDVIEW_H__
