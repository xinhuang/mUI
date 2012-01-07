#include <gtest/gtest.h>

#include <mUI.h>
using namespace mUI::System::Forms;
using namespace mUI::System::Drawing;

#include "mocks/ControlMock.h"

void DistanceFromChildRightToParentRight();

void AddChildCtrl();

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

	void AddChildCtrl(const Rectangle& childBounds)
	{
		_childCtrl->set_Location(childBounds.Location);
		_childCtrl->set_Size(childBounds.Size);
		_childCtrl->Show();
		_sut->Controls.Add(*_childCtrl);
	}

	int DistanceFromChildRightToParentRight(const Control& parent, const Control& child)
	{
		return parent.get_Size().Width 
			- child.get_Location().X 
			- child.get_Size().Width;
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
	Rectangle arbitraryBounds(30, 30, 10, 10);
	AddChildCtrl(arbitraryBounds);

	_sut->set_Size(Size(200, 200));

	ASSERT_EQ(arbitraryBounds.Location, _childCtrl->get_Location());
	ASSERT_EQ(arbitraryBounds.Size, _childCtrl->get_Size());
}

TEST_F(ControlTest, PerformLayout_WhenAnchorStyleTop)
{
	Rectangle arbitraryBounds(30, 30, 10, 10);
	AddChildCtrl(arbitraryBounds);

	_childCtrl->set_AnchorStyles(AnchorStyles::Top);
	_sut->set_Size(Size(200, 200));

	ASSERT_EQ(arbitraryBounds.Location, _childCtrl->get_Location());
	ASSERT_EQ(arbitraryBounds.Size, _childCtrl->get_Size());
}

TEST_F(ControlTest, PerformLayout_WhenAnchorStyleBottom)
{
	Rectangle arbitraryBounds(30, 30, 10, 10);
	AddChildCtrl(arbitraryBounds);

	int expectDistance = DistanceFromChildBottomToParentBottom(*_sut, *_childCtrl);

	_childCtrl->set_AnchorStyles(AnchorStyles::Bottom);
	_sut->set_Size(Size(200, 200));

	ASSERT_EQ(arbitraryBounds.Location.X, _childCtrl->get_Location().X);
	ASSERT_EQ(expectDistance, DistanceFromChildBottomToParentBottom(*_sut, *_childCtrl));
	ASSERT_EQ(arbitraryBounds.Size, _childCtrl->get_Size());
}

TEST_F(ControlTest, PerformLayout_WhenAnchorStyleLeft)
{
	Rectangle arbitraryBounds(30, 30, 10, 10);
	AddChildCtrl(arbitraryBounds);

	_childCtrl->set_AnchorStyles(AnchorStyles::Left);
	_sut->set_Size(Size(200, 200));

	ASSERT_EQ(arbitraryBounds.Location, _childCtrl->get_Location());
	ASSERT_EQ(arbitraryBounds.Size, _childCtrl->get_Size());
}

TEST_F(ControlTest, PerformLayout_WhenAnchorStyleRight)
{
	Rectangle arbitraryBounds(30, 30, 10, 10);
	AddChildCtrl(arbitraryBounds);
	int expectedDistance = DistanceFromChildRightToParentRight(*_sut, *_childCtrl);

	_childCtrl->set_AnchorStyles(AnchorStyles::Right);
	_sut->set_Size(Size(200, 200));

	ASSERT_EQ(expectedDistance, DistanceFromChildRightToParentRight(*_sut, *_childCtrl));
	ASSERT_EQ(arbitraryBounds.Location.Y, _childCtrl->get_Location().Y);
	ASSERT_EQ(arbitraryBounds.Size, _childCtrl->get_Size());
}

TEST_F(ControlTest, PerformLayout_WhenAnchorStyleTopBottom)
{
	Rectangle arbitraryBounds(10, 10, 80, 80);
	AddChildCtrl(arbitraryBounds);
	int newHeight = 200;
	Size expectedSize(arbitraryBounds.Size.Width, newHeight - arbitraryBounds.Location.Y 
		- (_sut->get_Height() - arbitraryBounds.Size.Height - arbitraryBounds.Location.Y));

	int expectDistance = DistanceFromChildBottomToParentBottom(*_sut, *_childCtrl);

	_childCtrl->set_AnchorStyles(AnchorStyles::TopBottom);
	_sut->set_Size(Size(333, newHeight));

	ASSERT_EQ(arbitraryBounds.Location.X, _childCtrl->get_Location().X);
	ASSERT_EQ(expectDistance, DistanceFromChildBottomToParentBottom(*_sut, *_childCtrl));
	ASSERT_EQ(expectedSize, _childCtrl->get_Size());
}

TEST_F(ControlTest, PerformLayout_WhenAnchorStyleLeftRight)
{
	Rectangle arbitraryBounds(10, 10, 80, 80);
	AddChildCtrl(arbitraryBounds);
	int newWidth = 200;
	Size expectedSize(newWidth - arbitraryBounds.Location.X
		- (_sut->get_Width() - arbitraryBounds.Size.Width - arbitraryBounds.Location.X),
		arbitraryBounds.Size.Height);

	int expectDistance = DistanceFromChildBottomToParentBottom(*_sut, *_childCtrl);

	_childCtrl->set_AnchorStyles(AnchorStyles::LeftRight);
	_sut->set_Size(Size(newWidth, 333));

	ASSERT_EQ(arbitraryBounds.Location.X, _childCtrl->get_Location().X);
	ASSERT_EQ(expectDistance, DistanceFromChildRightToParentRight(*_sut, *_childCtrl));
	ASSERT_EQ(expectedSize, _childCtrl->get_Size());
}
