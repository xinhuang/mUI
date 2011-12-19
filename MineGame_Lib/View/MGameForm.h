#ifndef __MAINFORM_H__
#define __MAINFORM_H__

#include <mUI.h>
using namespace mUI::System::Forms;

#include "View.h"

#include <vector>
using std::vector;

class SquareView;
class MGame;

class MGameForm : public Form, public View
{
public:
	MGameForm();

	virtual ~MGameForm();

	virtual vector<ISquareView*> CreateSquares(const Size& fieldSize);

	MGameForm& Center();
	MGameForm& Resize( const Size& fieldSize );

    virtual void set_RemainingMineTotal(int remainingTotal);

	void Uncover(ISquareView* squareView);
	void ToggleFlag( ISquareView* squareView );

protected:
	virtual	void OnSquareToggleFlag( SquareEventArgs* e );
	virtual void OnSquareUncovered( SquareEventArgs* e );
    virtual void OnFieldSizeChanged(FieldSizeChangedEventArgs* e);
    virtual void OnMineTotalChanged(MineTotalChangedEventArgs* e);
    virtual void OnNewGame(EventArgs* e);

	void InitializeComponents();
	void OnGameButtonClicked(void* sender, EventArgs* e);
private:
	struct Data;
	Data *_data;
};

#endif // __MAINFORM_H__
