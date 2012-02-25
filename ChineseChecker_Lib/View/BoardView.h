#ifndef __BOARDVIEW_H__
#define __BOARDVIEW_H__

#include <mUI.h>
using namespace mUI::System::Forms;

class BoardView : public Control
{
public:
    BoardView();
    virtual ~BoardView();

private:
    struct Data;
    Data* _d;
};

#endif // __BOARDVIEW_H__
