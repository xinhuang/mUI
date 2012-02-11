#include <Presenter/CGame.h>
#include <gtest/gtest.h>

#include <Presenter/Player.h>

class TestableCGame : public CGame
{
public:
	using CGame::get_CurrentPlayerIndex;
	using CGame::TakeTurn;
};

class CGameTest : public ::testing::Test
{
public:
	virtual void SetUp()
	{
		_sut = (TestableCGame*)new CGame();
	}
	virtual void TearDown()
	{
		delete _sut;
	}

protected:
	TestableCGame* _sut;
};

TEST_F(CGameTest, Constructor_Typical)
{
	CGame* sut = new CGame();

	ASSERT_NE(nullptr, sut);
	ASSERT_NE(nullptr, sut->get_Board());

	delete sut;
}

TEST_F(CGameTest, NewGame_Typical)
{
	_sut->set_PlayerTotal(2);
    _sut->set_PlayerColor(0, Color::Black);
    _sut->set_PlayerColor(1, Color::White);

	_sut->NewGame();

    Player* p0 = _sut->PlayerAt(0);
    Player* p1 = _sut->PlayerAt(1);
	ASSERT_NE(nullptr, p0);
	ASSERT_NE(nullptr, p1);
    ASSERT_TRUE(p0->Owns(Color::Black));
    ASSERT_FALSE(p0->Owns(Color::White));
}

TEST_F(CGameTest, TakeTurn_Typical)
{
	_sut->set_PlayerTotal(2);
	_sut->NewGame();

	_sut->TakeTurn(0);

	ASSERT_EQ(0, _sut->get_CurrentPlayerIndex());
	ASSERT_EQ(_sut->PlayerAt(0), _sut->get_CurrentPlayer());
}
