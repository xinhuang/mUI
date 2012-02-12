#include <Presenter/PieceGroup.h>

#include <gmock/gmock.h>
using ::testing::Return;
using ::testing::_;

#include <mocks/BoardMock.h>
#include <mocks/SquareMock.h>
#include <mocks/PieceMock.h>

#include <Presenter/Piece.h>

class PieceGroupTest : public ::testing::Test
{
public:
	virtual void SetUp()
	{
		_boardMock = new BoardMock();
		_pieceMock = new PieceMock();
		_sut = new PieceGroup(Index, _boardMock, StartPoint, GoalPoint);
		_savedPieces = _sut->get_Pieces();
		_sut->set_Pieces(vector<Piece*>(PieceGroup::PieceMax, _pieceMock));
	}
	virtual void TearDown()
	{
		_sut->set_Pieces(_savedPieces);
		delete _sut; _sut = nullptr;
		delete _boardMock; _boardMock = nullptr;
		delete _pieceMock; _pieceMock = nullptr;
	}

protected:
	static const int Index = 5;
	static const Point StartPoint;
	static const Point GoalPoint;

	PieceGroup* _sut;
	BoardMock* _boardMock;
	PieceMock* _pieceMock;
	vector<Piece*> _savedPieces;
};

const Point PieceGroupTest::StartPoint = Point(4, 0);
const Point PieceGroupTest::GoalPoint = Point(12, 16);

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

TEST_F(PieceGroupTest, Reset_Typical)
{
	EXPECT_CALL(*_boardMock, GetGoalSquares(_sut->get_StartPoint()))
		.Times(1)
		.WillOnce(Return(vector<Square*>(PieceGroup::PieceMax, nullptr)));
	EXPECT_CALL(*_pieceMock, MoveTo(nullptr)).Times(PieceGroup::PieceMax);

	_sut->Reset();
}
