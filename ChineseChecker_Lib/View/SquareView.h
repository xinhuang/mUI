#ifndef __SQUAREVIEW_H__
#define __SQUAREVIEW_H__

#include <mUI.h>
using namespace mUI::System::Forms;

class SquareView : public Control
{
public:
    SquareView();

    void InitializeComponents();

protected:
    virtual void OnPaint( PaintEventArgs* e ) override;

private:
    static const int Width = 30;
    static const int Height = 30;
};

#endif // __SQUAREVIEW_H__
