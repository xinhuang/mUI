#include <gtest/gtest.h>
#include <gmock/gmock.h>
using ::testing::Return;
using ::testing::_;

#include <Presenter/MGame.h>
#include <Presenter/MineField.h>
#include <Presenter/MineSquare.h>
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
	EXPECT_CALL(*_view, set_RemainMineTotal(arbitraryMineTotal));
	EXPECT_CALL(*_factoryMock, CreateSquares(_sut, _mineField, _))
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

TEST_F(MGameTest, Lose_Typical)
{
	_sut->set_MineFieldHeight(20);
	_sut->set_MineFieldWidth(20);
	_sut->set_MineTotal(20);
	EXPECT_CALL(*_view, CreateSquares(_))
		.WillOnce(Return(vector<ISquareView*>(20*20, NULL)));
	_sut->NewGame();

	_sut->Lose();

	ASSERT_TRUE(_sut->IsLost());
	for (int i = 0; i < _mineField->get_IndexMax(); ++i)
	{
		if (SquareState::Uncovered == _mineField->SquareAt(i)->get_State())
		{
			ISquare* square = _mineField->SquareAt(i);
			ASSERT_EQ(typeid(MineSquare), typeid(square));
			ASSERT_NE(SquareState::Boomed, square->get_State());
		}
	}
}

TEST_F(MGameTest, IncFlagCount_Typical)
{
	_mineField->set_MineTotal(100);
	EXPECT_CALL(*_view, set_RemainMineTotal(99));

	_sut->IncFlagCount();
}

TEST_F(MGameTest, DecFlagCount_Typical)
{
	_mineField->set_MineTotal(100);
	_sut->IncFlagCount();
	EXPECT_CALL(*_view, set_RemainMineTotal(100));

	_sut->DecFlagCount();
}
