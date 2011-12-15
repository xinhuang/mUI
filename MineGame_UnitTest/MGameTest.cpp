#include <gtest/gtest.h>
#include <gmock/gmock.h>
using ::testing::Return;
#include <mUI.h>

#include <Presenter/MGame.h>
#include <Presenter/MineField.h>
#include <Presenter/ISquare.h>

#include <mocks/ViewMock.h>
#include <mocks/SquareViewMock.h>
#include <mocks/ISquareMock.h>
#include <mocks/SquareFactoryMock.h>

class MGameTest : public testing::Test
{
public:
	void SetUp()
	{
		_view = new ViewMock();
		_sut = new MGame(_view);
		_factoryMock = new SquareFactoryMock();

		_mineField = _sut->get_MineField();
		_oldFactory = _mineField->get_SquareFactory();
	}

	void TearDown()
	{
		_mineField->set_SquareFactory(_oldFactory);
		delete _sut;
        delete _view;
		delete _factoryMock;
	}

protected:
	vector<ISquare*> CreateSquareMocks(ISquareView* squareView, int squareTotal) 
	{
		vector<ISquare*> squares;
		for (int i = 0; i < squareTotal; ++i)
		{
			ISquareMock* squareMock = new ISquareMock();
			squares.push_back(squareMock);
			EXPECT_CALL(*squareMock, Bind(squareView)).Times(1);
		}
		return squares;
	}
	void ReplaceFactoryUsingMock() 
	{
		_mineField->set_SquareFactory(_factoryMock);
	}

protected:
	MGame* _sut;
	ViewMock* _view;
	SquareFactoryMock* _factoryMock;

	MineField* _mineField;
	SquareFactory* _oldFactory;
};

TEST_F(MGameTest, Constructor_Typical)
{
	ASSERT_TRUE(NULL != _sut);
}

TEST_F(MGameTest, NewGame_Typical)
{
	Size arbitrarySize(3, 2);
	int arbitraryMineTotal = 2;
	int squareTotal = arbitrarySize.Width * arbitrarySize.Height;
	_sut->set_MineFieldWidth(arbitrarySize.Width);
	_sut->set_MineFieldHeight(arbitrarySize.Height);
	_sut->set_MineTotal(arbitraryMineTotal);
	ReplaceFactoryUsingMock();
	SquareViewMock squareViewMock;
	vector<ISquare*> squares = CreateSquareMocks(&squareViewMock, squareTotal);
	EXPECT_CALL(*_factoryMock, CreateSquares(_sut, _mineField))
		.Times(1)
		.WillOnce(Return(squares));
	vector<ISquareView*> squareViews(squareTotal, &squareViewMock);
    EXPECT_CALL(*_view, CreateSquares(arbitrarySize))
		.Times(1)
		.WillOnce(Return(squareViews));

	_sut->NewGame();

	ASSERT_TRUE(_sut->get_MineField() != NULL);
	ASSERT_EQ(arbitrarySize, _sut->get_MineField()->get_Size());
	ASSERT_EQ(arbitraryMineTotal, _sut->get_MineField()->get_MineTotal());
}

TEST_F(MGameTest, Uncover_OnMineSquare)
{
	_sut->set_MineFieldWidth(1);
	_sut->set_MineFieldHeight(1);
	_sut->set_MineTotal(1);

}
