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
    SquareControl(MGameForm* form, int x, int y);
    virtual ~SquareControl();

	static const Size& get_ImageSize();

	virtual void set_State(SquareViewState::Enum state);
	virtual const Point& get_Location() const { return _location; }

protected:
    virtual void OnPaint( PaintEventArgs* e );
	virtual void OnMouseClick( MouseEventArgs* e );

private:
    size_t _currentIndex;
    vector<Image*> _imageList;
	const Point _location;
	MGameForm* _gameForm;
    SquareViewState::Enum _imageIndex;
};

#endif // __SQUARECONTROL_H__
