#include <Presenter/CGame.h>
#include <gtest/gtest.h>

class CGameTest : public ::testing::Test
{
public:
};

TEST_F(CGameTest, Constructor_Typical)
{
	CGame* sut = new CGame();
	ASSERT_NE(nullptr, sut);
	ASSERT_NE(nullptr, sut->get_Board());
	delete sut;
}