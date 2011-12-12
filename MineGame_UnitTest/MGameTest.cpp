#include <gtest/gtest.h>
#include <gmock/gmock.h>
using ::testing::Return;
#include <mUI.h>

#include <Presenter/MGame.h>
#include <Presenter/MineField.h>
#include <Presenter/ISquare.h>

#include <mocks/ViewMock.h>
#include <mocks/ISquareViewMock.h>
#include <mocks/ISquareMock.h>
#include <mocks/SquareFactoryMock.h>

class MGameTest : public testing::Test
{
public:
	void SetUp()
	{
		_view = new ViewMock();
		_game = new MGame(_view);
		_factoryMock = new SquareFactoryMock();

		_mineField = _game->get_MineField();
		_oldFactory = _mineField->get_SquareFactory();
	}

	void TearDown()
	{
		_mineField->set_SquareFactory(_oldFactory);
		delete _game;
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
	MGame* _game;
	ViewMock* _view;
	SquareFactoryMock* _factoryMock;

	MineField* _mineField;
	SquareFactory* _oldFactory;
};

TEST_F(MGameTest, Constructor_Typical)
{
	ASSERT_TRUE(NULL != _game);
}

TEST_F(MGameTest, NewGame_Typical)
{
	Size arbitrarySize(3, 2);
	int arbitraryMineTotal = 2;
	int squareTotal = arbitrarySize.Width * arbitrarySize.Height;
	_game->set_MineFieldWidth(arbitrarySize.Width);
	_game->set_MineFieldHeight(arbitrarySize.Height);
	_game->set_MineTotal(arbitraryMineTotal);
	ReplaceFactoryUsingMock();
	ISquareViewMock squareViewMock;
	vector<ISquare*> squares = CreateSquareMocks(&squareViewMock, squareTotal);
	EXPECT_CALL(*_factoryMock, CreateSquares(_game, _mineField))
		.Times(1)
		.WillOnce(Return(squares));
	vector<ISquareView*> squareViews(squareTotal, &squareViewMock);
    EXPECT_CALL(*_view, CreateSquares(arbitrarySize))
		.Times(1)
		.WillOnce(Return(squareViews));

	_game->NewGame();

	ASSERT_TRUE(_game->get_MineField() != NULL);
	ASSERT_EQ(arbitrarySize, _game->get_MineField()->get_Size());
	ASSERT_EQ(arbitraryMineTotal, _game->get_MineField()->get_MineTotal());
}

TEST_F(MGameTest, Uncover_OnMineSquare)
{
	_game->set_MineFieldWidth(1);
	_game->set_MineFieldHeight(1);
	_game->set_MineTotal(1);

}
