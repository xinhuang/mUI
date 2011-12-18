#ifndef __MINEFIELDCONTROL_H__
#define __MINEFIELDCONTROL_H__

#include <vector>
using std::vector;

#include <mUI.h>
using namespace mUI::System::Forms;

#include "ISquareView.h"

class MineFieldControl : public Control
{
public:
	MineFieldControl();
	virtual ~MineFieldControl();

	void CreateSquares(int squareTotal);
	vector<ISquareView*> get_SquareViews() const;

private:
	struct Data;
	Data* _d;
};

#endif // __MINEFIELDCONTROL_H__
