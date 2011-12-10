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
        Adjacent1,
        Adjacent2,
        Adjacent3,
        Adjacent4,
        Adjacent5,
        Adjacent6,
        Adjacent7,
        Adjacent8,
        Empty,
        Mine,
        Question,
        Wrong,
        Max
    };};
    ImageIndex::Enum _imageIndex;
};

#endif // __SQUARECONTROL_H__
