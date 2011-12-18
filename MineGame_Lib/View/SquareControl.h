#ifndef __SQUARECONTROL_H__
#define __SQUARECONTROL_H__

#include <mUI.h>
using namespace mUI::System;
using namespace mUI::System::Forms;
using namespace mUI::System::Drawing;

#include "View.h"

class MGameForm;

class SquareControl : public Control, public ISquareView
{
public:
    SquareControl(int x, int y);
    virtual ~SquareControl();

	static const Size& get_ImageSize();

	virtual void set_State(SquareViewState::Enum state);
	virtual const Point& get_Coordinates() const { return _coordinates; }
	virtual void set_Coordinates(int x, int y);

protected:
    virtual void OnPaint( PaintEventArgs* e );
	virtual void OnMouseClick( MouseEventArgs* e );

private:
    size_t _currentIndex;
    vector<Image*> _imageList;
	Point _coordinates;
	MGameForm* _gameForm;
    SquareViewState::Enum _imageIndex;
};

#endif // __SQUARECONTROL_H__
