#ifndef __MAINFORM_H__
#define __MAINFORM_H__

#include <mUI.h>
using namespace mUI::System::Forms;

#include "View.h"

#include <vector>
using std::vector;

class SquareView;
class MGame;

class MGameView : public Form, public View
{
public:
	MGameView();

	virtual ~MGameView();

	virtual vector<ISquareView*> CreateSquares(const Size& fieldSize);

	MGameView& Center();
	MGameView& Resize( const Size& fieldSize );

    virtual void set_RemainMineTotal(int remainingTotal);
	virtual void set_Lost(bool value);

protected:
	virtual void OnSquareToggleFlag( void* sender, SquareEventArgs* e );
	virtual void OnSquareUncovered( void* sender, SquareEventArgs* e );
    virtual void OnFieldSizeChanged(FieldSizeChangedEventArgs* e);
    virtual void OnMineTotalChanged(MineTotalChangedEventArgs* e);
    virtual void OnNewGame(EventArgs* e);

	void InitializeComponents();

	void OnGameButtonClicked(void* sender, EventArgs* e);
	void OnSquareMouseDown(void* sender, MouseEventArgs* e);
	void OnSquareMouseUp(void* sender, MouseEventArgs* e);

private:
	struct Data;
	Data *_data;
};

#endif // __MAINFORM_H__
