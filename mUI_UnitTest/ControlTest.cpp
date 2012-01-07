#include <gtest/gtest.h>

#include <mUI.h>
using namespace mUI::System::Forms;
using namespace mUI::System::Drawing;

#include "mocks/ControlMock.h"

void DistanceFromChildBottomToParemtBottom();

using ::testing::_;

class ControlTest : public testing::Test
{
public:
    void SetUp()
    {
        _form = new Form();
		_sut = new Control();
		_sut->set_Size(Size(100, 100));
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

	int DistanceFromChildBottomToParentBottom(Control& parent, Control& child)
	{
		return parent.get_Size().Height 
			- child.get_Location().Y 
			- child.get_Size().Height;
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

TEST_F(ControlTest, PerformLayout_WhenAnchorStyleNone)
{
	int arbitraryX = 30, arbitraryY = 30;
	_childCtrl->set_Location(Point(arbitraryX, arbitraryY));
	_childCtrl->set_Size(Size(10, 10));
	_childCtrl->Show();
	_sut->Controls.Add(*_childCtrl);

	_sut->set_Size(Size(200, 200));

	ASSERT_EQ(arbitraryX, _childCtrl->get_Location().X);
	ASSERT_EQ(arbitraryY, _childCtrl->get_Location().Y);
}

TEST_F(ControlTest, PerformLayout_WhenAnchorStyleTop)
{
	int arbitraryX = 30, arbitraryY = 30;
	_childCtrl->set_Location(Point(arbitraryX, arbitraryY));
	_childCtrl->set_Size(Size(10, 10));
	_childCtrl->Show();
	_sut->Controls.Add(*_childCtrl);

	_childCtrl->set_AnchorStyles(AnchorStyles::Top);
	_sut->set_Size(Size(200, 200));

	ASSERT_EQ(arbitraryX, _childCtrl->get_Location().X);
	ASSERT_EQ(arbitraryY, _childCtrl->get_Location().Y);
}

TEST_F(ControlTest, PerformLayout_WhenAnchorStyleBottom)
{
	int arbitraryX = 30, arbitraryY = 30;
	_childCtrl->set_Location(Point(arbitraryX, arbitraryY));
	_childCtrl->set_Size(Size(10, 10));
	_childCtrl->Show();
	_sut->Controls.Add(*_childCtrl);
	int expectDistance = DistanceFromChildBottomToParentBottom(*_sut, *_childCtrl);

	_childCtrl->set_AnchorStyles(AnchorStyles::Bottom);
	_sut->set_Size(Size(200, 200));

	ASSERT_EQ(arbitraryX, _childCtrl->get_Location().X);
	ASSERT_EQ(10, _childCtrl->get_Size().Width);
	ASSERT_EQ(10, _childCtrl->get_Size().Height);
	ASSERT_EQ(expectDistance, DistanceFromChildBottomToParentBottom(*_sut, *_childCtrl));
}
