#include <gtest/gtest.h>

#include <mUI.h>
using namespace mUI::System::Forms;
using namespace mUI::System::Drawing;

#include "mocks/ControlMock.h"
using ::testing::_;

class ControlTest : public testing::Test
{
public:
    void SetUp()
    {
        _form = new Form();
        _sut = new Control();
        _form->Controls.Add(*_sut);
        _aribitraryLocation = Point(33, 47);
		_childMock = new ControlMock();
		_childCtrl = new Control();
    }

    void TearDown()
    {
		delete _childMock;
		delete _childCtrl;
        delete _form;
    }

protected:
    Control* _sut;
	Control* _childCtrl;
	ControlMock* _childMock;
    Form* _form;
    Point _aribitraryLocation;
};

TEST_F(ControlTest, Contructor_Typical)
{
    ASSERT_TRUE(NULL != _sut);
}

TEST_F(ControlTest, Controls_Remove_WhenNotExist)
{
	_sut->Controls.Remove(*_childCtrl);
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

TEST_F(ControlTest, OnLayout_Typical)
{
	EXPECT_CALL(*_childMock, OnLayout(_)).Times(0);
	_sut->Controls.Add(*_childMock);

	_sut->PerformLayout();

}

TEST_F(ControlTest, SuspendLayout_Typical)
{
	EXPECT_CALL(*_childMock, OnLayout(_)).Times(0);

	_sut->SuspendLayout();
	_sut->Controls.Add(*_childMock);
	_sut->PerformLayout();
}

TEST_F(ControlTest, ResumeLayout_WhenPerformLayoutTrue)
{
	EXPECT_CALL(*_childMock, OnLayout(_)).Times(0);
	_sut->SuspendLayout();
	_sut->Controls.Add(*_childMock);

	_sut->ResumeLayout(true);
}

TEST_F(ControlTest, ResumeLayout_WhenPerformLayoutFalse)
{
	EXPECT_CALL(*_childMock, OnLayout(_)).Times(0);
	_sut->SuspendLayout();
	_sut->Controls.Add(*_childMock);

	_sut->ResumeLayout(false);
}

TEST_F(ControlTest, ResumeLayout_WhenNoSuspendLayout)
{
	EXPECT_CALL(*_childMock, OnLayout(_)).Times(0);
	_sut->Controls.Add(*_childMock);

	_sut->ResumeLayout(true);
}

TEST_F(ControlTest, ResumeLayout_WhenSuspendTwiceButResumeOnce)
{
	EXPECT_CALL(*_childMock, OnLayout(_)).Times(0);
	_sut->SuspendLayout();
	_sut->SuspendLayout();
	_sut->Controls.Add(*_childMock);

	_sut->ResumeLayout(true);
}

TEST_F(ControlTest, ResumeLayout_WhenPerformLayoutTrueAndAfterPerformLayoutMultipleTimes)
{
	EXPECT_CALL(*_childMock, OnLayout(_)).Times(0);
	_sut->SuspendLayout();
	_sut->Controls.Add(*_childMock);

	_sut->PerformLayout();
	_sut->PerformLayout();
	_sut->PerformLayout();
	_sut->ResumeLayout(true);
}

TEST_F(ControlTest, ResumeLayout_WhenPerformLayoutFalseAndAfterPerformLayoutMultipleTimes)
{
	EXPECT_CALL(*_childMock, OnLayout(_)).Times(0);
	_sut->SuspendLayout();
	_sut->Controls.Add(*_childMock);

	_sut->PerformLayout();
	_sut->PerformLayout();
	_sut->PerformLayout();
	_sut->ResumeLayout(false);
}
