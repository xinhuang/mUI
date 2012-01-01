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

	void Initialize(const Size& fieldSize);

	vector<ISquareView*> get_SquareViews() const;

	SquareEventHandler Uncover;
	SquareEventHandler ToggleFlag;
	EventHandler<MouseEventArgs*> SquareMouseDown;
	EventHandler<MouseEventArgs*> SquareMouseUp;

protected:
	virtual void OnUncover(SquareEventArgs* e);
	virtual void OnToggleFlag(SquareEventArgs* e);
	virtual void OnSquareMouseDown(MouseEventArgs* e);
	virtual void OnSquareMouseUp(MouseEventArgs* e);

	void OnSquareMouseClick(void* sender, MouseEventArgs* e);
	void OnSquareMouseDown(void* sender, MouseEventArgs* e);
	void OnSquareMouseUp(void* sender, MouseEventArgs* e);

	void CreateSquares( const Size &fieldSize );

private:
	struct Data;
	Data* _d;
};

#endif // __MINEFIELDVIEW_H__
