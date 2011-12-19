#ifndef __SQUAREVIEW_H__
#define __SQUAREVIEW_H__

#include <mUI.h>
using namespace mUI::System;
using namespace mUI::System::Forms;
using namespace mUI::System::Drawing;

#include "View.h"

class MGameView;

class SquareView : public Control, public ISquareView
{
public:
    SquareView();
    virtual ~SquareView();

	static const Size& get_ImageSize();

	virtual void set_State(SquareViewState::Enum state);
	virtual const Point& get_Coordinates() const { return _coordinates; }
	virtual void set_Coordinates(const Point& coord);

protected:
    virtual void OnPaint( PaintEventArgs* e );
	virtual void OnMouseClick( MouseEventArgs* e );

private:
    size_t _currentIndex;
    vector<Image*> _imageList;
	Point _coordinates;
    SquareViewState::Enum _imageIndex;
};

#endif // __SQUAREVIEW_H__
