#include <Presenter/PieceGroup.h>

#include <gmock/gmock.h>
using ::testing::Return;

#include <mocks/BoardMock.h>

#include <Presenter/Piece.h>

class PieceGroupTest : public ::testing::Test
{
public:
	virtual void SetUp()
	{
		_boardMock = new BoardMock();
		_sut = new PieceGroup(Index, _boardMock, FromLocation, GoalLocation);
	}
	virtual void TearDown()
	{
		delete _sut; _sut = nullptr;
		delete _boardMock; _boardMock = nullptr;
	}

protected:
	static const int Index = 5;
	static const Point FromLocation;
	static const Point GoalLocation;
	PieceGroup* _sut;
	BoardMock* _boardMock;
};

const Point PieceGroupTest::FromLocation = Point(4, 0);
const Point PieceGroupTest::GoalLocation = Point(12, 16);

TEST_F(PieceGroupTest, Constructor_Typical)
{
	int groupId = 4;

	auto sut = new PieceGroup(groupId, nullptr, Point::Empty, Point::Empty);

	ASSERT_NE(nullptr, sut);
	ASSERT_EQ(groupId, sut->get_Id());
	auto pieces = sut->get_Pieces();
	ASSERT_EQ(PieceGroup::PieceMax, pieces.size());
	for (auto iter = pieces.begin(); iter != pieces.end(); ++iter)
	{
		ASSERT_NE(nullptr, *iter);
		ASSERT_EQ(sut->get_Id(), (*iter)->get_Id());
	}

	delete sut;
}

TEST_F(PieceGroupTest, get_StartSquares_Typical)
{
	EXPECT_CALL(*_boardMock, GetGoalSquares(FromLocation))
		.Times(1).WillOnce(Return(vector<Square*>()));

	auto startSquares = _sut->get_StartSquares();
}
