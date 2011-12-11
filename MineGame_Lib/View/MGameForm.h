#ifndef __MAINFORM_H__
#define __MAINFORM_H__

#include <mUI.h>
using namespace mUI::System::Forms;

#include "View.h"

#include <vector>
using std::vector;

class SquareControl;
class MGame;

class MGameForm : public Form, public View
{
public:
	MGameForm();
    virtual ~MGameForm();

    virtual void CreateSquares(const Size& size);

	MGameForm& Center();
	MGameForm& Resize( const Size& size );

	virtual void set_SquareState(const Point& location, SquareState::Enum state, IntPtr param);
    virtual void set_RemainingMineTotal(int remainingTotal);

	void Uncover(SquareControl* squareControl);

protected:
	virtual void OnPaint( PaintEventArgs* e );

    virtual void OnNewGame(EventArgs* e);
    virtual void OnFieldSizeChanged(FieldSizeChangedEventArgs* e);
    virtual void OnMineTotalChanged(MineTotalChangedEventArgs* e);
	virtual void OnSquareUncovered( SquareEventArgs* e );

    void DisposeSquares();
	void OnSquareControlClick(void* sender, MouseEventArgs* e);

private:
	vector<SquareControl*> _squareStates;
    MGame* _game;
};

#endif // __MAINFORM_H__
