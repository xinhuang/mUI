#ifndef __CGAMEVIEW_H__
#define __CGAMEVIEW_H__

#include <mUI.h>
using namespace mUI::System::Forms;

class CGameView : public Form
{
public:
    CGameView();

    void InitializeComponents();

    virtual ~CGameView();

private:
    struct Data;
    Data* _d;
};

#endif // __CGAMEVIEW_H__
