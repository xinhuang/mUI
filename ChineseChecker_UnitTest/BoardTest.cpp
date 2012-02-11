#include <gtest/gtest.h>

#include <Presenter/Board.h>
#include <Presenter/Square.h>

using namespace std;

#include <mUI.h>
using namespace mUI::System::Drawing;

class BoardTest : public ::testing::Test
{
public:
	virtual void SetUp()
	{
		_sut = new Board();
	}
	virtual void TearDown()
	{
		delete _sut; _sut = nullptr;
	}

	void VerifySquareLocationsContain(const vector<Square*>& container, const Point& location) const
	{
		for (auto iter = container.begin(); iter != container.end(); ++iter)
			ASSERT_NE(nullptr, *iter);
		for (auto iter = container.begin(); iter != container.end(); ++iter)
			if (location == (*iter)->get_Location())
				return;
		ASSERT_TRUE(false);
	}

protected:
	Board* _sut;
};

TEST_F(BoardTest, Constructor_Typical)
{
	Board* board = new Board();
	ASSERT_TRUE(nullptr != board);
	delete board;
}

TEST_F(BoardTest, GetGoalSquares_Location_0_4)
{
	vector<Square*> goalSquares = _sut->GetGoalSquares(Point(0, 4));

	ASSERT_EQ(15, goalSquares.size());
	for (int x = 0; x < 5; ++x)
	{
		for (int y = x + 4; y < 9; ++y)
		{
			VerifySquareLocationsContain(goalSquares, Point(x, y));
		}
	}
}

TEST_F(BoardTest, GetGoalSquares_Location_4_0)
{
	vector<Square*> goalSquares = _sut->GetGoalSquares(Point(4, 0));

	ASSERT_EQ(15, goalSquares.size());
	for (int y = 0; y < 5; ++y)
	{
		for (int x = 4; x < 4 + y; ++x)
		{
			VerifySquareLocationsContain(goalSquares, Point(x, y));
		}
	}
}

TEST_F(BoardTest, GetGoalSquares_Location_12_4)
{
	vector<Square*> goalSquares = _sut->GetGoalSquares(Point(12, 4));

	ASSERT_EQ(15, goalSquares.size());
	VerifySquareLocationsContain(goalSquares, Point(8, 4));
	VerifySquareLocationsContain(goalSquares, Point(9, 4));
	VerifySquareLocationsContain(goalSquares, Point(10, 4));
	VerifySquareLocationsContain(goalSquares, Point(11, 4));
	VerifySquareLocationsContain(goalSquares, Point(12, 4));
	VerifySquareLocationsContain(goalSquares, Point(9, 5));
	VerifySquareLocationsContain(goalSquares, Point(10, 5));
	VerifySquareLocationsContain(goalSquares, Point(11, 5));
	VerifySquareLocationsContain(goalSquares, Point(12, 5));
	VerifySquareLocationsContain(goalSquares, Point(10, 6));
	VerifySquareLocationsContain(goalSquares, Point(11, 6));
	VerifySquareLocationsContain(goalSquares, Point(12, 6));
	VerifySquareLocationsContain(goalSquares, Point(11, 7));
	VerifySquareLocationsContain(goalSquares, Point(12, 7));
	VerifySquareLocationsContain(goalSquares, Point(12, 8));
}
