#ifndef __SQUARECONTROL_H__
#define __SQUARECONTROL_H__

#include <mUI.h>
using namespace mUI::System;
using namespace mUI::System::Forms;
using namespace mUI::System::Drawing;

class SquareControl : public Control
{
public:
    SquareControl();
    virtual ~SquareControl();

protected:
    virtual void OnPaint( PaintEventArgs* e );

private:
    size_t _currentIndex;
    vector<Image*> _imageList;

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
