#ifndef __SQUARECONTROL_H__
#define __SQUARECONTROL_H__

#include <mUI.h>
using namespace mUI::System;
using namespace mUI::System::Forms;
using namespace mUI::System::Drawing;

#include "View.h"

class SquareControl : public Control, public ISquareView
{
public:
    SquareControl(int x, int y);
    virtual ~SquareControl();

	static const Size& get_ImageSize();

	virtual void set_State(SquareState::Enum state, IntPtr param) {}
	virtual const Point& get_Location() const { return _location; }

protected:
    virtual void OnPaint( PaintEventArgs* e );

private:
    size_t _currentIndex;
    vector<Image*> _imageList;
	const Point _location;

    struct ImageIndex{ enum Enum
    {
        Boom,
        Coverred,
        Flagged,
        Number1,
        Number2,
        Number3,
        Number4,
        Number5,
        Number6,
        Number7,
        Number8,
        Empty,
        Mine,
        Question,
        Wrong,
        Max
    };};
    ImageIndex::Enum _imageIndex;
};

#endif // __SQUARECONTROL_H__
