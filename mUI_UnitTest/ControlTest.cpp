#include <gtest/gtest.h>

#include <mUI.h>
using namespace mUI::System::Forms;
using namespace mUI::System::Drawing;

class ControlTest : public testing::Test
{
public:
    void SetUp()
    {
        _form = new Form();
        _sut = new Control();
        _form->Controls.Add(*_sut);
        _aribitraryLocation = Point(33, 47);
    }

    void TearDown()
    {
        delete _form;
    }

protected:
    Control* _sut;
    Form* _form;
    Point _aribitraryLocation;
};

TEST_F(ControlTest, Contructor_Typical)
{
    ASSERT_TRUE(NULL != _sut);
}

TEST_F(ControlTest, PointToScreen_WhenAtOriginPoint)
{
    _form->set_Location(_aribitraryLocation);
    _form->set_FormBorderStyle(FormBorderStyle::None);
    Point screenPt = _sut->PointToScreen(Point::Empty);

    ASSERT_EQ(_aribitraryLocation, screenPt);
}

TEST_F(ControlTest, PointToScreen_WhenNotAtOriginPoint)
{
    _sut->set_Location(_aribitraryLocation);
    _form->set_Location(_aribitraryLocation);
    _form->set_FormBorderStyle(FormBorderStyle::None);
    Point screenPt = _sut->PointToScreen(Point::Empty);

    ASSERT_EQ(_aribitraryLocation + _aribitraryLocation, screenPt);
}
